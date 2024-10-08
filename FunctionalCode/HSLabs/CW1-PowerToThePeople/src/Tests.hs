module Tests where

import Power
    ( comparePower1,
      comparePower2,
      comparisonList,
      power1,
      power2,
      stepsPower )

import Test.Tasty ( testGroup, TestTree )
import Test.Tasty.QuickCheck
    ( chooseBoundedIntegral,
      (===),
      (==>),
      forAll,
      testProperty,
      Gen,
      NonNegative(getNonNegative),
      Property )

import Data.Bifunctor ( Bifunctor(bimap, first) )
import Data.List (sortOn)
import Data.Ratio ((%))
import Text.Printf ( printf )
import Control.Arrow ((&&&))
import Data.Bool (bool)

tests :: TestTree
tests = testGroup "Power to the People Coursework"
          [task1, task2, task3, task4, task5]

------------------------------------------------------
-- Task 1                                           --
------------------------------------------------------

task1 :: TestTree
task1 = testGroup "Task 1 - stepsPower"
  [ testProperty "stepsPower returns the correct number of recursion steps"
      stepsPowerAccurate
  ]

stepsPowerAccurate :: Integer -> Integer -> Property
stepsPowerAccurate n k = k >= 0 ==> stepsPower n k === powerStepsRec n k
  where
    -- The power function, but it counts how many steps its done instead of calculating the power
    powerStepsRec :: Integer -> Integer -> Integer
    powerStepsRec n k
      | k < 0 = error "power: negative argument"
    powerStepsRec n 0  = 1
    powerStepsRec n k  = 1 + powerStepsRec n (k-1)

------------------------------------------------------
-- Power laws/rules/identities       --
------------------------------------------------------

powerLaws :: String -> (Integer -> Integer -> Integer) -> TestTree
powerLaws funcName powerFunc
  = testGroup "Power laws"
      [ testProperty (printf "Power addition identity (%s): n^(k+j) = n^k * n^j" funcName)
          (powerAdditionIdentity powerFunc)
      , testProperty (printf "Power power identity (%s): (n^k)^j = n^(k * j)" funcName)
          (powerPowerIdentity powerFunc)
      , testProperty (printf "Base multiplication identity (%s): (n * m)^k = n^k * m^k" funcName)
          (baseMultiplicationIdentity powerFunc)
      , testProperty (printf "Return value not constant (%s)" funcName)
          (notConstantReturnVal powerFunc)
      ]

-- n^(k+j) = n^k * n^j
powerAdditionIdentity ::  (Integer -> Integer -> Integer) -> Integer -> Integer -> Integer -> Property
powerAdditionIdentity powerFunc n k j = n /= 0 && k >= 0 && j >= 0
  ==>  powerFunc n (k+j) === (powerFunc n k * powerFunc n j)

-- (n^k)^j = n^(k * j)
powerPowerIdentity ::  (Integer -> Integer -> Integer) -> Integer -> Integer -> Integer -> Property
powerPowerIdentity powerFunc n k j = n /= 0 && k >= 0 && j >= 0
  ==>  powerFunc (powerFunc n k) j === powerFunc n (k * j) 

-- (n * m)^k = n^k * m^k
baseMultiplicationIdentity :: (Integer -> Integer -> Integer) -> Integer -> Integer -> Integer -> Property
baseMultiplicationIdentity powerFunc n m k = n /= 0 && m /= 0 && k >= 0
  ==>  powerFunc (n * m) k === (powerFunc n k * powerFunc m k)

notConstantReturnVal :: (Integer -> Integer -> Integer) -> Bool
notConstantReturnVal powerFunc
  = not (allSame [powerFunc n k | n <- [-10..10], k <- [0..10]])
  where
    allSame [] = True
    allSame (x:xs) = all (x ==) xs

------------------------------------------------------
-- Task 2                                           --
------------------------------------------------------

task2 :: TestTree
task2 = testGroup "Task 2 - power1"
      [ powerLaws "power1" power1 ]

------------------------------------------------------
-- Task 3                                           --
------------------------------------------------------

task3 :: TestTree
task3 = testGroup "Task 3 - power2"
  [ powerLaws "power2" power2
  , testProperty "power2 makes fewer recursive calls than power"
      power2RecursionDepth
  ]

power2RecursionDepth :: Integer -> Property
power2RecursionDepth n = n /= 0 ==> forAll (chooseBoundedIntegral (16, 256) :: Gen Int) (\k ->
  let k' = fromIntegral k
  in treeHeight (power2 (Lit n) (Lit k')) < treeHeight (power0 (Lit n) (Lit k')))

------------------------------------------------------
-- Task 4                            --
------------------------------------------------------

task4 :: TestTree
task4 = testGroup "Task 4 - comparison functions"
  [ testProperty "comparePower1 performs accurate comparison"
      comparePower1Test
  , testProperty "comparePower2 performs accurate comparison"
      comparePower2Test
  ]

comparePower1Test :: Integer -> Integer -> Property
comparePower1Test n k = k >= 0 ==> comparePower1 n k === obscure power1 n k

comparePower2Test :: Integer -> Integer -> Property
comparePower2Test n k = k >= 0 ==> comparePower2 n k === obscure power2 n k

-- This effectively implements comparePower1/comparePower2,
-- but it's horrendously convoluted on purpose so it doesn't just give away how to do it.
-- It's much, much easier to implement the comparePower functions yourself
-- than it is to reverse-engineer this function.
obscure :: (Integer -> Integer -> Integer) -> Integer -> Integer -> Bool
obscure foo bar baz
  = fmap (foldr (fmap const const True) False)
    (foldr (either bar baz) last)
  $ [power0, foo]
  where
    last = Left False

    either curry recip pure id = case id of
      Left False -> Right (pure curry recip)
      Left _  -> id
      mempty  -> foldr (\(snd, fst) acc -> flip bool acc (Right snd) fst) (first not $ Left False)
                <$> fmap ((&&&) (\n -> n) (pure curry recip /=)) $ mempty

------------------------------------------------------
-- Task 5 - Efficiency                              --
------------------------------------------------------

task5 :: TestTree
task5 = testGroup "Task 5 - Running comparisons"
  [ testProperty "comparisonList ns ks contains entry for every combination of ns and ks"
      (\ns ks -> length (comparisonList ns ks) === length ns * length ks)
  , testProperty "comparisonList accurately reports the results of comparePower1 and comparePower2"
      comparisonListAccurate
  ]
  where
    comparisonListAccurate :: [Integer] -> [NonNegative Integer] -> Property
    comparisonListAccurate ns ks
      =   sortComparisonList (comparisonList ns ks')
      === sortComparisonList (obscure2ElectricBoogaloo ns ks')
      where
        ks' = map getNonNegative ks
    
    sortComparisonList = sortOn (\(n,k,test1,test2) -> (n, k))

-- Again, this is horrendously overcomplicated on purpose
obscure2ElectricBoogaloo :: [Integer] -> [Integer] -> [(Integer, Integer, Bool, Bool)]
obscure2ElectricBoogaloo mempty mappend
  = fooMap (bimap (uncurry comparePower1) (uncurry comparePower2)) (curry ((&&&) id id) <$> mempty <*> mappend)
  where
    fooMap f xs = map (\val@((x,y),_) -> case f val of (m,n) -> (x,y,m,n)) xs

------------------------------------------------------
-- Misc                                             --
------------------------------------------------------

power0 :: Integral a => a -> a -> a
power0 n k
   | k < 0 = error "power0: negative argument"
power0 n 0  = 1
power0 n k  = n * power0 n (k-1) 

data IntExpr
  = Lit Integer
  | Add IntExpr IntExpr
  | Sub IntExpr IntExpr
  | Mul IntExpr IntExpr
  | Abs IntExpr
  | SigNum IntExpr
  | Quot IntExpr IntExpr
  | Rem IntExpr IntExpr
  | Div IntExpr IntExpr
  deriving Show

evalIntExpr :: IntExpr -> Integer
evalIntExpr e = case e of
  Lit n -> n
  Add x y -> evalIntExpr x + evalIntExpr y
  Sub x y -> evalIntExpr x - evalIntExpr y
  Mul x y -> evalIntExpr x * evalIntExpr y
  Abs x -> abs (evalIntExpr x)
  SigNum x -> signum (evalIntExpr x)
  Quot x y -> evalIntExpr x `quot` evalIntExpr y
  Rem x y -> evalIntExpr x `rem` evalIntExpr y
  Div x y -> evalIntExpr x `div` evalIntExpr y

instance Num IntExpr where
  (+) = Add
  (*) = Mul
  abs = Abs
  signum = SigNum
  fromInteger = Lit
  (-) = Sub

instance Eq IntExpr where
  x == y = evalIntExpr x == evalIntExpr y

instance Ord IntExpr where
  x <= y = evalIntExpr x <= evalIntExpr y

instance Enum IntExpr where
  toEnum = Lit . fromIntegral
  fromEnum = fromIntegral . evalIntExpr

instance Real IntExpr where
  toRational = (% 1) . evalIntExpr

instance Integral IntExpr where
  quotRem x y = (Quot x y, Rem x y)
  toInteger = evalIntExpr

foldIntExpr :: (Integer -> b) -> (b -> b) -> (b -> b -> b) -> IntExpr -> b
foldIntExpr lit unaryOp binOp expr = case expr of
  Mul x y  -> binOp (foldIntExpr lit unaryOp binOp x) (foldIntExpr lit unaryOp binOp y)
  Add x y  -> binOp (foldIntExpr lit unaryOp binOp x) (foldIntExpr lit unaryOp binOp y)
  Sub x y  -> binOp (foldIntExpr lit unaryOp binOp x) (foldIntExpr lit unaryOp binOp y)
  Quot x y -> binOp (foldIntExpr lit unaryOp binOp x) (foldIntExpr lit unaryOp binOp y)
  Rem x y  -> binOp (foldIntExpr lit unaryOp binOp x) (foldIntExpr lit unaryOp binOp y)
  Div x y  -> binOp (foldIntExpr lit unaryOp binOp x) (foldIntExpr lit unaryOp binOp y)
  Lit n    -> lit n
  Abs x    -> unaryOp (foldIntExpr lit unaryOp binOp x)
  SigNum x -> unaryOp (foldIntExpr lit unaryOp binOp x)

treeHeight :: IntExpr -> Int
treeHeight = foldIntExpr (const 1) (\x -> 1 + x) (\x y -> 1 + max x y)
