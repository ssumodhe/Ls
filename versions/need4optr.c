void	opt_r(t_merge **args)
{
	t_merge	*tmp;
	t_merge	*before;
	t_merge	*tmp_2;
	int		i;

	i = 0;
	tmp = *args;
	tmp->prev = NULL;
	before = tmp;
ft_putstr(RED);
			ft_putendl(tmp->str);
		//	ft_putstr(YELLOW);
		//	ft_putendl(tmp->prev->str);
			ft_putstr(RESET);
	tmp = tmp->next;



	while (tmp->next != NULL)
	{
		i++;
		tmp->prev = before;
			ft_putstr(RED);
			ft_putendl(tmp->str);
			ft_putstr(YELLOW);
			ft_putendl(tmp->prev->str);
			ft_putstr(RESET);
		before = tmp;
		tmp = tmp->next;
	}
	if (i != 0)
		tmp->prev = before;
			ft_putstr(RED);
			ft_putendl(tmp->str);
			ft_putstr(YELLOW);
			ft_putendl(tmp->prev->str);
			ft_putstr(RESET);

	tmp_2 = tmp;
			ft_putendl(tmp->str);
	before = tmp_2;
	while (tmp->prev != NULL)
	{
		tmp_2 = tmp;
		tmp_2->next = tmp->prev;
		tmp_2 = tmp_2->next;
		tmp = tmp->prev;
	}
	tmp_2->next = NULL;
	tmp = *args;
	*args = before;
}
