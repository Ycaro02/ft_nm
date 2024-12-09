#include "../include/nm.h"

/* Special char Parse Rule
If char in string -> simple quote:
---------------------------------------

    ! $ ^ & * ( ) = < > ? ; [ ] ` ~

---------------------------------------
 Cant use '/' exclusif for directory
Special char :
Simple quote add double quotes
 ' : add ""
Double quote add simple quotes
 " : add ''
 BRACKET_CHAR :
    - alway simple quote when alone { || }
    - remove simple quote whenn add any char include { || }: 
        - exemple: {{ : no simple quote != ## : simple quote
DIEZE_CHAR :
    - simple quote only when at idx 0
*/

/* Special str cmp for sort*/
# define TOKEN_NO_CASE_SENSITIVE 0
# define TOKEN_CHECK_SPE_CHAR 1

enum special_char_e {
    NORMAL_CHAR,                // all other char
    NOEFFECT_CHAR,              // @ % - _ + . , : 
    BRACKET_CHAR,               // { }
    DIEZE_CHAR,                 // #
    ADD_SIMPLE_QUOTE_CHAR,      // ! $ ^ & * ( ) = < > ? ; [ ] ` ~ "
    ADD_DOUBLE_QUOTE_CHAR,      // '
};



int ft_lower_strcmp(char *s1, char *s2) {
    int i = 0;
    char first = '\0';
    char two = '\0';
    while (s1 && s1[i] && s2 && s2[i])
    {
        first = ft_tolower(s1[i]);
        two = ft_tolower(s2[i]);
        if (first != two)
            return (first - two);
        i++;
    }
    if (s1[i] != '\0' || s2[i] != '\0')
        return (s1[i] - s2[i]);
    return (0);
}

/**

* parse special char

*/
int is_special_char(char c) {
    /* all no care char */
    if (c == '@' || c == '%' || c == '-'\
        || c == '_' || c == '+' || c == '.' || c == ',' || c == ':')
        return (NOEFFECT_CHAR);
    /* special rule */
    if ( c == '{' || c == '}')
        return (BRACKET_CHAR);
    if (c == '#')
        return (DIEZE_CHAR);
    if (c == '\'')
        return (ADD_DOUBLE_QUOTE_CHAR);
    /* alway add quote. special rule for ' or "*/
    if (c == '!' || c == '$' || c == '^' || c == '&' || c == '*' || c == '('\
        || c == ')' || c == '=' || c == '<' || c == '>' || c == '?' || c == ';'\
        || c == '[' || c == ']' || c == '`' || c == '~' || c == '\"')
            return (ADD_SIMPLE_QUOTE_CHAR);
    return (NORMAL_CHAR);

}


static int special_strcmp(char *s1, char *s2, int flag) {
    char first = 0;
    char second = 0;
    int i = 0;
    int j = 0;

    /*  skip special char before first count char */

    while (s1[i] && is_special_char(s1[i]) != NORMAL_CHAR)
        i++;
    while (s2[j] && is_special_char(s2[j]) != NORMAL_CHAR)
        j++;

    /* compare all 'count' char */
    while (s1[i] && s2[j]) {
        if (is_special_char(s1[i]) != NORMAL_CHAR)
            i++;
        else if (is_special_char(s2[j]) != NORMAL_CHAR)
            j++;
        else  {
            first = s1[i];
            second = s2[j];
            if (flag == TOKEN_NO_CASE_SENSITIVE) {
                first = ft_tolower(s1[i]);
                second = ft_tolower(s2[j]);
            }
            if (first != second) {
                // printf("CMP s1|%s%s%s|->char[%c][%d], s2|%s%s%s|->char[%c][%d]\n", GREEN, s1, RESET, s1[i], i, RED, s2, RESET,s2[j], j);
                return (first - second);
            }
            if (s1[i])
                i++;
            if (s2[j])
                j++;
        }
    }

    /* skip all special char after count char */

    while (s1[i] && is_special_char(s1[i]) != NORMAL_CHAR)
        i++;

    while (s2[j] && is_special_char(s2[j]) != NORMAL_CHAR)
        j++;
    // printf("CMP s1|%s%s%s|->char[%c][%d], s2|%s%s%s|->char[%c][%d]\n", GREEN, s1, RESET, s1[i], i, RED, s2, RESET,s2[j], j);

    if (flag == TOKEN_NO_CASE_SENSITIVE)
        return (ft_tolower(s1[i]) - ft_tolower(s2[j]));
    return (s1[i] - s2[j]);
}



static int special_char_gestion(char *current, char* min) {
    /*  if is same letter no case sentive no special char exemple: ..a == _A */
    int ret = special_strcmp(current, min, TOKEN_NO_CASE_SENSITIVE); 
    if (ret == 0) {
        /*  if we are here we are on egality on same letter, we need to check the case
            ret 0 for ..a == -a  */
        ret = special_strcmp(current, min, -1);
        if (ret == 0)  {
            if (ft_lower_strcmp(current, min) < 0)
                return (1);
        }
        else if (ret > 0) // ret > 0 because we want to print a before A
            return (1);
    }
    else if (ret < 0)
        return (1);
    return (0);

}

/**
 *	@brief Update t_list node to accordate sort
 *	@param lst list node
 *	@param min min node
 *	@param reverse_opt reverse option
 *	@return min node
*/
static t_list *update_min(t_list *lst, t_list *min, uint8_t reverse_opt)
{
	t_sym_tab	*min_sym, *current = ((t_list *) lst)->content;
	int 		cmp;

	if (!min)
		min = lst;
	
	min_sym = ((t_list *) min)->content;
	cmp = special_char_gestion(current->sym_name, min_sym->sym_name);
	
	if (reverse_opt) {
		if (cmp > 0)
			min = lst;
		
	} else {
		if (cmp < 0)
			min = lst;
	} 
	if (cmp == 0) {
		if (current->value < min_sym->value)
			min = lst;
	}
	return (min);
}

/** 
 *	@brief Get symbol name
 * 	@param symbole struct list
*/
void lst_name_sort(t_list *lst, uint8_t reverse_opt)
{
    t_list *head = lst;
    t_list *min = NULL, *tmp;
    
	if (!lst)
        return ;
    while (lst)  {
		min = update_min(lst, min, reverse_opt);
		lst = lst->next;
    }
    tmp = head->content;
    head->content = min->content;
    min->content = tmp;
    lst_name_sort(head->next, reverse_opt);
}



// static void sort_by_name(t_list *lst, int flag_nb)
// {
//     if (!lst)
//         return ;
//     t_list *head = lst;
//     t_list *min = NULL;
//     while (lst)  {
//         if (!min)
//             min = lst;
//         t_file *current = (t_file *)lst->content;
//         t_file *min_file = (t_file *)min->content;
//         if (special_char_gestion(current->name, min_file->name) == 1)
//             min = lst;
//         lst = lst->next;
//     }
//     t_file *tmp = head->content;
//     head->content = min->content;
//     min->content = tmp;
//     sort_by_name(head->next, flag_nb);
// }