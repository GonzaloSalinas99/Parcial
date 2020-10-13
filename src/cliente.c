/*
 * employee.c
 *
 *  Created on: 25 sept. 2020
 *      Author: Gonzalo
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cliente.h"
#include "utn.h"
#include "aviso.h"

#define QTY_CUIT 13
#define QTY_CLIENTES 100



static int cliente_generarNuevoId (void);

int cliente_init(Cliente * pArray, int limite)
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

int cliente_alta(Cliente * pArray, int limite)
{
	int retorno = -1;
	int indice;
	Cliente bufferCliente;


	if (pArray != NULL && limite >0)
	{

			if (cliente_buscarLibreRef (pArray, limite, &indice) == 0)
			{
					if (getNombre("\nIngrese su nombre: \n", "error",bufferCliente.nombreCliente,2,LIMITE_NOMBRE) == 0 &&
						getNombre("Ingrese su apellido: \n", "error",bufferCliente.apellidoCliente,2,LIMITE_NOMBRE) ==0 &&
						utn_getCuit("Ingrese su cuit: ","ERROR",&bufferCliente.cuitCliente,3,QTY_CUIT) == 0)
					{
							pArray[indice] = bufferCliente;
							pArray[indice].idCliente = cliente_generarNuevoId();
							pArray[indice].isEmpty = FALSE;
							retorno=0;
					}
					else
					{
						printf("ERROR");
					}
			}
			else
			{
				printf(" \n No quedan espacios libres");
			}
	}

		return retorno ;
}

int cliente_baja (Cliente * pArray, int limite)
{
	int retorno = -1;
	int idABorrar;
	int indiceABorrar;

	if (pArray != NULL && limite>0)
	{
		cliente_imprimir(pArray, limite);
		if(getInt("Ingrese ID de cliente a borrar","Error",&idABorrar,3,1000,0)==0)
		{
			if(cliente_buscarIndicePorId(pArray,limite,idABorrar,&indiceABorrar)==0)
			{
				pArray[indiceABorrar].isEmpty=TRUE;
			}
		}
	}
	return retorno;
}

int cliente_modificar (Cliente * pArray, int limite)
{
	int retorno = -1;
	int idBuscar;
	int indiceAModificar;

	Cliente bufferCliente;

	if (pArray != NULL && limite>0)
	{
		if(getInt("\ningrese el ID del cliente que quiere modificar: ","ERROR",&idBuscar,3,QTY_CLIENTES,0)==0)
		{
			if(cliente_buscarIndicePorId(pArray,limite,idBuscar,&indiceAModificar)==0)
			{
				if (getNombre("Ingrese su apellido: \n", "error",bufferCliente.nombreCliente,2,LIMITE_NOMBRE) == 0 &&
					getNombre("Ingrese su apellido: \n", "error",bufferCliente.nombreCliente,2,LIMITE_NOMBRE) == 0 &&
					utn_getCuit("Ingrese su cuit: ","ERROR",&bufferCliente.cuitCliente,3,QTY_CUIT) == 0)
				{
						pArray[indiceAModificar] = bufferCliente;
						pArray[indiceAModificar].isEmpty = FALSE;
						retorno=0;
				}
				else
				{
					printf("ERROR");
				}
			}

		}

	}
return retorno;
}




int cliente_buscarLibre (Cliente * pArray, int limite)
{
	int retorno = -1;
	int i ;
		if (pArray != NULL && limite >0)
		{
			for ( i = 0; i<limite; i++)
			{
				if(pArray[i].isEmpty == TRUE)
				{
					retorno = i;
					break;
				}
			}
		}
	return retorno;
}

int cliente_buscarLibreRef (Cliente * pArray, int limite, int * pIndice){
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

static int cliente_generarNuevoId (void) {
	static int id = 0;
	id = id+1;
	return id;
}

int cliente_buscarIndicePorId (Cliente * pArray, int limite,int idBuscar,int * pIndice)
{
	int retorno = -1;
	int i ;
		if (pArray != NULL && limite >0 && pIndice != NULL && idBuscar >= 0)
		{
				for ( i = 0; i<limite; i++)
				{
					if(pArray[i].idCliente == idBuscar)
					{
					*pIndice = i;
					retorno = 0;
					break;
					}
				}
			}
			else
			{
				printf("errrror");
			}
		return retorno;
}

int cliente_ordenarPorNombre (Cliente * pArray, int limite , int orden)
{
	int retorno = -1;
	int estadoDesordenado = 1;
	Cliente aux;
	if (pArray != NULL && limite >0){
	while(estadoDesordenado)
	{
		estadoDesordenado = 0;
		for(int i = 0; i < (limite - 1); i++)
		{
			if((orden == 1 && strncmp(pArray[i].nombreCliente, pArray[i + 1].nombreCliente,LIMITE_NOMBRE)>0)
					||
			  (orden == 0 && strncmp(pArray[i].nombreCliente, pArray[i + 1].nombreCliente,LIMITE_NOMBRE)<0))
			{
				aux = pArray[i];
				pArray[i] = pArray[i + 1];
				pArray[i + 1] = aux;
				estadoDesordenado = 1;
			}
		}
	}
	retorno = 0;


	}
	return retorno;
}


//IMPRIMIR

int cliente_imprimir(Cliente* pArray, int len)
{
	int retorno = -1;
	if(pArray != NULL && len > 0)
	{
		printf("\t\t\t****CLIENTES****\n");
		printf("ID\t\t NOMBRE \t\t APELLIDO \t\t CUIT\n");
		for(int i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				printf("%d\t\t %s\t\t %s\t\t %d",pArray[i].idCliente,pArray[i].nombreCliente,pArray[i].apellidoCliente,pArray[i].cuitCliente);

			}
		}
		retorno = 0;
	}
	return retorno;
}

int cliente_imprimirPorId(Cliente* pArray, int len, int id)
{
	int retorno=-1;

	if(pArray != NULL && len > 0 && id>=0)
		{
			printf("ID\t\t NOMBRE \t\t APELLIDO \t\t CUIT\n");
			for(int i=0;i<len;i++)
			{
				if(pArray[i].idCliente==id && pArray[i].isEmpty == FALSE )
				{
					printf("%d\t\t %s\t\t %s\t\t %d \n",pArray[i].idCliente,pArray[i].nombreCliente,pArray[i].apellidoCliente,pArray[i].cuitCliente);

				}
			}
			retorno = 0;
		}

	return retorno;
}


int cliente_menu(int* pOpcion)
{
	int retorno;

	printf("\n\n*************BIENVENIDO*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: ALTA A CLIENTE.\n");
	printf("*>OPCION 2: MODIFICAR DATOS CLIENTE.\n");
	printf("*>OPCION 3: BAJA A CLIENTE.\n");
	printf("*>OPCION 4: INFORMAR.\n");
	printf("*>OPCION 5: SALIR.\n");

	getInt("\ningresa la opcion: ","Error",&retorno,3,5,1);
	*pOpcion=retorno;
	return retorno;
}

int cliente_report(int* pOpcion)
{
	int retorno;
	printf("\n\n*************INFORMES*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: ORDENAR.\n");
	printf("*>OPCION 2: IMPRIMIR.\n");
	printf("*>OPCION 3: PROMEDIO SALARIO Y CUANTOS EMPLEADOS SUPERAN ESTE PROMEDIO.\n");
	printf("*>OPCION 4: VOLVER AL MENU PRINCIPAL.\n");


	getInt("\ningresa la opcion: ","Error",&retorno,3,4,1);
	*pOpcion=retorno;
	return retorno;
}

void cliente_hardcodeo(Cliente* pArray,int indice,char* nombre,char* apellido, int cuit, int id)
{
	strncpy(pArray[indice].nombreCliente,nombre,LIMITE_NOMBRE);
	strncpy(pArray[indice].apellidoCliente,apellido,LIMITE_NOMBRE);
	pArray[indice].cuitCliente=cuit;
	pArray[indice].idCliente=id;
	pArray[indice].isEmpty = FALSE;
}
