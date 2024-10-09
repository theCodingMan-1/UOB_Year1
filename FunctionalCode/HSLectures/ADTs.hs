module ADTs where
--import Prelude hiding (Bool(..)) -- since Bool is already a type we hide it


type User = (Int, String) -- creating a custom type

egUser :: User
egUser = (20, "Greg")

data User' = MkUser' Int String

egUser' :: User'
egUser' = MkUser' 20 "Greg"

getAge :: User' -> Int
getAge (MkUser' age name) = age


-- data Bool = True | False
--     deriving Show

egBool :: Bool
egBool = True
egBool2 = False


ifE :: Bool -> a -> a -> a
ifE True x y = x
ifE False x y = y


data User'' = MkUser'' Int String 
            | Anon Cookie

type Cookie = String

loggedIn :: User'' -> Bool
loggedIn (MkUser'' _age _name) = True
loggedIn (Anon _) = False


getAge' :: User'' -> Int
getAge' (MkUser'' age name) = age
getAge' (Anon cookie) = error "no name available"



data Maybe a = Just a | Nothing

-- getAge'' :: User'' -> Maybe Int
-- getAge'' (MkUser'' age name) = Just age
-- getAge'' (Anon cookie) = Nothing

