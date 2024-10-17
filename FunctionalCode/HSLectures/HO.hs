module HO where
import Prelude hiding (filter, map, zipWith, takeWhile)



-- Abstraction is power
--  * less cognative load
--  * represent more things
--  * composable and modular


-- >>> filterOdd [1, 2, 3]
-- [1, 3]
filterOdd :: [Int] -> [Int]
filterOdd [] = []
filterOdd (x : xs)
    | odd x = x : filterOdd xs
    | otherwise = filterOdd xs


-- >>> filterEven [1, 2, 3]
-- [2]
filterEven :: [Int] -> [Int]
filterEven [] = []
filterEven (x : xs)
    | even x = x : filterEven xs
    | otherwise = filterEven xs


onlyA :: [Char] -> [Char]
onlyA [] = []
onlyA (x : xs)
    | x == 'A' = x : onlyA xs
    | otherwise = onlyA xs


-- all of these functions do generally the same sort of filtering. 
-- below is that general structure.
-- all we need to do is decide what the predicate 'p' is

filter :: (a -> Bool) -> [a] -> [a]
filter p [] = []
filter p (x : xs)
    | p x = x : filter p xs
    | otherwise = filter p xs

filterOdd' :: [Int] -> [Int]
filterOdd' xs = filter odd xs

filterEven' :: [Int] -> [Int]
filterEven' xs = filter even xs

onlyA' :: [Char] -> [Char]
onlyA' xs = filter isA xs
    where
        isA :: Char -> Bool
        isA x = x == 'A'

-- the above function is quite long

onlyA'' :: [Char] -> [Char]
onlyA'' xs = filter (\x -> x == 'A') xs



-- the next two functions are equivelent
fun x = x
fun' = \x -> x



onlyA''' :: [Char] -> [Char]
onlyA''' = filter (=='A')


mapPlusTwo :: [Int] -> [Int]
mapPlusTwo [] = []
mapPlusTwo (x : xs) = (x + 2) : mapPlusTwo xs

mapShow :: Show a => [a] -> [String]
mapShow [] = []
mapShow (x : xs) = show x : mapShow xs

map :: (a -> b) -> [a] -> [b]
map f [] = []
map f (x : xs) = f x : map f xs


mapPlusTwo' :: [Int] -> [Int]
mapPlusTwo' xs = map (+2) xs


mapShow' :: Show a => [a] -> [String]
mapShow' xs = map show xs