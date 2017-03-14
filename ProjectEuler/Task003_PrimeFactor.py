from math import sqrt

def largest_prime_factor(N):
    for x in xrange(2, int(sqrt(N)) + 1):
        while N % x == 0:
            N /= x
        if N == 1:
            return x

if __name__ == '__main__':
    print largest_prime_factor(600851475143)