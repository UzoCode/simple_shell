#include "shell.h"

/**
 * initialize - Begins execution all program
 * @recent_commands: attempts checking current token
 * @types_commands: parse token
 *
 * Return: void
 */

void initialize(char **recent_commands, int types_commands)
{
	pid_t PID;

	if (types_commands == EXTERNAL_COMMAND || types_commands == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			execute_commands(recent_commands, types_commands);
		else
		{
			waitpid(PID, &statue, 0);
			statue >>= 8;
		}
	}
	else
		execute_commands(recent_commands, types_commands);
}
