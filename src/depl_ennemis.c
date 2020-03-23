/*
 * depl_ennemis.c
 *
 *  Created on: 24 janv. 2020
 *      Author: allan
 */
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "vt100.h"
#include "serie.h"
#include "depl_enn.h"
#include <stdio.h>
#include <stdlib.h>
typedef uint16_t u16;

static u8 sens = 0;
static u8 compteur_sens = 0;
static u8 compteur_vies_ennemis = VIE_ENNEMIS * NOMBRE_ENNEMIS;
static u8 compteur_tir_enn = 0;
u8 x_mun;
u8 y_mun_;
u8 *ptr_y_mun_enn = &y_mun_;
u8 *ptr_x_mun_enn = &x_mun;
u8 *ptr_vies_ennemis = &compteur_vies_ennemis;
u8 *ptr_compteur_tir = &compteur_tir_enn;
int tps = VITESSE_ENNEMI_TPS;
donnees_ennemi tableau_ennemis[9] =
{
{ 15, 3, VIE_ENNEMIS, 0, TAILLE_ENNEMIS },
{ 25, 3, VIE_ENNEMIS, 1, TAILLE_ENNEMIS },
{ 35, 3, VIE_ENNEMIS, 2, TAILLE_ENNEMIS },
{ 45, 3, VIE_ENNEMIS, 3, TAILLE_ENNEMIS },
{ 15, 5, VIE_ENNEMIS, 4, TAILLE_ENNEMIS },
{ 25, 5, VIE_ENNEMIS, 5, TAILLE_ENNEMIS },
{ 35, 5, VIE_ENNEMIS, 6, TAILLE_ENNEMIS },
{ 45, 5, VIE_ENNEMIS, 7, TAILLE_ENNEMIS },
{ 4, 4, 4, ID_BOSS, 3 }, };

void depl_1_enn(donnees_ennemi *p_ennemy)
{
	uint8_t i;
	//condition ennemi vivant
	if (p_ennemy->vie_enne != 0)
	{

//game over si l'ennemi est en bas de l'ecran
		if (p_ennemy->y_enne == 22)
		{
			game_over();
		}

		//condition servant a connaitre le sens de mouvement de l'ennemi avec les bordures de l'ecran

		if (p_ennemy->x_enne + p_ennemy->taille == 79
				|| p_ennemy->x_enne - 2 == 1)
		{
			compteur_sens += 1;
		}
		sens = compteur_sens % 2;

		//vers la droite
		if (sens == 0)
		{
			vt100_move(p_ennemy->x_enne, p_ennemy->y_enne);
			serial_puts(" ");
			p_ennemy->x_enne += 1;
			if (p_ennemy->ID != ID_BOSS)
			{
				ennemi_base(p_ennemy->x_enne, p_ennemy->y_enne);
			}
			else
				boss(p_ennemy->x_enne, p_ennemy->y_enne);
		}
		//vers la gauche
		if (sens == 1)
		{

			vt100_move(p_ennemy->x_enne + p_ennemy->taille - 1,
					p_ennemy->y_enne);
			serial_puts(" ");
			p_ennemy->x_enne -= 1;
			if (p_ennemy->ID != ID_BOSS)
			{
				ennemi_base(p_ennemy->x_enne, p_ennemy->y_enne);
			}
			else
				boss(p_ennemy->x_enne, p_ennemy->y_enne);

		}

		// descendre d'une ligne
		if ((p_ennemy->x_enne == 72 && p_ennemy->ID != 8)
				|| (p_ennemy->x_enne == 3 && p_ennemy->ID != 8))
		{

			if (sens == 0)
			{
				compteur_sens = 1;
				/*cette ligne a résolu le problème de l'ennemi droite qui se rapprochait
				 de sont voisin jusqu'a fusionner avec et causer des bugs vers la fin du jeu.
				 je ne comprends pas pourquoi x)  */

			}

			for (i = 0; i <= ID_CASE_MAX; i++)
			{

				vt100_move(tableau_ennemis[i].x_enne,
						tableau_ennemis[i].y_enne);
				serial_puts("      ");
				tableau_ennemis[i].y_enne++;
			}
			ennemi_base(p_ennemy->x_enne, p_ennemy->y_enne);

			sleep_moi(VITESSE_ENNEMI_TPS);

		}
	}

}

void tir_enn(donnees_ennemi *p_ennemy)
{
	//condition pour que le missile ne suive pas l'ennemi une fois lancé
	if (*ptr_compteur_tir == 0)
	{
		*ptr_y_mun_enn = p_ennemy->y_enne;
		*ptr_x_mun_enn = p_ennemy->x_enne + (p_ennemy->taille / 2);
	}

	//actions pour faire descendre le missile
	vt100_move(*ptr_x_mun_enn, *ptr_y_mun_enn);
	serial_puts(" ");
	*ptr_y_mun_enn += 1;
	vt100_move(*ptr_x_mun_enn, *ptr_y_mun_enn);
	serial_puts(":");
	*ptr_compteur_tir = 1;

	//effacer le missile une fois qu'il a dépassé le perso
	if (*ptr_y_mun_enn == 23)
	{
		vt100_move(*ptr_x_mun_enn, *ptr_y_mun_enn - 1);
		serial_puts(" ");
		vt100_move(*ptr_x_mun_enn, *ptr_y_mun_enn);
		serial_puts(" ");

		*ptr_compteur_tir = 0;
		*ptr_y_mun_enn = p_ennemy->y_enne;

	}
	// condition d'annimation si hit + implémentation de la hitbox
	if (*ptr_vie_perso != 0&& *ptr_y_mun_enn == INIT_PERSO_Y
	&& *ptr_x_mun_enn >= *ptr_x_perso
	&& *ptr_x_mun_enn <= *ptr_x_perso + TAILLE_PERSO)
	{
		vt100_move(*ptr_x_mun_enn, *ptr_y_mun_enn + 1);
		serial_puts(" ");
		//sleep_moi(tps);
		vt100_move(*ptr_x_perso, INIT_PERSO_Y);
		serial_puts("#@~@#");
		*ptr_vie_perso -= 1;

		sleep_moi(20);
		perso(*ptr_x_perso, INIT_PERSO_Y);
	}
}

void hit_ennemis(donnees_ennemi *p_ennemy)
{
	// condition d'annimation si hit
	if (p_ennemy->vie_enne != 0 && *ptr_y_mun == p_ennemy->y_enne
			&& *ptr_x_missile >= p_ennemy->x_enne
			&& *ptr_x_missile <= p_ennemy->x_enne + p_ennemy->taille)

	{
		vt100_move(*ptr_x_missile, *ptr_y_mun + 1);
		serial_puts(" ");
		sleep_moi(tps);
		vt100_move(p_ennemy->x_enne, p_ennemy->y_enne);
		serial_puts("&#$#&");
		p_ennemy->vie_enne -= 1;
		//le faire disparaitre
		sleep_moi(20);
		vt100_move(p_ennemy->x_enne, p_ennemy->y_enne);
		serial_puts("       ");
		*ptr_y_mun = 3;
		compteur_vies_ennemis -= 1;

	}
}

void random_tir(donnees_ennemi *p_ennemy)
{
	if (*ptr_y_mun_enn == p_ennemy->y_enne) //opération determinant un
											//nombre aléatoire
	{
		*ptr_lun_apres_lautre = *ptr_tir_ennemi_switch
				% (*ptr_vies_ennemis / VIE_ENNEMIS);
	}
	//condition de tir
	if ((p_ennemy->vie_enne != 0 && *ptr_y_mun_enn == p_ennemy->y_enne)
			|| *ptr_y_mun_enn != p_ennemy->y_enne)

	{
		tir_enn(&tableau_ennemis[*ptr_lun_apres_lautre]);
		sleep_moi(1);
	}
	//si l'ennemi est mort, effacer son missile
	else if (p_ennemy->vie_enne == 0)
	{
		vt100_move(*ptr_x_mun_enn, *ptr_y_mun_enn);
		serial_puts(" ");
		*ptr_y_mun_enn = 23;
	}
}
