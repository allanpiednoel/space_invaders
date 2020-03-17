/*
 * menu.h
 *
 *  Created on: 13 janv. 2020
 *      Author: allan
 */

#ifndef MENU_H_
#define MENU_H_
#include <stdint.h>
#include "depl_enn.h"
#define INIT_PERSO_X (37)
#define INIT_PERSO_Y (22)
#define VITESSE_JEU (4)
#define VIES_PERSO (3)
#define LIMITE_DROITE_ECRAN (74)
#define LIMITE_GAUCHE_ECRAN (2)
#define BAUDRATE (115200)
#define TAILLE_PERSO (6)

void menu();
void bordures();
void rangs_ennemis();
void perso_init();
void depl_perso();
void ecran_jeu(void);
void sleep_moi(unsigned long t);
void init_enns();
void game_over();
void compteur_vies();
void ecran_fin();
void tir();
void jeu();
int *ptr_x_missile;
int *ptr_y_mun;
u8*ptr_tir_ennemi;
int *ptr_x_perso;
u8 *ptr_vie_perso;
u8 *ptr_lun_apres_lautre;
u8 *ptr_tir_ennemi_switch;

#endif /* MENU_H_ */
