#include "main.h"

/**-*-*-*-*-*-*-*-*-* Print unsigned number -*-*-*-*-*-*-*-*-*-**/
/**
* print_unsigned - Prints an unsigned number using the given parameters.
* @types: A va_list of arguments.
* @buffer: An array used to handle the output.
* @flags:  An integer used to calculate active flags.
* @width: An integer used to get the width.
* @precision: An integer used to specify precision.
* @size: An integer used to specify size.
*
* Return: The number of characters printed.
*/
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
    /* Declare and initialize variables. */
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	/* Convert the given size. */
	num = convert_size_unsgnd(num, size);

	/* Handle special case of 0. */
	if (num == 0)
		buffer[i--] = '0';

    /* Null terminate the buffer. */
	buffer[BUFF_SIZE - 1] = '\0';

	/* Fill the buffer with the given number. */
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
    /* Increment i to correct position. */
	i++;

	/* Write the output to the console. */
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**-*-*-*-*-*-* Print unsigned number in octal *-*-*-*-*-*-**/
/**
* print_octal - Prints an unsigned number in octal notation.
* @types: A va_list of arguments.
* @buffer: An array used to handle the output.
* @flags: An integer used to calculate active flags.
* @width: An integer used to get the width.
* @precision: An integer used to specify precision.
* @size: An integer used to specify size.
*
* Return: The number of characters printed.
*/
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

    /* Declare and initialize variables. */
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	/* Convert the given size. */
	num = convert_size_unsgnd(num, size);

	/* Handle special case of 0. */
	if (num == 0)
		buffer[i--] = '0';

    /* Null terminate the buffer. */
	buffer[BUFF_SIZE - 1] = '\0';

	/* Fill the buffer with the octal representation of the number. */
	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	/* Add '0' prefix if necessary. */
	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';
/* Increment i to correct position. */
	i++;

	/* Write the output to the console. */
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
/**-*-*-*-*-*-* Print unsigned number in hexadecimal *-*-*-*-*-*-**/
/**
* print_hexadecimal - Prints an unsigned number in hexadecimal notation
* @types: A va_list of arguments
* @buffer: Buffer array to handle print.
* @flags: A variable that calculates active flags
* @width: A variable that specifies width
* @precision: Precision specification
* @size: Size specifier
*
* Return: Number of chars printed
*/
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**-*-*-*-*-*-* Print unsigned number in upper hexadecimal *-*-*-*-*-*-**/
/**
* print_hexa_upper - Prints an unsigned number in upper hexadecimal notation.
* @types: Lista of arguments.
* @buffer: Buffer array to handle print.
* @flags:  Calculates active flags.
* @width: An integer that represents the width of the output.
* @precision: Precision specification.
* @size: Size specifier.
* Return: The number of characters printed by the function.
*/
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**-*-*-*-*Print hexadecimal number in upper or lower*-*-*-*-**/
/**
* print_hexa - Prints a hexadecimal number in lower or upper
* @types: Lista of arguments
* @map_to: Array of values to map the number to
* @buffer: Buffer array to handle print
* @flags:  Calculates active flags
* @flag_ch: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
*@size: Size specification
* Return: Number of chars printed
*/
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
