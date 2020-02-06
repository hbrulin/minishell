#ifndef ESCAPE_SEQUENCES_H
# define ESCAPE_SEQUENCES_H

/*
** Single quotes : all interpreted as string literal but single quote itself
** !!! escapes do not work in single quotes !!!
** [> bash: unexpected EOF while looking for matching `'']
** [bash: syntax error: unexpected end of file]
**
** Double quotes : variables will be expanded and escape char need to be escaped
** for avoiding multiline mode
** '$' alone will be interpreted as string literal, followed by anything it will
** try to reach for a variables
** '"' need to be escaped since it's the same char
** '\' need to be escaped since it's the escape char
** '$' can be escaped
**
** without quotes : instructions char needs to be escaped :
** '\', '|', '>', '<'
*/

# define BS 23644 // '\'
# define SQ 10076 // '''
# define DQ 8796  // '"'
# define DR 9308  // '$'
# define PP 31836 // '|'
# define LT 15452 // '<'
# define GT 15964 // '>'

typedef union	u_convert
{
	char tab[2];
	unsigned short pack;
}	t_convert;


#endif
