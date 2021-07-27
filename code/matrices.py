
from functools import reduce

def transpose2(mx):
    columnsCount = len(mx[0])
    columnAsVector = lambda n: list(map(lambda e: e[n], mx))
    return list(map(columnAsVector, range(columnsCount)))

def scalarProduct(vo, vi):
    return reduce(lambda a, b: a + b, list(map(lambda x, y: x * y, vo, vi)), 0)

def multiplyMatrices(mo, mi):
    pass




# examples
m0 = [[1], [2], [3], [4]]
m1 = [[1, 2, 3, 4]]



if __name__ == '__main__':
    t0 = transpose2(m0)
    print(t0)

    t1 = transpose2(m1)
    print(t1)

