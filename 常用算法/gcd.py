# -*- encoding:gbk -*-

# 辗转相除求GCD LCM
# PYTHON 2

# greatest common divisor
def gcd(g,l):
    if l>g:
        g^=l
        l^=g
        g^=l
        
    while True:
        c=g%l
        if c==0:
            break
        g=l
        l=c
        
    return l

# least common multiple
def lcm(g,l):
    return g*l/gcd(g,l)

print gcd(15,24), lcm(12,15)
