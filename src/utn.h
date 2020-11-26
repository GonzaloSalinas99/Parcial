/*
 * utn.h
 *
 *  Created on: 16 sept. 2020
 *      Author: Gonzalo
 */

#ifndef UTN_H_
#define UTN_H_
//#define LEN_CUIT

int getInt(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo);
int esNumerica(char* array,int limite);
int esUnNombreValido(char* cadena,int limite);
int getNombre(char* mensaje,char* mensajeError,char* pResultado, int reintentos, int limite);
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);
int utn_getDireccion(char* mensaje,char* mensajeError,char* pResultado, int reintentos, int limite);
int esAlfaNumerica(char* pResultado);
int esCuit(char* pResultado);
int getNumero(char* mensaje,char* mensajeError,char* pResultado, int reintentos, int limite);
int esUnTextoValido(char* cadena,int limite);
int utn_getCuit(char* mensaje,char* mensajeError,int* pResultado, int reintentos, int limite);




#endif /* UTN_H_ */
