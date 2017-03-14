
PRIMES = []


def check_prime_inc(N):
    for x in PRIMES:
        if x * x > N:
            break

        if N % x == 0:
            return

    PRIMES.append(N)
    return N


def iter_primes(N):
    for x in xrange(2, N):
        if check_prime_inc(x):
            yield x

if __name__ == '__main__':
    print sum(iter_primes(2000000))
