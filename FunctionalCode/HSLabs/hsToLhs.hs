import System.Directory.Extra
import System.Environment

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



main :: IO ()
main = do
    (x : y : xs) <- getArgs
    hsToLhs x y

