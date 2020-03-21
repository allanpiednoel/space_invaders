/*
 * jeu.c
 *
 *  Created on: 19 mars 2020
 *      Author: allan
 */

#include <stdlib.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "vt100.h"
#include "serie.h"
#include "depl_enn.h"

extern signed char carac;
static u8 vie_perso = VIES_PERSO;
u8 *ptr_vie_perso = &vie_perso;

void jeu()
{
	//u8 a;
	uint8_t i;
	//boucle infinie faisant tourner le jeu
	while (1)
	{
		*ptr_tir_ennemi_switch += 1;

		//fonction déplacement joueur
		depl_perso();

		//determine le nombre de vies restantes du joueur
		compteur_vies(vie_perso);

		//fonction déplacement ennemi
		for (i = 0; i <= ID_CASE_MAX; i++)
		{
			depl_1_enn(&tableau_ennemis[i]);
			hit_ennemis(&tableau_ennemis[i]);

		}
		random_tir(&tableau_ennemis[*ptr_lun_apres_lautre]);



		//condition pour pouvoir tirer et faire continer la course du missile
		if (carac == 'z' || *ptr_y_mun != 22)
		{

			tir();

		}

		//animation combat final après avoir tué tout les ennemis
		if (*ptr_vies_ennemis == 0)
		{
			break;
		}

		//animation game over
		if (*ptr_vie_perso == 0)
		{
			vt100_clear_screen();
			bordures();
			game_over();
		}
		//limiter l'accélération du jeu lorsqu'il reste peu d'ennemis
		sleep_moi(VITESSE_JEU);
	}
	vt100_clear_screen();
	bordures();
	combat_final();
	vt100_clear_screen();
	bordures();
	while (1)
	{
		ecran_fin();
	}
}
