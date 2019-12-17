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

uint32_t	leftrotate(uint32_t x, uint32_t c)
{
	return (((x) << (c)) | ((x) >> (32 - (c))));
}

void	to_bytes(uint32_t val, uint8_t *bytes)
{
	bytes[0] = (uint8_t) val;
	bytes[1] = (uint8_t) (val >> 8);
	bytes[2] = (uint8_t) (val >> 16);
	bytes[3] = (uint8_t) (val >> 24);
}

uint32_t	to_int32(const uint8_t *bytes)
{
	return ((uint32_t) bytes[0]
        	| ((uint32_t) bytes[1] << 8)
        	| ((uint32_t) bytes[2] << 16)
        	| ((uint32_t) bytes[3] << 24));
}

void	md5(const uint8_t *msg, const size_t len, uint8_t *res)
{
	int			h0;
	int			h1;
	int			h2;
	int			h3;
	uint8_t			*new_msg;
	size_t			new_len;
	size_t			offset;
	uint32_t		w[16];
	uint32_t		a, b, c, d, i, f, g, tmp;

	h0 = 0x67452301;
	h1 = 0xEFCDAB89;
	h2 = 0x98BADCFE;
	h3 = 0x10325476;
	new_len = len + 1;
	while (new_len % (512/8) != 448/8)
		new_len++;
	new_msg = (uint8_t*)malloc(sizeof(uint8_t) * (new_len + 8));
	ft_memcpy(new_msg, msg, len);
	new_msg[len] = 0x80;
	offset = len + 1;
	while (offset < new_len)
	{
		new_msg[offset] = 0;
		offset++;
	}
	to_bytes(len * 8, new_msg + new_len);
	to_bytes((len * 8) >> 32, new_msg + new_len + 4);
	offset = 0;
	while (offset < new_len)
	{
		i = 0;
		while (i < 16)
		{
			w[i] = to_int32(new_msg + offset + i * 4);
			i++;
		}
		a = h0;
		b = h1;
		c = h2;
		d = h3;
		i = 0;
		while (i < 64)
		{
			if (i < 16)
			{
				f = (b & c) | ((-b) & d);
				g = i;
			}
			else if (i < 32)
			{
				f = (d & b) | ((-d) & c);
				g = (5*i + 1) % 16;
			}
			else if (i < 48)
			{
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			}
			else
			{
				f = c ^ (b | (-d));
				g = (7 * i) % 16;
			}
			tmp = d;
			d = c;
			c = b;
			b = b + leftrotate((a + f + g_k[i] + w[g]), g_r[i]);
			a = tmp;
			i++;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		offset += (512 / 8);
	}
	free(new_msg);
	to_bytes(h0, res);
	to_bytes(h1, res + 4);
	to_bytes(h2, res + 8);
	to_bytes(h3, res + 12);
}

int		sha256(char *str)
{
	return (0);
}

char		*getstr_from_res(uint8_t *res)
{
	char	*ret;
	int	i;

	ret = (char*)malloc(sizeof(char) * 33);
	ret[32] = 0;
	i = 0;
	while (i < 16)
	{
		ret[i * 2] = "0123456789abcdef"[res[i] / 16];
		ret[i * 2 + 1] = "0123456789abcdef"[res[i] % 16];
		i++;
	}
	return (ret);
}

int		main(int ac, char **av)
{
	uint8_t	res[16];
	char	*printable;

	if (ac != 3)
	{
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
		return (0);
	}
	if (ft_strcmp(av[1], "md5") == 0)
	{
		md5((uint8_t*)av[2], ft_strlen(av[2]), res);
		printable = getstr_from_res(res);
		ft_putstr(printable);
		free(printable);
	}
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
