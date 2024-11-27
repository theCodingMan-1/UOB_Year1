module Hangman where

data Model = MkModel String Int [Char]

update :: Char -> Model -> Model
update c model@(MkModel word numGuesses guesses)
    | c `elem` guesses = model
    | c `elem` word = MkModel word numGuesses (c : guesses)
    | otherwise = MkModel word (numGuesses + 1) (c : guesses)


view :: Model -> String
view (MkModel word numGuesses guesses) = [x | x <- word, x `elem` guesses]


