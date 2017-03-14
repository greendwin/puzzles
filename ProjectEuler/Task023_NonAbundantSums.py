"""
Problem 23

A perfect number is a number for which the sum of its proper divisors is exactly equal to the number.
For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28,
which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n
and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number
that can be written as the sum of two abundant numbers is 24. By mathematical analysis,
it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers.
However, this upper limit cannot be reduced any further by analysis even though it is known
that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
"""
from util import iterDividers

MAX_N = 28123 + 1
ABUNDANT = []
ABUNDANT_SET = set()


def isAbundant(N):
    return N < sum(iterDividers(N))


def isExprBySum(N):
    for X in ABUNDANT:
        if X > N // 2:
            return

        if N - X in ABUNDANT_SET:
            return X, N - X


def run():
    global ABUNDANT, ABUNDANT_SET

    ABUNDANT = [
        k for k in xrange(MAX_N)
        if isAbundant(k)]
    ABUNDANT_SET = set(ABUNDANT)

    # for X in ABUNDANT[:30]:
    #     print X, sum(iterDividers(X)), sorted(iterDividers(X))

    # for X in xrange(100):
    #     p = isExprBySum(X)
    #     if p:
    #         print X, '=', p[0], '+', p[1]

    print sum(X for X in xrange(MAX_N)
              if not isExprBySum(X))

if __name__ == '__main__':
    run()