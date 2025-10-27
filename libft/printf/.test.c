#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>


int main(void)
{
    char			*s		= "Shello Minnie";
	char			c		= 'A';
	int				i		= -1;
	unsigned int	u		= -1;
	unsigned int	x		= 3058;
	void 			*p		= &x;
	int				count;
	
    printf("size of pointer: %lu\n", sizeof(uintptr_t));

	count = printf(   "%%s EXP: %s  ->", s);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%s GOT: %s  ->", s);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%c EXP: %c  ->", c);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%c GOT: %c  ->", c);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%d EXP: %d  ->", i);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%d GOT: %d  ->", i);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%i EXP: %i  ->", i);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%i GOT: %i  ->", i);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%u EXP: %u  ->", u);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%u GOT: %u  ->", u);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%%% EXP: %%  ->");
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%%% GOT: %%  ->");
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%x EXP: %x  ->", x);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%x GOT: %x  ->", x);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%X EXP: %X  ->", x);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%X GOT: %X  ->", x);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%p EXP: %p  ->", p);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%p GOT: %p  ->", p);
	printf("%d bytes were printed\n\n", count);

	count = printf(   "%%p EXP: %p  ->", NULL);
	printf("%d bytes were printed\n", count);
	count = ft_printf("%%p GOT: %p  ->", NULL);
	printf("%d bytes were printed\n\n", count);

	char	*pfmt	= "pf: Hello %s there are %d burners and %s lets go!%c\n";	
	char	*ftpfmt	= "ftp:Hello %s there are %d burners and %s lets go!%c\n\n";
	char	*args	= "Shello Minnie";
	char	*args2	= "Me he quemao";
	int		argi  	= -1;
	char	argc	= 'A';
	
	printf(pfmt, args, argi, args2, argc);
	ft_printf(ftpfmt, args, argi, args2, argc);
	
	printf(   "pf:  This is a signed int as an unsigned int %u its huge\n", argi);
	ft_printf("ftpf:This is a signed int as an unsigned int %u its huge\n\n", argi);

    count = 0;
    count = ft_printf("ft %c ", '0');
    printf(           "bytes: %d\n", count);
    count = printf(   "pf %c ", '0');
    printf(           "bytes: %d\n\n", count);
    
    count = printf(   "pt %s %s %s %s %s ", " - ", "", "4", "", "2 ");
    printf(           "bytes: %d\n", count);
    count = ft_printf("ft %s %s %s %s %s ", " - ", "", "4", "", "2 ");
    printf(           "bytes: %d\n\n", count);

    char *var = NULL;
	count = printf(   "pt NULL %s NULL ", var);
    printf(           "bytes: %d\n", count);
    count = ft_printf("ft NULL %s NULL ", var);
    printf(           "bytes: %d\n\n", count);

	count = printf(   " EXP:  ->");
	printf("%d bytes were printed\n", count);
	count = ft_printf(" GOT:  ->");
	printf("%d bytes were printed\n\n", count);

	// count = printf(   " EXP:  ->%");
	// printf("%d bytes were printed\n", count);
	count = ft_printf(" GOTk: %k ->%k");
	printf("%d bytes were printed\n\n", count);
	
	count = ft_printf(" GOT%%:  ->%");
	printf("%d bytes were printed\n\n", count);
	
    return (0);
}
