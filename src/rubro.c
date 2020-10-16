/*
 * rubro.c
 *
 *  Created on: 15 oct. 2020
 *      Author: Gonzalo
 */

/*

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "rubro.h"
static int rubro_generarNuevoId (void);


int rubro_cargarRubros(Rubro* pArrayRubro, int limiteRubro,Aviso* pArrayAviso, int limiteAviso)
{
	int retorno=-1;
	int i;
	int indice;
	if(pArrayRubro!= NULL && pArrayAviso!=NULL && limiteRubro>0 && limiteAviso>0)
	{
		for(i=0;i<limiteAviso;i++)
		{
			if(pArrayAviso[i].isEmpty==FALSE && (rubro_buscarLibreRef(pArrayRubro,limiteRubro,&indice)==0))
			{
				strncpy(pArrayRubro[indice].nombreRubro,pArrayAviso[i].rubroAviso,LONG_NOMBRE);
				pArrayRubro[indice].cantRubro++;
				pArrayRubro[indice].idRubro=rubro_generarNuevoId();
				pArrayRubro[indice].isEmpty=FALSE;
				retorno=0;
			}
		}
	}
	return retorno;
}


static int rubro_generarNuevoId (void)
{
	static int id = 0;
	id = id+1;
	return id;
}

int rubro_ImprimirMayorCantidadDeRubros(Rubro* pArrayRubro, int limiteRubro)
{
	int retorno=-1;
	int i;
	int banderaPrimerRubro=TRUE;
	int cantidadAvisos;
	int rubroMaximo;
	Rubro bufferRubro;

	if(pArrayRubro!=NULL && limiteRubro>0)
	{
		for(i=0;i<limiteRubro;i++)
		{
			if(rubro_mayorCantidadAvisos(pArrayRubro,limiteRubro,pArrayRubro[i].nombreRubro,&cantidadAvisos)==0)
			{
				if(banderaPrimerRubro==TRUE || rubroMaximo<cantidadAvisos)
				{
					banderaPrimerRubro=FALSE;
					rubroMaximo=cantidadAvisos;
					strncpy(bufferRubro.nombreRubro,pArrayRubro[i].nombreRubro,LONG_NOMBRE);
					retorno=0;
				}
			}
		}
	}
	if(retorno==0)
	{
		printf("El rubro con mas cantidad de avisos es %s y sus avisos son %d",bufferRubro.nombreRubro,cantidadAvisos);
	}
	else
	{
		printf("No hay rubros cargados");
	}
	return retorno;
}


int rubro_mayorCantidadAvisos(Rubro* pArrayRubro, int limiteRubro, char* textoRubro,int* pResultado)
{
	int retorno=-1;
	int i;
	int contadorRubro=0;
	if(pArrayRubro!=NULL && limiteRubro>0 && textoRubro!=NULL && pResultado!=NULL)
	{
		for(i=0;i<limiteRubro;i++)
		{
			if(pArrayRubro[i].isEmpty && (strncmp(pArrayRubro[i].nombreRubro,textoRubro,LONG_NOMBRE)==0))
			{
				contadorRubro++;
				retorno=0;
			}
		}
	}
	return retorno;
}

int rubro_buscarLibreRef (Rubro * pArray, int limite, int * pIndice)
{
	int retorno = -1;
	int i ;
		if (pArray != NULL && limite >0 && pIndice != NULL){
			for ( i = 0; i<limite; i++) {
				if(pArray[i].isEmpty == TRUE)
					{
						*pIndice = i;
						retorno = 0;
						break;
					}
			}
		}
	return retorno;
}
int rubro_init(Rubro * pArray, int limite)
{
	int retorno = -1;
	if (pArray != NULL && limite >0){
		for (int i = 0; i<limite; i++ )
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}
*/
