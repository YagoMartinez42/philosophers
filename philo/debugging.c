#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s)
	{
		len = ft_strlen(s);
		write (fd, s, len);
	}
}

static int	drop_d(char *str, long n, unsigned int base, int sign)
{
	unsigned long	dig;
	char			base_symbols[33];

	dig = 0;
	ft_strcpy(base_symbols, "0123456789ABCDEFGHIJKLMNOPQRSTUV");
	while ((n * sign) >= base)
	{
		str[dig] = base_symbols[(n % base) * sign];
		n = n / base;
		dig++;
	}
	str[dig] = base_symbols[n * sign];
	if (sign == -1)
	{
		dig++;
		str[dig] = '-';
	}
	str[dig + 1] = '\0';
	return (dig + 1);
}

/**
 * It reverses a string copying it in another one.
 * 
 * @param str_dst The destination string.
 * @param str_org The original string.
 * @param len the length of the string to be reversed.
 */
static void	rev_str(char *str_dst, char *str_org, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		str_dst[i] = str_org[len - i - 1];
		i++;
	}
	str_dst[i] = '\0';
}

/**
 * It takes a number and a base, and returns a string representing the number in
 * the given base.
 * 
 * @param n the number to convert.
 * @param base the base of the number to be converted.
 * 
 * @return A string of characters that represent the number in the base given.
 */
char	*ft_itoab(long n, unsigned int base)
{
	char			strswp[66];
	char			*nb_as_str;
	unsigned long	dig;
	int				sign;

	if (base <= 32)
	{
		if (n < 0)
			sign = -1;
		else
			sign = 1;
		dig = drop_d (strswp, n, base, sign);
		nb_as_str = malloc ((dig + 1) * sizeof(char));
		if (!nb_as_str)
			return (0);
		rev_str(nb_as_str, strswp, dig);
	}
	else
		return (NULL);
	return (nb_as_str);
}

static void	print_addr(void *addr)
{
	char	*addr_line;
	int		len;

	addr_line = ft_itoab((long)addr, 16);
	len = 0;
	while (addr_line[len] != '\0')
		len++;
	while (len < 16)
	{
		ft_putstr_fd ("0", 1);
		len++;
	}
	ft_putstr_fd (addr_line, 1);
	ft_putstr_fd (": ", 1);
	free(addr_line);
}

static void	print_val(char *sym_line, void *addr, unsigned int pos)
{
	unsigned char	c;
	char			*pair;

	if (!addr)
	{
		ft_putstr_fd ("  ", 1);
		sym_line[pos % 16] = '\0';
	}
	else
	{
		c = *(unsigned char *)addr;
		if (c < 16)
			ft_putstr_fd("0", 1);
		pair = ft_itoab(c, 16);
		ft_putstr_fd(pair, 1);
		free (pair);
		if (c >= ' ' && c <= '~')
			sym_line[pos % 16] = c;
		else
			sym_line[pos % 16] = '.';
	}
	if (pos % 2 == 1)
		ft_putstr_fd (" ", 1);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	char			*sym_line;
	unsigned int	pos;

	sym_line = malloc (18 * sizeof(char));
	sym_line[16] = '\n';
	sym_line[17] = '\0';
	pos = 0;
	while (!(pos >= size && (pos % 16) == 0))
	{
		if (pos % 16 == 0)
			print_addr(addr + pos);
		if (pos < size)
			print_val(sym_line, addr + pos, pos);
		else
			print_val(sym_line, 0, pos);
		pos++;
		if (pos % 16 == 0)
			ft_putstr_fd (sym_line, 1);
	}
	free (sym_line);
	return (addr);
}
