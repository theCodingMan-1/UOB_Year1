--1.1
--(a)
safeLog :: (Floating a, Ord a) => a -> Maybe a
safeLog x
    | x >= 0 = Just (log x)
    | otherwise = Nothing

--(b)
safeSqrt :: (Floating a, Ord a) => a -> Maybe a
safeSqrt x
    | x >= 0 = Just (sqrt x)
    | otherwise = Nothing


--(c)
safeLogSqrt :: (Floating a, Ord a) => a -> Maybe a
safeLogSqrt x = do
    a <- safeSqrt x
    safeLog(a)


--(d)
safeLogSqrt' :: (Floating a, Ord a) => a -> Maybe a
safeLogSqrt' x = safeSqrt x >>= safeLog



--1.2
-- lookup :: Eq k => k -> [(k, v)] -> Maybe b
-- lookup k [ ] = Nothing
-- lookup k ((k' : v) : kvs)
--     | k == k' = Just v
--     | otherwise = lookup k kvs


productNameCost :: [(String, Int)] -> [(Int, Float)] -> String -> Maybe Float
productNameCost as bs string = do
    id <- lookup string as
    lookup id bs



--1.3
handleMaybe :: Maybe a -> a -> a
handleMaybe (Just x) a = x
handleMaybe Nothing a = a


safeLogSqrt'' :: (Floating a, Ord a) => a -> a
safeLogSqrt'' x = handleMaybe (safeLogSqrt' x) 0




--2.1
lookupEither :: (Show k, Eq k) => k -> [(k, v)] -> Either String v
lookupEither string xs = lookUpEither' (lookup string xs)
    where
        lookUpEither' :: Maybe a -> Either String a
        lookUpEither' Just x = Right x
        lookUpEither' Nothing = Left "Missing key"
