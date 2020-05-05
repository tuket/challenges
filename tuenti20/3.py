# -*- coding: utf-8 -*-

f = open("text.txt", "r", encoding="utf-8")
s = f.read()
f.close()

s = s.lower()
s2 = u""
for i in range(len(s)):
	if s[i] in u"abcdefghijklmnopqrstuvwxyzáéíñóúü":
		s2 += s[i]
	else:
		s2 += u' '
s = s2.strip()
#print(s)

s2 = u""
prevWasSpace = False
for c in s:
	if c == u' ':
		if not prevWasSpace:
			s2 += u' '
		prevWasSpace = True
	else:
		s2 += c
		prevWasSpace = False

ss = s2.split(u' ')
#print(len(ss))

"""
queTimes = 0
for s in ss:
	if s == u'que':
		queTimes += 1
print(queTimes)
"""

m = {}
for s in ss:
	if len(s) >= 3:
		m[s] = 0

for s in ss:
	if len(s) >= 3:
		m[s] += 1

rank = [(v, k) for k, v in m.items()]
rank.sort(key=lambda r:(-r[0], r[1]))
#print(rank)

m = {}
for i in range(len(rank)):
	(v, k) = rank[i]
	m[k] = (i, v)

f = open("submitInput", "r", encoding="utf-8")
s = f.read()
ss = s.split('\n')

#print(m['fortunata'])

n = int(ss[0])
for i in range(1, n+1):
	s = ss[i]
	if s.isdigit():
		x = int(s)-1
		print("Case #" + str(i) + ": " + rank[x][1] + " " + str(rank[x][0]))
	else:
		print("Case #" + str(i) + ": " + str(m[s][1]) + " #" + str(m[s][0]+1))
