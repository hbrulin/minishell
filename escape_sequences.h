#ifndef ESCAPE_SEQUENCES_H
# define ESCAPE_SEQUENCES_H

# define BZ 12380
# define AL 24924
# define EC 25180
# define PB 26204
# define NL 28252
# define CR 29276
# define HT 29788
# define VT 30300
# define BS 23644
# define SQ 10076
# define DQ 8796
# define QM 16220

/*
** si \x chiffres -> convertis d'hexa en decimal et print le char
** si \0 chiffres -> convertis d'octal en decimal et print le char
*/

typedef union	u_convert
{
	char tab[2];
	unsigned short pack;
}	t_convert;


#endif
