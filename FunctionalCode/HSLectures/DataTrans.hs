-- function machines


(.>) = flip (.)



add3 :: Int -> Int
add3 x = x + 3

mul5 :: Int -> Int
mul5 x = x * 5


myFuncMachine :: Int -> Int
myFuncMachine = mul5 . add3



-- round :: Float -> Int
-- (==10) :: Int -> Bool
roundsTo10 :: Float -> Bool
-- roundsTo10 = round .> (==10)
-- roundsTo10 = \input -> (==10) (round input)
-- roundsTo10 = \input -> (round input) == 10
roundsTo10 input = (round input) == 10












countWords :: String -> Int
countWords = words .> length


addLineStartToContents :: String -> String
addLineStartToContents
    = lines
    .> map ('>' :)
    .> unlines