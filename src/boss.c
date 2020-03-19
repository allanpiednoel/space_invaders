/*
 * boss.c
 *
 *  Created on: 10 mars 2020
 *      Author: allan
 */
#include <stdlib.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "vt100.h"
#include "persos.h"
#include "serie.h"
#include "depl_enn.h"
#include "menu.h"

extern signed char carac;

void animation()
{
	int xboss;
	int yboss = 12;
	sleep_moi(100);
	vt100_move(35, 8);
	serial_puts("ATTENTION");
	sleep_moi(100);
	vt100_move(35, 9);
	serial_puts("LE PATRON");
	sleep_moi(100);
	vt100_move(37, 10);
	serial_puts("ARRIVE");
	for (xboss = 2; xboss <= 40; xboss++)
	{
		boss(xboss, yboss);
		if (xboss > 2)
		{
			vt100_move(xboss - 1, yboss);
			serial_putchar(' ');
		}
		sleep_moi(8);
	}
	sleep_moi(50);
	vt100_move(41, 13);
	serial_putchar('\\');
	vt100_move(40, 14);
	serial_puts("c'est moi");
	sleep_moi(400);
	vt100_clear_screen();
	bordures();
	do
	{
		vt100_move(xboss, yboss);
		serial_puts("   ");
		yboss -= 1;
		xboss -= 3;
		boss(xboss, yboss);
		sleep_moi(10);
	} while (yboss != 4);
	for (; xboss >= 3; xboss--)
	{
		vt100_move(xboss + 1, yboss);
		serial_puts("   ");
		boss(xboss, yboss);
		sleep_moi(5);
	}
	sleep_moi(100);
}

void combat_final()
{
	animation();
	while (tableau_ennemis[8].vie_enne != 0)
	{
		if (*ptr_vie_perso == 0)
		{
			vt100_clear_screen();
			bordures();
			game_over();
		}
		depl_perso();
		compteur_vies(*ptr_vie_perso);
		if (carac == 'z' || (*ptr_y_mun != 22 && *ptr_tir_ennemi % 2 == 0))
		{
			tir();
		}

		depl_1_enn(&tableau_ennemis[8]);
		hit_ennemis(&tableau_ennemis[8]);
		*ptr_tir_ennemi += 1;
		if ((*ptr_tir_ennemi % 2 == 0 && p_ennemy->vie_enne != 0)
				|| *ptr_y_mun_enn != p_ennemy->y_enne)
		{
			tir_enn(&tableau_ennemis[8]);

			sleep_moi(VITESSE_JEU);
		}

	}
}

