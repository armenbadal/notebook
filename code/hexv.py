
def oHex(num):
    c = "0123456789abcdef"[num % 16]

    return c if num < 16 else oHex(num // 16) + c


def rHex(num, r):
    c = "0123456789abcdef"[num % 16]
    return c if num < 16 else rHex(num // 16, c + r) 



print(oHex(0))
print(oHex(1))
print(oHex(16))
print(oHex(127))
print(oHex(256))

print("012345"[2])

