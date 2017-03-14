from collections import Counter


def iterRows(path):
    with open(path) as f:
        for line in f:
            yield map(int, line.strip().split())


def process(path):
    prev = Counter()
    next = Counter()

    for row in iterRows(path):
        for idx, val in enumerate(row):
            next[idx] = val + max(prev[idx], prev[idx - 1])

        next, prev = prev, next

    return max(prev.values())

if __name__ == '__main__':
    print process('task018_example.txt')
    print process('task018_input.txt')
    print process('task018_067_input.txt')