import math

MAX_N = 20


CALC = [None] * ((MAX_N + 1) * (MAX_N + 1))
CALC[0] = 1

X_RANGE = xrange(MAX_N + 1)


def calc(X, Y):
    if X not in X_RANGE or Y not in X_RANGE:
        return 0

    idx = X * MAX_N + X + Y
    r = CALC[idx]

    if not r:
        r = calc(X - 1, Y) + calc(X, Y - 1)
        CALC[idx] = r

    return r


if __name__ == '__main__':
    print calc(MAX_N, MAX_N)
    print math.factorial(2 * MAX_N) / math.factorial(MAX_N) / math.factorial(MAX_N)