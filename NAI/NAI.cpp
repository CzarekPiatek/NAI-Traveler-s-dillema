// Botek.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

void game(int choice_bot1, int choice_bot2, int *w);
int bot_low(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[]);
int bot_high(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[]);
int bot_demo(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[]);
int bot_rand(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[]);

const int R = 25;
const int ilosc_gier = 1000;
int wybory1[ilosc_gier];
int wybory2[ilosc_gier];

int main()
{
	int j = 0;
	int choice1 = 0, choice2 = 0;
	int SCORE[2] = { 0, 0 };
	int *s;
	s = SCORE;

	srand(time(NULL));
	do {
		cout << "Runda " << j + 1 << endl;
		choice1 = bot_rand(SCORE[0], SCORE[1], j, wybory1, wybory2);
		choice2 = bot_demo(SCORE[1], SCORE[0], j, wybory2, wybory1);
		cout << "Gracz  wybral: " << choice1 << "\t";
		cout << "Gracz  wybral: " << choice2 << "\t" << endl;
		wybory1[j] = choice1;
		wybory2[j] = choice2;
		game(choice1, choice2, s);
		cout << endl << "Punktacja: \n\t" << SCORE[0] << "\n\t" << SCORE[1] << endl << endl << endl;
		j++;
	} while (j < ilosc_gier);
	cout << "Ncisnij ENTER aby kontynuowac...";
	getchar();
	system("CLS");
	cout << "Koniec gry!\n\t Gracz  uzyskal: " << SCORE[0] << "\n\t Gracz  uzyskal: "
		<< SCORE[1] << endl;
	getchar();
	return 0;
}

void game(int choice_bot1, int choice_bot2, int *w)
{
	bool flag = 0;
	if ((choice_bot1 < 180) || (choice_bot1 > 300)) {
		if ((choice_bot2 >= 180) && (choice_bot2 <= 300))
			w[1] += choice_bot2 + R;
		flag = 1;
	}
	if (!flag && ((choice_bot2 < 180) || (choice_bot2 > 300))) {
		if ((choice_bot1 >= 180) && (choice_bot1 <= 300))
			w[0] += choice_bot1 + R;
		flag = 1;
	}

	if (!flag) {
		if (choice_bot1 == choice_bot2) {
			w[0] += choice_bot1;
			w[1] += choice_bot1;
		}
		else {
			if (choice_bot1 > choice_bot2) {
				w[0] += choice_bot2 - R;
				w[1] += choice_bot2 + R;
			}
			else {
				w[0] += choice_bot1 + R;
				w[1] += choice_bot1 - R;
			}
		}
	}
}


int bot_low(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[])
{
	return 180;
}

int bot_high(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[])
{
	return 300;
}

int bot_rand(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[])
{
	return (rand() % 40) + 260;
}
int bot_demo(int points_bot1, int points_bot2, int round, int wybory1[], int wybory2[])
{
	int sum = 0, average = 0, averagelast5 = 0;
	if (round == 0)
	{
		return 290;
	}
	if (round > 1)
	{
		sum = 0;
		for (int i = round; i >= 0; i--)
		{
			sum = wybory2[i] + sum;
		}
		average = sum / round;
	}
	if (round > 15)
	{
		sum = 0;
		for (int i = round; i >= round - 15; i--)
		{
			sum = wybory2[i] + sum;
		}
		averagelast5 = sum / 15;
	}
	if (round == 150 || round == 450 || round == 800 || (wybory2[round - 1] < 180 || wybory2[round - 1] > 300))
	{
		return 300;
	}
	if (round <= 10 && wybory2[round-1] >= 185)
	{
		return wybory2[round - 1] - 5;
	}
	if (wybory2[round - 1] == wybory1[round - 1])
	{
		return wybory2[round - 1];
	}
	if (wybory2[round - 1] <= wybory1[round - 1])
	{
		return wybory2[round - 1];
	}
	else
	{
		return averagelast5;
	}
}