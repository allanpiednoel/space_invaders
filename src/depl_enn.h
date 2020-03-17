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
#define VIE_ENNEMIS (2)
#define NOMBRE_ENNEMIS (8)
#define FREQUENCE_TIR_ENNEMIS (10000)
#define ID_BOSS (8)
#define TAILLE_ENNEMIS (6)

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
void hit_ennemis(donnees_ennemi *p_ennemy);
void depl_1_enn(donnees_ennemi *p_ennemy);
u8 depl_enn();
u8 *ptr_x_mun_enn;
u8 *ptr_y_mun_enn;
u8 *ptr_compteur_tir;
u8 *ptr_vie_perso;
u8 *pstart_combat_final;
void tir_enn(donnees_ennemi *p_ennemy);
void combat_final();
void random_tir(donnees_ennemi *p_ennemy);

#endif /* DEPL_ENN_H_ */
