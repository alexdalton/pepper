#include <stdio.h>

int main(void)
{
    int value1, value2; /* Calculate GCF of value1 and value2 */

    /* Read value1 and value2 */
    printf("Enter two positive integers: ");
    scanf("%d%d", &value1, &value2);

    if (value1 < 1 || value2 < 1)
    {
        printf("Invalid value\n");
        return -1;
    }

    /* Find and print the GCF of value1 and value2
       Insert your code here */
    int loopCount, i, currentGCF;
    if (value1 < value2)
        loopCount = value1;
    else
        loopCount = value2;
    for (i = 1; i <= loopCount; i++)
    {
        if (!(value1 % i) && !(value2 % i))
        {
            currentGCF = i;
        }
    }
    printf("The GCF of %d and %d is %d\n", value1, value2, currentGCF);
    return 0;
}
