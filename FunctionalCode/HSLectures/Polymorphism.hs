
tail' :: [a] -> [a]
-- 'a' stands for any type. This means you could enter anything from a string to an integer

tail' [] = []
tail' (x : xs) = xs



sum' :: Num a => [a] -> a
-- specifically tells us that 'a' must be a number. 
-- 'a' can be any number type as long as its the same number type.

sum' [] = 0
sum' (x : xs) = x + sum' xs




class MyEq a where
    equals :: a -> a -> Bool
-- equals has the type class of Eq. 

notEquals :: MyEq a => a -> a -> Bool
notEquals x y = not (equals x y)

instance MyEq Bool where
    equals :: Bool -> Bool -> Bool
    equals x y = x == y


instance MyEq Int where
    equals x y = x == y


instance Eq a => MyEq [a] where
    equals x y = x == y