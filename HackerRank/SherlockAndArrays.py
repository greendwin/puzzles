#!/usr/bin/env python

# link: https://www.hackerrank.com/challenges/sherlock-and-array


def find_middle_elem(A):
    left = 0
    right = sum(A)

    for x in A:
        # remove from right sum
        right -= x

        # check whether it is a middle element
        if left == right:
            return True

        # move next
        left += x


def run():
    T = int(raw_input())

    for testN in xrange(T):
        N = int(raw_input())
        line = raw_input()  # numbers
        A = map(int, line.split())

        if find_middle_elem(A):
            print 'YES'
        else:
            print 'NO'


if __name__ == '__main__':
    run()
