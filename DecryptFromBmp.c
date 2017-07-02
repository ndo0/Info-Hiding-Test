#include "stdio.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
	FILE *in;
	char inFileName[90];
	int single;

	/* input encrypted file name, open file and check */
	printf("Input inFileName: ");
	scanf("%s", &inFileName);
	in = fopen(inFileName, "rb");
	assert(in);

	/* skip first 54bit of data(bmp headers) */
	fseek(in, 54L, 0);

	/* retrieve date, 1bit plain in every 8bit */
	do {
		single = 0;
		for (int i = 0; i < 8; i++) {
			single = single + ((fgetc(in) & 0x01) << i);
		}
		putchar(single);
	} while (single);
	putchar('\n');

	fclose(in);
	
	return 0;
}
