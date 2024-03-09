# include "../include/handle_flag.h"
# include "../libft/basic_define.h"
# include "../libft/libft.h"
/**
* 00000000 -> Our current flag value is 0
* | 00000100 -> Do or operation with Flag3, which has a value of 4
* = 00000100 -> The bit for Flag3 gets set to 1, flag value is now 4
* Enable target flag
*/
void set_flag(int *flags, int flag_val)
{
    if (flags)
        *flags |= flag_val;
}

/**
* 00000100 -> We get Flag3 as input to unset
* ~= 11111011 -> We flip all the bits of Flag3
* 00010110 -> Our current value had Flag2, 3 and 5 set already
* &  11111011 -> AND operation with the result of previous inversion
* =  00010010 -> Our new value only has Flag2 and 5 set
* Disable target flag
*/
void unset_flag(int *flags, int flag_val)
{
    if (flags)
        *flags &= ~flag_val;
}

/*
* 00010110 -> Starting value has Flag2, Flag3 and Flag5 set
* & 00000100 -> Perform & with Flag3
* = 00000100 -> Result is equal to Flag3
* check if flag_val enable in flags
// __always_inline int has_flag(int flags, int flag_val)
*/

int8_t has_flag(int flags, int flag_val) {
   return ((flags & flag_val) == flag_val);
}

int8_t flag_already_present(int flags, int flag_val) {
    return (has_flag(flags, flag_val));
}

void display_flags(int flags) {
    const char *flag_strings[NB_FLAG] = {"A_OPTION","G_OPTION","U_OPTION","R_OPTION","P_OPTION"};
    const char *flag_colors[NB_FLAG] = {GREEN,YELLOW,RED,PURPLE,CYAN};

    ft_printf_fd(2, FILL_YELBLACK"Flags: [%d] : "RESET, flags);
    for (int i = 0; i < NB_FLAG; ++i) {
        if ((flags >> i) & 1) {
            ft_printf_fd(2, "%s[%s]%s, ", flag_colors[i], flag_strings[i], RESET);
        }
    }
    ft_printf_fd(2, "\n");
}

/** get_flag_value
 * Convert char to flag value see ALL_FLAG and e_flag, define_enum.c
*/
static int get_flag_value(char c) 
{
    int i = 0;
    int flag = -1;

    while (i < NB_FLAG) {
        if (c == ALL_FLAG[i]) {
            flag = (1 << i);
            break;
        }
        ++i;
    }
    return (flag);
}

/** parse_flag
 * Parse user input to get flag
*/
int parse_flag(int argc, char **argv)
{
    int i = 1, flags = 0, tmp_value = 0;

    while (i < argc) {
        if (argv[i][0] == '-') {
            if (!argv[i][1]) {   /* special case ugly */
                ft_printf_fd(2, "%s: cannot access %s: No such file or directoryn", argv[0], argv[i]); // special case
            }
            else if (argv[i][1] == '-' && argv[i][2] == '\0') {
                ++i;
                continue;
            }
            else {
                for (int j = 1; argv[i][j]; ++j) {
                    tmp_value =  get_flag_value(argv[i][j]);
                    if (tmp_value == -1) {
                        ft_printf_fd(2, "%s: invalid option -- %cnTry ./%s --help for more information\n",  argv[0], argv[i][j],  argv[0]);
                        return (-1);
                    }
                    if (flag_already_present(flags, tmp_value) == FALSE)
                        set_flag(&flags, tmp_value);
                }
            }
        }
        ++i;
    }
    // flags = manage_bonus_flag(flags);
    display_flags(flags);
	return (flags);
}
