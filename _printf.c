#include "main.h"

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 *
 * Return: void
 */
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format string.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	/* Variable declarations */
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	/* Check if format string is NULL */
	if (format == NULL)
		return (-1);

	/* Initialize va_list */
	va_start(list, format);

	/* Loop through the format string */
	for (i = 0; format && format[i] != '\0'; i++)
	{
		/* If current char is not '%' */
		if (format[i] != '%')
		{
			/* Add char to buffer and increment printed_chars */
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		/* If current char is '%' */
		else
		{
/* Print buffer, read & process format modifiers, handle formatted output */
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	/* Print any remaining characters in buffer */
	print_buffer(buffer, &buff_ind);

	/* Clean up and return total number of printed characters */
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 *
 * Return: void
 */
void print_buffer(char buffer[], int *buff_ind)
{
	/* If buffer has contents, print them and reset buffer index */
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}

