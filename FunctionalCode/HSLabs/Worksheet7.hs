--1.1

--(a)
data Maybe' a = Just' a | Nothing'

instance Functor Maybe' where
    fmap f Nothing' = Nothing'
    fmap f (Just' x) = Just' (f x)



--(b) 
data Either' a b = Left' a | Right' b

instance Functor (Either' a) where
    fmap f (Right' x) = Right' (f x)


--(c)
data Expr a 
    = Var a
    | Lit Int
    | Add (Expr a) (Expr a)
    | Mul (Expr a) (Expr a)

instance Functor Expr where
    fmap f (Var x) = Var (f x)
    fmap f (Lit x) = Lit x
    fmap f (Add x y) = Add (fmap f x) (fmap f y)
    fmap f (Mul x y) = Mul (fmap f x) (fmap f y)



--1.1
maybeAddition :: Maybe Int -> Maybe Int
maybeAddition x = fmap (+1) x


--1.2
listAddition :: [Int] -> [Int]
listAddition x = fmap (+1) x


--1.3
functorAddition :: Functor f => f Int -> f Int
functorAddition x = fmap (+1) x



--1.4
--(a)

safeDiv :: Int -> Int -> Maybe Int
safeDiv x y
    | y == 0 = Nothing
    | otherwise = Just (x `div` y)

qux :: Int -> Int -> Maybe Int
qux x y = fmap (*2) (safeDiv x y)



--(b)
quxList :: Int -> [Int] -> [Maybe Int]
quxList x [] = []
quxList x  (y : ys) = qux x y : quxList x ys


-- (c)
quxList' :: Int -> [Int] -> [Maybe Int]
quxList' x ys = fmap (qux x) ys



--1.5
-- renameExprs :: (String -> String) -> [Expr String] -> [Expr String]
-- renameExprs = fmap


-----------------------------------------------------------------------------------------------------

--2
(.>) = flip (.)

keepEvens :: [Int] -> [Int]
keepEvens xs = filter even xs

keepOdds :: [Int] -> [Int]
keepOdds xs = filter odd xs

--2.1
foo :: [Int] -> [Int]
foo = keepEvens .> map (*10)

--2.2
bar :: [Int] -> Int
bar = keepOdds .> map (+1) .> foldr (+) 0


--2.3
baz :: [[a]] -> [Int]
baz  = filter (\xs -> odd (length ))  .> map length

