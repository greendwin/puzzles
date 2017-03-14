

def fib():
    a, b = 1, 1
    yield a

    while True:
        yield b
        a, b = b, a + b


if __name__ == '__main__':
    for idx, val in enumerate(fib()):
        if len(str(val)) >= 1000:
            print idx + 1
            break