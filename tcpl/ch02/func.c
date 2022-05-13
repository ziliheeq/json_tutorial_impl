#include<stdio.h>
#include<ctype.h>

/* atoi: convert s to integer */
int atoi(char s[]) {
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <='9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}



int main() {
    char s[] = "912102";
    printf("res = %d\n", atoi(s));
    printf("num2 ? = %d\n", isdigit(2));

    return 0;
}
