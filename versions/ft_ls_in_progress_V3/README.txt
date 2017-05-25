
PARSING:

1 - Attention ls tout seul (le . est un directory qui contient tous les
elements du fichiers sur lequel on travaille)
2 - Attention ls --
3 - Si ls -'' -> Segfault
4 - Attention ls -
5 - Attention MESSAGE D'ERREUR SUR LA SORTIE D'ERREUR
6 - Attention si argument envoyer avec / a la fin

Ft_Ls:

Main_ls.c:
	Je recupere tous les arguments passes en parametre.
	Je recupere en premier les options dans une liste chainee (->fill_option)
	Puis je recupere les arguments dans une liste chainee (->fill_args)
	Si il n'y a pas d'arguments, je cree tout de meme une liste avec un
	maillon et un "." comme nom (->fill_args).
	J'appelle ->ft_prog avec les deux listes generees (*opt et *args).

Prog_ls.c:
	J'initialise une structure flag.
	Puis je verifie si les options passes en parametre sont valides avec ->check_opt
	qui met le message d'erreur + usage en cas de necessite (EXIT si illegal option)
	et rempli la structure flag avec les differentes options valides (->fill_flag).
	Je range par ordre ascii les arguments de la liste *args (->ascii_order_args)
	Je verifie les erreurs des arguments, fournis par errno, et stock cet errno dans
	la liste associee *args (->get_error_args)
	Puis j'affiche les erreurs non liees au errno = 0, = 13 et = 20 (->put_error_args)
	Avec ->count_args, je recupere une structure numbers avec le nombre de fichier 
	directory et les autres.
	Je supprime de la liste *args, toutes les erreurs precedement affichees et 
	recupere le nombre de maillon supprimer dans numbers (->remove_error_args)
	J'appelle ->process_args avec la liste *args
	J'appelle ->process_flag avec la liste *args et les structures flag et numbers


