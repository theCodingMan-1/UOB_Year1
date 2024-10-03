
func :: [Int] -> Int
func [] = 0
-- if the input matches the pattern func [], the empty list, 0 is returned

func (x : xs) = 1 + func xs 
-- if the input matches the pattern func [xs] where xs stands for a list, it will recursively call itself
  -- adding one each time. This calculates the length of the list.
  -- Here x is the first element and xs is the rest of the list.
  
-- Example: func ['a', 'b', 'c'] 
  -- = 1 + func ['b', 'c']
  -- = 1 + (1 + func ['c'])
  -- = 1 + (1 + (1 + func []))
  -- = 1 + (1 + (1 + 0))
  -- = 1 + (1 + (1))
  -- = 1 + (2)
  -- = 3


fac :: Int  -> Int
fac n
  | n < 1 = error "input was negative"
  | n /=1 = n * fac (n - 1)
  | otherwise = 1

fac' :: Int -> Int
fac' 3 = 123456789 -- if 'fac' 3' is typed, '123456789' is returned
fac' n = fac n -- if 'fac' n' is typed where n stands for any number, then it returns 'fac n'

-- in pattern matching you are matching the a function to another but changing some aspects



-- lists



sum' :: [Int] -> Int
sum' [] = 0 -- in case of the empty list, it returns 0 (base case)
sum' (x : []) = x -- in case of one element, it returns the single element
sum' (x : xs) = x + sum' xs  -- in case of more than one element, it returns the first element, plus sum' of the rest of the list
-- xs stands for the rest of the list. 




