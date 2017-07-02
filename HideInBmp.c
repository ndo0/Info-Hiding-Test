#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
	FILE *in, *out;
	char inFileName[90], outFileName[90], *plain, str[90];

	/* input plain text and store in str */
	printf("Input plain text: ");
	scanf("%s", &str);
	plain = str;

	/* input source file name(same root) */
	printf("Input your inFileName: ");
	scanf("%s", &inFileName);

	/* input output file name(same root) */
	printf("Input your outFileName: ");
	scanf("%s", &outFileName);

	/* initialize in & out and check */
	in = fopen(inFileName, "rb");
	out = fopen(outFileName, "wb");
	assert(in);
	assert(out);

	/* char2bin */
	char *temp = (char *)malloc(8 * strlen(str));
	for (int m = 0; m < strlen(str); m++, plain++) {
		for (int n = 0; n < 8; ++n){
			temp[8 * m + n] = 0x01 & ((*plain) >> n);
		}
	}

	/* insert secret data */
	for (int i = 0, j = 0; !feof(in); ++i) {
		if (i < 54) {
			fputc(fgetc(in), out);
		} else {
			if (j < 8 * strlen(str)){
				fputc((fgetc(in) & 0xfe) + temp[j], out);	
			} else {
				fputc(fgetc(in) & 0xfe, out);
			}
			j++;
		}
	}

	fclose(in);
	fclose(out);

	return 0;
}
