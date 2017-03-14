"""
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
"""


def daysInYear(N):
    r = 30 * 4      # sep, apr, jun, nov
    r += 31 * 7     # rest except feb
    r += 28
    r += N % 4 == 0 and N % 100 != 0 or N % 400 == 0
    return r


def daysInMonth(M, Y):
    # jan feb mar apr may jun jul aug sep oct nov dec
    # 0   1   2   3*  4   5*  6   7   8*  9   10* 11
    if M in [3, 5, 8, 10]:
        return 30

    if M == 1:
        if Y % 4 == 0 and Y % 100 != 0 or Y % 400 == 0:
            return 29
        return 28

    return 31


def run():
    N = 0
    for Y in xrange(1901, 2000 + 1):
        for M in xrange(12):
            D = sum(daysInYear(Yk) for Yk in xrange(1900, Y))      # prev years
            for Mk in xrange(M):
                D += daysInMonth(Mk, Y)
            N += (D + 1) // 7 - D // 7
    print N

if __name__ == '__main__':
    run()
