"""
Problem 24.

A permutation is an ordered arrangement of objects.
For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4.
If all of the permutations are listed numerically or alphabetically, we call it lexicographic order.
The lexicographic permutations of 0, 1 and 2 are:
    012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
"""
import math

from util import timeIt


def applyPerm(V, P):
    return [V[k] for k in P]


def iterPerms(N):
    if N == 1:
        yield [0]
        return

    if N == 2:
        yield [0, 1]
        yield [1, 0]
        return

    for k in xrange(N):
        rest = [t for t in xrange(N) if t != k]
        for p in iterPerms(N - 1):
            yield [k] + applyPerm(rest, p)


def run():
    with timeIt('*** Smart'):
        rest = range(10)
        N = 1000000 - 1     # count from 0
        r = [0] * 10
        for k in xrange(10):
            idx, N = divmod(N, math.factorial(9 - k))
            r[k] = rest.pop(idx)

        print ''.join(map(str, r))

    with timeIt('*** Basic'):
        for N, p in enumerate(iterPerms(10)):
            if N == 1000000 - 1:
                print ''.join(map(str, p))
                break

if __name__ == '__main__':
    run()