from operator import itemgetter
import urllib2


def getNames():
    r = urllib2.urlopen(r'http://projecteuler.net/project/resources/p022_names.txt')
    r = r.read()
    r = r.split(',')
    return map(itemgetter(slice(1, -1)), r)     # remove quotes


def score(name):
    ORD_A = ord('A')
    return sum(
        ord(ch) - ORD_A + 1
        for ch in name)


if __name__ == '__main__':
    lst = getNames()
    lst.sort()

    print sum(
        score(name) * (idx + 1)
        for idx, name in enumerate(lst))
