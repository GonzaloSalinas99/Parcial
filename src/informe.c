/*
 * informe.c
 *
 *  Created on: 13 oct. 2020
 *      Author: Gonzalo
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "informe.h"


#define QTY_CUIT 13
#define QTY_CLIENTE 100
#define QTY_AVISOS 1000
//b) Cliente con más avisos activos. c) Cliente con más avisos pausados

/*
 * brief Calcula el total de avisos que tiene cada cliente
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param id ID del cliente a contarle sus avisos
 * param *pResultado Direccion de memoria donde se escribira el resultado obtenido
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_calcularTotalAvisos(Aviso* pArray,int len,int id,int *pResultado)
{
	int retorno=-1;
	int indiceAviso;
	int contadorAvisos=0;

	if(pArray!=NULL && len>0 && id>0 && pResultado!=NULL)
	{
		for(indiceAviso=0;indiceAviso<len;indiceAviso++)
		{
			if(pArray[indiceAviso].isEmpty==FALSE && id==pArray[indiceAviso].idCliente)
			{
				contadorAvisos++;
				retorno=0;
			}
		}
	}
	*pResultado=contadorAvisos;
	return retorno;
}
/*
 * brief Imprime el cliente con la mayor cantidad de avisos
 * param Aviso* pArray lista de avisos
 * param lenAvisos cantidad de posiciones que tiene la lista de Avisos
 * param Cliente pArrayCliente Lista de clientes
 * param lenCliente Cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_imprimirClienteMayorCantidadAvisos(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente)
{
	int retorno=-1;
	int indiceCliente;
	int cantidadAvisos;
	int banderaPrimerNumero=TRUE;
	int maximoAvisos;
	Cliente bufferCliente;

	if(pArray!=NULL && lenAviso>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		for(indiceCliente=0;indiceCliente<lenCliente;indiceCliente++)
		{
			if(informe_calcularTotalAvisos(pArray,lenAviso,pArrayCliente[indiceCliente].idCliente,&cantidadAvisos)==0)
			{
				if(banderaPrimerNumero==TRUE || maximoAvisos<cantidadAvisos)
				{
					banderaPrimerNumero=FALSE;
					maximoAvisos=cantidadAvisos;
					strncpy(bufferCliente.nombreCliente,pArrayCliente[indiceCliente].nombreCliente,LONG_NOMBRE);
					strncpy(bufferCliente.apellidoCliente,pArrayCliente[indiceCliente].apellidoCliente,LONG_NOMBRE);

					retorno=0;
				}
			}
		}
	}
	if(retorno==0)
	{
		printf("\n\n%s %s Es el cliente con mas avisos, la cantidad es: %d\n\n",bufferCliente.nombreCliente,
																					bufferCliente.apellidoCliente,maximoAvisos);
	}
	else
	{
		printf("\nNo hay clientes con avisos cargados");
	}
	return retorno;
}
/*
 * brief Saca la cantidad de avisos PAUSADOS
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_cantidadAvisosPausados(Aviso* pArray,int limite)
{
	int retorno=-1;
	int contadorAvisosPausados=0;
	int i;

	if(pArray!=NULL && limite>0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty== FALSE && pArray[i].isActive==PAUSADO)
			{
				contadorAvisosPausados++;
				retorno=0;
			}
		}
	}
	printf("\n\nLa cantidad de avisos pausados es de %d\n",contadorAvisosPausados);
	return retorno;
}
/*
 * brief Calcula el rubro con mayor cantidad de Avisos activos
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
/*
int informe_rubroMayorCantidadAvisos(Aviso* pArrayAviso,int limite)
{
	int retorno=-1;
	int contadorRubro1=0;
	int contadorRubro2=0;
	int contadorRubro3=0;
	int contadorRubro4=0;
	int contadorRubro5=0;
	int indiceAviso;
	int rubroElegido;

	if(pArrayAviso!=NULL && limite>0)
	{
		for(indiceAviso=0;indiceAviso<limite;indiceAviso++)
		{
			if(pArrayAviso[indiceAviso].isEmpty==FALSE && pArrayAviso[indiceAviso].isActive==ACTIVO)
			{
				rubroElegido=pArrayAviso[indiceAviso].rubroAviso;

				switch(rubroElegido)
				{
					case 1:
							contadorRubro1++;
						break;
					case 2:
							contadorRubro2++;
						break;
					case 3:
							contadorRubro3++;
						break;
					case 4:
							contadorRubro4++;
						break;
					case 5:
							contadorRubro5++;
						break;
				}
			}

		}
	}

	if(contadorRubro1 > contadorRubro2 && contadorRubro1 > contadorRubro3 && contadorRubro1 > contadorRubro4 && contadorRubro1 > contadorRubro5)
	{
		printf("El rubro 1 es el que mas avisos tiene");
	}
	else
	{
		if(contadorRubro2 > contadorRubro3 && contadorRubro2 > contadorRubro4 && contadorRubro2 >contadorRubro5)
		{
			printf("El rubro 2 es el que mas avisos tiene");
		}
		else
		{
			if(contadorRubro3 > contadorRubro4 && contadorRubro3 > contadorRubro5)
			{
				printf("El rubro 3 es que mas avisos tiene");
			}
			else
			{
				if(contadorRubro4 > contadorRubro5)
				{
					printf("El rubro 4 es el que mas avisos tiene");
				}
				else
				{
					printf("El rubro 5 es el que mas avisos tiene");
				}
			}
		}
	}

	return retorno;
}
*/
/*
 *brief Menu de opciones
 *param int* pOpcion Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 *return (0) si se ingreso correctamente la opcion (-1) Si la opcion es invalida
 */
int informe_subMenu(int* pOpcion)
{
	int retorno;
	printf("\n\n*************INFORMES*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: CLIENTES CON MAS AVISOS.\n");
	printf("*>OPCION 2: CANTIDAD DE AVISOS PAUSADOS.\n");
	printf("*>OPCION 3: RUBRO CON MAS AVISOS.\n");
	printf("*>OPCION 4: CLIENTES CON MAS AVISOS PAUSADOS.\n");
	printf("*>OPCION 5: CLIENTES CON MAS AVISOS ACTIVOS.\n");
	printf("*>OPCION 6: VOLVER AL MENU PRINCIPAL.\n");

	getInt("\ningresa la opcion: ","Error",&retorno,3,6,1);
	*pOpcion=retorno;
	return retorno;
}


/*
 * brief Calcula el total de avisos pausados que tiene cada cliente
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param id ID del cliente a contarle sus avisos
 * param *pResultado Direccion de memoria donde se escribira el resultado obtenido
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_calcularTotalAvisosDeClientesPausados(Aviso* pArray,int len,int id,int *pResultado)
{
	int retorno=-1;
	int indiceAviso;
	int contadorAvisos=0;

	if(pArray!=NULL && len>0 && id>0 && pResultado!=NULL)
	{
		for(indiceAviso=0;indiceAviso<len;indiceAviso++)
		{
			if(pArray[indiceAviso].isEmpty==FALSE && id==pArray[indiceAviso].idCliente && pArray[indiceAviso].isActive==PAUSADO)
			{
				contadorAvisos++;
				retorno=0;
			}
		}
	}
	*pResultado=contadorAvisos;
	return retorno;
}
/*
 * brief Imprime el cliente con la mayor cantidad de avisos pausados
 * param Aviso* pArray lista de avisos
 * param lenAvisos cantidad de posiciones que tiene la lista de Avisos
 * param Cliente pArrayCliente Lista de clientes
 * param lenCliente Cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_imprimirClienteMayorCantidadAvisosPausados(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente)
{
	int retorno=-1;
	int indiceCliente;
	int cantidadAvisos;
	int banderaPrimerNumero=TRUE;
	int maximoAvisos;
	Cliente bufferCliente;

	if(pArray!=NULL && lenAviso>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		for(indiceCliente=0;indiceCliente<lenCliente;indiceCliente++)
		{
			if(informe_calcularTotalAvisosDeClientesPausados(pArray,lenAviso,pArrayCliente[indiceCliente].idCliente,&cantidadAvisos)==0)
			{
				if(banderaPrimerNumero==TRUE || maximoAvisos<cantidadAvisos)
				{
					banderaPrimerNumero=FALSE;
					maximoAvisos=cantidadAvisos;
					strncpy(bufferCliente.nombreCliente,pArrayCliente[indiceCliente].nombreCliente,LONG_NOMBRE);
					strncpy(bufferCliente.apellidoCliente,pArrayCliente[indiceCliente].apellidoCliente,LONG_NOMBRE);

					retorno=0;
				}
			}
		}
	}
	if(retorno==0)
	{
		printf("\n\n%s %s Es el cliente con mas avisos pausados, la cantidad es: %d\n\n",bufferCliente.nombreCliente,
																						bufferCliente.apellidoCliente,maximoAvisos);
	}
	else
	{
		printf("\nNo hay clientes con avisos pausados");
	}
	return retorno;
}

/*
 * brief Calcula el total de avisos activos que tiene cada cliente
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param id ID del cliente a contarle sus avisos
 * param *pResultado Direccion de memoria donde se escribira el resultado obtenido
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_calcularTotalAvisosDeClientesActivos(Aviso* pArray,int len,int id,int *pResultado)
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
/*
 * brief Imprime el cliente con la mayor cantidad de avisos activos
 * param Aviso* pArray lista de avisos
 * param lenAvisos cantidad de posiciones que tiene la lista de Avisos
 * param Cliente pArrayCliente Lista de clientes
 * param lenCliente Cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_imprimirClienteMayorCantidadAvisosActivos(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente)
{
	int retorno=-1;
	int indiceCliente;
	int cantidadAvisos;
	int banderaPrimerNumero=TRUE;
	int maximoAvisos;
	Cliente bufferCliente;

	if(pArray!=NULL && lenAviso>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		for(indiceCliente=0;indiceCliente<lenCliente;indiceCliente++)
		{
			if(informe_calcularTotalAvisosDeClientesActivos(pArray,lenAviso,pArrayCliente[indiceCliente].idCliente,&cantidadAvisos)==0)
			{
				if(banderaPrimerNumero==TRUE || maximoAvisos<cantidadAvisos)
				{
					banderaPrimerNumero=FALSE;
					maximoAvisos=cantidadAvisos;
					strncpy(bufferCliente.nombreCliente,pArrayCliente[indiceCliente].nombreCliente,LONG_NOMBRE);
					strncpy(bufferCliente.apellidoCliente,pArrayCliente[indiceCliente].apellidoCliente,LONG_NOMBRE);

					retorno=0;
				}
			}
		}
	}
	if(retorno==0)
	{
		printf("\n\n%s %s Es el cliente con mas avisos activos, la cantidad es: %d\n\n",bufferCliente.nombreCliente,
																						bufferCliente.apellidoCliente,maximoAvisos);
	}
	else
	{
		printf("No hay clientes con avisos activos");
	}
	return retorno;
}
/*
 * brief Imprime el rubro con la mayor cantidad de avisos
 * param Aviso* pArrayAviso lista de avisos
 * param limiteAvisos cantidad de posiciones que tiene la lista de Avisos
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_imprimirRubroConMayorCantidadAviso(Aviso *pArrayAviso, int limiteAvisos)
{
	int retorno=-1;
	int contadorAvisos;
	int maxContadorAvisos;
	int rubroMayorCantidadAvisos;
	if(pArrayAviso!=NULL && limiteAvisos)
	{
		for(int i=0;i<limiteAvisos;i++)
		{
			if(pArrayAviso[i].isEmpty == FALSE && informe_calcularRubroPorAviso(pArrayAviso,limiteAvisos,pArrayAviso[i].rubroAviso, &contadorAvisos)==0)
			{
				if(i==0 || contadorAvisos>maxContadorAvisos)
				{
					maxContadorAvisos = contadorAvisos;
					rubroMayorCantidadAvisos = pArrayAviso[i].rubroAviso;
					retorno=0;
				}
			}
		}
		printf("\nEl rubro con mas avisos es el  %d  con  %d publicaciones.\n",rubroMayorCantidadAvisos,contadorAvisos);
	}
	else
	{
		printf("\nNo hay datos cargados.\n");
	}
	return retorno;
}

/*
 * brief Calcula los rubros que tiene cada Aviso
 * param Aviso* pArrayAviso lista de avisos
 * param limiteAviso cantidad de posiciones que tiene la lista de Avisos
 * param rubro Rubro a contar sus avisos
 * param *pResultado Direccion de memoria donde se escribira el resultado obtenido
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int informe_calcularRubroPorAviso(Aviso *pArrayAviso, int limiteAviso, int rubro, int *pResultado)
{
	int retorno=-1;
	int contadorAvisos=0;
	if(pArrayAviso!=NULL && limiteAviso>0)
	{
		for(int i=0;i<limiteAviso;i++)
		{
			if(pArrayAviso[i].isEmpty == FALSE && pArrayAviso[i].rubroAviso == rubro)
			{
				contadorAvisos++;
				retorno=0;
			}
		}
		*pResultado = contadorAvisos;
	}
	return retorno;
}
