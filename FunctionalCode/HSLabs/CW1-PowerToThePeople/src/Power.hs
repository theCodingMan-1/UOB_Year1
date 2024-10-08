module Power where
-- Code for the Power to the People Coursework.
-- Write all your code in this file.
-- *DO NOT CHANGE THE FUNCTION NAMES OR TYPE SIGNATURES*

---------------------------------------------
-- An example implementation of the power function.
-- *DO NOT EDIT THIS FUNCTION OR USE IT IN YOUR CODE*

power :: Integer -> Integer -> Integer
power n k
   | k < 0 = error "power: negative argument"
power n 0  = 1
power n k  = n * power n (k-1)

-- Task 1 -------------------------

stepsPower :: Integer -> Integer -> Integer
stepsPower n k
   | k < 0 = 1
stepsPower n k = k + 1

-- Task 2 -------------------------

replicate' :: Int -> a -> [a]
replicate' k n = replicate'' [] k n
   where
      replicate'' :: [a] -> Int -> a -> [a]
      replicate'' list 0 n = []
      replicate'' list 1 n = list
      replicate'' list k n = replicate'' (n : list) (k - 1) n

product' :: Num a => [a] -> a
product [] = 1
product' (x : xs) = x * product' xs 

power1 :: Integral a => a -> a -> a
power1 n k = product' (replicate' k n)

-- Task 3 -------------------------

power2 :: Integral a => a -> a -> a
power2 n k = error "Implement me!"

-- Task 4 -------------------------

comparePower1 :: Integer -> Integer -> Bool
comparePower1 n k = error "Implement me!"

comparePower2 :: Integer -> Integer -> Bool
comparePower2 n k = error "Implement me!"

-- Task 5 -------------------------

-- Each entry should be in this format: (n, k, result of comparePower1, result of comparePower2)
comparisonList :: [Integer] -> [Integer] -> [(Integer, Integer, Bool, Bool)]
comparisonList ns ks = error "Implement me!"
