#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Get Input
    string text = get_string("Text: ");

    // Count letters
    int i = 0;
    int l = 0; // letters
    int w = 1; // words
    int s = 0; // sentences
    do // Until end of string
    {
        // Count letters
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            l++;
        }
        // Count words
        if (text[i] == 32)
        {
            w++;
        }
        // Count sentences
        if ((text[i] == 33 || text[i] == 46) || text[i] == 63)
        {
            s++;
        }
        i++;
    } while (text[i] > 0);

    // printf("I count %i letters, %i words, and %i sentences\n",l,w,s);

    // Calculate Coleman-Liau index
    float L = l * 100.0 / w;
    float S = s * 100.0 / w;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Output it
    if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n",index);
    }
}