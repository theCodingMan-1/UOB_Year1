{-# language RecordWildCards, NamedFieldPuns, QuasiQuotes, OverloadedStrings #-}
module Main (main) where

import Tests

import Test.Tasty
import Data.Text (Text)
import qualified Data.Text as T
import qualified Data.Text.IO as TIO
import Data.String.Interpolate (__i)
import Test.Tasty.Runners
import Test.Tasty.Providers
import Data.Functor ((<&>))
import Flow
import Test.Tasty.QuickCheck
import Test.Tasty.Options

main = markingMain 2000 42 tests

markingMain :: Int -> Int -> TestTree -> IO ()
markingMain numTests seed testTree = do
  let testTree' = testTree
                  |> localOption (QuickCheckTests numTests)
                  |> localOption (QuickCheckReplay (Just seed))

  statsMaybe <- makeResultTree testTree' 
                  <&> fmap calcGroupedStats
  case statsMaybe of
    Nothing -> putStrLn "Couldn't create stats!"
    Just stats -> TIO.writeFile "fb.md" (genFeedbackGrouped stats)

data Foo = MkFoo
  { groupMap :: [(TestName, [(TestName, Result)])]
  , yetToBeGrouped :: [(TestName, Result)]
  }

data ResultTree
  = Test TestName Result
  | Group TestName [ResultTree]
  deriving (Show)

foldResultTree :: (TestName -> Result -> b)
               -> (TestName -> [(TestName, Result)] -> b)
               -> (TestName -> [b] -> b)
               -> ResultTree
               -> b
foldResultTree testFunc height1GroupFunc groupFunc rt = case rt of
  Test testName result -> testFunc testName result
  Group testName resultTrees -> if all isTest resultTrees
    then height1GroupFunc testName (map (\(Test tn r) -> (tn, r)) resultTrees)
    else groupFunc testName (map (foldResultTree testFunc height1GroupFunc groupFunc) resultTrees) 

isTest :: ResultTree -> Bool
isTest (Test _ _) = True
isTest _ = False

makeResultTree :: TestTree -> IO (Maybe ResultTree)
makeResultTree
  = foldTestTree alg mempty
  .> fmap headMaybe
  where
    alg :: TreeFold (IO [ResultTree])
    alg = trivialFold{ foldSingle, foldGroup }

    foldSingle :: IsTest t => OptionSet -> TestName -> t -> IO [ResultTree]
    foldSingle optSet name test = do
      result <- run optSet test (const $ pure ())
      pure [Test name result]

    foldGroup :: OptionSet -> TestName -> [IO [ResultTree]] -> IO [ResultTree]
    foldGroup optSet name acc = do
      trees <- mconcat acc
      pure [Group name trees]

headMaybe :: [a] -> Maybe a
headMaybe [] = Nothing
headMaybe (x:xs) = Just x

data Stats = MkStats
  { totalTests :: Int
  , totalPassed :: Int
  , totalFailed :: Int
  , failedTests :: [(TestName, Result)]
  , mark :: Int -- Between 0 and 100
  } deriving (Show)

calcStats :: [(TestName, Result)] -> Stats
calcStats results = MkStats{..}
  where
    totalTests = length results
    totalPassed = count (resultSuccessful . snd) results
    failedTests = filter (not . resultSuccessful . snd) results
    totalFailed = length failedTests
    mark = ceiling ((fromIntegral totalPassed / fromIntegral totalTests) * 100)

    senseCheck = totalTests == totalPassed + totalFailed

count :: (a -> Bool) -> [a] -> Int
count p xs = length $ filter p xs

data GroupedStats = MkGroupedStats
  { totalTestGroups :: Int
  , completeGroups :: Int
  , failedGroups :: [(TestName, [TestName])]
  , markG :: Int -- Between 0 and 100
  } deriving (Show)

calcGroupedStats :: ResultTree -> GroupedStats
calcGroupedStats resultTree = MkGroupedStats{..}
  where
    totalTestGroups = countHeight1Groups (const 1) resultTree

    completeGroups
      = countHeight1Groups
          (all (snd .> resultSuccessful) .> fromEnum)
          resultTree

    failedGroups = foldResultTree
      (\_ _ -> [])
      (\testName testResults
          -> let failedSingleTests = filter (snd .> resultSuccessful .> not) testResults
             in [ (testName, map fst failedSingleTests)
                | not (null failedSingleTests) ]
      )
      (const concat)
      resultTree

    markG = ceiling ((fromIntegral completeGroups / fromIntegral totalTestGroups) * 100)

countHeight1Groups :: ([(TestName, Result)] -> Int) -> ResultTree -> Int
countHeight1Groups f
  = foldResultTree
      (\_ result -> 0)
      (const f)
      (\_ accs -> sum accs)

type Markdown = Text

genFeedback :: Stats -> Markdown
genFeedback MkStats{..} = [__i|
  #{markComment}

  $+#{mark}
  #{failedTestInfo}
|]
  where
    markComment :: Markdown
    markComment
      | totalPassed == totalTests = "You passed all the tests. Well done!"
      | otherwise = [__i|Your code passes #{totalPassed} out of #{totalTests} tests.|]

    failedTestInfo :: Markdown
    failedTestInfo
      | null failedTests = ""
      | otherwise = [__i|
        The following tests failed:
        #{forEach failedTests renderFailedTest}
      |]
    
    forEach xs f = T.unlines $ map f xs

    renderFailedTest :: (TestName, Result) -> Markdown
    renderFailedTest (name, _) = "- " <> T.pack name

genFeedbackGrouped :: GroupedStats -> Markdown
genFeedbackGrouped MkGroupedStats{..} = [__i|
  #{markComment}

  $+#{markG}
  #{failedTestInfo}
|]
  where
    markComment :: Markdown
    markComment
      | completeGroups == totalTestGroups = "You passed all the tests. Well done!"
      | otherwise = [__i|You completed #{completeGroups} out of #{totalTestGroups} tasks successfully.|]

    failedTestInfo :: Markdown
    failedTestInfo
      | null failedGroups = ""
      | otherwise = forEach failedGroups renderFailedGroup

    forEach xs f = T.unlines $ map f xs

    renderFailedGroup :: (TestName, [TestName]) -> Markdown
    renderFailedGroup (name, testNames) = [__i|
      - #{name} fails the following tests: 
      #{forEach testNames renderTestName}
    |]

    renderTestName :: TestName -> Markdown
    renderTestName name = "  - " <> T.pack name
