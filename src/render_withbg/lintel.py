import argparse
from ctypes import *

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-l',dest='lbn',help=".lbn file required",required=True)
    parser.add_argument('-r',dest='render',help="render flag required <r or n>",required=True)
    parser.add_argument('-s',dest='figure',help="figure flag required <m or f>",required=True)
    args = parser.parse_args() 
    cCode = CDLL("./linter.so")

if __name__=="__main__":
    main()


