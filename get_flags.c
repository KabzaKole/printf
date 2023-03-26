#include "main.h"

/**
* get_flags - Calculates active flags
* @format: Formatted string in which to print the arguments
* @i: take a parameter.
*
* Return: integer value representing the active flags
*
* F_MINUS (1) for left-aligning text
* F_PLUS (2) for printing a plus sign for positive numbers
* F_ZERO (4) for zero-padding numbers
* F_HASH (8) for prefixing numbers with 0 or 0x/0X
* F_SPACE (16) for printing a space before positive numbers
*/
int get_flags(const char *format, int *i)
{
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	/* iterate over characters in format string to find active flags */
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
