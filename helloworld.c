#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//TEST

#define START_VAL 1 // Start value for checking power (Used in calcLogOfNumber). Should remain 1.
#define TEST_NUM 2 // Powers of this number are checked.
#define PARITAL_POWER_INDICATOR -1 // Value to indicate the number is not a whole power of TEST_NUMBER.
#define ARRAY_PLACEHOLDER -1 // Used to indicate element is not valid.

// Tokens comment
bool getInputSize(int* size);
bool getInputArray(int* array, int* powers, int size, int* power_count);

int calcLogOfNumber(int num, int base);

void printInputRequest();
void printInvalidSize();
void printEnterNumber();
void printInvalidNumber();
void printEndMessage(int* array, int* powers, int size, int power_count);

// End tokens

int main()
{
	int input_size, power_count = 0;
	int* input_numbers = NULL;
	int* powers = NULL;

	bool error = false;

	error = !getInputSize(&input_size); // Step 1+2, receive input for size and handle invalid input
	if (!error) // If no error occured,		proceed to defining arrays
	{
		input_numbers = malloc(sizeof(int) * input_size);
		powers = malloc(sizeof(int) * input_size);
		if (input_numbers == NULL || powers == NULL)
		{
			error = true;
		}
	}
	if (!error) // If no error occured, procced to input numbers
	{
		error = !getInputArray(input_numbers, powers, input_size, &power_count); // Step 3
	}
	if (!error) // This is a comment
	{
		printEndMessage(input_numbers, powers, input_size, power_count); // Step 4
	}
	free(input_numbers); //prevent memory leak
	free(powers); //prevent memory leak
	return 0;
}
// Recives input for array size. returns bool whether input is valid
bool getInputSize(int* size)
{
	printInputRequest();
	if (scanf("%d", size) == 0 || *size <= 0) // Receive invalid input, or less/eq 0 W/lazy evaluation
	{
		printInvalidSize();
		return false;
	}
	return true;
}

// Receives all numbers according to size and checks if they are a whole power of TEST_NUMBER.
// Also sums power_count
bool getInputArray(int* array, int* powers, int size, int* power_count)
{ // Nice comment
	printEnterNumber();
	for (int i = 0; i < size; i++)
	{
		int temp_num;
		int power;

		if (scanf("%d", &temp_num) == 0) // Invalid input
		{
			printInvalidNumber();
			return false;
		}
		power = calcLogOfNumber(temp_num, TEST_NUM); // Assign value returned to power
		if (power != PARITAL_POWER_INDICATOR)
		{
			*power_count += power;
			powers[i] = power;
			array[i] = temp_num;
		}
		else
		{
			powers[i] = ARRAY_PLACEHOLDER;
			array[i] = ARRAY_PLACEHOLDER;
		}
	}
	return true;
}
// Calculates logarithm of TEST_NUMBER. Returns -1 if it is not a whole number
int calcLogOfNumber(int num, int base)
{

	if (num <= 0)
	{
		return PARITAL_POWER_INDICATOR;// default=-1 for indicating that the number is not a whole power of two.
	}
	int power = 0;
	int incrementing_num = START_VAL; // Should start from 1
	while (incrementing_num < num)
	{
		incrementing_num *= base;
		power++;
	}

	return incrementing_num == num ? power : PARITAL_POWER_INDICATOR;
}

// Print functions
void printInputRequest()
{
	printf("Enter size of input:\n");
}
void printInvalidSize()
{
	printf("Invalid size\n");
}
void printEnterNumber()
{
	printf("Enter numbers:\n");
}
void printInvalidNumber()
{
	printf("Invalid number\n");
}
void printEndMessage(int* array, int* powers, int size, int power_count)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == ARRAY_PLACEHOLDER)
		{
			continue;
		}
		printf("The number %d is a power of %d: %d = 2^%d\n", array[i], TEST_NUM, array[i], powers[i]);
	}
	printf("Total exponent sum is %d\n", power_count);
}
