from cs50 import get_int
import math

# Main function here
def main():
    while True: # ensure card is right length
        card = int(input("Card Number: "))
        #print(type(card))
        card_digits = len(str(card))
        if card_digits < 17:
            if card_digits < 13:
                print("INVALID")
            break

    counter = 0
    # Step 1
    for i in range(2,17,2):
        digit = get_digit(card,i)
        print(digit, end= " ")
        digit = digit * 2
        if digit > 9:
            digit = math.floor((digit % 10)) + math.floor((digit / 10))
        counter = counter + digit

    # Step 2
    for i in range(1,17,2):
        digit = get_digit(card,i)
        counter = counter + digit

    # Step 3
    print(counter)
    if (counter % 10) == 0:
        if get_digit(card,16) < 1:
            if get_digit(card,14) < 1:
                if get_digit(card,13) == 4:
                    print("VISA")
                else:
                    print("INVALID")
            elif get_digit(card,15) == 3:
                if get_digit(card,14) == 4 or get_digit(card,14) == 7:
                    print("AMEX")
                else:
                    print("INVALID")
            else:
                print("INVALID")
        elif get_digit(card,16) == 5 and get_digit(card,15) < 6:
            print("MASTERCARD")
        elif get_digit(card,16) == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def get_digit(card,idx):
    #print(card," ",idx)
    temp = card / 10**(idx-1)
    #print(temp)
    return math.floor(temp % 10)

main()