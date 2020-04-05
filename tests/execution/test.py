import sys

with open('testfile','w') as f:
    print(sys.argv[1], file=f)
    print(input(), file=f)
    print(input(), file=f)
    print(input(), file=f)


