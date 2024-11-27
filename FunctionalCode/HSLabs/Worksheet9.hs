--1.1

import qualified Data.Map as M
import Graphics.Vty (Vty, Attr, Image, Picture, Event (..), Key(..))
import qualified Graphics.Vty as V
import Graphics.Vty.CrossPlatform (mkVty)


-- main :: IO()
-- main = do
--     --(1) get vty handle
--     vty <- mkVty V.defaultConfig

--     --(2) set mouse mode to true to have clickable app
--     V.setMode (V.outputIface vty) V.Mouse True

--     --(3) run game loop in the initial mode
--     gameLoopEg vty initModelEg
--     gameLoopEg :: Vty -> ModelEg -> IO ()
--     gameLoopEg vty model = error "TODO"





-- --1.2
-- type ModelEg = [String]

-- initModelEg :: ModelEg
-- initModelEg = []


-- --1.3
-- --(a)
-- -- V.picForImage (
-- --     V.vertCar
-- --         [V.string V.defAttr "Hello",
-- --         V.string V.defAttr "World!"
-- --         ]
-- -- )

-- view :: ModelEg -> Picture
-- view model =
--     V.picForImage (
--         V.vertCat $ map (V.string V.defAttr) ("Press Esc. to exit": model)

--     )



-- --(b) 
-- update :: V.Event -> ModelEg -> Maybe ModelEg
-- update (V.EvKey V.KEsc modifiers) model = Nothing
-- update event model = Just (show event : model)


--1.4
-- gameLoopEg :: Vty -> ModelEg -> IO()
-- gameLoopEg vty model = do
--     let picture = view model
--     V.update vty picture
--     event <- V.nextEvent vty
--     let newModel = update event model
--     if newModel == Nothing then pure ()
--     else gameLoopEg vty newModel



--2

type Model = M.Map (Int,Int) Cell
data Cell
    =Hidden Flag Mine
    | Revealed Int
    | Exploded
    deriving (Eq)
data Mine = Mine | NoMine deriving (Eq,Show)
data Flag = Flag | NoFlag deriving (Eq,Show)

--2.1
surroundingCords :: (Int, Int) -> [(Int, Int)]
surroundingCords (x, y) = [(i, j) | i <- [x - 1, x, x + 1], j <- [y - 1, y, y + 1]]

--2.2
-- counter :: [(Int, Int)] -> Int
-- counter ()

-- surroundingMines :: Model -> (Int, Int) -> Int

