from itertools import permutations

for i in xrange(10, 10 ** 10):
    j = ""
    seen = set()
    for k in permutations(str(i)):
        if (k[0] != '0'):
            if k not in seen:
                seen.add(k)
                print './crazy ' + " ".join(list(k))  + ' | grep "^' + str(i) + ' " |head -1 &'
