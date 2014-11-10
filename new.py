for i in xrange(10, 10 ** 9):
    j = ""
    for k in str(i):
        j += k + " "
    print './crazy ' + j  + ' | grep "^' + str(i) + ' " |head -1 &'
    if (i % 10 != 0):
        ii = str(i)[::-1]
        print './crazy ' + j[::-1]  + ' | grep "^' + str(i) + ' " |head -1'
