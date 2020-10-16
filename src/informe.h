/*
 * informe.h
 *
 *  Created on: 13 oct. 2020
 *      Author: Gonzalo
 */

#ifndef INFORME_H_
#define INFORME_H_
#define TRUE 1
#define FALSE 0

int informe_calcularTotalAvisos(Aviso* pArray,int len,int id,int *pResultado);
int informe_imprimirClienteMayorCantidadAvisos(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente);

int informe_cantidadAvisosPausados(Aviso* pArray,int limite);

int informe_imprimirRubroConMayorCantidadAviso(Aviso *pArrayAviso, int limiteAvisos);
int informe_calcularRubroPorAviso(Aviso *pArrayAviso, int limiteAviso, int rubro, int *pContador);



int informe_subMenu(int* pOpcion);

int informe_calcularTotalAvisosDeClientesPausados(Aviso* pArray,int len,int id,int *pResultado);
int informe_imprimirClienteMayorCantidadAvisosPausados(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente);


int informe_calcularTotalAvisosDeClientesActivos(Aviso* pArray,int len,int id,int *pResultado);
int informe_imprimirClienteMayorCantidadAvisosActivos(Aviso* pArray,int lenAviso,Cliente* pArrayCliente,int lenCliente);


#endif /* INFORME_H_ */
