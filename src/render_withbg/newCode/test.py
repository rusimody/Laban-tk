from ctypes import *

test = CDLL("./test.so")

def main():
    a = 5
    b = 3
    c = test.addition(a,b)
    print(c)

if __name__=="__main__":
    main()
