f = open("primes2.txt", "r")
ss = f.read()
ss = ss.split()
pp = [int(s) for s in ss]
s = None
ss = None
f.close()

#M1 = "First test\n"
#M2 = "Second text\n"
M1 = "First test\n"
M2 = "Second text\n"
C1 = """{h&�Ʀ?,/|�.F������Y2��Tc�{Xc�A�I��A>��K0���H�@2 ug�CI�1B
�����6�Nk7����-���{	�����c:z�sp����v��dAq�����)����J�"""
C2 = """ ����@l�ao��s�@l؈�*&�v��uCn�C)$v�(�<���e�����0Qg�/v�^��	\�͏�c�*}�:f����eVЯ��w�VZ��G��{��zI�
'���kW�LI��fB�,�"""

def pw(x,e,m):
    X = x
    E = e
    Y = 1
    while E > 0:
        if E % 2 == 0:
            X = (X * X) % m
            E = E/2
        else:
            Y = (X * Y) % m
            E = E - 1
    return Y

def strToInt(str):
    i = 0
    for c in str:
        i *= 256
        i += ord(c)
    return i

m1 = strToInt(M1)
m2 = strToInt(M2)
c1 = strToInt(C1)
c2 = strToInt(C2)

def cyf(m, e, n):

    return pw(m, e, n)

def solve():
    for ij in range(len(pp)):
        for i in range(ij//2+1):
            j = ij-i
            p = pp[i]
            q = pp[j]
            n = p*q
            for e in range(n):
                if e%p != 0 and e%q != 0:
                    if cyf(m1, e, n) == c1 and cyf(m2, e, n) == c2:
                        return p*q

print(solve())