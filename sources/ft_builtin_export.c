
// #include "lib_for_minishell.h"

// char	*ft_strncpy(char *dest, char *src, unsigned int n);
// void extractNameAndValue(char *String, char **name, char **value);
// void print_export(t_environment_list *envp, int assigned_val);
// size_t get_index_of_char(const char *str, char c);
// int findEqualChar(const char *text);
// int check_order(char *str);
// void extract_2(char *String, char **name, char **value);
// t_environment_list *set_last_node(t_environment_list **envp, int flag);  //setting flag
// int hasPlusEqual(char *str);
// t_environment_list *ft_list_new_for_export(char *name, char *value);
// char	*ft_strnstr(char *str, char *to_find, size_t len);



// int ft_export(char **str, t_environment_list **envp, int exit_num)
// {
//     printf("I am in EXPORT\n");
//     (void)exit_num;

//     int i = 1;   //exporti argumentnery mekic skselu hamar
//     static int assigned_val; //if assigned, and than set again with no arg, don't remove from env list visibility 
//     char *name = NULL;
//     char *value = NULL;

//         if (!str[1]) //ete arg chka mena export grac
//         {
//             print_export(*envp, assigned_val);   //no arg only export (PRINTING EXPORT LIST)
//             return 0;
//         }
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



// void print_export(t_environment_list *envp, int assigned_val)  //no arg only export (PRINTING EXPORT LIST)
// {
//     t_environment_list *env = envp;

//     int count = 0;
//     t_environment_list *current = env;
//     while (current != NULL)
//     {
//         count++;
//         current = current->next;
//     } 
//     t_environment_list **nodes = (t_environment_list **)malloc(count * sizeof(t_environment_list *));
//     if (nodes == NULL)
//         return;
//     current = env;
//     int index = 0;
//     while (current != NULL)
//      {
//         nodes[index++] = current;
//         current = current->next;
//     }

    
//     for (int i = 0; i < count - 1; i++)
//      {
//         int min_idx = i;
//         for (int j = i + 1; j < count; j++)
//          {
//             if (strcmp(nodes[j]->name_and_value[0], nodes[min_idx]->name_and_value[0]) < 0) 
//                 min_idx = j;
//         }
//         if (min_idx != i) 
//         {
//             t_environment_list *temp = nodes[i];
//             nodes[i] = nodes[min_idx];
//             nodes[min_idx] = temp;
//         }
//     }
//     for (int i = 0; i < count; i++)
//      {
//         if (nodes[i]->envp_flag == 1 || assigned_val) 
//                 printf("declare -x %s=\"%s\"\n", nodes[i]->name_and_value[0], nodes[i]->name_and_value[1]);
//         else if (nodes[i]->envp_flag == 0)
//             printf("declare -x %s\n", nodes[i]->name_and_value[0]);
//     }
//     free(nodes);
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



