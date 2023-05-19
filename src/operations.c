#include "..\\./headers/screens.h"
#include "..\\./headers/operations.h"

extern int arr[3][3];
extern int pos, turn;

void getFirst(void)
{
	// if()
	pos = 0;
	while (arr[pos / 3][pos % 3])
		pos = (pos + 1) % 9;
	arr[pos / 3][pos % 3] = 3;
	return;
}


void move(void)
{
	arr[pos / 3][pos % 3] = 0;
	pos = (pos + 1) % 9;
	while (arr[pos / 3][pos % 3])
		pos = (pos + 1) % 9;
	arr[pos / 3][pos % 3] = 3;
}




int update(void)
{
	int w;
	if (turn == 0)
	{
		arr[pos / 3][pos % 3] = 1;
	}
	else
		arr[pos / 3][pos % 3] = 2;

	w = checkWinner();

	if (w != 0)
	{
		startGame();
		// Delay100ms(2);
	}

	if (w == 1)
	{
		// GPIO_PORTF_DATA_R=0x04;
		winner_x();
	}
	else if (w == 2)
	{
		// GPIO_PORTF_DATA_R = 0x08;
		winner_o();
	}
	else if (w == 3)
	{
		// GPIO_PORTF_DATA_R=0x0F;
		draw();
	}

	if (w != 0)
		return 1;

	getFirst();
	turn ^= 1;
	return 0;
}

int checkWinner(void)
{
	int i, j, x = 0, o = 0, d = 0, xd = 0, od = 0, rdo = 0, rdx = 0, xc = 0, oc = 0;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{

			if (arr[i][j] == 1)
			{
				if (i == j)
					xd++;
				if (2 - i == j)
					rdx++;

				x++;

				d++;
			}
			else if (arr[i][j] == 2)
			{
				if (i == j)
					od++;

				if (2 - i == j)
					rdo++;
				o++;
				d++;
			}

			if (arr[j][i] == 1)
			{
				xc++;
			}
			else if (arr[j][i] == 2)
			{
				oc++;
			}
		}
		if (x == 3 || xc == 3)
			return 1;
		else if (o == 3 || oc == 3)
			return 2;
		x = 0, o = 0, xc = 0, oc = 0;
	}

	if (xd == 3 || rdx == 3)
		return 1;
	if (od == 3 || rdo == 3)
		return 2;

	if (d == 9)
		return 3;
	return 0;
}

