from collections import Counter


def factors(N):
    assert N > 0

    r = Counter()
    for x in xrange(2, N + 1):
        while N % x == 0:
            r[x] += 1
            N /= x

        if N == 1:
            return r


def update_max(dst, src):
    for k, v in src.items():
        if dst[k] < v:
            dst[k] = v


if __name__ == '__main__':
    r = Counter()
    for x in range(2, 21):
        update_max(r, factors(x))

    N = 1
    for x, p in r.items():
        N *= x ** p

    print N