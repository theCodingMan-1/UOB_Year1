-- TYPES!!!!

-- Types are a collection of types

-- Int - The type of integers - 3
-- Bool - The type of Booleans - False
-- String - The type of text - "Hello"

example1 :: Int -- annotation defining example1 as an integer
example1 = 10 + 12


--example2 = example1 + "Hello, World" --error is shown as we know that example1 is an integer


tuples :: (Int, String)
tuples = (10, "Hello, World!")
-- 'fst' takes the first component. Therefore the command, 'fst tuples', returns '10'
-- 'snd' takes the second component. Therefore the command, 'snd tuples', returns '"Hello, World!"'

-- example3 = fst _ + 2
-- '_' is a hole. when ran the terminal will show an error and tell you the type expected. 

example4 :: (Int, Char) -> (Char, Int) 
-- tells you the intention of the code. We can guess that the two items in the tuple will be swapped
example4 p = (snd p, fst p)


-- -- Function Types :)
-- fst' :: (Int, Char) -> Int

-- mod :: Int -> Int -> Int

-- prime :: Int -> Int -> Int
-- prime n m
--     | n `mod` m = True
--     | otherwise = False

