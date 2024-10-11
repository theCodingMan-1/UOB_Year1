
-- returns the final character of a string
myLast :: String -> Char
myLast [] = error "tried to give empty list"
myLast [x] = x
myLast (x : xs) = myLast xs


myReverse :: String -> String
myReverse [x] = [x]
myReverse (x : xs) = myReverse xs ++ [x]




encode :: String -> String
encode str = stringify (reverse (go str[]))
    where
        go :: String -> [(Char, Int)] -> [(Char, Int)]
        go [] [] = []
        go [] list = list
        go (c : cs) [] = go cs [(c, 1)]
        go (c : cs) ((c', acc) : xs) 
            | c' == c = go cs ((c', acc + 1) : xs)
            | otherwise= go cs $ (c , 1) : (c', acc) : xs
            -- $ just means everything after it is in a bracket together


        stringify :: [(Char, Int)] -> String
        stringify [] = []
        stringify ((c, acc) : xs) = [c] ++ show acc ++ stringify xs
