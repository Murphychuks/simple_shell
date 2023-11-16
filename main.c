#include "main.h"


/**
 * main - starts execution of the shell like program.
 *
 * Return: Always 0.
 */

int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
		interractive_mode();
	else
		non_interractive_mode();

	return (0);
}
