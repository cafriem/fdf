#include <stdio.h>
#include "libft.h"
#include <math.h>

int	ft_strhex(char const *str)
{
	int	c;
	int	add;
	int	total;

	c = ft_strlen(str) - 1;
	add = 0;
	total = 0;
	while (c != -1)
	{
		if (ft_strchr("0123456789", str[c]) != NULL)
		{
			if (!total || str[c] == '0')
				total += (str[c] - 48);
			else
				total += ((str[c] - 48) * pow(16, add));
		}
		if (ft_strchr("abcdef", str[c]) != NULL)
		{
			if (!total && add == 0)
				total += (str[c] - 87);
			else
				total += ((str[c] - 87) * pow(16, add));
		}
		add++;
		c--;
	}
	return (total);
}
