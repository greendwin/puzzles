from collections import Counter


CACHE_D = {}


def divisors(N):
    for x in range(1, N):
        if N % x == 0:
            yield x


def d(N):
    try:
        return CACHE_D[N]
    except KeyError:
        r = CACHE_D[N] = sum(divisors(N))
        return r


def amicableNumbers(MAX_N):
    for N in range(2, MAX_N):
        if N != d(N) and N == d(d(N)):
            yield N


def run():
    print 'Sum:', sum(amicableNumbers(10000))


if __name__ == '__main__':
    # print d(284)
    # print d(220)
    run()
