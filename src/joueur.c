/*
 * joueur.c
 *
 *  Created on: 13 mars 2020
 *      Author: allan
 */
#include <stdlib.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "vt100.h"
#include "serie.h"
#include "depl_enn.h"
extern int carac;
extern int x_missile;
extern int x_perso;
extern int y_perso;

void tir()
{
	//condition pour que le missile ne suive pas le perso une fois lancé
	if (*ptr_y_mun == 22)
	{
		*ptr_x_missile = *ptr_x_perso + 2;
	}

	//actions pour faire descendre le missile
	vt100_move(*ptr_x_missile, *ptr_y_mun);
	serial_puts("|");
	vt100_move(*ptr_x_missile, *ptr_y_mun + 1);
	serial_puts(" ");
	;
	*ptr_y_mun -= 1;

	//effacer le missile une fois qu'il a dépassé les ennemis
	if (*ptr_y_mun == 2)
	{
		vt100_move(*ptr_x_missile, *ptr_y_mun + 1);
		serial_puts(" ");

		//reinitialisation du missile
		*ptr_y_mun = 22;

	}
}

void depl_perso(void)
{

	carac = serial_get_last_char();
	//aller vers la droite
	if (carac == 'd')
	{
		vt100_move(*ptr_x_perso, y_perso);
		serial_puts("     ");
		*ptr_x_perso += 1;
		//empecher le perso de sortir de l'ecran
		if (*ptr_x_perso > LIMITE_DROITE_ECRAN)
		{
			*ptr_x_perso = LIMITE_DROITE_ECRAN;

		}
		perso(*ptr_x_perso, y_perso);
	}
//aller vers la gauche
	if (carac == 'q')
	{
		vt100_move(*ptr_x_perso, y_perso);
		serial_puts("     ");
		*ptr_x_perso -= 1;

		//empecher le perso de sortir de l'ecran

		if (*ptr_x_perso < LIMITE_GAUCHE_ECRAN)
		{
			*ptr_x_perso = LIMITE_GAUCHE_ECRAN;

		}
		perso(*ptr_x_perso, y_perso);

	}

}

