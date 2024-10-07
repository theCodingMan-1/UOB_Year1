import Data.List

-- data Maybe a = Just a | Nothing

-- data Either a b = Left a | Right b

-- 1.1 Using pattern matching, define a function that returns
--  True if the argument is of the form Just x and False otherwise

isJust :: Maybe a -> Bool
isJust (Just x) = True
isJust Nothing = False



-- 1·2 Write a function which extracts the value of a given
--      Mabye if it is a Just and uses the default value
--      of type a otherwise

fromMaybe :: a -> Maybe a -> a
fromMaybe y (Just x) = x
fromMaybe y (Nothing) = y


-- 1.3
forget :: Either String a -> Maybe a
forget (Right y) = (Just y)


-- 1.4
--Just (Right True) :: Maybe (Either a Bool)


-- 1.5 (a)
safeDiv :: Int -> Int -> Maybe Int
safeDiv x 0 = Nothing
safeDiv x y = Just (div x y)

-- 1.5 (b)
safeDiv' :: Int -> Int -> Either String Int
safeDiv' x 0 = Left "ERROR"
safeDiv' x y = Right (div x y)

-- 1.5 (c)
checkForErrors :: [Either String a] -> Either String [a]
checkForErrors xs = checkForErrors' [] xs
    where
        checkForErrors' :: [a] -> [Either String a] -> Either String [a]
        checkForErrors' _ ((Left x) : xs) = Left x
        checkForErrors' list [] = Right (reverse list)
        checkForErrors' list ((Right x) : xs) = checkForErrors' (x : list) xs
