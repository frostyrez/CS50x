#include <stdio.h>
#include <math.h>

// void swap(int *a, int *b);

int main(void)
{
    // int x = 1;
    // int y = 2;

    // printf("x is %i, y is %i\n", x, y);
    // printf("%i is the int and %p is the address/pointer going into swap\n",x,&x);
    // swap(&x, &y);
    // printf("x is %i, y is %i\n", x, y);


// void swap(int *a, int *b)
// {
//     printf("%p %p\n",a,b);
//     int tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

  int i[2][2] = {1,0},{0,1};
  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < 2; k++) {
      printf("%i",i[j][k]);
    }
    printf("\n");
  }

}