from operator import itemgetter

CACHE = {}


def collatzSeq(start):
    N = start
    count = 0
    while True:
        count += 1
        if N == 1:
            CACHE[start] = count
            return count

        # N0 = N
        N = 3 * N + 1 if N % 2 else N / 2
        # print 'Iter %d -> %d' % (N0, N)

        if N in CACHE:
            count += CACHE[N]
            CACHE[start] = count
            return count


def iterChains(MAX_N):
    for N in xrange(1, MAX_N):
        yield N, collatzSeq(N)


if __name__ == '__main__':
    print max(iterChains(1000000), key=itemgetter(1))