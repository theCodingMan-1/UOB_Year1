data ZipList a = ZL [a] a [a] deriving (Eq, Show)


newZipList :: a -> ZipList a
newZipList x = ZL [] x []


fromList :: [a] -> ZipList a
fromList (x : xs) = ZL [] x xs

toList :: ZipList a -> [a]
toList (ZL bs x fs) = bs ++ x:fs



isSingleton :: ZipList a -> Bool
isSingleton (ZL [] x []) = True
isSingleton _ = False



after :: ZipList a -> ZipList a
after (ZL bs x (f : fs)) = ZL (x : bs) f fs