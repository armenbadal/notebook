
def integral(a, b, f):
    d = (b - a) / 1e6

    s = 0
    while a < b:
        b0 = f(a)
        b1 = f(a + d)
        s += (b0 + b1) / 2.0 * d
        a += d

    return s


print(integral(0.0, 1.0, lambda x: x * x))

