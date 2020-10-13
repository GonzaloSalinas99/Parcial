/*
 * employee.h
 *
 *  Created on: 25 sept. 2020
 *      Author: Gonzalo
 */

#ifndef AVISO_H_
#define AVISO_H_
#define TRUE 1
#define FALSE 0
#define LONG_NOMBRE 64
#define PAUSADO 1
#define ACTIVO 0
#include "cliente.h"

typedef struct
{
	char textoAviso[LONG_NOMBRE];
	int rubroAviso;
	int idAviso;
	int isEmpty;
	int idCliente;
	int isActive;
}Aviso;

int aviso_menu(int* pOpcion);
int aviso_report(int* pOpcion);

int aviso_init(Aviso * pArrayAvisos, int limite);

int aviso_alta(Aviso * pArrays, int limite, Cliente* pArrayCliente, int lenCliente);
int aviso_baja (Aviso * pArrays, int limite, Cliente* pArrayCliente, int lenCliente);
int aviso_estadoPublicacionPausa (Aviso * pArrays, int limite, Cliente* pArrayCliente, int lenCliente);
int aviso_estadoPublicacionActiva(Aviso * pArray, int limite, Cliente* pArrayCliente, int lenCliente);


int aviso_imprimir(Aviso* pArray, int len);
int aviso_buscarLibre (Aviso * pArrayAvisos, int limite);
int aviso_buscarLibreRef (Aviso * pArrayAvisos, int limite, int * pIndice);
int aviso_buscarIndicePorId (Aviso * pArrayAvisos, int limite, int idBuscar,int * pIndice);
int aviso_ordenarPorNombre (Aviso * pArrays, int limite , int orden);

int aviso_buscarIdPorCiut(Aviso* pArrays, int limite, int cuitABuscar, int* pResultado);
int aviso_imprimirPorId(Aviso* pArray,int len,int idCliente);
int aviso_imprimirClientesYAvisos(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente);
int aviso_cantidadAvisos(Aviso* pArray,int len,int id,int *pResultado);


#endif /* AVISO_H_ */