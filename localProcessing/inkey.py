import msvcrt

def main():
    while 1:
        input = msvcrt.getch()
        output = input.decode('utf-8')
        print('Detected key: '+output)

if __name__ == "__main__":
    main()
