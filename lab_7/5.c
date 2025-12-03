#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    // char str[] = "ffaa sss haaaa aaaaaaaaafaaa ssaqaaaaaaaaaaaaaaaqqqqqqqh";
    int sum_a = 0;
    int max_sum_a = 0;
    int k = 0;
    char *arr = malloc(4);
    int prob = 0; 
    for (int i=0; i<sizeof(str);i++)
    {        
        if (str[i] == 'a')
        {
            sum_a++;
        }
        k++;
        if ((str[i] == ' ') || (i==strlen(str)-1))
        {
            prob = i;
            if (sum_a > max_sum_a)
            {
                max_sum_a =sum_a;
                char *tmp = realloc(arr, (k-1)*sizeof(char));
                if (tmp != NULL) 
                {
                    arr = tmp;
                    
                }
                int c=0;
                for (int j = i - k +1; j<i;j++)
                {
                    arr[c]=str[j];
                    c++;

                }                
            }
            k = 0;
            sum_a=0;

        }

    }

    
    printf("arr: %s\n",arr);
    free(arr);
    printf("%c",str[strlen(str)-1]);
    // printf("%ld  %d\n",sizeof(str),sum_a);
}