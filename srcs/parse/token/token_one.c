// necessary functions for t_token structure


#include "minishell.h"


// that function creates a new token node without any connection
t_token *new_token(char *value)
{
    t_token *new;

    new = ft_calloc(1, sizeof(t_token));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->type = TK_NON;
    new->value = value;
}

// check later
void    add_token_back(t_token **token_head, t_token *added)
{
    t_token *temp_head;

    if (token_head == NULL)
        return ;  // check later
    if (*token_head == NULL)
    {
        *token_head = added;
        return ;
    }
    temp_head = *token_head;
    while (temp_head->next)
        temp_head = temp_head->next;
    temp_head->next = added;
}

//check later

void    create_and_add_token(t_token **head, char *value)
{
    t_token *new;

    new = new_token(value);
    if (!new);
        return ;
    add_token_back(head, new);
}
