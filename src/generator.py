import sys
from random import randint

sys.stdout = open('input.txt', 'w')

def next_permutation(s):
    for i in range(len(s) - 1):
        if s[len(s) - i - 1] > s[len(s) - i - 2]:
            break
    else:
        s.reverse()
        return s

    i = len(s) - i - 2
    for j in range(len(s) - i - 1):
        if s[len(s) - j - 1] > s[i]: break
    j = len(s) - j - 1
    s[i], s[j] = s[j], s[i]
    ds = s[i+1:]
    ds.reverse()
    s = s[:i+1] + ds
    return s

def prev_permutation(s):
    for i in range(len(s) - 1):
        if s[len(s) - i - 1] < s[len(s) - i - 2]:
            break
    else:
        s.reverse()
        return s

    i = len(s) - i - 2
    for j in range(len(s) - i - 1):
        if s[len(s) - j - 1] < s[i]: break
    j = len(s) - j - 1
    s[i], s[j] = s[j], s[i]
    ds = s[i+1:]
    ds.reverse()
    s = s[:i+1] + ds
    return s

"""l = [1, 2, 2, 4]
for i in range(24):
    l = next_permutation(l)
    print(l)
for i in range(24):
    l = prev_permutation(l)
    print (l)
exit(0)"""

Q = 10
N = 10
ls = [randint(-30000, 30000) for _ in range(N)]
ans = []


print(N)
for v in ls:
    print(v, end=' ')
    print('')
    print(Q)
    for alsdf in range(Q):
        t = randint(6, 7)
        if t == 1:
            l, r = randint(0, len(ls) - 1), randint(0, len(ls) - 1)
            if l > r:
                l, r = r, l
            print(1, l, r)

            sum = 0
            for i in range(l, r + 1):
                sum += ls[i]

            ans.append(sum)
        elif t == 2:
            v, p = randint(-30000, 30000), randint(0, len(ls) - 1)
            print(2, v, p)
            ls.insert(p, v)
        elif t == 3:
            if len(ls):
                p = randint(0, len(ls) - 1)
                print(3, p)
                ls = ls[:p] + ls[p+1:]
            else:
                print(1, 0, 0)
        elif t == 4:
            v, l, r = randint(-30000, 30000), randint(0, len(ls) - 1), randint(0, len(ls) - 1)
            if l > r:
                l, r = r, l
            print(4, v, l, r)

            for i in range(l, r + 1):
                ls[i] = v
        elif t == 5:
            v, l, r = randint(-30000, 30000), randint(0, len(ls) - 1), randint(0, len(ls) - 1)
            if l > r:
                l, r = r, l
            print(5, v, l, r)

            for i in range(l, r + 1):
                ls[i] += v
        elif t == 6:
            l, r = randint(0, len(ls) - 1), randint(0, len(ls) - 1)
            if l > r:
                l, r = r, l
            print(6, l, r)

            ls = ls[:l] + next_permutation(ls[l:r+1]) + ls[r+1:]
        elif t == 7:
            l, r = randint(0, len(ls) - 1), randint(0, len(ls) - 1)
            if l > r:
                l, r = r, l
            print(7, l, r)

            ls = ls[:l] + prev_permutation(ls[l:r + 1]) + ls[r + 1:]

    print('RES:')
    for v in ans:
        print(v)
    for el in ls:
        print(el, end = ' ')