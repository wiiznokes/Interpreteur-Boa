



def mod_x(x, mod):
    if (x == 0):
        return 0
    
    if (x < mod):
        return x
    else:
        return mod_x(x - mod, mod)

x = mod_x(19, 20)


print(x)