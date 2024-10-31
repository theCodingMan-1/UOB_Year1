-- Folds are an example of a higher order function (HO)

import Prelude hiding(sum, length, foldr)

-- >>> sum [1, 2, 3]
-- 6

sum :: [Int] -> Int
sum [] = 0
sum (x : xs) = x + sum xs


prod :: [Int] -> Int
prod [] = 1
prod (x : xs) = x * prod xs


length :: [a] -> Int
length [] = 0
length (x : xs) = 1 + length xs






data TrickOrTreat = Trick | Treat deriving Show


tricksVsTreats :: [TrickOrTreat] -> (Int, Int)
tricksVsTreats [] = (0, 0)
tricksVsTreats (Trick : xs) = let (icks, eats) = tricksVsTreats xs
                                in (1 + icks, eats)
tricksVsTreats (Treat : xs) = let (icks, eats) = tricksVsTreats xs
                                in (icks, 1 + eats)





name :: [a] -> b
name [] = k
    where
        k :: b
        k = undefined
name (x : xs) = x `f` name xs
    where
        f :: a -> b -> b
        f = undefined



-- f is the function we apply to the elements of the list
-- k is the base case (what is returned when the list is empty)
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f k [] = k
foldr f k (x : xs) = x `f` foldr f k xs

sum' :: [Int] -> Int
sum' xs = foldr (+) 0 xs

prod' :: [Int] -> Int
prod' xs = foldr (*) 1 xs


length' :: [a] -> Int
length' xs = foldr f 0 xs
    where
        f :: a -> Int -> Int
        f x l = l + 1