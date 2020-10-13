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
int informe_cantidadAvisosPausados(Aviso* pArray,int len);
int informe_subMenu(int* pOpcion);

#endif /* INFORME_H_ */
