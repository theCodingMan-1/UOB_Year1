module Simplify where
-- Write all of your code in this file!

import Expr
import Poly

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











-- add :: Expr -> Expr -> String
-- add (NumLit x) (ExpX y)
--     | y == 0 = prettyExpr (NumLit (x + 1))
--     | x == 0 = prettyExpr (ExpX y)
--     | otherwise = prettyExpr (Op AddOp (NumLit x) (ExpX y))
-- add (ExpX x) (NumLit y)
--     | x == 0 = prettyExpr (NumLit (y + 1))
--     | y == 0 = prettyExpr (ExpX x)
--     | otherwise = prettyExpr (Op AddOp (ExpX x) (NumLit y))
-- add (NumLit x) (NumLit y) = prettyExpr (NumLit (x + y))
-- add (ExpX x) (ExpX y) 
--     | x == 0 && y == 0 = prettyExpr (NumLit 2)
--     | x == 0 = prettyExpr (Op AddOp (NumLit 1) (ExpX y))
--     | y == 0 = prettyExpr (Op AddOp (ExpX x) (NumLit 1))
--     | x == y = prettyExpr (Op MulOp (NumLit 2) (ExpX x))
--     | otherwise = prettyExpr (Op AddOp (ExpX x) (ExpX y))

--------------------------------------------------------------------------------
-- * Task 2
-- Define mul, which multiplies 2 expressions together without introducing
-- any 'junk'.

mul :: Expr -> Expr -> Expr
mul expr1 expr2 = error "Implement me!"

--------------------------------------------------------------------------------
-- * Task 3
-- Define addAll, which adds a list of expressions together into
-- a single expression without introducing any 'junk'.

addAll :: [Expr] -> Expr
addAll exprs = error "Implement me!"

--------------------------------------------------------------------------------
-- * Task 4
-- Define mulAll, which multiplies a list of expressions together into
-- a single expression without introducing any 'junk'.

mulAll :: [Expr] -> Expr
mulAll exprs = error "Implement me!"

--------------------------------------------------------------------------------
-- * Task 5
-- Define exprToPoly, which converts an expression into a polynomial.

exprToPoly :: Expr -> Poly
exprToPoly expr = error "Implement me!"

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
