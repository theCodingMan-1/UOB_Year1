>import System.Directory.Extra
>
>
>-- 1.1
>helloWorld :: IO ()
>helloWorld = putStrLn "Hello World!"
>
>
>-- 1.2
>greet :: IO ()
>greet = do
>    name <- getLine
>    putStrLn ("Hello " ++ name)
>
>
>-- 1.3
>greetFormally :: IO ()
>greetFormally = do
>    putStrLn "What is you name"
>    greet
>
>
>-- 1.4
>getInt :: IO Int
>getInt = do
>    num <- getLine
>    pure (read num)
>
>---------------------------------------------------------------
>
>-- 2.1
>addLineStart :: [String] -> [String]
>addLineStart xs = addLineStart' [] xs
>    where
>        addLineStart' :: [String] -> [String] -> [String]
>        addLineStart' list [] = reverse list
>        addLineStart' list (x : xs) = addLineStart' ((">" ++ x) : list) xs
>
>
>
>-- 2.2
>addLineStartToContents :: String -> String
>addLineStartToContents x = unlines (addLineStart (lines x))
>
>-- 2.3
>hsToLhs :: FilePath -> FilePath -> IO ()
>hsToLhs hsFile lhsFile = do
>    strFile <- readFile hsFile
>    writeFile lhsFile (addLineStartToContents strFile)
>
>
