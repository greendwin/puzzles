from collections import Counter


def factors(N):
    assert N > 0

    r = Counter()
    for x in xrange(2, N + 1):
        while N % x == 0:
            r[x] += 1
            N /= x

        if N == 1:
            break
    return r


def num_divisors(F):
    r = 1
    for x, k in F.items():
        r *= (k + 1)
    return r


if __name__ == '__main__':
    N = 0
    for x in xrange(1, 1000000):
        N += x
        f = factors(N)
        # print N, num_divisors(f)
        if num_divisors(f) > 500:
            print N
            break