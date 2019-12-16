/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:02:31 by lvasseur          #+#    #+#             */
/*   Updated: 2019/11/22 16:29:50 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const uint32_t g_r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};

const uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

char		*string_to_bits(char *str)
{
	size_t	len;
	char	*ret;
	int	i;
	int	j;
	char	ch;
	
	len = ft_strlen(str);
	ret = (char*)malloc(sizeof(char) * (len * 8 + 1));
	ret[0] = '\0';
	i = 0;
	while (i < len)
	{
		j = 7;
		ch = str[i];
		while (j >= 0)
		{
			if (ch & (1 << j))
				ft_strcat(ret, "1");
			else
				ft_strcat(ret, "0");
			j--;
		}
		i++;
	}
	return (ret);
}

char		*addchar_to_str(char *str, char c)
{
	size_t	len;

	len = ft_strlen(str);
	str = (char*)realloc(str, sizeof(char) * (len + 2));
	str[len] = c;
	str[len + 1] = '\0';
	return (str);
}

int		md5(char *str)
{
	int			i;
	int			h0;
	int			h1;
	int			h2;
	int			h3;
	char			*bitmsg;
	int			originalbitlengh;

	h0 = 0x67452301;
	h1 = 0xEFCDAB89;
	h2 = 0x98BADCFE;
	h3 = 0x10325476;
	bitmsg = string_to_bits(str);
	originalbitlength = ft_strlen(bitmsg);
	bitmsg = addchar_to_str(bitmsg, '1');
	while (ft_strlen(bitmsg) % 512 != 448)
		bitmsg = addchar_to_str(bitmsg, '0');
	ft_putendl(bitmsg);
	return (0);
}

int		sha256(char *str)
{
	return (0);
}

int		main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
		return (0);
	}
	if (ft_strcmp(av[1], "md5") == 0)
		return (md5(av[2]));
	else if (ft_strcmp(av[1], "sha256") == 0)
		return (sha256(av[2]));
	else
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(av[1]);
		ft_putendl("' is an invalid command.");
		ft_putendl("\nStandard commands:");
		ft_putendl("\nMessage Digest commands:");
		ft_putendl("md5");
		ft_putendl("sha256");
		ft_putendl("\nCipher commands:");
		return (0);
	}
	return (0);
}
