/*
 * employee.h
 *
 *  Created on: 25 sept. 2020
 *      Author: Gonzalo
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#define TRUE 1
#define FALSE 0
#define LIMITE_NOMBRE 50
typedef struct
{
	char nombreCliente[LIMITE_NOMBRE];
	char apellidoCliente[LIMITE_NOMBRE];
	int cuitCliente;
	int idCliente;
	int isEmpty;
}Cliente;

int cliente_menu(int* pOpcion);
int cliente_report(int* pOpcion);

int cliente_init(Cliente * pArray, int limite);

int cliente_alta(Cliente * pArray, int limite);
int cliente_baja (Cliente * pArray, int limite);
int cliente_modificar (Cliente * pArray, int limite);

int cliente_imprimir(Cliente* pArray, int len);
int cliente_imprimirPorId(Cliente* pArray, int len, int id);
int cliente_buscarLibre (Cliente * pArray, int limite);
int cliente_buscarLibreRef (Cliente * pArray, int limite, int * pIndice);
int cliente_buscarIndicePorId (Cliente * pArray, int limite, int idBuscar,int * pIndice);
int cliente_ordenarPorNombre (Cliente * pArray, int limite , int orden);

int cliente_buscarIdPorCiut(Cliente* pArray, int limite, int cuitABuscar, int* pResultado);
int cliente_imprimirPorCuit(Cliente* pArray,int limite);

void cliente_hardcodeo(Cliente* pArray,int indice, char* nombre,char* apellido, int cuit, int id);

#endif /* CLIENTE_H_ */
