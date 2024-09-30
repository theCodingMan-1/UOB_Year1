-- 3.1
calcTip c = 
    if c > 10 
        then c * 0.15
    else
        c * 0.1

--3.2
mysterious n 
    | even n = div n 2
    | otherwise = (3 * n) + 1

--3.4
clamp lower upper num
    | num < lower = lower
    | num > upper = upper
    | otherwise = num

clamp' lower upper num = max lower (min upper num)


--3.5
function
    | happiness > 10 = "Hello!"
    | otherwise = goodbye
    where
        happiness = 10
        goodbye = "Goodbye"


--4.1
fact n 
    | n <= 1 = 1
    | otherwise =  n * fact(n - 1)

--4.2
fibonacci n
    | n <= 2 = 1
    | otherwise = (fibonacci (n - 1)) + (fibonacci (n - 2))

--4.3
divisor bigNum smallNum
    | (mod bigNum smallNum) == 0 = True
    | otherwise = False

anyDivisors bigNum smallNum
    | smallNum == 1 = False
    | (divisor bigNum smallNum) == True = True
    | otherwise = anyDivisors bigNum (smallNum - 1)

prime num
    | (anyDivisors num (num - 1)) == True = False
    | otherwise = True


--4.4

root n = helper n 0

helper n m
    | m ^ 2 >= n = m
    | otherwise = helper n (m + 1)


-- 4.5
mysterious' n
    | n == 1 = 0
    | otherwise = 1 + (mysterious' (mysterious n))