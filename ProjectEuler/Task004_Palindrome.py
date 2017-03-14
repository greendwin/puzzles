

def is_palindrome(N):
    p = str(N)
    return p == ''.join(reversed(p))


def iterXY():
    for x in range(100, 1000):
        for y in range(100, 1000):
            yield x, y


if __name__ == '__main__':
    print max(x * y for x, y in iterXY() if is_palindrome(x * y))