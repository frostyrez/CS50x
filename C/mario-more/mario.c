#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask for height
    int height = 1;
    do {
       height = get_int("Height: ");
    } while (height < 1 || height > 8);

    for (int i = 0; i <= height; i++) // For each row
    {
        for (int a = 0; a < (height-i); a++) // Put in height-i spaces at first
        {
            printf(" ");
        }
        for (int k = 0; k < 2; k++) // Loop twice
        {

            for (int j = 0; j < i; j++) // for j=1:i
            {
                printf("#");
            }
            if (k == 0)
            {
                printf(" "); // Put in a space between the loops
            }
        }
        printf("\n"); // New line after row is done
    }
}