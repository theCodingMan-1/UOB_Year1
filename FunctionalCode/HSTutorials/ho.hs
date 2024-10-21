sumOddElements :: [Int] -> Int
sumOddElements [] = 0
sumOddElements (x : xs)
    | odd x = x + sumOddElements xs
    | otherwise = sumOddElements xs


take' :: Int -> [a] -> [a]
take' n [] = []
take' 0 xs = []
take' n (x : xs) = x : take' (n - 1) xs


drop' :: Int -> [a] -> [a]
drop' 0 xs = xs
drop' n [] = []
drop' n (x : xs) = drop' (n - 1) xs


splitAt' :: Int -> [a] -> ([a], [a])
splitAt' 0 xs = ([], xs)
splitAt' n [] = ([], [])
splitAt' n (x : xs) = 
    let (f, s) = splitAt' (n - 1) xs
    in (x : f, s)

-- splitAt' n xs = (take' n xs, drop' n xs)



replicateElements :: Int -> [a] -> [a]
replicateElements 0 xs = xs
replicateElements n [] = []
replicateElements n (x : xs) = replicate n x ++ replicateElements n xs

lower :: String -> String
lower "" = ""
lower (x : xs) = toLower x : lower xs


