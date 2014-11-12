from itertools import permutations

z = 0
for i in xrange(10 ** 8, 10 ** 10):
    j = ""
    seen = set()
    for k in permutations(str(i)):
        if (k[0] != '0'):
            if k not in seen:
                seen.add(k)
                z = (1 + z) % 2
                print './crazy ' + " ".join(list(k))  + ' | grep "^' + str(i) + ' " |head -1 ' + ('&' if z == 0 else '')
