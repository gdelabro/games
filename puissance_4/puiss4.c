/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puiss4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:31:10 by gdelabro          #+#    #+#             */
/*   Updated: 2017/01/10 13:02:38 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NBLIN 6
#define NBCOL 7

/* Function that clear the terminal's screen */
void clearScreen() {
	/* Animation - clear the previous display */
	printf("%c[2J", 0x1B);
	/* Animation - Move the cursor top-left */
	printf("%c[%d;%dH", 0x1B, 1, 1);
}


void	initArray(int nbLin, int nbCol, int board[nbLin][nbCol], int value)
{
	int i;
	int i2;

	i = -1;
	while (++i < nbLin && (i2 = -1))
		while (++i2 < nbCol)
			board[i][i2] = value;
}

void	showBoard(int nbLin, int nbCol, int board[nbLin][nbCol])
{
	int i;
	int i2;

	i = -1;
	clearScreen();
	while (++i < nbLin && (i2 = -1))
	{
		while (++i2 < nbCol)
		{
			if (i2 == 0)
				printf("|");
			if (board[i][i2] == 0)
				printf("   |");
			if (board[i][i2] == 1)
				printf("\033[31;01m o\033[00m |");
			if (board[i][i2] == 2)
				printf("\033[36;01m o\033[00m |");
		}
		printf("\n");
	}
	i = -1;
	while (++i < nbCol)
		printf(" ---");
	i = -1;
	printf("\n");
	while (++i < nbCol)
		printf("  %d ", i);
	printf("\n");
}

int		getColumnForPawn(int nbLin, int nbCol, int board[nbLin][nbCol])
{
	int col;
	int ret;

	printf("Enter the coordinate of the column you want to put your pawn on: ");
	!(ret = scanf("%d", &col)) ? exit (-1) : 0;
	while (col >= nbCol || col < 0|| board[0][col])
	{
		col > nbCol ? printf("Wrong number of column (outside of the board), please re-try.\n") : printf("\nThis column is full so you can't add any more pawn, please re-try.\n");
		scanf("%d", &col);
	}
	return (col);
}

int		placePawn(int nbLin, int nbCol, int board[nbLin][nbCol], int pawnCol, int pawn)
{
	int i;

	i = nbLin;
	while (--i >= 0)
	{
		if (board[i][pawnCol] == 0)
		{
			board[i][pawnCol] = pawn;
			return (i);
		}
	}
	return (0);
}

int		checkFourInLine(int nbLin, int nbCol, int board[nbLin][nbCol], int pawnLin, int pawnCol)
{
	int nbPawn;
	int i;
	int i2;

	if (board[pawnLin][pawnCol] == 0)
		return (0);
	i = pawnLin;
	i2 = pawnCol;
	nbPawn = 1;
	while (i2 - 1 >= 0 && board[i][i2 - 1] == board[pawnLin][pawnCol])
		i2--;
	while (i2 + 1 < nbCol && board[i][i2 + 1] == board[pawnLin][pawnCol] && ++i2)
		if (++nbPawn >= 4)
			return (1);
	i = pawnLin;
	i2 = pawnCol;
	nbPawn = 1;
	while (i - 1 >= 0 && i2 - 1 >= 0 && board[i - 1][i2 - 1] == board[pawnLin][pawnCol] && --i > -1)
		i2--;
	while (i + 1 < nbLin && i2 + 1 < nbCol && board[i + 1][i2 + 1] == board[pawnLin][pawnCol] && ++i2 && ++i)
		if (++nbPawn >= 4)
			return (1);
	i = pawnLin;
	i2 = pawnCol;
	nbPawn = 1;
	while (i + 1 < nbLin && i2 - 1 >= 0 && board[i + 1][i2 - 1] == board[pawnLin][pawnCol] && ++i)
		i2--;
	while (i - 1 >= 0 && i2 + 1 < nbCol && board[i - 1][i2 + 1] == board[pawnLin][pawnCol] && ++i2 && --i > -1)
		if (++nbPawn >= 4)
			return (1);
	i = pawnLin;
	i2 = pawnCol;
	nbPawn = 1;
	while (i - 1 >= 0 && board[i - 1][i2] == board[pawnLin][pawnCol])
		i--;
	while (i + 1 < nbLin && board[i + 1][i2] == board[pawnLin][pawnCol] && ++i)
		if (++nbPawn >= 4)
			return (1);
	return (0);
}

int		runAStep(int nbLin, int nbCol, int board[nbLin][nbCol], int numPlayer)
{
	int pawnCol;
	int i;
	int i2;

	i = -1;
	i2 = -1;
	printf("\n#### Player %d, your turn ####\n", numPlayer);
	pawnCol = getColumnForPawn(nbLin, nbCol, board);
	placePawn(nbLin, nbCol, board, pawnCol, numPlayer);
	while (++i < nbLin && (i2 = -1))
		while (++i2 < nbCol)
			if (checkFourInLine(nbLin, nbCol, board, i, i2) == 1)
				return (1);
	return (0);
}

int		runGame(int nbLin, int nbCol, int board[nbLin][nbCol])
{
	int a;
	int coup;
	int joueur;
	int gagnant;

	a = 1;
	joueur = 1;
	coup = nbLin * nbCol;
	gagnant = 0;
	do
	{
		showBoard(nbLin, nbCol, board);
		runAStep(nbLin, nbCol, board, joueur) == 1 ? a = 0 : 0;
		a == 0 ? gagnant = joueur : 0;
		--coup == 0 ? a = 0 : 0;
		if (joueur == 1)
			joueur = 2;
		else
			joueur = 1;
	} while (a);
	showBoard(nbLin, nbCol, board);
	return (gagnant);
}

void	endOfGame(int numWinner)
{
	printf("\n\n#### THE GAME IS OVER ####\n");
	if (numWinner == 0)
		printf("\nIt's a draw!\n");
	else
		printf("\nAnd the winner is Player %d!\n", numWinner);
}

int		main(void)
{
	int		board[NBLIN][NBCOL];
	int		winner;

	initArray(NBLIN, NBCOL, board, 0);
	winner = runGame(NBLIN, NBCOL, board);
	endOfGame(winner);
	return (1);
}
