/*
 * menu.c
 *
 *  Created on: 13 janv. 2020
 *      Author: allan
 */
#include <stdlib.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "vt100.h"
#include "serie.h"
#include "depl_enn.h"

typedef uint8_t u8;

signed char carac = -1;
extern int tps;
static int x_perso = INIT_PERSO_X;
static int y_mun = INIT_PERSO_Y;
static int x_missile;
static u8 tir_ennemi;

static u8 lun_apres_lautre;
u8 *ptr_lun_apres_lautre = &lun_apres_lautre;
static uint8_t tir_ennemi_switch;
u8 *ptr_tir_ennemi_switch = &tir_ennemi_switch;
const u8 y_perso = INIT_PERSO_Y;
int *ptr_x_perso = &x_perso;
int *ptr_y_mun = &y_mun;
int *ptr_x_missile = &x_missile;
u8 *ptr_tir_ennemi = &tir_ennemi;

donnees_ennemi *p_ennemy;

void bordures()
{
	u8 x;
	u8 y;
	//bordures horizontales
	for (x = 1; x < 81; x++)
	{
		vt100_move(x, 1);
		serial_putchar(35);
		vt100_move(x, 24);
		serial_putchar(35);
	}

	//bordures verticales
	for (y = 1; y < 81; y++)
	{
		vt100_move(1, y);
		serial_putchar(35);
		vt100_move(80, y);
		serial_putchar(35);
	}
}

void ecran_fin()
{
	vt100_move(35, 8);
	serial_puts("OUUAAAAAAH");
	sleep_moi(50);
	vt100_move(35, 8);
	serial_puts("          ");
	vt100_move(38, 10);
	serial_puts("T'ES");
	sleep_moi(30);
	vt100_move(38, 10);
	serial_puts("    ");
	vt100_move(38, 12);
	serial_puts("TROP");
	sleep_moi(60);
	vt100_move(38, 12);
	serial_puts("    ");
	vt100_move(37, 14);
	serial_puts("FOOORT");
	sleep_moi(90);
	vt100_move(37, 14);
	serial_puts("      ");
}

void game_over()
{
	vt100_move(35, 8);
	serial_puts("GAME OVER");
	sleep_moi(50);
	vt100_move(35, 8);
	serial_puts("         ");
	sleep_moi(50);
//	vt100_move(36, 10);
//	serial_puts("T'ES NUL");
//	sleep_moi(50);
//	vt100_move(36, 10);
//	serial_puts("        ");
//	sleep_moi(50);
//	vt100_move(31, 12);
//	serial_puts("PERSONNE NE T'AIME");
//	sleep_moi(100);
//	vt100_move(31, 12);
//	serial_puts("                  ");
//	sleep_moi(100);
}

void menu()
{

	//menu
	vt100_clear_screen();
	bordures();
	vt100_move(18, 3);
	serial_puts("une escouade d'aliens veulent envahir la terre ");
	vt100_move(20, 4);
	serial_puts("tu as été choisi pour déjouer leurs plans");
	vt100_move(27, 5);
	serial_puts("(moi perso ils me font peur)");
	vt100_move(23, 6);
	serial_puts("J'espère on a fait le bon choix...");
	vt100_move(34, 10);
	serial_puts("SPACE INVADERS");
	vt100_move(3, 22);
	serial_puts("Réalisé par :");
	vt100_move(3, 23);
	serial_puts("Allan Piednoel");

	//commencer le jeu via la pression d'une touche
	while (carac < 0)
	{
		carac = serial_get_last_char();
		vt100_move(23, 18);
		serial_puts("appuyez sur n'importe quelle touche");

		sleep_moi(50);
		vt100_move(23, 18);
		serial_puts("                                      ");
		sleep_moi(50);

	}
	vt100_clear_screen();
	bordures();
	perso(INIT_PERSO_X, INIT_PERSO_Y);
	jeu();

}
