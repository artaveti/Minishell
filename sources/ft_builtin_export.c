
#include "lib_for_minishell.h"

//// '#' sign in export ???
//// '=' sign in export ???
//// '+=' sign in export ???
//// krknvogh anunner

void ft_print_for_export(t_environment_list *envp);
int ft_check_name_for_export(char *str);
void ft_check_and_add_to_environment(t_environment_list **envp, char *str);
char *ft_creat_last_part_of_word_for_export(char *string, char *symbols);


char	*ft_strncpy(char *dest, char *src, unsigned int n);
void extractNameAndValue(char *String, char **name, char **value);
size_t get_index_of_char(const char *str, char c);
int findEqualChar(const char *text);
int check_order(char *str);
void extract_2(char *String, char **name, char **value);
t_environment_list *set_last_node(t_environment_list **envp, int flag);  //setting flag
int hasPlusEqual(char *str);
t_environment_list *ft_list_new_for_export(char *name, char *value);
char	*ft_strnstr(char *str, char *to_find, size_t len);


void ft_export(t_environment_list **envp, char **array_of_strings, int fd_out, int exit_num)
{
    int i;
    
    exit_status_msh = EXIT_SUCCESS;
    i = 1;
    if (array_of_strings[i] == NULL)
    {
        ft_print_for_export(*envp);
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_SUCCESS);
        return ;
    }
    while(array_of_strings[i] != NULL)
    {
        dup2(fd_out, STDOUT_FILENO);
        if (ft_check_name_for_export(array_of_strings[i]) == 1)
        {
            exit_status_msh = EXIT_FAILURE;
            i++;
        }
        else
        {
            ft_check_and_add_to_environment(envp, array_of_strings[i]);
            i++;
        }
    }
    if (exit_num == BUILTIN_EXIT)
        exit(exit_status_msh);
    return ;
}



void ft_print_for_export(t_environment_list *envp)
{
    t_environment_list *tmp;

    tmp = envp;
    while(tmp != NULL)
    {
        if (tmp->envp_flag == 0)
            printf("declare -x %s\n", tmp->name_and_value[0]);
        else
            printf("declare -x %s=\"%s\"\n", tmp->name_and_value[0], tmp->name_and_value[1]);
        tmp = tmp->next;
    }
    return ;
}



int ft_check_name_for_export(char *str)
{
    int i;

    if (!str || str == NULL)
        return (1);
    if (ft_isnum(str[0]) || str[0] == '+' || str[0] == '=')
    {
        printf(ERROR_FOR_EXPORT, str);
        return (1);
    }
    i = 0;
    while(str[i] != '\0')
    {
        if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
            return (0);
        if ((ft_strchr(WRONG_SIGN_EXPORT, str[i])) && str[i] != '\0')
        {
            printf(ERROR_FOR_EXPORT, str);
            return (1);
        }
        i++;
    }
    return (0);
}


void ft_check_and_add_to_environment(t_environment_list **envp, char *str)
{
    t_environment_list *tmp;
    t_environment_list *tmp_new;
    char *before_equal;
    char *after_equal;
    char *tmp_str;
    int flag_for_equal;
    int flag_for_plus;

    tmp = *envp;
    before_equal = NULL;
    after_equal = NULL;
    flag_for_equal = ft_char_find('=', str);
    flag_for_plus = 0;
    if (flag_for_equal == 1)
    {
        if (*(ft_strchr(str, '=') - 1) == '+')
            flag_for_plus = 1;
        if (flag_for_plus == 1)
            before_equal = ft_creat_first_part_of_word(str, "+");
        else
            before_equal = ft_creat_first_part_of_word(str, "=");
        after_equal = ft_creat_last_part_of_word_for_export(str, "=");
    }
    else
        before_equal = ft_strdup(str);
    while (tmp != NULL)
    {
        if (!ft_strncmp(tmp->name_and_value[0], before_equal, ft_strlen(before_equal) + 1))
        {
            if (flag_for_equal == 1 && flag_for_plus == 1)
            {   
                tmp_str = tmp->name_and_value[1];
                tmp->name_and_value[1] = ft_strjoin(tmp->name_and_value[1], after_equal);
                free(tmp_str);
                free(before_equal);
                free(after_equal);
                return ;
            }
            else if (flag_for_equal == 1 && flag_for_plus == 0)
            {
                free(tmp->name_and_value[1]);
                tmp->name_and_value[1] = ft_strdup(after_equal);
                free(before_equal);
                free(after_equal);
                return ;
            }
            else
            {
                free(before_equal);
                return ;
            }
        }
        tmp = tmp->next;
    }
    free(before_equal);
    free(after_equal);
    tmp_new = ft_list_new_for_environment(str);
    ft_list_add_back_for_environment(envp, tmp_new);
    return ;
}



char *ft_creat_last_part_of_word_for_export(char *string, char *symbols)
{
    char *last_part;
    int i;

    i = 0;
    while (string[i] != '\0')
    {
        if (ft_strchr(symbols, string[i]))
        {
            last_part = ft_strdup(&string[i + 1]);
            return (last_part);
        }
        i++;
    }
    return (NULL);
}



//     while (str[i])     //argumentneri vrayov ancnuma
//     {
//         if (check_order(str[i])) // stuguma += (1), te miayn = a(0)
//              extract_2(str[i], &name, &value);  // avelacnuma nami ev valui mej, += ov ktrelov
//         else
//              extractNameAndValue(str[i], &name, &value);   // avelacnuma nami ev valui mej, arajin = ov ktrelov
//         if ( !ft_wrong_name(name, str[i]))  //stuguma anuny tpum error(funkciayi mej), ete chka  error, avelacnuma env, kam poxum valuen
//         {
//          t_environment_list *newNode;
        
//            newNode = ft_list_new_for_export(name, value);  //nor listi ptr (CREATING NEW LIST
//            t_environment_list *current = *envp;  
          
//             while (current != NULL) // ITERaTION (ADDING NODES WITH FLAGS AND SETTING FLAGS TO PRINT)
//          {
//                  if (streq(current->name_and_value[0], name))  //ete arden ka ed anunov node (OLD VALUE WITH =)
//                 {
//                       if (findEqualChar(str[i]))
//                        {

//                             if (assigned_val && value && hasPlusEqual(str[i]))
//                                 value = ft_strjoin(current->name_and_value[1], value); /////
//                             printf("CASE 1 (old value with =) value [%s]\nenv_list\n)  [%s]\n\n", str[i], value);
//                             current->name_and_value[1] = ft_strdup(value);
//                             set_last_node(envp, 1);              //WILL BE SHOWN IN ENV
//                             assigned_val = 1;
//                             break ;
//                       }
//                     else    
//                     {
//                         printf("CASE 2 (old value without =) value [%s])  [%s]\nexport_list\n", str[i], value); //PLD VALUE WITHOUT =
//                         break ;
//                     }
//                 }
//                 assigned_val = 0;
//                 if (current->next == NULL)          //NEW VALUE
//                 { 
//                     ft_list_add_back_for_environment(envp, newNode);  //ADD NODE
//                     // print_all(*envp);
//                     if (findEqualChar(str[i])) //NEW VAL WITH =
//                     {
//                         assigned_val = 1;
//                           printf("CASE 3\n (new value with =) [%s]\nenv_list\n", str[i]);
//                         set_last_node(envp, 1);
//                     }
//                     else
//                     {
//                         printf("CASE 4 (NEW value without =) [%s]\nexport_list\n", str[i]);  //NEW VAL WITHOUT =
//                          if (!assigned_val)
//                             set_last_node(envp, 0); //NOT SHOWN IN EXPORT
//                     }
//                     break ;
//                 }
//                     current = current->next;
//           }    
//         }
//          i++; 
//       }

//     // exit(EXIT_SUCCESS);
//      return (0);
// }



// size_t streq(char *s1, char *s2)  //ete datarka kam export chi (IF NOT EXPORT DO NOTHING)
// {
//     int i = 0;
//     if ((!s1 || !(*s1) || !s2 || !(*s2)) || (ft_strlen(s1) != ft_strlen(s2)))
//         return  0;
//     while (s1[i])
//     {
//         if (s1[i] != s2[i])
//             return 0;
//         i++;
//     }
//     return 1;
// }



// int check_order(char *str) // stuguma += (1), te miayn = -ra(0)
// {
//     int equal_pos = 0;
//     int plus_pos = 0;

//     if (!str || !ft_strchr(str, '+'))
//         return 0;
//     int i = 0;
//     while (str[i])
//     {
//         if (str[i] == '=')
//         {
//             equal_pos=i;
//             break;
//         }
//         else if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
//         {
//             plus_pos=i;
//             break ;
//         }
//         i++;
//     }
//     if (plus_pos > equal_pos)
//         return 1;
//     return 0;
// }



// void extract_2(char *String, char **name, char **value)  // avelacnuma nami ev valui mej
// {
//     char *equalSignPos = ft_strnstr(String, "+=", ft_strlen(String));

//     if (equalSignPos != NULL)
//     {
//         int nameLength = equalSignPos - String;

//         *name = (char *)malloc((nameLength + 1) * sizeof(char));
//         if (*name) 
//         {
//             ft_strncpy(*name, String, nameLength);
//             (*name)[nameLength] = '\0';
//            // printf("NAME: %s\n", *name);
//         } 
//         else 
//         {
//             //printf("Memory allocation failed for name.\n");
//             *name = NULL;
//         }
//         int valueLength = ft_strlen(equalSignPos + 2);

//         *value = (char *)malloc((valueLength + 1) * sizeof(char));
//         if (*value)
//         {
//             ft_strncpy(*value, equalSignPos + 2, valueLength);
//             (*value)[valueLength] = '\0';
//            // printf("VALUE: %s\n", *value);
//         } else 
//         {
//             printf("Memory allocation failed for value.\n");
//             *value = NULL;
//         }
//     } 
//     else 
//     {
//        // printf("+= not found in the string.\n");
//         *name = String;
//         *value = NULL;
//     }
// }



// void extractNameAndValue(char *String, char **name, char **value)   // avelacnuma nami ev valui mej
// {
//     char *equalSignPos = ft_strchr(String, '=');
   
   
//     if (equalSignPos != NULL)
//     {
//         int nameLength = equalSignPos - String;
//         int valueLength = ft_strlen(String) - nameLength - 1;
//         *name = (char *)malloc((nameLength + 1) * sizeof(char));
//         *value = (char *)malloc((valueLength + 1) * sizeof(char));
//         if (*name && *value)
//         {
//             ft_strncpy(*name, String, nameLength);
//             (*name)[nameLength] = '\0';
//             ft_strncpy(*value, equalSignPos + 1, valueLength);
//             (*value)[valueLength] = '\0';
//         } 
//         else
//         {
//             printf("Memory allocation failed.\n");
//             *name = NULL;
//             *value = NULL;
//         }
//     } 
//     else
//     {
//         *name = String;
//         *value = NULL;
//     }
// }



// t_environment_list *ft_list_new_for_export(char *name, char *value)
// {
//     t_environment_list *result = (t_environment_list *)malloc(sizeof(t_environment_list));

//     if (!result || !name)
//         return NULL;

// result->name_and_value = (char **)malloc(2 * sizeof(char *));
//     if (!result->name_and_value)
//      {
//         free(result);
//         return NULL;
//     }
//     result->name_and_value[0] = ft_strdup(name); 
//     if (value) 
//     {
//         result->name_and_value[1] = ft_strdup(value); 
//         if (!result->name_and_value[1]) 
//         {
//             free(result->name_and_value[0]);
//             free(result->name_and_value);
//             free(result);
//             return NULL;
//         }
//     } 
//     else 
//         result->name_and_value[1] = NULL;
//     result->next = NULL;
//     return result;
// }


// char	*ft_strnstr(char *str, char *to_find, size_t len)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	to_find_len;

// 	i = 0;
// 	to_find_len = ft_strlen(to_find);
// 	if (!str && !len)
// 		return (NULL);
// 	if (to_find_len == 0)
// 		return (str);
// 	while (str[i] && (i + to_find_len) <= len)
// 	{
// 		j = 0;
// 		while (to_find[j] && str[i + j] == to_find[j])
// 			j++;
// 		if (j == to_find_len)
// 			return (str + i);
// 		i++;
// 	}
// 	return (NULL);
// }





// int plus_before_eq(char* str) 
// {
//     if (!str)
//         return 0;
//     int plusIndex = -1;
//     int equalIndex = -1;
//     int i = 0;
//     while (str[i] != '\0') 
//     {
//         if (str[i] == '+') 
//             plusIndex = i;
//         else if (str[i] == '=') 
//             equalIndex = i;
//         if (plusIndex != -1 && equalIndex != -1) 
//             break;
//         i++;
//     }
//     if (plusIndex != -1 && equalIndex != -1) 
//         return plusIndex < equalIndex;
//     return 0;
// }




// t_environment_list *set_last_node(t_environment_list **envp, int flag)  //setting flag tpelu hamar vor env ereva kam chereva
// {
//     if (*envp == NULL) 
//         return NULL; 
//     t_environment_list *current = *envp;

//     while (current->next != NULL) 
//         current = current->next;
//     current->envp_flag = flag;
//     return current;
// }





// int hasPlusEqual(char *str)
// {
//     int i = 0;
//     while (str[i] != '\0') 
//     {
//         if (str[i] == '+' && str[i + 1] == '=')
//         {
//             return 1;
//         }
//         i++;
//     }
//     return 0; 
// }



// char	*ft_strncpy(char *dest, char *src, unsigned int n)
// {
// 	unsigned int	i = 0;
//     if (!src || !(*src))
//         return NULL;
//    while (src[i] != '\0' && i < n)
// 	{
// 		dest[i] = src[i];
// 		++i;
// 	}
// 	while (i < n)
// 	{
// 		dest[i] = '\0';
// 		++i;
// 	}
// 	return (dest);
// }


// size_t get_index_of_char(const char *str, char c)
// {
    
//     size_t len = 0;
//     while (str[len] != '\0' && str[len] != c)
//         len++;
//     if (c == '+')
//         len++;
//     return len;
// }


// int findEqualChar(const char *text)
// {
//     if (!text || !(*text))
//         return 0;
//     while (*text != '\0')
//     {
//         if (*text == '=') 
//             return 1;
//         text++;
//     }
//     return 0;
// }
