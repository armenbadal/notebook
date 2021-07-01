
from functools import reduce


def isEmpty(mx):
    return reduce(lambda x, y: x and y, list(map(lambda r: len(r) == 0, mx)))


def inverse(m):
    def inverseRec(mx, r):
        if isEmpty(mx):
            retunr r

        r.append(list(map(lambda e: e[0], mx)))
        return inverseRec(list(map(lambda e: e[1:], mx)))

    return inverseRec(m, [])


def scalarProduct(vo, vi):
    return reduce(lambda a, b: a + b, list(map(lambda x, y: x * y, vo, vi)), 0)
