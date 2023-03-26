#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Width to be used for printing.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	/* Loop through the format string, starting from current index */
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
	    /* If the character is a digit, calculate the width */
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
/* If the character is an asterisk, get the width from the list of arguments */
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
/* If the character isn't a digit or an asterisk, stop calculating the width */
		else
			break;
	}

	/* Update the current index */
	*i = curr_i - 1;

	return (width);
}
