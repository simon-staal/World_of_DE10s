import msvcrt

def getKey():
    inkey = msvcrt.getch()
    import sys
    for i in range(sys.maxsize):
        k=inkey()
        if k!='': break

    return k

def main():
    input = getKey()
    print(input)

if __name__ == "__main__":
    main()
