module Main (main) where

import Tests (tests)

import Test.Tasty ( defaultMain, localOption )
import Test.Tasty.QuickCheck ( QuickCheckTests(QuickCheckTests) )

main :: IO ()
main = defaultMain tests'
  where
    tests' = localOption (QuickCheckTests testsPerProperty) tests
    testsPerProperty = 200
