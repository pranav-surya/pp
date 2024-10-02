#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b)
{
	a = abs(a);
	b = abs(b);
	if (!a && !b) { return 0; }
	while (b) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

void compress_numbers(void)
{
	int total_bits = 10000000;
	int integer_size = 64;
	int buffer_size = (total_bits / integer_size) + 1;
	int mask = integer_size - 1;
	uint64_t* buffer = (uint64_t*)calloc(buffer_size, sizeof(uint64_t));
	int input_line_size = (integer_size / 8) + 1;
	char input_line[input_line_size];

	FILE* fp = fopen("/Users/prsurya/Desktop/pp/10_million_numbers.txt", "r");
    if (fp == NULL) {
    	printf("%s\n", "Input file could not be opened");
    	exit(EXIT_FAILURE);
    }
    uint64_t integer_bit_pos;
    int buffer_index;
    uint64_t number;
    while (fgets(input_line, input_line_size, fp) != NULL) {
    	input_line[strcspn(input_line, "\n\r")] = '\0';
    	number = atoll(input_line);
		integer_bit_pos = number & mask;
		buffer_index = number / integer_size;
		buffer[buffer_index] = buffer[buffer_index] | (1LL << integer_bit_pos);
    }
	fclose(fp);

	fp = fopen("/Users/prsurya/Desktop/pp/10_million_numbers_compressed.txt", "w");
    if (fp == NULL) {
    	printf("%s\n", "Output file could not be opened");
    	exit(EXIT_FAILURE);
    }
    for (number = 0; number < total_bits; number++) {
    	integer_bit_pos = number & mask;
    	buffer_index = number / integer_size;
    	if (buffer[buffer_index] & (1LL << integer_bit_pos)) {
    		fprintf(fp, "%llu\n", number);
    	}
    }
	fclose(fp);

	free(buffer);
}

int main(void)
{
	compress_numbers();
	return 0;
}