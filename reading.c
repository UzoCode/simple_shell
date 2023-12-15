int main()
{
	char lines[1024];
	ssize_t totalbytes_read = 0;
	ssize_t bytes_readd;

	while (1)
	{
		bytes_readd = read(STDIN_FILENO, lines + totalbytes_read, 1);

		if (bytes_readd < 0)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if (bytes_readd == 0)
		{
			break;
		}
		else
		{
			totalbytes_read += bytes_readd;
			if (lines[totalbytes_read - 1] == '\n')
			{
				break;
			}
		}
	}
	lines[totalbytes_read] = '\0';
	printf("%s", lines);

	return 0;
}
