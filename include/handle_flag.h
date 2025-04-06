# ifndef HANDLE_FLAG_H
# define HANDLE_FLAG_H 1

# include <sys/types.h>


/* OPT DETAILS

	-a, debug-syms
	Display all symbols, even debugger-only symbols; normally these are not listed.

	-g, extern-only
    Display only external symbols.

	-u, undefined-only
	Display only undefined symbols (those external to each object file).
	By default both defined and undefined symbols are displayed.

	-r, reverse-sort
	Reverse the order of the sort (whether numeric or alphabetic);
	let the last come first.

	-p, no-sort
	Do not bother to sort the symbols in any order; print them in the order encountered.

*/

#define HELP_STRING "Usage: ./ft_nm [option(s)] [file(s)]\n\
 List symbols in [file(s)] (a.out by default).\n\
 The options are:\n\
  -a, --debug-syms\n\
  Display all symbols, even debugger-only symbols; normally these are not listed.\n\
  -g, --extern-only\n\
  Display only external symbols.\n\
  -u, --undefined-only\n\
  Display only undefined symbols (those external to each object file).\n\
  -r, --reverse-sort\n\
  Reverse the order of the sort (whether numeric or alphabetic);\n\
  let the last come first.\n\
  -p, --no-sort\n\
  Do not bother to sort the symbols in any order; print them in the order encountered.\n\
  -h, --help\n\
  Display this help message and exit.\n"

/****************************************************************************/
/*																			*/
/*								FLAGS CHAR									*/
/*																			*/
/****************************************************************************/
# define	A_FLAG_CHAR 'a'         /* 0 */ 
# define	G_FLAG_CHAR 'g'			/* 1 */
# define	U_FLAG_CHAR 'u'			/* 2 */
# define	R_FLAG_CHAR 'r'			/* 3 */
# define	P_FLAG_CHAR	'p'			/* 4 */
# define	H_FLAG_CHAR 'h'			/* 5 */
# define 	NB_FLAG		6			/* max flag str index*/
# define	ALL_FLAG	"agurph"	/* all flag str */


/****************************************************************************/
/*																			*/
/*								ENUM FLAGS VAL								*/
/*																			*/
/****************************************************************************/
enum nm_flag  {
    UNKNOW=0, 
    A_OPTION=1,
	G_OPTION=2,
	U_OPTION=4,
	R_OPTION=8,
	P_OPTION=16,
	H_OPTION=32,
};

/* typedef */
typedef enum nm_flag t_nmflag;

#endif	/* HANDLE_FLAG_H */