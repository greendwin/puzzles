

def sum_sq_diff(N):
    X = sum(xrange(N + 1))
    Y = sum(p * p for p in xrange(N + 1))
    return X * X - Y


if __name__ == '__main__':
    print sum_sq_diff(100)