#include "main.h"

/**
 * exec_env - a function that prints environment variables.
 * @variable: variables whose value is to be retrived
 *
 * Return: 0 on success.
*/

void exec_env (char **variables)
{
	int i = 0;
	char *value;

	while (i < 12)
	{
		if (variables[i])
		{
			if (my_strncmp(variables[i], "games", 5) == 0)
			{
				value = getenv(variables[i]);

				if (value)
				{
					my_fprintf(stdout, "%s:%s\n", variables[i], value);
				}
			}
			else if (strcmp(variables[i], "_") == 0)
			{
				setenv(variables[i], "/bin/env", 1);
			}
			else
			{
				value = getenv(variables[i]);

				if (value)
				{
					my_fprintf(stdout, "%s=%s\n", variables[i], value);
				}
			}
			i++;
		}
		else
			i++;
	}
}
