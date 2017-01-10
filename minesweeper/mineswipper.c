#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *c)
{
	int i;

	i = -1;
	while (c[++i])
		ft_putchar(c[i]);
}

char	**create_map(int taille, int nb_mine)
{
	char **tab;
	int  **coord;
	int x;
	int y;
	int i;
	int i2;

	i = -1;
	if (nb_mine <= 0 || nb_mine > taille * taille || taille <= 0)
	{
		ft_putstr("nbr de mine ou taille incorrect.");
		exit (1);
	}
	tab = (char**)malloc(sizeof(*tab) * taille);
	coord = (int**)malloc(sizeof(*coord) * nb_mine);
	while (++i < taille)
	{
		tab[i] = (char*)malloc(sizeof(tab) * taille);
		i2 = -1;
		while (++i2 < taille)
			tab[i][i2] = '0';
	}
	i = -1;
	while (++i < nb_mine)
	{
		coord[i] = (int*)malloc(sizeof(coord) * 2);
		coord[i][0] = -1;
		coord[i][1] = -1;
	}
	while (coord[nb_mine - 1][0] == -1)
	{
		x = rand() * time(NULL) % taille;
		y = rand() * time(NULL) % taille;
		i2 = -1;
		while (i2 < nb_mine && coord[++i2][0] != x && coord[i2][1] != y && coord[i2][0] != -1)
			;
		if (coord[i2][0] == -1)
		{
			coord[i2][0] = x;
			coord[i2][1] = y;
			tab[y][x] = '1';
		}
	}
	return (tab);
}

int		mine_around(int i, int i2, int taille, char **tab)
{
	int nb;

	nb = 0;
	i && i2 && tab[i - 1][i2 - 1] == '1' ? nb++ : 0;
	i && tab[i - 1][i2] == '1' ? nb++ : 0;
	i2 && tab[i][i2 - 1] == '1' ? nb++ : 0;
	i < taille - 1 && i2 < taille - 1 && tab[i + 1][i2 + 1] == '1' ? nb++ : 0;
	i < taille - 1 && tab[i + 1][i2] == '1' ? nb++ : 0;
	i2 < taille - 1 && tab[i][i2 + 1] == '1' ? nb++ : 0;
	i && i2 < taille - 1 && tab[i - 1][i2 + 1] == '1' ? nb++ : 0;
	i < taille - 1 && i2 && tab[i + 1][i2 - 1] == '1' ? nb++ : 0;
	return (nb);
}

void	print_tab(char **tab, int taille)
{
	int i;
	int i2;
	int nb;

	i = -1;
	while (++i < taille && (i2 = -1))
	{
		while (++i2 < taille)
		{
			if (tab[i][i2] == '0')
				ft_putstr("-");
			else if (tab[i][i2] == '1')
				ft_putchar('-');
			else if (tab[i][i2] == '2')
				ft_putchar(mine_around(i, i2, taille, tab) + 48);
			ft_putchar(' ');
		}
		ft_putstr("\n");
	}
	ft_putstr("\n");
}

int		ft_compare(char **tab, char **tab2, int taille)
{
	int i;
	int i2;
	
	i = -1;
	while (++i < taille && (i2 = -1))
		while (++i2 < taille)
		{
			if (tab[i][i2] != tab2[i][i2])
				return (1);
		}
	return (0);
}

char	**ft_unlock_around(char **tab, int taille)
{
	int i;
	int i2;
	char **tab2;

	i = -1;
	tab2 = (char**)malloc(sizeof(*tab2) * taille);
	while (++i < taille && (i2 = -1))
	{
		tab2[i] = (char*)malloc(sizeof(tab2) * taille);
		while (++i2 < taille)
		{
			tab2[i][i2] = tab[i][i2];
		}
	}
	i = -1;
	while (++i < taille && (i2 = -1))
		while (++i2 < taille)
		{
			if (mine_around(i, i2, taille, tab) == 0 && tab2[i][i2] == '2')
			{
				i && i2 && tab2[i - 1][i2 - 1] == '0' ? tab2[i - 1][i2 - 1] = '2' : 0;
				i && tab2[i - 1][i2] == '0' ? tab2[i - 1][i2] = '2' : 0;
				i2 && tab2[i][i2 - 1] == '0' ? tab2[i][i2 - 1] = '2' : 0;
				i < taille - 1 && i2 < taille - 1 && tab2[i + 1][i2 + 1] == '0' ? tab2[i + 1][i2 + 1] = '2' : 0;
				i < taille - 1 && tab2[i + 1][i2] == '0' ? tab2[i + 1][i2] = '2' : 0;
				i2 < taille - 1 && tab2[i][i2 + 1] == '0' ? tab2[i][i2 + 1] = '2' : 0;
				i && i2 < taille - 1 && tab2[i - 1][i2 + 1] == '0' ? tab2[i - 1][i2 + 1] = '2' : 0;
				i < taille - 1 && i2 && tab2[i + 1][i2 - 1] == '0' ? tab2[i + 1][i2 - 1] = '2' : 0;
			}
		}
	while (--i > -1 && (i2 = taille))
		while (--i2 > 1)
		{
			if (mine_around(i, i2, taille, tab) == 0 && tab2[i][i2] == '2')
			{
				i && i2 && tab2[i - 1][i2 - 1] == '0' ? tab2[i - 1][i2 - 1] = '2' : 0;
				i && tab2[i - 1][i2] == '0' ? tab2[i - 1][i2] = '2' : 0;
				i2 && tab2[i][i2 - 1] == '0' ? tab2[i][i2 - 1] = '2' : 0;
				i < taille - 1 && i2 < taille - 1 && tab2[i + 1][i2 + 1] == '0' ? tab2[i + 1][i2 + 1] = '2' : 0;
				i < taille - 1 && tab2[i + 1][i2] == '0' ? tab2[i + 1][i2] = '2' : 0;
				i2 < taille - 1 && tab2[i][i2 + 1] == '0' ? tab2[i][i2 + 1] = '2' : 0;
				i && i2 < taille - 1 && tab2[i - 1][i2 + 1] == '0' ? tab2[i - 1][i2 + 1] = '2' : 0;
				i < taille - 1 && i2 && tab2[i + 1][i2 - 1] == '0' ? tab2[i + 1][i2 - 1] = '2' : 0;
			}
		}
	return (tab2);
}

void	ft_test_win(char **tab, int taille)
{
	int i;
	int i2;

	i = -1;
	while (++i < taille && (i2 = -1))
		while (++i2 < taille)
			if (tab[i][i2] == '0')
				return ;
	print_tab(tab, taille);
	ft_putstr("GAGNEE.\n");
	exit (1);
}

int		main(int argc, char **argv)
{
	int taille;
	char **tab;
	int i;
	int i2;
	int x;
	int y;

	i2 = -1;
	i = -1;
	if (argc != 3)
	{
		ft_putstr("usage: ./exe map_size nb_mine\n");
		exit (1);
	}
	taille = atoi(argv[1]);
	tab = create_map(taille, atoi(argv[2]));
	while (1)
	{
		print_tab(tab, taille);
		ft_putstr("entrer x: ");
		scanf("%d", &x);
		ft_putstr("entrer y: ");
		scanf("%d", &y);
		if (x >= taille || y >= taille)
			ft_putstr("x ou y invalide\n");
		if (tab[y][x] == '1')
		{
			ft_putstr("Perdu. T'es nul\n");
			exit (1);
		}
		if (tab[y][x] == '0')
		{
			tab[y][x] = '2';
			while (ft_compare(tab, ft_unlock_around(tab,taille),taille) == 1)
				tab = ft_unlock_around(tab, taille);
		}
		ft_test_win(tab, taille);
	}
	return (1);
}
