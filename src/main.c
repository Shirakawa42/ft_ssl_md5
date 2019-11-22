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

int		*set_r()
{
	int		*r;

	r = (int*)malloc(sizeof(int) * 64);
	r[0] = 7;
	r[1] = 12;
	r[2] = 17;
	r[3] = 22;
	r[4] = 7;
	r[5] = 12;
	r[6] = 17;
	r[7] = 22;
	r[8] = 7;
	r[9] = 12;
	r[10] = 17;
	r[11] = 22;
	r[12] = 7;
	r[13] = 12;
	r[14] = 17;
	r[15] = 22;
	r[16] = 5;
	r[17] = 9;
	r[18] = 14;
	r[19] = 20;
	r[20] = 5;
	r[21] = 9;
	r[22] = 14;
	r[23] = 20;
	r[24] = 5;
	r[25] = 9;
	r[26] = 14;
	r[27] = 20;
	r[28] = 5;
	r[29] = 9;
	r[30] = 14;
	r[31] = 20;
	r[32] = 4;
	r[33] = 11;
	r[34] = 16;
	r[35] = 23;
	r[36] = 4;
	r[37] = 11;
	r[38] = 16;
	r[39] = 23;
	r[40] = 4;
	r[41] = 11;
	r[42] = 16;
	r[43] = 23;
	r[44] = 4;
	r[45] = 11;
	r[46] = 16;
	r[47] = 23;
	r[48] = 6;
	r[49] = 10;
	r[50] = 15;
	r[51] = 21;
	r[52] = 6;
	r[53] = 10;
	r[54] = 15;
	r[55] = 21;
	r[56] = 6;
	r[57] = 10;
	r[58] = 15;
	r[59] = 21;
	r[60] = 6;
	r[61] = 10;
	r[62] = 15;
	r[63] = 21;
	return (r);
}

char	*big_str(char *str)
{
	
}

int		md5(char *str)
{
	int			*r;
	int			*k;
	int			i;
	int			h0;
	int			h1;
	int			h2;
	int			h3;

	r = set_r();
	k = (int*)malloc(sizeof(int) * 64);
	i = 0;
	while (i < 64)
	{
		k[i] = floor(fabs(sin(i + 1)) * pow(2, 32));
		i++;
	}
	h0 = 0x67452301;
	h1 = 0xEFCDAB89;
	h2 = 0x98BADCFE;
	h3 = 0x10325476;
	str = big_str(str);
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
