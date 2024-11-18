{-# OPTIONS_GHC -Wno-overlapping-patterns #-}
module Simplify where
-- Write all of your code in this file!

import Expr
import Poly
import Control.Concurrent (yield, waitQSem)
import Data.Bits (Bits(xor))

--------------------------------------------------------------------------------
-- * Task 1
-- Define add, which adds 2 expressions together without introducing
-- any 'junk'.

add :: Expr -> Expr -> Expr
add (NumLit x) (ExpX y)
    | y == 0 = NumLit (x + 1)
    | x == 0 = ExpX y
    | otherwise = Op AddOp (NumLit x) (ExpX y)
add (ExpX x) (NumLit y)
    | x == 0 = NumLit (y + 1)
    | y == 0 = ExpX x
    | otherwise = Op AddOp (ExpX x) (NumLit y)
add (NumLit x) (NumLit y) = NumLit (x + y)
add (ExpX x) (ExpX y)
    | x == 0 && y == 0 = NumLit 2
    | x == 0 = Op AddOp (NumLit 1) (ExpX y)
    | y == 0 = Op AddOp (ExpX x) (NumLit 1)
    | x == y = Op MulOp (NumLit 2) (ExpX x)
    | otherwise = Op AddOp (ExpX x) (ExpX y)

add x y
    | x == NumLit 0 = y
    | y == NumLit 0 = x

    |otherwise = Op AddOp x y


--------------------------------------------------------------------------------
-- * Task 2
-- Define mul, which multiplies 2 expressions together without introducing
-- any 'junk'.

mul :: Expr -> Expr -> Expr
mul (NumLit x) (NumLit y) = NumLit (x * y)
mul (NumLit x) (ExpX y)
    | x == 0 = NumLit 0
    | y == 0 = NumLit x
    | x == 1 = ExpX y
    | otherwise = Op MulOp (NumLit x) (ExpX y)
mul (ExpX x) (NumLit y)
    | y == 0 = NumLit 0
    | x == 0 = NumLit y
    | y == 1 = ExpX x
    | otherwise = Op MulOp (ExpX x) (NumLit y)
mul (ExpX x) (ExpX y)
    | y == 0 && x == 0 = NumLit 1
    | y == 0 = ExpX x
    | x == 0 = ExpX y
    | otherwise = ExpX (x + y)

mul x y
    | x == NumLit 0 || y == NumLit 0 = NumLit 0
    | x == NumLit 1 = y
    | y == NumLit 1 = x

    |otherwise = Op MulOp x y

--------------------------------------------------------------------------------
-- * Task 3
-- Define addAll, which adds a list of expressions together into
-- a single expression without introducing any 'junk'.

addAll :: [Expr] -> Expr
addAll xs = foldr add (NumLit 0) xs

--------------------------------------------------------------------------------
-- * Task 4
-- Define mulAll, which multiplies a list of expressions together into
-- a single expression without introducing any 'junk'.

mulAll :: [Expr] -> Expr
mulAll xs = foldr mul (NumLit 1) xs

--------------------------------------------------------------------------------
-- * Task 5
-- Define exprToPoly, which converts an expression into a polynomial.


makeList :: Int -> [Int] -> [Int]
makeList a xs = makeList' [a] xs
    where
        makeList' :: [Int] -> [Int] -> [Int]
        makeList' list [] = list
        makeList' list (x : xs) = makeList' (list ++ [0]) xs


exprToPoly :: Expr -> Poly
exprToPoly (NumLit x) = listToPoly [x]
exprToPoly (ExpX x) = listToPoly (makeList 1 [1..x])
exprToPoly (Op AddOp x y) = addPoly (exprToPoly x) (exprToPoly y)
exprToPoly (Op MulOp x y) = mulPoly (exprToPoly x) (exprToPoly y)


--------------------------------------------------------------------------------
-- * Task 6
-- Define polyToExpr, which converts a polynomial into an expression.

listToExpr :: [Int] -> Expr
listToExpr xs = listToExpr' 0 xs
    where
        listToExpr' :: Int -> [Int] -> Expr
        listToExpr' a [] = NumLit 0
        listToExpr' a (x : xs)
            | a == 0 = add (NumLit x) (listToExpr' 1 xs)
            | x == 0 = listToExpr' (a + 1) xs
            | otherwise = add (mul (NumLit x) (ExpX a)) (listToExpr' (a + 1) xs)

polyToExpr :: Poly -> Expr
polyToExpr poly = listToExpr (reverse (polyToList poly))


--------------------------------------------------------------------------------
-- * Task 7
-- Define a function which simplifies an expression by converting it to a
-- polynomial and back again.

simplify :: Expr -> Expr
simplify expr = polyToExpr (exprToPoly expr)

--------------------------------------------------------------------------------
