#include "main.h"

/**-*-*-*-*-*-*-*-*-* Print Characters -*-*-*-*-*-*-*-*-*-**/
/**
 * print_char - Prints a character.
 * @types: va_list of arguments.
 * @buffer: character buffer to handle the print.
 * @flags: integer that stores the active format flags.
 * @width: integer that stores the width specified in the format string.
 * @precision: integer that stores the precision specified
 *		in the format string.
 * @size: integer that stores the size specified in the format string.
 *
 * Return: number of characters printed.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
    /* Extract the character argument from va_list */
	char c = va_arg(types, int);

	/* Call handle_write_char function to format and print the character */
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**-*-*-*-*-*-*-*-*-* Print string -*-*-*-*-*-*-*-*-*-**/
/**
 * print_string - Prints a string.
 * @types: va_list of arguments.
 * @buffer: character buffer to handle the print (unused).
 * @flags:  integer that stores the active format flags (unused).
 * @width: integer that stores the width specified in the format string.
 * @precision: integer that stores the precision specified
 *		in the format string.
 * @size: integer that stores the size specified in the format string (unused).
 * Return: number of characters printed.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0') /* Get the length of the string */
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)/* Handle width formatting */
	{
		if (flags & F_MINUS)/* Left-justify */
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else /* Right-justify (default) */
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/**-*-*-*-*-*-*-*-*-* Print % sign -*-*-*-*-*-*-*-*-*-**/
/**
 * print_percent - Prints a percent sign.
 * @types: A list of arguments.
 * @buffer: Buffer array to handle print.
 * @flags:  Calculates active flags.
 * @width:  Width of output.
 * @precision: Precision of output.
 * @size: Size specifier.
 *
 * Return: the number of characters printed.
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
    /* unused variables */
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	/*print a single percent sign*/
	return (write(1, "%%", 1));
}

/**-*-*-*-*-*-*-*-*-* Print integer -*-*-*-*-*-*-*-*-*-**/
/**
 * print_int - Prints an integer.
 * @types: A list of arguments.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of chars printed.
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
    /* Initializing variables */
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	/* Convert to specified size */
	n = convert_size_number(n, size);

	/* Handling case for 0 */
	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	/* Handling case for negative number */
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	/* Converting number to string */
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	/* Writing formatted string to output */
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**-*-*-*-*-*-*-*-*-* Print binary -*-*-*-*-*-*-*-*-*-**/
/**
 * print_binary - Prints an unsigned number in binary format.
 * @types: variadic list of arguments.
 * @buffer: unused buffer array.
 * @flags:  unused flag parameter.
 * @width: unused width parameter.
 * @precision: unused precision parameter.
 * @size: unused size parameter.
 *
 * Return: Returns the number of characters printed to stdout.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
    /* Declare variables */
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	/* Unused parameters */
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	/* Get the argument from the variadic list */
	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
	    /* Initialize a binary array a to store the binary representation of n */
		m /= 2;
		a[i] = (n / m) % 2;
	}
	/* Print the binary number stored in array a */
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
	    /* Keep track of the number of binary digits printed */
		sum += a[i];
		if (sum || i == 31)
		{
		    /* Convert the binary digit to a character and write it to stdout */
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	/* Return the number of characters printed */
	return (count);
}
