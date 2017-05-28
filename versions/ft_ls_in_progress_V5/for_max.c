	t_args	*tmp;
	t_args	*before;
	t_args	*tmp_2;

	tmp = *args;
	before = NULL;
	while (tmp->next != NULL)
	{
		tmp->prev = before;
		before = tmp;
		tmp = tmp->next;
	}
	tmp->prev = before;
