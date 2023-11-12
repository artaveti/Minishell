
#include "lib_for_minishell.h"

void unset(t_environment_list **head, t_environment_list ***e_head, const char *name);

int ft_unset(char **array_of_strings, t_environment_list **envp)
{
    int i = 1;
    while (array_of_strings[i] != NULL)
    {
        if (ft_wrong_name(array_of_strings[i]))
            break;
        unset(envp, &envp, array_of_strings[i]); 
        i++;
    }
    //exit(EXIT_SUCCESS);
    return (0);
}


void unset(t_environment_list **head, t_environment_list ***e_head, const char *name)
{
    t_environment_list *current;
    t_environment_list *prev;
    t_environment_list *temp;

    (void)e_head;
    if (*head == NULL) 
        return;
    if (!ft_strncmp((*head)->name_and_value[0], name, ft_strlen(name) + 1))
    {
        temp = *head;
        *e_head = &temp->next;
        free(temp->name_and_value[0]);
        free(temp->name_and_value[1]);
        free(temp->name_and_value);
        free(temp);
        // temp->name_and_value[0] = "HELLO";
        // temp->name_and_value[1] = "world";
        return;
    }
    current = *head;
    prev = current;
    while (current != NULL)
    {
        if (!ft_strncmp(current->name_and_value[0], name, ft_strlen(name) + 1))
        {
            prev->next = current->next;
            free(current->name_and_value[0]);
            current->name_and_value[0] = NULL;
            free(current->name_and_value[1]);
            current->name_and_value[1] = NULL;
            free(current->name_and_value);
            current->name_and_value = NULL;
            free(current);
            current = NULL;
            return;
        }
        prev = current;
        current = current->next;
    }
}
