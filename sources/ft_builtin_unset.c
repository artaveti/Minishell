
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
    {
        exit_status_msh = 0;
        return (BUILTIN_RETURN);
    }
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
