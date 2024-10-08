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
stepsPower n k = error "Implement me!"

-- Task 2 -------------------------

power1 :: Integral a => a -> a -> a
power1 n k = error "Implement me!"

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
