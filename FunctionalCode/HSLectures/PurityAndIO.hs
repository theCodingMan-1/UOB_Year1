-- module PurityAndIo where
-- module Main where

import Prelude
import Data.Semigroup (diff)


main :: IO ()
main = do
    putStrLn "Hello World"
    putStrLn "Good Bye!"


-- print x = putStrLn(show x)


echo :: IO ()
echo = do
    line <- getLine
    putStrLn line