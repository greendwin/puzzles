
if __name__ == '__main__':
    N = 2 ** 1000
    S = 0
    while N:
        S += N % 10
        N /= 10
    print S