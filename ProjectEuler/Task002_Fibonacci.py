

MAX_VALUE = 4000000


def fib():
    a, b = 1, 2
    yield a

    while b <= MAX_VALUE:
        yield b
        a, b = b, a + b


if __name__ == '__main__':
    print sum(x for x in fib() if x % 2 == 0)