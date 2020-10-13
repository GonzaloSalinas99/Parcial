/*
 * utn.c
 *
 *  Created on: 16 sept. 2020
 *      Author: Gonzalo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#define LIMITE_NOMBRE 50

static int myGets(char *cadena, int longitud);
static int getFloat(float* pFloat);
static int esFlotante(char* array,int limite);



/*
 * getInt : Solicita un numero al usuario, luego de verificarlo devuelve el resultado
 * mensaje : El mensaje que imprime para pedir un valor.
 * mensajeError: El mensaje que imprime si el rango no es valido.
 * pResultado : Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * maximo : valor maximo valido (inclusive)
 * minimo : valor minimo valido (inclusive)
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 */
int getInt(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo)
{
	int retorno = -1;
	char bufferChar[4096];
	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			maximo >= minimo)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(myGets(bufferChar,LIMITE_NOMBRE) == 0 && strnlen(bufferChar,sizeof(bufferChar)-1)<= 4096 &&
					esNumerica(bufferChar,4096) != 0 )
						{
							retorno=0;
							*pResultado=atoi(bufferChar);
							break;
						}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/*
 *brief verifica una cadena recibida para determinar si es un numero valido
 *param char* cadena Cadena a ser analizada
 *param int limite Indica la cantidad maxima de caracteres
 *return (0) si no pude ser validado el numero (1) Si el numero es valido
 */
int esNumerica(char* array,int limite)
{
	int retorno = 1;
	int i;
	if(array != NULL && limite>0)
	{
		for(i=0;array[i] != '\0';i++)
		{
			if((array[i] != ' ') && (array[i] < '0' || array[i] > '9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
 * utn_getNumeroFloat : Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
 * pResultado : Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * mensaje : El mensaje que imprime para pedir un valor.
 * mensajeError: El mensaje que imprime si el rango no es valido.
 * minimo : valor minimo valido (inclusive)
 * maximo : valor maximo valido (inclusive)
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos){
	int retorno = -1;
	float bufferFloat;
	int resultadoScan;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos > 0){
		do{
			printf("%s", mensaje);
			fflush(stdin);
			resultadoScan = getFloat(&bufferFloat);
			if(resultadoScan && minimo <= bufferFloat && maximo >= bufferFloat){
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}else{
				printf("%s", mensajeError);
				printf("\n-REINTENTOS: %d \n",reintentos);
				reintentos--;
			}

		}while(reintentos >= 0);
	}
	return retorno;
}

/*
 * getFloat: verifica si la cadena ingresada es flotante
 * pFloat: puntero numero float
 * Retorno: devuelve un 1 si esta todoOK. Devuelve 0 si hubo un error.
 *
 */
static int getFloat(float* pFloat)
{
	int retorno = 0;
	char bufferFloat[5000];
	if(pFloat != NULL){
		fflush(stdin);

		if(!myGets(bufferFloat,sizeof(bufferFloat)) && esFlotante(bufferFloat,sizeof(bufferFloat))){
			*pFloat = atof(bufferFloat);
			retorno = 1;
		}
	}
	return retorno;
}

/*
 * esFlotante: Verifica si la cadena ingresada es flotante
 * cadena: cadena de caracteres a ser analizada
 * limite: limite de la cadena
 * Retorno: 1 (verdadero) si la cadena es flotante , 0 (falso) si no y -1 en caso de ERROR de parametro
 *
 */
static int esFlotante(char* array,int limite){
	int retorno = -1;
	int i = 0;
	int contadorDePuntos = 0;

	if(array != NULL && limite > 0){
		retorno = 1;
		if(array[0] != '+' || array[0] != '-'){
			i = 1;
		}
		while(array[i] != '\0'){
			if((array[i] < '0' || array[i] > '9') && array[i] != '.'){
				retorno = 0;
				break;
			}
			if(array[i] == '.'){
				contadorDePuntos++;
				if(contadorDePuntos > 1){
					retorno = 0;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

/*
 * brief : Solicita un numero nombre al usuario, luego de verificarlo devuelve el resultado
 * mensaje : El mensaje que imprime para pedir un nombre.
 * mensajeError: El mensaje que imprime si el rango no es valido.
 * pResultado : Direccion de memoria de la variable donde escribe el nombre ingresado por el usuario
 * Reintentos: cantidad de veces que tiene el usuario para ingresar un valor valido
 * Retorno: devuelve un 0 si esta todoOK. Devuelve -1 si hubo un error.
 *
 */
int getNombre(char* mensaje,char* mensajeError,char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferChar[LIMITE_NOMBRE];

	if(mensaje!=NULL && mensajeError!=NULL && pResultado!=NULL && reintentos>0 && limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if(myGets(bufferChar,LIMITE_NOMBRE) == 0 && strnlen(bufferChar,sizeof(bufferChar)-1)<= limite &&
					esUnNombreValido(bufferChar,limite) != 0 )
			{
				retorno=0;
				strncpy(pResultado,bufferChar,limite);
				break;
			}
			else
			{
				printf("%s\n",mensajeError);
				reintentos--;
			}
		}while(reintentos>=0);

	}
return retorno;
}

/*
 *brief verifica una cadena recibidar para determinar si es un nombre valido
 *param char* cadena Cadena a ser analizada
 *param int limite Indica la cantidad maxima de caracteres
 *return (0) si no pude ser validado el nombre (1) Si el nombre es valido
 */

int esUnNombreValido(char* cadena,int limite)
{
	int respuesta = 1;
	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{

		if(	(cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			cadena[i]!=' ' && cadena[i]!='.')
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}
static int myGets(char* cadena, int longitud)
{
	int retorno = -1; //ERROR
	char bufferString[4096];
	fflush(stdin);

	if(cadena != NULL && longitud > 0)
	{
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL && cadena[0] != '\n')
			{
				if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
				{
					bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
				}
				if(strlen(bufferString) <= longitud)
				{
					strncpy(cadena,bufferString,longitud);
					retorno = 0;
				}
			}
		}
		return retorno;
}

int utn_getDireccion(char* mensaje,char* mensajeError,char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferChar[LIMITE_NOMBRE];

	if(mensaje!=NULL && mensajeError!=NULL && pResultado!=NULL && reintentos>0 && limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if(myGets(bufferChar,LIMITE_NOMBRE) == 0 && strnlen(bufferChar,sizeof(bufferChar)-1)<= limite &&
					esAlfaNumerica(bufferChar) != 0 )
			{
				retorno=0;
				strncpy(pResultado,bufferChar,limite);
				break;
			}
			else
			{
				printf("%s\n",mensajeError);
				reintentos--;
			}
		}while(reintentos>=0);

	}
return retorno;
}

int esAlfaNumerica(char* pResultado)
{
	int retorno = 1;
	int i;
	if(pResultado != NULL){
		for(i=0;pResultado[i] != '\0';i++)
		{
			if((pResultado[i] != ' ') && (pResultado[i] < 'a' || pResultado[i] > 'z') && (pResultado[i] < 'A' || pResultado[i] > 'Z') && (pResultado[i] < '0' || pResultado[i] > '9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int utn_getCuit(char* mensaje,char* mensajeError,int* pResultado, int reintentos, int limite)
{
	int retorno=-1;
	char bufferChar[LIMITE_NOMBRE];
	bufferChar[2]='-';
	bufferChar[11]='-';

		if(mensaje!=NULL && mensajeError!=NULL && pResultado!=NULL && reintentos>0 && limite > 0)
		{
			do
			{
				printf("%s",mensaje);
				if(myGets(bufferChar,LIMITE_NOMBRE) == 0 && strnlen(bufferChar,sizeof(bufferChar)-1)<= limite &&
						esCuit(bufferChar) != 0 )
				{
					retorno=0;
					*pResultado=atoi(bufferChar);
					break;
				}
				else
				{
					printf("%s\n",mensajeError);
					reintentos--;
				}
			}while(reintentos>=0);

		}


	return retorno;
}

int esCuit(char* pResultado)
{
	int retorno = 1;
	int i;
	if(pResultado != NULL)
	{
		for(i=0;pResultado[i] != '\0';i++)
		{
			if((pResultado[i] != ' ') && (pResultado[i] < '0' || pResultado[i] > '9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int getConfirmacion(char* mensaje,char* mensajeError,char* pResultado, int reintentos, int limite)
{
	int retorno=-1;

	char bufferChar[3];

	if(mensaje!=NULL && mensajeError!=NULL && pResultado!=NULL && reintentos>0 && limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if(myGets(bufferChar,3) == 0 && strnlen(bufferChar,sizeof(bufferChar)-1)<= limite)
			{
				if(esConfirmacion(bufferChar)==0)
				{
					retorno=0;
					strncpy(pResultado,bufferChar,limite);
					break;
				}
				else
				{
					if(esConfirmacion(bufferChar)==1)
					{
						retorno=1;
						strncpy(pResultado,bufferChar,limite);
						break;
					}
				}
			}
			else
			{
				printf("%s\n",mensajeError);
				reintentos--;
			}
		}while(reintentos>=0);

	}

	return retorno;
}

int esConfirmacion(char* pResultado)
{
	int retorno=-1;
	int i;

	if(pResultado != NULL){
		for(i=0;pResultado[i] != '\0';i++)
		{
			if((pResultado[i] != ' ') && (pResultado[i] == 's' || pResultado[i] == 'i'))
			{
				retorno = 0;
				break;
			}
			else
			{
				if((pResultado[i] != ' ') && (pResultado[i] == 'n' || pResultado[i] == 'o'))
				{
					retorno = 1;
					break;
				}
			}
		}
	}

	return retorno;
}
