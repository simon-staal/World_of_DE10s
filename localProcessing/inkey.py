import msvcrt

def main():
    while 1:
        input = msvcrt.getch()
        if input == b'\x1b': break
        output = input.decode('utf-8')
        print('Detected key: '+output)
    print("Program terminated")

if __name__ == "__main__":
    main()
