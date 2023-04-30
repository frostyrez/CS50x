#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_digit(long card, int idx);

int main(void)
{
    long card = 0;
    do
    {
       card = get_long("Card Number: "); // Ask for card number
    } while (card > 10000000000000000);// || card < 1000000000000);

    if (card < 1000000000000)
    {
        return printf("INVALID\n");
    }

    int counter = 0;
        // Step 1
        for (int i = 2; i < 17; i = i+2)
        {
            int digit = get_digit(card,i);
            digit = digit * 2;
            if (digit > 9)
            {
                digit = floor((digit % 10)) + floor((digit / 10));
                // printf("double digit calculated is %i\n", digit);
            }
            counter = counter + digit;
            // printf("i = %i", i);
            // printf(", digit = %i", digit);
            // printf(", counter = %i\n", counter);
        }

        // Step 2
        for (int i = 1; i < 17; i = i+2)
        {
            int digit = get_digit(card,i);
            counter = counter + digit;
            // printf("i = %i", i);
            // printf(", digit = %i", digit);
            // printf(", counter = %i\n", counter);
        }

        // Step 3
        if (counter % 10 == 0)
        {
            if (get_digit(card,16) < 1)
            {
                if (get_digit(card,14) < 1)
                {
                    if (get_digit(card,13) == 4)
                    {
                        printf("VISA\n");
                    }
                    else
                    {
                    printf("INVALID\n");
                    }
                }
                else if (get_digit(card,15) == 3)
                {
                    if (get_digit(card,14) == 4 || get_digit(card,14) == 7)
                    {
                        printf("AMEX\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                }
                else
                {
                printf("INVALID\n");
                }
            }
            else if (get_digit(card,16) == 5 && get_digit(card,15) < 6)
            {
                printf("MASTERCARD\n");
            }
            else if (get_digit(card,16) == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
}

int get_digit(long card, int idx)
{
    long temp = card / pow(10,idx-1);
    return (temp % 10);
}