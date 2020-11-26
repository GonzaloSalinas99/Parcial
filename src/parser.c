#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"
#include "string.h"
#include "Venta.h"
#include "Cliente.h"

/** \brief Parsea los datos de los clientes desde el archivo en modo texto
 * \param FILE* pFile puntero a la estructura FILE
 * \param pArrayListEmployee LinkedList* puntero a la lista enlazada
 * \return int (0) si salio todo bien (-1)si hubo un error
 */
int parser_EnvioFromTextCliente(FILE* pFile , LinkedList* this)
{
	int retorno = -1; //retorno error
	Cliente* pCliente;
	char nombre[128];
	char apellido[128];
    char id[10];
    char cuit[LEN_CUIT];

	if(pFile != NULL && this != NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, apellido, cuit)==4)
			{
				pCliente = cliente_newParametros(nombre, apellido, id, cuit);
				if(pCliente!= NULL)
				{
					ll_add(this, pCliente);
					retorno = 0;
				}
			}
		}
		while(feof(pFile) == 0);
	}
	return retorno;
}

/** \brief Parsea los datos de las ventas desde el archivo en modo texto
 * \param FILE* pFile puntero a la estructura FILE
 * \param pArrayListEmployee LinkedList* puntero a la lista enlazada
 * \return int (0) si salio todo bien (-1)si hubo un error
 */
int parser_EnvioFromTextVenta(FILE* pFile , LinkedList* this)
{
	int retorno = -1; //retorno error
	Venta* pVenta;
    char nombreVenta[128];
    char cantidadAfiches[4096];
    char destino[128];
    char idCliente[4096];
	char idVenta[4096];
	char isEmpty[10];

	if(pFile != NULL && this != NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idVenta, nombreVenta, cantidadAfiches,destino ,idCliente,isEmpty)==6)
			{

				pVenta = venta_newParametros( nombreVenta, cantidadAfiches, destino, idCliente,idVenta,isEmpty);
				if(pVenta != NULL)
				{
					ll_add(this, pVenta);
					retorno = 0;
				}
			}
		}
		while(feof(pFile) == 0);
	}
	return retorno;
}
