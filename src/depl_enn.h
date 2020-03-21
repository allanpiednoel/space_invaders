/*
 * depl_enn.h
 *
 *  Created on: 24 janv. 2020
 *      Author: allan
 */

#ifndef DEPL_ENN_H_
#define DEPL_ENN_H_
#include <stdint.h>
typedef uint8_t u8;
#define VITESSE_ENNEMI_TPS (1)
#define VITESSE_BOSS_TPS (4)
#define ID_CASE_MAX (7)
#define VIE_ENNEMIS (1)
#define NOMBRE_ENNEMIS (8)
#define ID_BOSS (8)
#define TAILLE_ENNEMIS (6)
#define INIT_PERSO_X (37)
#define INIT_PERSO_Y (22)
#define VITESSE_JEU (4)
#define VIES_PERSO (3)
#define LIMITE_DROITE_ECRAN (74)
#define LIMITE_GAUCHE_ECRAN (2)
#define BAUDRATE (115200)
#define TAILLE_PERSO (6)

typedef struct
{
	u8 x_enne;
	u8 y_enne;
	u8 vie_enne;
	u8 ID;
	u8 taille;
} donnees_ennemi;
donnees_ennemi *p_ennemy;
donnees_ennemi tableau_ennemis[9];
u8 *ptr_vies_ennemis;

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
void ennemi_base(int x, int y);
void perso(int x, int y);
void boss(int x, int y);
void compteur_vies(int nb_vies);
void tir_enn(donnees_ennemi *p_ennemy);
void combat_final();
void random_tir(donnees_ennemi *p_ennemy);
void hit_ennemis(donnees_ennemi *p_ennemy);
void depl_1_enn(donnees_ennemi *p_ennemy);


int *ptr_x_missile;
int *ptr_y_mun;
u8*ptr_tir_ennemi;
int *ptr_x_perso;
u8 *ptr_vie_perso;
u8 *ptr_lun_apres_lautre;
u8 *ptr_tir_ennemi_switch;
u8 *ptr_x_mun_enn;
u8 *ptr_y_mun_enn;
u8 *ptr_compteur_tir;
u8 *ptr_vie_perso;
u8 *pstart_combat_final;






#endif /* DEPL_ENN_H_ */
