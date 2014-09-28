#include <stdio.h>
 
 int main(void)
 {
    int n; /* calculate from 1! to n! */
              
    /* Read n */
    printf("Enter n: ");
    scanf("%d", &n);
                               
    if ((n < 1) || (n > 12)) {
        printf("Number out of range.\n");
        return -1;
    }
                                                          
    /* Calculate 1! to n! Insert your code here */
    int i, j;
    printf("1 = 1\n");
    for (i = 2; i <= n; i++)
    {
        unsigned int factorial = 1;
        printf("1 ");
        for(j = 2; j <= i; j++)
        {
            printf("* %d ", j);
            factorial *= j;
        }
        printf("= %d\n", factorial);
    }
    return 0;
}
