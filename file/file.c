#include "file.h"

int		parse_resolution_line(t_vars *vars, const char *str)
{
	int i;

	i = 0;
	while (str[i] )


	return 1;
}

//0 == R | 1 == NO | 2 == SO | 3 == WE | 4 == EA | 5 == S | 6 == F | 7 == C | 8 == map start
int check_line_type (t_vars *vars, const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'R')
		return parse_resolution_line(vars, str[i]);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		return (1);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (3);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (4);
	else if (str[i] == 'S')
		return (5);
	else if (str[i] == 'F')
		return (6);
	else if (str[i] == 'C')
		return (7);
	else if (str[i] == '1')
		return (8);
	else
		return (-1);
}



int		check_file(t_vars *vars, const char *file_name)
{
	int fd = open(file_name, O_RDONLY);
	char *line;
	int correct_line;
	while (get_next_line(fd, &line) == 1)
	{
		printf("line: %s\n", line);
		correct_line = check_line_type(vars, line);

	}

	return 1;
}