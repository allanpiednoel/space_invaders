/*
 * compteur.c
 *
 *  Created on: 27 janv. 2020
 *      Author: allan
 */

#include "vt100.h"
#include "depl_enn.h"

void sleep_moi(unsigned long int t)
{

	int i = 0;
	unsigned long int max = t * 100000;
	do
	{
		i++;
	} while (i <= max);
}
