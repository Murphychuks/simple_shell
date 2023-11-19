#include "main.h"

/**
 * find_next_newline - function that look up for newline or end of the buffer
 *
 * @buffer: buffer to look up in
 * @length: the length of the buffer
 * Return: number of read character or -1 in case of error
 */
size_t find_next_newline(char *buffer, size_t length)
{
	size_t position;

	position = 0;
	while (position < length && buffer[position] != '\n')
		position++;
	return (position);
}


/**
 * _getline - function takes address of line to fill with characters
 *
 * @line: address to line that will be filled with characters
 * Return: number of read characters in case of error return -1
 */
ssize_t _getline(char **line)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t current_position, end_of_buffer;
	ssize_t old_size, next_newline;

	*line = NULL;
	old_size = 0;
	while (1)
	{
		if (current_position >= end_of_buffer)
		{
			end_of_buffer = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			current_position = 0;
			if (end_of_buffer < 0)
			{
				free(*line);
				*line = NULL;
				return (-1);
			}
			if (end_of_buffer == 0)
				return (old_size);
		}
		next_newline = find_next_newline(buffer + current_position,
										 end_of_buffer - current_position);
		*line = _realloc(*line, old_size, old_size + next_newline);
		if (!*line)
			return (-1);
		_copy((*line) + old_size, buffer + current_position, next_newline);
		old_size += next_newline;
		current_position += next_newline;
		if (current_position < end_of_buffer)
		{
			current_position++;
			return (old_size);
		}
		current_position++;
	}
	return (-1);
}



/**
 * _get_command_from_path - function that takes command
 * and return it's corresponding path
 *
 * @command: command to lookup for it's path
 * Return: path where command located
 */
char *_get_command_from_path(char *command)
{
	char *proper_command, *path,
		**path_2d, **iterator;
	struct stat st;

	if ((command[0] == '.' || command[0] == '/') &&
		!stat(command, &st))
		return (_strdup(command));
	path = _enviroment_management(GET_VALUE, "PATH", NULL);
	if (!path)
		return (_strdup(command));
	iterator = path_2d = _split(path, ":");
	free(path);
	while (*iterator)
	{
		path = _strcat(*iterator, "/");
		proper_command = _strcat(path, command);
		free(path);
		if (!stat(proper_command, &st))
		{
			_free_split(&path_2d);
			return (proper_command);
		}
		free(proper_command);
		iterator++;
	}
	_free_split(&path_2d);
	return (_strdup(command));
}


/**
 * _realloc - function that takes buffer and increase it's size
 *
 * @old_buffer: old data of the buffer
 * @old_size: size of the buffer before update
 * @new_size: size of the buffer after
 * Return: buffer after it's being allocated, NULL in error
 */
void *_realloc(void *old_buffer, size_t old_size, size_t new_size)
{
	unsigned char *buffer;
	unsigned char *char_buffer;
	size_t iter;

	buffer = malloc(sizeof(unsigned char) * (new_size + 1));
	if (!buffer)
		return (NULL);
	char_buffer = old_buffer;
	iter = 0;
	while (char_buffer && iter < old_size)
	{
		buffer[iter] = char_buffer[iter];
		iter++;
	}

	while (iter < new_size)
	{
		buffer[iter] = 0;
		iter++;
	}
	buffer[iter] = 0;
	free(old_buffer);
	return (buffer);
}


/**
 * _str2dlen - function that counts
 * the length of 2d array
 *
 * @arr2d: to count it's length
 * Return: length of given array
 */
int _str2dlen(char **arr2d)
{
	int len;

	len = 0;
	if (!arr2d)
		return (0);
	while (arr2d[len])
		len++;
	return (len);
}
