void		ft_prog(t_option *opt, t_args *args)
{
	t_flags		flag;
	int			removed;
	t_numbers	numbers;

	flag = init_flag();
	flag = check_opt(opt, flag);
	args = ft_mergesort(args, ft_ascii_mergesort);
	get_error_args(&args); // recupere les valeurs errno
	put_error_args(&args);
	removed = remove_error_args(&args, 0);
	numbers = get_numbers(args, flag);
	numbers.removed = removed;

	if (flag.u_r == 1) // if -R.
	{
	/*	if (flag.t == 1 && args)
			all_args_opt_t(&args);
		if (flag.l_r == 1 && args)
			all_args_opt_r(&args);*/

		process_args(&args, flag.a); // creer tous les bellow des args et trie ascii
		process_flags(&args, flag); // tri -t et -r et -l pour les args

	if (flag.l_r == 1 && args)
		opt_l_r(&args); // trie les bellow pour -r //NE PAS METTRE DANS PROCESS_FLAGS
	if (flag.t == 1 && args)
		opt_t(&args); // trie les bellow pour -t 
	//if (flag.l == 1 && args)
		//opt_l(&args); // trie les bellow pour -l 

		alone_2(args, flag); // affiche les file NON OUVRABLES
		if (args)
		{
			opt_u_r(&args, flag, numbers);
		}
	}
	else if (flag.u_r == 0) // if pas -R.
	{
	/*	if (flag.t == 1 && args)
			all_args_opt_t(&args);
		if (flag.l_r == 1 && args)
			all_args_opt_r(&args);*/
		process_args(&args, flag.a);
		process_flags(&args, flag); //trie les arg

	if (flag.l_r == 1 && args)
		opt_l_r(&args); // trie les bellow pour -r //NE PAS METTRE DANS PROCESS_FLAGS
	if (flag.t == 1 && args)
		opt_t(&args); // trie les bellow pour -t 
	//if (flag.l == 1 && args)
		//opt_l(&args); // trie les bellow pour -l 

		alone(&args, flag, numbers);
	}
}
