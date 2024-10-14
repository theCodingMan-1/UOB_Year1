import System.Directory.Extra
import System.Environment
import Data.Bits (Bits(xor))


-- 1.1
helloWorld :: IO ()
helloWorld = putStrLn "Hello World!"


-- 1.2
greet :: IO ()
greet = do
    name <- getLine
    putStrLn ("Hello " ++ name)


-- 1.3
greetFormally :: IO ()
greetFormally = do
    putStrLn "What is you name"
    greet


-- 1.4
getInt :: IO Int
getInt = do
    num <- getLine
    pure (read num)

---------------------------------------------------------------

-- 2.1
addLineStart :: [String] -> [String]
addLineStart xs = addLineStart' [] xs
    where
        addLineStart' :: [String] -> [String] -> [String]
        addLineStart' list [] = reverse list
        addLineStart' list (x : xs) = addLineStart' ((">" ++ x) : list) xs



-- 2.2
addLineStartToContents :: String -> String
addLineStartToContents x = unlines (addLineStart (lines x))

-- 2.3
hsToLhs :: FilePath -> FilePath -> IO ()
hsToLhs hsFile lhsFile = do
    strFile <- readFile hsFile
    writeFile lhsFile (addLineStartToContents strFile)


-------------------------------------------------------------------------

-- 3.1
main :: IO ()
main = do
    number <- getInt
    playRound number


-- 3.2 
echoArgs :: IO ()
echoArgs = do
    args <- getArgs
    print (unwords args)


-- 3.3
-- See hsToLhs.hs


--------------------------------------------------------------

--4.1
playRound' :: Int -> Int -> IO ()
playRound' guess x
    | guess == x = putStrLn "You got it right"
    | guess < x = do
        putStrLn "Too low"
        playRound x
    | otherwise = do
        putStrLn "Too high"
        playRound x



playRound :: Int -> IO ()
playRound x = do
    guess <- getLine
    playRound' (read guess) x






