
#include "lib_for_minishell.h"

void unset(t_environment_list **head, const char *name);

int ft_unset(char **str, t_environment_list **envp)
{
  
   int i = 1;
   char *name;

    while (str[i])     
    {
        if (!str[i])            //unset without arguments
            break;
        name = ft_strdup(str[i]);
        if (wrong_name(str[i], name))
            break;
        unset(envp, name);  //if correct name
        i++;
     }
     //exit(EXIT_SUCCESS);
     return (0);
}


void unset(t_environment_list **head, const char *name)
{
    t_environment_list *current;
    t_environment_list *prev;

    if (*head == NULL) 
        return;
    if (ft_strncmp((*head)->name_and_value[0], name, ft_strlen((*head)->name_and_value[0])) == 0)
    {
        t_environment_list *temp = *head;
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
            current->name_and_value[0] = NULL;
            free(current->name_and_value[1]);
            current->name_and_value[1] = NULL;
            free(current->name_and_value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
