
-- 1.1 return the first element of the list or 0 if its empty
headorZero :: [Int] -> Int
headorZero [] = 0
headorZero (x : xs) = x


-- 1.2 return the number of elements in a given list
length' :: [Int] -> Int
length' [] = 0
length' (x : xs) = 1 + length' xs


-- 1.3 return the summation of all the elements in the list
sum' :: [Int] -> Int
sum' [] = 0
sum' (x : xs) = x + sum' xs

-- 1.4 returns the product of all the element in the list
product' :: [Int] -> Int
product' [] = 1
product' (x : xs) = x * product' xs


-- 1.5 adds an element to the end of the list
snoc' :: Int -> [Int] -> [Int]
snoc' x [] = [x]
snoc' x (y : xs) = y : snoc' x xs


-- 1.6 returns the first n items in the list
take' :: Int -> [Int] -> [Int]
take' 1 (x : xs) = [x]
-- when you get down to y = 1, you take the element at the front of the list (x)

take' y (x : xs) = x : take' (y - 1) (xs)
-- otherwise y is decreased by one, and the first element of the list is taken to be returned


-- 1.7 given an element x, and a sorted input list xs is in acending order
--      it produces another sorted list with x inserted into
--      the correct position
insert :: Int -> [Int] -> [Int]
insert x [] = [x]
insert x (y : xs)
    | x < y = x : (y : xs)
    | otherwise = y : insert x (xs)

-- 1.8 use insert to implement a function that sorts a list
isort :: [Int] -> [Int]
isort [] = []
isort (x : xs) = insert x (isort (xs))


-- 1.9 merge two sorted lists together
merge :: [Int] -> [Int] -> [Int]
merge [] [] = []
merge [] ys = ys
merge (x : xs) ys = isort (merge xs (x : ys))


-- 1.10 returns the two values in the same location
zip' :: [Int] -> [Int] -> [(Int, Int)]
zip' [] [] = []
zip' (x : xs) (y : ys) = (x, y) : (zip' xs ys)


-- 1.11 define a function that appends one list to the end of another
combine' :: [Int] -> [Int] -> [Int]
combine' [] [] = []
combine' as [] = as
combine' (as) (b : bs) = combine' (snoc' b as) bs



-- 2.1
squaresUpto :: Int -> [Int]
squaresUpto x
    | x <= 0 = [0]
    | otherwise = squaresUpto (x - 1) ++ [x * x]

--2.2
odds :: Int -> [Int]
odds x = filter odd [1..x]

--2.3
tuple :: Int -> [Int] -> [(Int, Int)]
tuple x [] = []
tuple x (y : ys) = (x , y) : tuple x ys

order :: [Int] -> [(Int, Int)]
order [] = []
order (x : xs) = tuple x xs ++ order xs

orderedPairs :: [Int] -> [(Int, Int)]
orderedPairs xs = order (isort xs)


--2.4
-- bitString :: Int -> [String]
-- bitString x = bitString' x ""
--     where
--         bitString' :: Int -> String -> [String]
--         bitString' x text
--             | x == 0 = [text]
--             | otherwise = (bitString' (x - 1) (text ++ "0")) ++ (bitString' (x - 1) (text ++ "1"))


bitString :: Int -> [String]
bitString 0 = [""]
bitString  = [a ++ b | a <- ["0", "1"], y <- bitString (n - 1)]




--3.1

