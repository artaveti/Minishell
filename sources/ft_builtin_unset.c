
#include "lib_for_minishell.h"

void for_ft_unset(t_environment_list **head, const char *name);
int ft_unset_head_of_envp_list(t_environment_list **head, const char *name);

void ft_unset(char **array_of_strings, t_environment_list **envp, int exit_num)
{
    int i = 1;
    while (array_of_strings[i] != NULL)
    {
        if (ft_wrong_name(array_of_strings[i]))
        {
            if (exit_num == BUILTIN_EXIT)
                exit(EXIT_FAILURE);
            exit_status_msh = EXIT_FAILURE;
            return ;
        }
        for_ft_unset(envp, array_of_strings[i]); 
        i++;
    }
    if (exit_num == BUILTIN_EXIT)
        exit(EXIT_SUCCESS);
    exit_status_msh = 0;
    return ;
}



void for_ft_unset(t_environment_list **head, const char *name)
{
    t_environment_list *current;
    t_environment_list *prev;

    if (ft_unset_head_of_envp_list(head, name))
        return ;
    current = *head;
    prev = NULL;
    while (current != NULL)
     {
        if (ft_strncmp(current->name_and_value[0], name,
            ft_strlen((*head)->name_and_value[0]) + 1) == 0)
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



int ft_unset_head_of_envp_list(t_environment_list **head, const char *name)
{
    t_environment_list *temp;

    if (*head == NULL) 
        return (1);
    if (ft_strncmp((*head)->name_and_value[0], name,
        ft_strlen((*head)->name_and_value[0]) + 1) == 0)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp->name_and_value[0]);
        free(temp->name_and_value[1]);
        free(temp->name_and_value);
        free(temp);
        return (1);
    }
    return (0);
}
