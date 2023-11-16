#include "main.h"

/**
 *interractive_mode - mode to be executed wen d shell is in interractive mode
 *
 *@void: no argument expected
 *Return: no value is returned
 */

void interractive_mode(void)
{
	char *command;
	int count = 0, i;
	char **parsed_commands;

	while (1)
	{
		print_prompt();
		command = read_command();
		count++;

		/* Check for end of file (Ctrl+D) or "exit"*/
		if (command == NULL || strcmp(command, "exit") == 0)
		{
			free_command(command);
/*			my_fprintf(stdout, "\n");*/
			exit(EXIT_SUCCESS);
		}

		parsed_commands = parse_commands(command);

		/* Execute each command*/
		for (i = 0; parsed_commands[i] != NULL; i++)
		{
/*			printf("Executing command: %s\n", parsed_commands[i]);*/
			execute_command(parsed_commands[i], count);
		}

		/* Free the memory allocated for parsed commands*/
		free_commands(parsed_commands);

		free_command(command);
	}


}







/**
 *non_interractive_mode -To be executed wen d shell is in non_interractive mode
 *
 *@void: no argument expected
 *Return: no value is returned
 */

void non_interractive_mode(void)
{
	char *command;
	int count = 0, i;
	char **parsed_commands;

	while (1)
	{
		/*print_prompt();*/
		command = read_input();
		count++;

		/* Check for end of file (Ctrl+D) or "exit"*/
		if (command == NULL || strcmp(command, "exit") == 0)
		{
			free_command(command);
/*			my_fprintf(stdout, "\n");*/
			exit(EXIT_SUCCESS);
		}

		parsed_commands = parse_commands(command);

		/* Execute each command*/
		for (i = 0; parsed_commands[i] != NULL; i++)
		{
/*			printf("Executing command: %s\n", parsed_commands[i]);*/
			execute_command(parsed_commands[i], count);
		}

		/* Free the memory allocated for parsed commands*/
		free_commands(parsed_commands);

		free_command(command);
	}

}
