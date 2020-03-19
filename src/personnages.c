/*
 * personnages.c
 *
 *  Created on: 13 janv. 2020
 *      Author: allan
 */
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "vt100.h"
#include "serie.h"
#include "depl_enn.h"
#include "menu.h"
#include <stdint.h>



void ennemi_base(int x, int y)
{
	vt100_move(x, y);
	serial_puts("-|**|-");
}

void perso(int x, int y)
{
	vt100_move(x, y);
	serial_puts("_^|^_");
}

void boss(int x, int y)

{
	vt100_move(x, y);
	serial_puts("\\£/");
}

void compteur_vies(int nb_vies)
{
//
	int compteur;
	for (compteur = 0; compteur <= nb_vies - 1; compteur++)
	{
	vt100_move(2, 23);
	serial_puts("vies restantes : ");
		perso(19 + 6 * compteur, 23);
	}
	vt100_move(19 + 6 * *ptr_vie_perso, 23);
	serial_puts("     ");
}

//on peut aussi passer par un switch case

//	switch (*ptr_vie_perso)
//	{
//	case 2:
//
//
//		vt100_move(19 + 6 * *ptr_vie_perso, 23);
//		serial_puts("     ");
//		break;
//
//	case 1:
//
//
//		vt100_move(19 + 6 * *ptr_vie_perso, 23);
//		serial_puts("     ");
//		break;
//
//	case 0:
//
//		vt100_move(19 + 6 * *ptr_vie_perso, 23);
//		serial_puts("     ");
//		break;
//	}
//
//	}

