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
fromMaybe y Nothing = y


-- 1.3
forget :: Either String a -> Maybe a
forget (Right y) = Just y


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

------------------------------------------------------------------------------

-- 2.1 (a)

data Expr = Lit Int
    | Add Expr Expr
    | Mul Expr Expr
    | Sub Expr Expr

size :: Expr -> Int
size (Lit x) = 0 -- stands for the literal value of a number
size (Add x y) = size x + size y + 1
size (Mul x y) = size x + size y + 1
size (Sub x y) = size x + size y + 1
-- The expression {Add [Add (Lit 5) (Lit 7)] [Mul (Lit 4) (Lit 2)]}
-- will be split into size (Add (Lit 5) (Lit 7)) + size (Mul (Lit 4) (Lit 2)) + 1
-- which splits into (size (Lit 5) + size (Lit 7) + 1) + (size (Lit 4) + size (Lit 2) + 1) + 1
-- which goes to (0 + 0 + 1) + (0 + 0 + 1) + 1
-- which equals 3


--2.1 (b)
eval :: Expr -> Int
eval (Lit x) = x
eval (Add x y) = eval x + eval y
eval (Mul x y) = eval x * eval y
eval (Sub x y) = eval x - eval y


-- 2.1 (c)


pretty :: Expr -> String
pretty (Lit x) = show x
pretty (Add x y) = pretty x ++ " + " ++ pretty y
pretty (Mul x y) = pretty x ++ " x " ++ pretty y
pretty (Sub x y) = pretty x ++ " - " ++ pretty y


-- 2.2 -- adding the sub constructor to the functions above.

-----------------------------------------------------------------------



-- 3.1 (a) (b) (c)
addTwo :: Num a => a -> a
addTwo x = x + 2


-- 3.2

data RPS = Rock | Paper | Scissors deriving (Show, Eq)
-- Eq -> Checks whether two values of type RPS are equal.

shoot :: RPS -> RPS -> Bool

shoot x y
    | (x == Rock) && (y == Scissors) = True
    | (x == Paper) && (y == Rock) = True
    | (x == Scissors) && (y == Paper) = True
    | otherwise = False



-- 3.3
instance Ord RPS where

    Scissors <= Rock = True
    Paper <= Scissors = True
    Rock <= Paper = True
    player1 <= player2 = player1 == player2





--4.1
data Suit = Hearts | Diamonds | Clubs | Spades deriving (Show, Eq)
type Pip = Int
type Rank = Either Pip Court
data Card = Joker | Card Suit Rank deriving Show

data Court = Ace | Jack | Queen | King deriving (Show, Eq, Ord)


--4.2
instance Eq Card where
    Joker == Joker = True
    (Card s1 r1) == (Card s2 r2) = s1 == s2 && r1 == r2


--4.3
snap :: Card -> Card -> String
snap Joker Joker = "SNAP"
snap (Card s1 r1) (Card s2 r2)
    | r1 == r2 = "SNAP"
    | otherwise = "..."
snap x y = "..."


--4.4
instance Ord Card where
    card <= Joker = True
    Joker <= card = False
    (Card s r) <= (Card s' r')
        | s' == Spades && s != Spades = True
        | s' != Spades && s == Spades = False
        | s' == Hearts && s != Hearts = True
        | s' != Hearts && s == Hearts = False
        | otherwise = f <= f'



play :: [Card] -> Card -> Maybe Card
play [] y = Nothing
play (x : xs) y
    | x >= y = Just x
    | otherwise = play xs y
