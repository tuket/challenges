def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair

def car(p):
    return p(lambda x, y: x)

def cdr(p):
    return p(lambda x, y: y)

print car(cons("a", "b"))
print cdr(cons("a", "b"))