
PRIMES = []


def check_prime_inc(N):
    for x in PRIMES:
        if x * x > N:
            break

        if N % x == 0:
            return

    PRIMES.append(N)
    return N


if __name__ == '__main__':
    x = 1
    count = 0

    while True:
        x += 1
        if not check_prime_inc(x):
            continue

        # print x, PRIMES
        count += 1
        if count == 10001:
            print x
