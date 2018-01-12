#include <stdio.h>
#include <string.h>

/* This program gives "root" for input sizes >= 16, as expected. That is:
 * This doesn't work:   123456789012345
 * But this does:       1234567890123456
 */

int main(void)
{
    char buff[15];
    char pass = 0;

    printf("Enter the password: ");
    gets(buff);                 // This allows buffer overflows.
    // fgets(buff, 15, stdin);  // This prevents them.

    if (strcmp(buff, "thegeekstuff")) {
        printf("Wrong Password\n");
    } else {
        printf("Correct Password\n");
        pass = 1;
    }
    printf("pass is 0x%x, or ascii character %c\n", pass, pass);

    if (pass) {
        printf("Root privileges granted\n");
    }

    return 0;
}
