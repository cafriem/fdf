/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:14:11 by cafriem           #+#    #+#             */
/*   Updated: 2022/06/28 18:39:25 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c] != '\0')
		c++;
	return (c);
}

char	*ft_strchr(const char *s, int c)
{
	int	c1;

	c1 = 0;
	while (s[c1] != (char)c && s[c1] != '\0')
		c1++;
	if (s[c1] == '\0' && c != '\0')
		return (NULL);
	return (&((char *)s)[c1]);
}

char	*ft_strjoin_gl(char *s1, const char *s2)
{
	int		c;
	int		c1;
	int		c2;
	char	*ptr;

	c = 0;
	c1 = ft_strlen(s1);
	c2 = ft_strlen(s2);
	ptr = (char *)malloc(c1 + c2 + 1);
	if (ptr == NULL)
		return (NULL);
	while (s1[c] != '\0')
	{
		ptr[c] = s1[c];
		c++;
	}
	c2 = 0;
	while (s2[c2] != '\0')
		ptr[c++] = s2[c2++];
	ptr[c] = '\0';
	free (s1);
	return (ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if ((size != 0) && count > (SIZE_MAX / size))
		return (NULL);
	result = (void *)malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	c;

	c = 0;
	while (c != n)
	{
		((unsigned char *)s)[c] = 0;
		c++;
	}
}
