f = open("in.txt", "r")
s = f.read()
f.close()



m = {}
for c in s:
    m[c] = 0

for c in s:
    m[c] += 1
pp = [(a, b) for a, b in m.items()]
print(sorted(pp, key = lambda p: -p[1]))

m = {
	' ' : ' ',
	'\n' : '\n',
	'0' : '0',
	'1' : '1',
	'2' : '2',
	'3' : '3',
	'4' : '4',
	'5' : '5',
	'6' : '6',
	'7' : '7',
	'8' : '8',
	'9' : '9',
	'.' : 'e',
	'y' : 't',
	'd' : 'h',
	'a' : 'a',
	'r' : 'o',
	',' : 'w',
	'p' : 'r',
	'o' : 's',
	'b' : 'n',
	'u' : 'f',
	'c' : 'i',
	'j' : 'c',
	'i' : 'g',
	'n' : 'l',
	'e' : 'd',
	'x' : 'b',
	'm' : 'm',
	'l' : 'p',
	'f' : 'y',
	"'" : 'q',
	'g' : 'u',
	'k' : 'v',
	'-' : "'",
	'w' : ',',
	'v' : '.',
	't' : 'k',
	'(' : '(',
	')' : ')',
	'q' : 'x',
	'h' : 'j',
	';' : 'z',
	'z' : '/',
	's' : ';'
	#'b' : 'i',
}

def ts(m, a):
    b = ""
    for i in range(len(a)):
            if a[i] in m:
                    b += m[a[i]]
            else:
                    b += '*'
    return b
"""
f = open("out.txt", "w")
f.write(ts(m, s))
f.close()
"""

f = open("out.txt", "w")
ss = s.split("\n")
n = int(ss[0])
res = ""
for i in range(1, n+1):
	res += "Case #" + str(i) + ": " + ts(m, ss[i]) + "\n"
f.write(res)
f.close()