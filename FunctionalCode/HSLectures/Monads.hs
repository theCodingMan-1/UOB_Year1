import Control.Concurrent (yield)
safeDiv :: Int -> Int -> Either String Int
safeDiv x y
    | y == 0 = Left "Divide by Zero!"
    | otherwise = Right (x `div` y)


test :: Int -> Int -> Either String String
test x y = fmap show (safeDiv x y)