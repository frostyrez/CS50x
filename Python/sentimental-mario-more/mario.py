from cs50 import get_int

def main():
    while True:
        height = get_int("Height: ")
        if height >= 1 and height < 9:
            break
    print_mario(height)

def print_mario(height):
    for i in range(height):
        i += 1
        print(" "*(height-i),end="")
        print("#"*i,"","#"*i)

main()