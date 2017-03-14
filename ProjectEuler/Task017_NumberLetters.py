

SIMPLE = {
    0: 'zero',
    1: 'one',
    2: 'two',
    3: 'three',
    4: 'four',
    5: 'five',
    6: 'six',
    7: 'seven',
    8: 'eight',
    9: 'nine',
    10: 'ten',
    11: 'eleven',
    12: 'twelve',
    13: 'thirteen',
    14: 'fourteen',
    15: 'fifteen',
    16: 'sixteen',
    17: 'seventeen',
    18: 'eighteen',
    19: 'nineteen',
    1000: 'one thousand',
}

TENS = {
    2: 'twenty',
    3: 'thirty',
    4: 'forty',
    5: 'fifty',
    6: 'sixty',
    7: 'seventy',
    8: 'eighty',
    9: 'ninety',
}

HUNDRED = 'hundred', 'hundred'
THOUSAND = 'thousand', 'thousands'


def spell(N):
    if N in SIMPLE:
        return SIMPLE[N]

    if N >= 100:
        D, UNITS = N < 1000 and (100, HUNDRED) or (1000, THOUSAND)

        dv, rm = divmod(N, D)
        r = '%s %s' % (spell(dv), UNITS[int(dv > 1)])
        if rm != 0:
            r += ' and %s' % spell(rm)
        return r

    dv, rm = divmod(N, 10)

    if rm:
        return '%s %s' % (TENS[dv], spell(rm))
    return TENS[dv]


def get_letters(text):
    return sum(map(len, text.split()))


if __name__ == '__main__':
    r = 0
    for x in xrange(1, 1001):
        text = spell(x)
        print '[%3d]' % get_letters(text), text
        r += get_letters(text)

    print r