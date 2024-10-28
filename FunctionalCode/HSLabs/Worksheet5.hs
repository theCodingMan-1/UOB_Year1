import Data.Char

--Part 1



-- filter :: (a → Bool) → [a] → [a]
-- filter p [ ] = [ ]
-- filter p (x : xs)
--     | p x = x : filter p xs
--     | otherwise = filter p xs


--1
greaterThan :: Int -> [Int] -> [Int]
greaterThan x xs = filter (>x) xs



--2
filterOdd :: Integral a => [a] -> [a]
filterOdd xs = filter odd xs


--3
filterSquare :: [Double] -> [Double]
filterSquare xs = filter square xs
    where
        square :: Double -> Bool
        square a
            | fromIntegral (floor (sqrt a)) == sqrt a = True
            | otherwise = False


--4
--(a)
-- primeSieveUpTo :: Int -> [Int]
-- primeSieveUpTo x = primeSieveUpTo' (makeList x) []
--     where
--         primeSieveUpTo' :: [Int] -> [Int] -> [Int]
--         primeSieveUpTo' [] list = []
--         primeSieveUpTo' (x : xs) list
--             -- if x is prime it is added to the list of primes.
--             -- (x:list) makes sure it is on the list of prime numbers
--                 -- to 
--             | (checkPrime x list) = x : primeSieveUpTo' xs (x : list)

--             -- if it is not prime it is not added to the list
--             | otherwise = primeSieveUpTo' xs (list)




-- -- goes through a list of all prime numbers less than that number.
-- -- checks if those numbers divide into that number.
-- -- If they do it is not prime (False)
-- -- otherwise it is prime (True)
-- checkPrime :: Int -> [Int] -> Bool
-- checkPrime a [] = True
-- checkPrime a (x : xs)
--     | mod a x == 0 = False
--     | otherwise = checkPrime a xs


-- -- This function creates a list of n elements
-- -- >>> makeList 9
-- -- [1, 2, 3, 4, 5, 6, 7, 8, 9]
-- makeList :: Int -> [Int]
-- makeList x = makeList' [] x
--     where
--         makeList' :: [Int] -> Int -> [Int]
--         makeList' list x 
--             | x <= 1 = list
--             | otherwise = makeList' (x : list) (x - 1)








primeSieveUpTo :: Int -> [Int]
primeSieveUpTo x = go [2..x]

go :: [Int] -> [Int]
go [] = []
go (x : xs) = x : go (filter (\i -> i `mod` x /= 0) xs)





-- (b)
filterPrime :: [Int] -> [Int]
filterPrime [] = []
filterPrime (x : xs) = filter (==x) (primeSieveUpTo x) ++ filterPrime xs




--Part 2

--1.

double :: [Int] -> [Int]
double xs = map (*2) xs


--2
shout :: String -> String
shout [] = []
shout (x : xs) = toUpper x : shout xs


--3 
whisper :: String -> String
whisper [] = []
whisper (x : xs) = toLower x : whisper xs


--4
basicTitle :: String -> String
basicTitle xs = unwords (basicTitle' (words  xs))
    where
        basicTitle' :: [String] -> [String]
        basicTitle' [] = []
        basicTitle' (x : xs) = basicTitle'' 1 x : basicTitle' xs
            where
                basicTitle'' :: Int -> String -> String
                basicTitle'' a (x : xs)
                    | a == 1 = toUpper x : basicTitle'' 2 xs
                    | otherwise = x : xs



--5 
--(a)
anyList :: (a -> Bool) -> [a] -> Bool
anyList p xs = or (map p xs)

--(b)
