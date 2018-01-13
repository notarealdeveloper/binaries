#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main() {

	char str[]="Hi\nSup Guys?\n";
	write(0, str, strlen(str));
	return 0;
}
