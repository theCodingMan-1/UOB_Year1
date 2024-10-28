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
primeSieveUpTo :: Int -> [Int]
primeSieveUpTo x = primeSieveUpTo' (makeList x) []
    where
        primeSieveUpTo' :: [Int] -> [Int] -> [Int]
        primeSieveUpTo' [] list = []
        primeSieveUpTo' (x : xs) list 
            | (checkPrime x list) = x : primeSieveUpTo' xs (x : list)
            | otherwise = primeSieveUpTo' xs (x : list)

checkPrime :: Int -> [Int] -> Bool
checkPrime a [] = True
checkPrime a (x : xs)
    | mod a x == 0 = False
    | otherwise = checkPrime a xs


makeList :: Int -> [Int]
makeList x = makeList' [] x
    where
        makeList' :: [Int] -> Int -> [Int]
        makeList' list x 
            | x <= 1 = list
            | otherwise = makeList' (x : list) (x - 1)
