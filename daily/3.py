class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def serialize(node):
    if node == None:
        return ""
    str = node.val + ":"
    str += "("
    str += serialize(node.left)
    str += ","
    str += serialize(node.right)
    str += ")"
    return str

def deserialize(str):
    if(str == ""):
        return None
    iColon = str.find(":")
    node = Node(str[:iColon])
    i = iColon + 2
    d = 0
    ij = i
    while not(d == 0 and str[ij] == ','):
        if str[ij] == '(':
            d += 1
        elif str[ij] == ')':
            d -= 1
        ij += 1
    j = ij + 1
    while not(d == 0 and str[j] == ')'):
        if str[j] == '(':
            d += 1
        elif str[j] == ')':
            d -= 1
        j += 1
    node.left = deserialize(str[i : ij])
    node.right = deserialize(str[ij+1 : j])
    return node


node = Node('root', Node('left', Node('left.left')), Node('right'))
print serialize(node)
print serialize(deserialize(serialize(node)))