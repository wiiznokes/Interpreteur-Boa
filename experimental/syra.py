

def syracuse(n):
    if n == 1 :
        return 0
    elif n % 2 == 0 :
        return syracuse(n/2) + 1
    else :
        return syracuse(3*n+1) + 1


a = syracuse(40)

print(a)