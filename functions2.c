#include "main.h"

/**-*-*-*-*-*-*-*-*-* Print pointer -*-*-*-*-*-*-*-*-*-**/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	/* Check if the pointer is NULL */
	if (addrs == NULL)
		return (write(1, "(nil)", 5));

    /* Initialize buffer */
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	/* Convert the pointer to a hexadecimal string */
	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	/* Handle padding and extra characters */
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/* Write the pointer value to the output buffer */
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**-*-*-*-*-*-*-*-*-* Print non printable -*-*-*-*-*-*-*-*-*-**/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments (va_list)
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	/* Unused parameters. */
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	/* If the string is NULL, print (null) and return. */
	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
	    /* If the character is printable, add it to the buffer. */
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		/* If it's not printable, append its hexadecimal code to the buffer. */
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	/* Null-terminate the buffer. */
	buffer[i + offset] = '\0';

	/* Return the number of characters printed. */
	return (write(1, buffer, i + offset));
}

/**-*-*-*-*-*-*-*-*-* Print reverse -*-*-*-*-*-*-*-*-*-**/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	/* Unused parameters */
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	/* Handle null string */
	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	/* Iterate through string in reverse */
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**-*-*-*-*-*-*-*-*-* Print a string in rot13 -*-*-*-*-*-*-*-*-*-**/
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
    /* iterate through the string */
	for (i = 0; str[i]; i++)
	{
	    /* iterate through the ROT13 alphabet */
		for (j = 0; in[j]; j++)
		{
		    /* if the character is found in the input alphabet */
			if (in[j] == str[i])
			{
				x = out[j]; /* encode it */
				write(1, &x, 1); /* print it */
				count++;/* increase the count of characters printed */
				break; /* exit the loop */
			}
		}
		/* if the character is not found in the input alphabet */
		if (!in[j])
		{
			x = str[i]; /* keep the character as is */
			write(1, &x, 1); /* print it */
			count++; /* increase the count of characters printed */
		}
	}
	return (count); /* return the total count of characters printed */
}
