#include "main.h"

/**
* print_buffer - Prints the buffer.
* @buffer: character buffer to print.
* @buff_ind: pointer to the buffer index.
*
* Return: void.
*/

void print_buffer(char buffer[], int *buff_ind);

/**
* _printf - Printf function that formats and prints output.
* @format: string with format specifiers.
*
* Return: number of printed characters.
*/
int _printf(const char *format, ...)
{
    /* Variable Declarations */
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	/* Error checking */
	if (format == NULL)
		return (-1);

    /* Initialize variable argument list */
	va_start(list, format);

    /* Loop through format string */
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{

		    /* Flush the buffer before processing the format specifier */
			print_buffer(buffer, &buff_ind);
			/* Get format specifier flags, width, precision, and size */
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			/* Process the format specifier and get the number of printed characters */
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
		/* Handle errors */
			if (printed == -1)
				return (-1);
	/* Update the number of printed characters */
			printed_chars += printed;
		}
	}

	/* Flush the buffer before returning */
	print_buffer(buffer, &buff_ind);

	/* Clean up variable argument list */
	va_end(list);

	/* Return the number of printed characters */
	return (printed_chars);
}

/**
* print_buffer - Prints the contents of the buffer if it exist
* @buffer: Array of chars
* @buff_ind: Index at which to add next char, represents the length.
*/
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
