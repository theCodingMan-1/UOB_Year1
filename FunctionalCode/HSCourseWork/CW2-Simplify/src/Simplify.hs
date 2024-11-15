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

maximum' :: Ord a => [a] -> a
maximum' [x] = x
maximum' (x : x' : xs)
    | x >= x' = maximum' (x : xs)
    | otherwise = maximum' (x' : xs)




makePowerList :: Expr -> [Expr]
makePowerList (ExpX x) = [ExpX x]
makePowerList (NumLit x) = [NumLit x]
makePowerList (Op AddOp x y) = makePowerList x ++ makePowerList y

count :: Expr -> [Expr] -> Int
count a [] = 0
count a (x : xs)
    | a == x = 1 + count a xs
    | otherwise = count a xs

makeCoList :: [Expr] -> [Int]
makeCoList (x : xs) = count x (x : xs) : makeCoList (filter (/= x) xs)
-- makeCoList [] = []
-- makeCoList xs = count (maximum' xs) xs : makeCoList (filter (/= maximum' xs) xs)

makeList :: Int -> [Int] -> [Int]
makeList a xs = makeList' [a] xs
    where
        makeList' :: [Int] -> [Int] -> [Int]
        makeList' list [] = list
        makeList' list (x : xs) = makeList' (list ++ [x]) xs

--ExpX 4
-- >>> [1, 0, 0, 0, 0]
-- >>> x^4

exprToPoly :: Expr -> Poly
exprToPoly (NumLit x) = listToPoly [x]
exprToPoly (ExpX x) = listToPoly (makeList 1 [1..x])
exprToPoly (Op AddOp x y) = addPoly (exprToPoly x) (exprToPoly y)
exprToPoly (Op MulOp x y) = mulPoly (exprToPoly x) (exprToPoly y)

-- exprToPoly x = listToPoly (makeCoList (makePowerList x))
-- exprToPoly (Op AddOp x y) = exprToPoly ([x] + [y])

--------------------------------------------------------------------------------
-- * Task 6
-- Define polyToExpr, which converts a polynomial into an expression.

polyToExpr :: Poly -> Expr
polyToExpr poly = error "Implement me!"

--------------------------------------------------------------------------------
-- * Task 7
-- Define a function which simplifies an expression by converting it to a
-- polynomial and back again.

simplify :: Expr -> Expr
simplify expr = error "Implement me!"

--------------------------------------------------------------------------------
