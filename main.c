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

void reverse(char* array, int array_size, int l, int r)
{
	if (l < 0)
		l = 0;

	if (r >= array_size)
		r = array_size-1;

	for (;l < r; l++, r--) {
		char t = array[l];
		array[l] = array[r];
		array[r] = t;
	}
}

void rotate_left(char* array, int array_size, int rotate_by)
{
	rotate_by = rotate_by % array_size;
	reverse(array, array_size, 0, rotate_by-1);
	reverse(array, array_size, rotate_by, array_size-1);
	reverse(array, array_size, 0, array_size-1);
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
		buffer[buffer_index] = buffer[buffer_index] | (1LLU << integer_bit_pos);
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
    	if (buffer[buffer_index] & (1LLU << integer_bit_pos)) {
    		fprintf(fp, "%llu\n", number);
    	}
    }
	fclose(fp);

	free(buffer);
}

int binary_search(int* array, int array_size, int number)
{
	int l = 0;
	int r = array_size-1;
	int m;
	while (l <= r) {
		m = l + (r-l)/2;
		printf("l = %d | m = %d | r = %d\n", l, m, r);
		if (array[m] == number) {
			return 1;
		} else if (number < array[m]) {
			r = m-1;
		} else {
			l = m+1;
		}
	}
	return 0;
}

int main(void)
{
	int array[] = {1, 2, 3, 4, 5, 6, 7};
	int array_size = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < array_size; ++i)
	{
		printf("search result = %d\n", binary_search(array, array_size, i+19));
	}
	return 0;
}