{-# language RecordWildCards, NamedFieldPuns #-}
{-# language QuasiQuotes, OverloadedStrings, LambdaCase #-}
module Main (main) where

import Tests (tests)

import Data.Functor ((<&>))
import Data.Text (Text)
import qualified Data.Text as T
import qualified Data.Text.IO as TIO
import Data.String.Interpolate (__i)
import Flow

import Test.Tasty
import Test.Tasty.Runners
import Test.Tasty.Providers
import Test.Tasty.QuickCheck
import Test.Tasty.Options

main :: IO ()
main = markingMain 2000 42 tests

markingMain :: Int -> Int -> TestTree -> IO ()
markingMain numTests seed testTree = do
  let testTree' = testTree
                  |> localOption (QuickCheckTests numTests)
                  |> localOption (QuickCheckReplay (Just seed))

  statsMaybe <- makeResultTree testTree' 
                  <&> fmap calcTasksStats

  case statsMaybe of
    Nothing -> putStrLn "Couldn't create stats!"
    Just stats -> TIO.writeFile "fb.md" (genFeedbackGrouped stats)

data ResultTree
  = Test TestName Result
  | Group TestName [ResultTree]
  deriving (Show)

foldResultTree :: (TestName -> Result -> b)
               -> (TestName -> [b] -> b)
               -> ResultTree
               -> b
foldResultTree test group = go
  where
    go = \case
      Test testName result -> test testName result
      Group testName resultTrees -> group testName (map go resultTrees)

mapTasks :: (TestName -> [ResultTree] -> b) -> ResultTree -> [b]
mapTasks f = \case
  Group _cwName tasks -> map (\case Group taskName results -> f taskName results
                                    _ -> error "Expected only Groups on the first level down of the results tree!")
                             tasks
  _ -> error "Expected single Group at top level of the results tree!"

foldTaskResults :: (TestName -> Result -> b)
                -> (TestName -> [b] -> b)
                -> ([b] -> b)
                -> [ResultTree]
                -> b
foldTaskResults test group mergeTaskOut
  = map (foldResultTree test group)
 .> mergeTaskOut

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

data TasksStats = MkTasksStats
  { totalTasks :: Int
  , completedTasks :: Int
  , failedTasks :: [(TestName, [TestName])]
  , mark :: Int -- Between 0 and 100
  } deriving (Show)

calcTasksStats :: ResultTree -> TasksStats
calcTasksStats resultTree = MkTasksStats{..}
  where
    totalTasks
      = resultTree
        |> mapTasks (\_ _ -> 1)
        |> sum

    completedTasks
      = resultTree
        |> mapTasks (\_ results -> taskSuccessful results |> fromEnum)
        |> sum

    failedTasks
      = resultTree
        |> mapTasks (\taskName results -> (taskName, failedSingleTests results))
        |> filter (snd .> (not . null))

    mark = ceiling ((fromIntegral completedTasks / fromIntegral totalTasks) * 100)

taskSuccessful :: [ResultTree] -> Bool
taskSuccessful
  = foldTaskResults
      (\_ -> resultSuccessful)
      (\_ -> and) -- all tests must succeed to pass task
      and

failedSingleTests :: [ResultTree] -> [TestName]
failedSingleTests
  = foldTaskResults
      (\testName result -> if resultFailed result then [testName] else [])
      (\_groupName failedTestss -> concat failedTestss)
      concat

resultFailed :: Result -> Bool
resultFailed = not . resultSuccessful

type Markdown = Text

genFeedbackGrouped :: TasksStats -> Markdown
genFeedbackGrouped MkTasksStats{..} = [__i|
  #{markComment}

  $+#{mark}
  #{failedTestInfo}
|]
  where
    markComment :: Markdown
    markComment
      | completedTasks == totalTasks = "You passed all the tests. Well done!"
      | otherwise = [__i|You completed #{completedTasks} out of #{totalTasks} tasks successfully.|]

    failedTestInfo :: Markdown
    failedTestInfo
      | null failedTasks = ""
      | otherwise = forEach failedTasks renderFailedGroup

    forEach xs f = T.unlines $ map f xs

    renderFailedGroup :: (TestName, [TestName]) -> Markdown
    renderFailedGroup (name, testNames) = [__i|
      - #{name} fails the following tests: 
      #{forEach testNames renderTestName}
    |]

    renderTestName :: TestName -> Markdown
    renderTestName name = "  - " <> T.pack name
