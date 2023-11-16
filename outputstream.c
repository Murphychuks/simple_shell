 #include "main.h"


/**
 * read_input - A function that read inputs from non-interactive mode.
 *
 * Return: input read
 */

char *read_input(void)
{
	int buffer_size = 1024, index = 0;
	char *input = malloc(sizeof(char) * buffer_size);
	ssize_t bytesRead;
	char c;
	char *more_input = NULL;

	if (!input)
	{
		perror("Memory allocation error");
		free(input);
		exit(EXIT_FAILURE);
	}
	while ((bytesRead = read(STDIN_FILENO, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		input[index++] = c;
		if (index >= (buffer_size - 1))
		{
			buffer_size += 1024;

			more_input = realloc(input, buffer_size);

			if (!more_input)
			{
				perror("Memory reallocation error");
				free(input);
				exit(EXIT_FAILURE);
			}
			input = more_input;
		}
	}
	my_kill(bytesRead, input);

	/* add a NULL terminating character */
	/* to indicate end of string */
	/*input[index] = '\0';*/

	return (input);
}




/**
 * my_kill - To check for EOF condition empty input condtions
 * @n: number of bytes read
 * @k: buffer being read
 */

void my_kill(ssize_t n, char *k)
{
	if (n == -1)
	{
		perror("Error reading from stdin");
		free(k);
		exit(127);
	}
	if (n == 0)
	{
		free(k);
		exit(EXIT_SUCCESS);
	}
}
