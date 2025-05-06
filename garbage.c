#include "garbage.h"

void	free_garbage(t_garbage **garbage)
{
	t_garbage	*temp;

	if (!garbage)
		return ;
	if (*garbage)
	{
		while (*garbage)
		{
			temp = *garbage;
			*garbage = (*garbage)->next;
			if (temp->ptr)
				free(temp->ptr);
			free(temp);
		}
	}
}

t_garbage *new_garbage(void *allocated)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (write(2,"malloc failure\n",15) ,NULL);
	new->ptr = allocated;
	new->next = NULL;
	return (new);
}

void	garbage_add_back(void *allocated, t_garbage **garbage)
{
	t_garbage	*last;
    t_garbage *new_allocation;

	if (!garbage)
		return ;
    new_allocation = new_garbage(allocated);
    if (!new_allocation)
        return (free(allocated));
    if (!*garbage)
	{
		*garbage = new_allocation;
		return ;
	}
	last = *garbage;
	while (last->next)
		last = last->next;
	if (last)
		last->next = new_allocation;
}

/*
** This function is used to allocate memory and add it to the garbage list.
** It takes a size and an action (ALLOC or FREE) as parameters.
** If the action is ALLOC, it allocates memory of the given size and adds it to the garbage list.
** If the action is FREE, it frees all the memory in the garbage list.
** It uses static t_garbage *garbage to keep track of the allocated memory.
** It returns the allocated memory if action is ALLOC, or NULL if action is FREE.
*/

void *alloc(size_t size, e_action action)
{
    void *returned;
    static t_garbage *garbage;
    if(action == ALLOC)
    {
        returned = malloc(size);
        if (!returned)
            return (write(2,"malloc failure\n",15) ,NULL);
        garbage_add_back(returned, &garbage);
        return (returned);
    }
    else if (action == FREE)
        free_garbage(&garbage);
    return (NULL);
}
