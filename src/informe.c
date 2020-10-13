/*
 * informe.c
 *
 *  Created on: 13 oct. 2020
 *      Author: Gonzalo
 */

#include <ctype.h>
#include <string.h>

#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "informe.h"

#define QTY_CUIT 13
#define QTY_CLIENTE 100
#define QTY_AVISOS 1000


//cliente con mas avisos
int informe_calcularTotalAvisos(Aviso* pArray,int len,int id,int *pResultado)
{
	int retorno=-1;
	int indiceAviso;
	int contadorAvisos=0;

	if(pArray!=NULL && len>0 && id>0 && pResultado!=NULL)
	{
		for(indiceAviso=0;indiceAviso<len;indiceAviso++)
		{
			if(pArray[indiceAviso].isEmpty==FALSE && id==pArray[indiceAviso].idCliente && pArray[indiceAviso].isActive==ACTIVO)
			{
				contadorAvisos++;
				retorno=0;
			}
		}
	}
	*pResultado=contadorAvisos;
	return retorno;
}

int informe_imprimirClienteMasCantidadAvisos(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente)
{
	int retorno=-1;
	int indiceCliente;
	int cantidadAvisos;
	int banderaPrimerNumero=TRUE;
	int maximoAvisos;
	int idMaximoAvisos;
	if(pArray!=NULL && lenAviso>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		for(indiceCliente=0;indiceCliente<lenCliente;indiceCliente++)
		{
			if(aviso_cantidadAvisos(pArray,lenAviso,pArrayCliente[indiceCliente].idCliente,&cantidadAvisos)==0)
			{
				if(banderaPrimerNumero==TRUE || maximoAvisos<cantidadAvisos)
				{
					banderaPrimerNumero=FALSE;
					maximoAvisos=cantidadAvisos;
					idMaximoAvisos=pArrayCliente[indiceCliente].idCliente;
					retorno=0;
				}
			}
		}
	}
	printf("\n\n%d es el cliente con mas avisos activos, la cantidad es: %d\n\n",idMaximoAvisos,maximoAvisos);
	return retorno;
}

int informe_cantidadAvisosPausados(Aviso* pArray,int len)
{
	int retorno=-1;
	int contadorAvisosPausados=0;
	int i;

	if(pArray!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty== FALSE && pArray[i].isActive==PAUSADO)
			{
				contadorAvisosPausados++;
			}
		}
	}
	printf("\n\nLa cantidad de avisos pausados es de %d\n",contadorAvisosPausados);
	return retorno;
}
int informe_subMenu(int* pOpcion)
{
	int retorno;
	printf("\n\n*************INFORMES*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: CLIENTES CON MAS AVISOS.\n");
	printf("*>OPCION 2: CANTIDAD DE AVISOS PAUSADOS.\n");
	printf("*>OPCION 3: RUBRO CON MAS AVISOS.\n");
	printf("*>OPCION 4: VOLVER AL MENU PRINCIPAL.\n");


	getInt("\ningresa la opcion: ","Error",&retorno,3,4,1);
	*pOpcion=retorno;
	return retorno;
}
