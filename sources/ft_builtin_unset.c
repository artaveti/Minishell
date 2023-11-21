
#include "lib_for_minishell.h"

void unset(t_environment_list **head, const char *name);

int ft_unset(char **array_of_strings, t_environment_list **envp, int exit_num)
{
    int i = 1;
    while (array_of_strings[i] != NULL)
    {
        if (ft_wrong_name(array_of_strings[i]))
            break;
        unset(envp, array_of_strings[i]); 
        i++;
    }
    if (exit_num == BUILTIN_EXIT)
        exit(EXIT_SUCCESS);
    else
        return (BUILTIN_RETURN);
}

void unset(t_environment_list **head, const char *name)
{
    t_environment_list *temp;
    t_environment_list *current;
    t_environment_list *prev;

    if (*head == NULL) 
        return;
    if (ft_strncmp((*head)->name_and_value[0], name, ft_strlen((*head)->name_and_value[0])) == 0)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp->name_and_value[0]);
        free(temp->name_and_value[1]);
        free(temp->name_and_value);
        free(temp);
        return;
    }
    current = *head;
    prev = NULL;
    while (current != NULL)
     {
        if (ft_strncmp(current->name_and_value[0], name, ft_strlen((*head)->name_and_value[0])) == 0)
        {
            prev->next = current->next;
            free(current->name_and_value[0]);
            free(current->name_and_value[1]);
            free(current->name_and_value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    return ;
}




// void unset(t_environment_list **head, t_environment_list ***e_head, const char *name)
// {
//     t_environment_list *current;
//     t_environment_list *prev;
//     t_environment_list *temp;

//     (void)e_head;
//     if (*head == NULL) 
//         return;
//     if (!ft_strncmp((*head)->name_and_value[0], name, ft_strlen(name) + 1))
//     {
//         temp = *head;
//         *e_head = &temp->next;
//         free(temp->name_and_value[0]);
//         free(temp->name_and_value[1]);
//         free(temp->name_and_value);
//         free(temp);
//         // temp->name_and_value[0] = "HELLO";
//         // temp->name_and_value[1] = "world";
//         return;
//     }
//     current = *head;
//     prev = current;
//     while (current != NULL)
//     {
//         if (!ft_strncmp(current->name_and_value[0], name, ft_strlen(name) + 1))
//         {
//             prev->next = current->next;
//             free(current->name_and_value[0]);
//             current->name_and_value[0] = NULL;
//             free(current->name_and_value[1]);
//             current->name_and_value[1] = NULL;
//             free(current->name_and_value);
//             current->name_and_value = NULL;
//             free(current);
//             current = NULL;
//             return;
//         }
//         prev = current;
//         current = current->next;
//     }
// }






// void ft_unset(char **str, t_environment_list **envp)
// {
  
//    int i = 0;

//     if (!str || !(*str) || !streq(str[i], "unset"))  //ete datarka kam unset chi ( DO NOTHING)
//         return;

//     while (str[i])     
//     {

//         if (i == 0 && streq(str[i], "unset")) //skip unset(first)
//             i++;
//         if (!str[i])            //unset without arguments
//             break;
//           char *name = ft_strdup(str[i]);
//         if (wrong_name(str[i], name))
//             break;
      
//             unset(envp, name);  //if correct name
//         i++;
//      }
// }