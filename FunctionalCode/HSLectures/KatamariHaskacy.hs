module KatamariHaskacy where

import System.Directory.Extra


main :: IO ()
main = do 
    cmd <- getLine -- allows us to input something that stores it into a variable 'cmd'
    putStrLn ("Your input was: " ++ cmd)
    case cmd of 
        "look" -> do
            putStrLn "You are trying to look" -- similar to pattern matching i guess. The same as (*)
            files <- listFiles "."
            print files
        a -> putStrLn "Unrecognised input"
        -- "quit" -> putStrLn "hey"



printFileSizes :: [FilePath] -> IO ()
printFileSizes (file : files) = do
    printFileSize file
    printFileSizes files
printFileSizes [] = pure ()


printFileSize :: FilePath -> IO ()
printFileSize file = do
    size <- getFilesize file
    print file
    print size
    putStrLn (file ++ " : " ++ show size)


--(*)
-- foo "look" = putStrLn "You are trying to look"
-- foo "quit" = putStrLn "hey"
