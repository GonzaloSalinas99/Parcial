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

#include "utn.h"
#include "cliente.h"
#include "aviso.h"

#define QTY_CUIT 13
#define QTY_CLIENTE 100
#define QTY_AVISOS 1000

static int aviso_bajaTodasPublicaciones(Aviso* pArray,int len, int idCliente);
static int aviso_generarNuevoId (void);

int aviso_init(Aviso * pArray, int limite)
{
	int retorno = -1;
	if (pArray != NULL && limite >0){
		for (int i = 0; i<limite; i++ )
		{
			pArray[i].isEmpty = TRUE;
			pArray[i].isActive = PAUSADO;
		}
		retorno = 0;
	}

	return retorno;
}


int aviso_alta(Aviso * pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int indice;
	int idABuscar;
	int indiceCliente;
	Aviso bufferAviso;


	if (pArray != NULL && limite >0 && pArrayCliente!=NULL && lenCliente>0)
	{
		cliente_imprimir(pArrayCliente,lenCliente);
		if(getInt("\n\ningrese el ID del cliente cargado para contratar el aviso: : ","ERROR",&idABuscar,3,QTY_AVISOS,0)==0 &&
			cliente_buscarIndicePorId(pArrayCliente,lenCliente,idABuscar,&indiceCliente)==0)
		{
			if (aviso_buscarLibreRef (pArray, limite, &indice) == 0)
			{
					if (getNombre("\nIngrese el texto del aviso", "error",bufferAviso.textoAviso,2,LONG_NOMBRE) == 0 &&
						getInt("A que rubro pertenece el aviso:\n"
								"Opcion 1:PROGRAMACION\n"
								"Opcion 2: GASTRONOMIA\n"
								"Opcion 3: ELECTRONICA\n"
								"Opcion 4: CONSTRUCCION\n"
								"Opcion 5: HOTELERIA\n"
								"\nIngrese ","ERROR",&bufferAviso.rubroAviso,3,5,1) == 0)
					{
							pArray[indice] = bufferAviso;
							pArray[indice].idCliente = pArrayCliente[indiceCliente].idCliente;
							pArray[indice].idAviso = aviso_generarNuevoId();
							pArray[indice].isEmpty = FALSE;
							pArray[indice].isActive = FALSE;
							retorno=0;
							printf("El ID de esta publicacion es: %d",pArray[indice].idAviso);
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
	}
		return retorno ;
}








int aviso_baja (Aviso* pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int idABorrar;
	int indiceABorrar;
	int confirmacion;

	if (pArray != NULL && limite>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		cliente_imprimir(pArrayCliente, lenCliente);

		if(getInt("Ingrese ID de cliente a borrar","Error",&idABorrar,3,1000,0)==0 &&
				aviso_buscarIndicePorId(pArray,limite,idABorrar,&indiceABorrar)==0  &&
				aviso_imprimirPorId(pArray, limite,idABorrar)==0)
		{

			if( getInt("Desea confirmar la baja?? Ingrese 1-Si o 2-No :","ERROR",&confirmacion,3,2,1)== 0)
			{
				if(confirmacion==1 && aviso_bajaTodasPublicaciones(pArray,limite,idABorrar)==0)
				{
					pArray[indiceABorrar].isEmpty=TRUE;
					retorno=0;
				}
			}
		}
	}
	return retorno;
}

int aviso_estadoPublicacionPausa (Aviso * pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int idBuscar;
	int indiceAModificar;
	int confirmacion;


	if (pArray != NULL && limite>0 && pArrayCliente!= NULL && lenCliente>0)
	{
		aviso_imprimir(pArray,limite);
		if(getInt("Ingrese el ID de la publicacion a modificar","ERROR",&idBuscar,3,QTY_AVISOS,1)==0 &&
			aviso_buscarIndicePorId(pArray, limite, idBuscar, &indiceAModificar) == 0)
		{
			if(cliente_imprimirPorId(pArrayCliente, lenCliente,pArray[indiceAModificar].idCliente)==0)
			{
				if(getInt("\nEsta seguro de modificar esta publicacion?? Ingrese 1-Si o 2-No : ","Error",&confirmacion,3,2,1)==0)
				{
					pArray[indiceAModificar].isActive = PAUSADO;
					printf("Esta pausada");
					retorno = 0;
				}
				else
				{
					printf("\nSigue activa");
				}
			}
		}
	}
return retorno;
}

int aviso_estadoPublicacionActiva(Aviso * pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int idBuscar;
	int indiceAModificar;
	int confirmacion;


	if (pArray != NULL && limite>0 && pArrayCliente!= NULL && lenCliente>0)
	{
		aviso_imprimir(pArray,limite);
		if(getInt("Ingrese el ID de la publicacion a modificar","ERROR",&idBuscar,3,QTY_AVISOS,1)==0 &&
			aviso_buscarIndicePorId(pArray, limite, idBuscar, &indiceAModificar) == 0)
		{
			if(cliente_imprimirPorId(pArrayCliente, lenCliente,pArray[indiceAModificar].idCliente)==0)
			{
				if(getInt("\nEsta seguro de modificar esta publicacion?? Ingrese 1-Si o 2-No : ","Error",&confirmacion,3,2,1)==0)
				{
					pArray[indiceAModificar].isActive = ACTIVO;
					printf("Esta pausada");
					retorno = 0;
				}
				else
				{
					printf("\nSigue en pausa");
				}
			}
		}
	}
return retorno;
}


int aviso_buscarLibre (Aviso * pArray, int limite){
	int retorno = -1;
	int i ;
		if (pArray != NULL && limite >0){
			for ( i = 0; i<limite; i++) {
				if(pArray[i].isEmpty == TRUE)
					{
					retorno = i;
					break;
					}
			}
		}
	return retorno;
}

int aviso_buscarLibreRef (Aviso * pArray, int limite, int * pIndice){
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

static int aviso_generarNuevoId (void) {
	static int id = 0;
	id = id+1;
	return id;
}

int aviso_buscarIndicePorId (Aviso * pArray, int limite,int idBuscar,int * pIndice)
{
	int retorno = -1;
	int i ;
		if (pArray != NULL && limite >0 && pIndice != NULL && idBuscar >= 0)
		{
				for ( i = 0; i<limite; i++)
				{
					if(pArray[i].idAviso == idBuscar)
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

int aviso_ordenarPorNombre (Aviso * pArray, int limite , int orden)
{
	int retorno = -1;
	int estadoDesordenado = 1;
	Aviso aux;
	if (pArray != NULL && limite >0){
	while(estadoDesordenado)
	{
		estadoDesordenado = 0;
		for(int i = 0; i < (limite - 1); i++)
		{
			if((orden == 1 && strncmp(pArray[i].textoAviso, pArray[i + 1].textoAviso,LONG_NOMBRE)>0)
					||
			  (orden == 0 && strncmp(pArray[i].textoAviso, pArray[i + 1].textoAviso,LONG_NOMBRE)<0))
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

int aviso_imprimir(Aviso* pArray, int len)
{
	int retorno = -1;
	if(pArray != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				printf("Hola");

			}
		}
		retorno = 0;
	}
	return retorno;
}



int aviso_menu(int* pOpcion)
{
	int retorno;

	printf("\n\n*************BIENVENIDO*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: ALTA A EMPLEADO.\n");
	printf("*>OPCION 2: MODIFICAR DATOS EMPLEADO.\n");
	printf("*>OPCION 3: BAJA A EMPLEADO.\n");
	printf("*>OPCION 4: INFORMAR.\n");
	printf("*>OPCION 5: SALIR.\n");

	getInt("\ningresa la opcion: ","Error",&retorno,3,5,1);
	*pOpcion=retorno;
	return retorno;
}

int aviso_report(int* pOpcion)
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

int aviso_imprimirPorId(Aviso* pArray,int len,int idCliente)
{
	int retorno=-1;
	int i;

	if(pArray!=NULL && len>0 && idCliente>0)
	{
		printf("Publicaciones del cliente con el ID: %d",idCliente);
		printf("TEXTO DEL AVISO\t\tRUBRO\t\tID DEL AVISO\t\tESTADO");
		for(i=0;i<len;i++)
		{
			if(pArray[i].idCliente==idCliente && pArray[i].isEmpty==FALSE)
			{
				printf("%s\t\t%d\t\t%d\t\t%d",pArray[i].textoAviso,pArray[i].rubroAviso,pArray[i].idAviso,pArray[i].isActive);
				retorno=0;
			}
		}

	}

	return retorno;
}

static int aviso_bajaTodasPublicaciones(Aviso* pArray,int len, int idCliente)
{
	int retorno=-1;
	int i;
	if(pArray!=NULL && len>0 && idCliente>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].idCliente==idCliente)
			{
				pArray[i].isEmpty=TRUE;
				retorno=0;
			}
		}
	}

	return retorno;
}

int aviso_cantidadAvisos(Aviso* pArray,int len,int id,int *pResultado)
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

int aviso_imprimirClientesYAvisos(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente)
{
	int retorno=-1;
	int indiceCliente;
	int cantidadAvisos;
	if(pArray!=NULL && lenAviso>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		for(indiceCliente=0;indiceCliente<lenCliente;indiceCliente++)
		{
			if(aviso_cantidadAvisos(pArray,lenAviso,pArrayCliente[indiceCliente].idCliente,&cantidadAvisos)==0)
			{
				printf("%d : %d avisos activos.",pArrayCliente[indiceCliente].cuitCliente,cantidadAvisos);
				retorno=0;
			}
		}
	}

	return retorno;
}
