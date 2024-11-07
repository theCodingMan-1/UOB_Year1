
plus1 :: Num a => a -> a
plus1 x = x + 1

mapMaybe :: (a -> b) -> Maybe a -> Maybe b
mapMaybe f Nothing  = Nothing
mapMaybe f (Just x) = Just x





class Functor f where
    fmap :: (a -> b) -> f a -> f b


instance Functor Maybe where
    fmap :: (a -> b) -> Maybe a -> Maybe b
