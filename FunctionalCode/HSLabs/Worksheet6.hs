-- FOLDS!

--using,



import Prelude hiding (sum, product, and, or, all, any, length, map, foldl, reverse, filter)



--1 Folding Lists
-- foldr :: (a → b → b) → b → [a] → b
-- foldr f k [ ] = k
-- foldr f k (x : xs) = f x (foldr f k xs)


--1.1 
sum :: [Integer] -> Integer
sum xs = foldr (+) 0 xs


--1.2 
product :: [Integer] -> Integer
product xs = foldr (*) 1 xs


--1.3
and :: [Bool] -> Bool
and xs = foldr (&&) True xs


--1.4
or :: [Bool] -> Bool
or xs = foldr (||) False xs


--1.5

boolList :: (a -> Bool) -> [a] -> [Bool]
boolList p [] = []
boolList p (x : xs) = p x : boolList p xs


all :: (a -> Bool) -> [a] -> Bool
all p xs = and (boolList p xs)


--1.6
any :: (a -> Bool) -> [a] -> Bool
any p xs = or (boolList p xs)




--1.7
length :: [a] -> Int
length xs = foldr f 0 xs
    where
        f a b = 1 + b 


-- 1.8
map :: (a -> b) -> [a] -> [b]
map f [] = []
map f (x : xs) = f x : map f xs



--1.9
-- reverse :: [a] -> [a]
-- reverse [] = []
-- reverse (x : xs) = reverse xs ++ [x]

reverse :: [a] -> [a]
reverse xs = foldr f [] xs
    where
        f x xs = xs ++ [x]


--1.10
filter :: (a -> Bool) -> [a] -> [a]
filter p xs = foldr f [] xs
    where
        f x xs
            | p x == True = x : xs
            | otherwise = xs


--1.11
group :: Eq a => [a] -> [[a]]
group xs = foldr f [[]] xs
    where
        f a [[]] = [[a]]
        f a ((x : xs) : ks) 
            | a == x = ([a] ++ [x] ++ xs) : ks
            | otherwise = [a] : ([x] ++ xs): ks



--1.12
transpose :: [[a]] -> [[a]]
transpose xs = foldr f [[]] xs
    where
        f (x : xs) [[]] = [x] : f xs [[]] 
        f [] z = []
        f (x : xs) (ys :zs) = ([x] ++ ys) : f xs zs



--1.13 

--1.14


-- 

