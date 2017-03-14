from contextlib import contextmanager
import time


@contextmanager
def timeIt(info):
    t0 = time.time()
    yield
    print '%s: %.2f' % (info, time.time() - t0)


def iterDividers(N):
    for k in xrange(2, N):
        if k * k > N:
            return

        d, r = divmod(N, k)
        if r != 0:
            continue

        yield k
        if d != k:
            yield d
