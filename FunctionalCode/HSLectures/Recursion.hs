-- 5! = 5 * 4 * 3 * 2 * 1

fac5 = 5 * 4 * 3 * 2 * 1

fac5' = 5 * fac4

fac4 = 4 * 3 * 2 * 1


-- fac n = if n/= 1 then n * fac (n - 1) else 1
-- fac n is a recursive 

--but what if n is negative! it will continue removing one for infinity
fac n 
    = if n < 1 
        then error "input was negative" 
    else if n /= 1 
        then n * fac (n - 1) 
    else 1

--or
fac' n 
    = if n >= 1 
        then n * fac' (n - 1) 
    else 1

--or 
fac'' n 
    | n< 1 = error "input was negative" 
    | n /= 1 = n * fac'' (n - 1) 
    | otherwise = 1
