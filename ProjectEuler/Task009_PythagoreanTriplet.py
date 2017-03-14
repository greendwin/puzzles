

def iter():
    for C in xrange(1000):
        for B in xrange(C):
            for A in xrange(B):
                if A + B + C == 1000:
                    yield A, B, C


if __name__ == '__main__':
    r = [a * b * c for a, b, c in iter() if a * a + b * b == c * c]
    print r[0]