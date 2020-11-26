#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Venta.h"
#include "utn.h"
#include "LinkedList.h"

Venta* venta_new(void)
{
	return (Venta*)malloc(sizeof(Venta));
}
/*
 * brief Carga, a travez de variables, los campos de un empleado
 * param char* idStr Id a ser cargado
 * param char* nombreStr Nombre a ser cargado
 * param char* horasTrabajadasStr Horas a ser cargadas
 * param char* sueldo Sueldo a ser cargado
 * return Puntero al nuevo empleado
 */
Venta* venta_newParametros(char* nombreVenta,char* cantidadAfiches,char* destino,char* idCliente,char* idVenta,char*isEmpty)
{
	Venta* this = venta_new();
	//int estado=FALSE;

	if(nombreVenta !=NULL && cantidadAfiches!=NULL && destino!=NULL && idCliente != NULL&& idVenta != NULL&& isEmpty != NULL)
	{
		venta_setNombreVenta(this, nombreVenta);
		venta_setCantidadAfiches(this,atoi(cantidadAfiches));
		venta_setDestino(this, atoi(destino));
		venta_setIdCliente(this, atoi(idCliente));
		venta_setIdVenta(this, atoi(idVenta));
		venta_setIsEmpty(this,atoi(isEmpty));
	}
	return this;
}
/*
 * brief Libera el espacio de memoria de un empleado
 */
void venta_borrar(Venta* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

/*
 * brief Escribe en el campo IDVenta
 * param Venta* this puntero a ventas
 * param int idVenta ID a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_setIdVenta(Venta* this,int idVenta)
{
    int retorno = -1;

    if(this != NULL && idVenta >= 0)
    {
        this->idVenta = idVenta;
        retorno = 0;
    }
    return retorno;
}
/*
 * brief Duevuelve el ID de la Venta
 * param Venta* this puntero a ventas
 * param int* idVentas puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_getIdVenta(Venta* this,int* idVenta)
{
    int retorno = -1;

    if(this != NULL && idVenta != NULL)
    {
        *idVenta = this->idVenta;
        retorno = 0;
    }
    return retorno;
}
/*
 * brief Escribe en el campo ID Cliente
 * param Venta* this puntero a ventas
 * param int idCliente ID a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_setIdCliente(Venta* this,int idCliente)
{
    int retorno = -1;

    if(this != NULL && idCliente >= 0)
    {
        this->idCliente = idCliente;
        retorno = 0;
    }
    return retorno;
}
/*
 * brief Duevuelve el ID del Cliente
 * param Venta* this puntero a ventas
 * param int* idCliente puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_getIdCliente(Venta* this,int* idCliente)
{
    int retorno = -1;

    if(this != NULL && idCliente != NULL)
    {
        *idCliente = this->idCliente;
        retorno = 0;
    }
    return retorno;
}

/*
 * brief Escribe en el campo NombreVenta
 * param Venta* this puntero a ventas
 * param char* id Nombre a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_setNombreVenta(Venta* this,char* nombreVenta)
{
    int retorno = -1;

    if(this != NULL && nombreVenta != NULL)
    {
        if(esUnNombreValido(nombreVenta, 128) == 1)
        {
            strncpy(this->nombreVenta, nombreVenta, 128);
            retorno = 0;
        }
    }
    return retorno;
}
/*
 * brief Devuelve nombre
 * param Venta* this puntero a ventas
 * param char* nombre puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_getNombreVenta(Venta* this,char* nombreVenta)
{
    int retorno = -1;
    if(this != NULL && nombreVenta != NULL && esUnNombreValido(this->nombreVenta,128) == 1)
    {
        strncpy(nombreVenta,this->nombreVenta, 128);
        retorno = 0;
    }
    return retorno;
}
/*
 * brief Escribe en el campo destino
 * param Venta* this puntero a ventas
 * param int destino numero a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_setDestino(Venta* this,int destino)
{
    int retorno = -1;

    if(this != NULL)
    {
    	this->destino=destino;
    }
    return retorno;
}
/*
 * brief Devuelve el destino
 * param Venta* this puntero a ventas
 * param int* destino puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_getDestino(Venta* this,int* destino)
{
    int retorno = -1;
    if(this != NULL && destino != NULL)
    {
    	*destino=this->destino;
    	retorno = 0;
    }
    return retorno;
}

/*
 * brief Escribe en el campo cantidadAfiches
 * param Venta* this puntero a ventas
 * param int cantidadAfiches cantidad a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_setCantidadAfiches(Venta* this,int cantidadAfiches)
{
    int retorno = -1;

    if(this != NULL && cantidadAfiches >= 0)
    {
        this->cantidadAfiches = cantidadAfiches;
        retorno = 0;
    }
    return retorno;
}
/*
 * brief Devuelve la cantidad de afiches
 * param Venta* this puntero a venta
 * param int* cantidadAfiches puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_getCantidadAfiches(Venta* this,int* cantidadAfiches)
{
    int retorno = -1;

    if(this != NULL && cantidadAfiches != NULL)
    {
        *cantidadAfiches = this->cantidadAfiches;
        retorno = 0;
    }
    return retorno;
}

/*
 * brief Escribe en el campo isEmpty
 * param Venta* this puntero a venta
 * param int isEmpty Numero a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_setIsEmpty(Venta* this,int isEmpty)
{
    int retorno = -1;

    if(this != NULL && isEmpty >= 0)
    {
        this->isEmpty = isEmpty;
        retorno = 0;
    }
    return retorno;
}
/*
 * brief Devuelve el valor del campo IsEmpty
 * param Venta* this puntero a venta
 * param int* isEmpty puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int venta_getIsEmpty(Venta* this,int* isEmpty)
{
    int retorno = -1;

    if(this != NULL && isEmpty != NULL)
    {
        *isEmpty = this->isEmpty;
        retorno = 0;
    }
    return retorno;
}

/* brief Genera un ID Maximo
* param LinkedList pArrayListVenta puntero a la lista enlazada a empleados
* return (0)si salio todo bien (-1)si hubo un error
*/
int venta_generarId(LinkedList* this)
{
   Venta* auxiliar;
   int cant;
   int auxId;
   int maxID = -1;
   int i;
   if(this != NULL)
   {
       cant = ll_len(this);
       for(i=0;i<cant;i++)
       {
           auxiliar = ll_get(this, i);
           venta_getIdVenta(auxiliar, &auxId);
           if(auxId > maxID)
           {
               maxID = auxId;
           }
       }
   }
   maxID += 1;
   return maxID;
}


/*
 * brief Imprime un elemento de la lista de ventas
 * param void* pElement Elemento de la lista enlazada a empleados
 * return (0)si salio todo bien (-1)si hubo un error
 */
int venta_printVenta(void* pElement)
{
    int retorno = -1;

    Venta* pAuxVenta=(Venta*)pElement;
    char nombreVenta[128];
    int cantidadAfiches;
    int destino;
    int idCliente;
	int idVenta;
	int isEmpty;
	char estado[128];
	char destinoChar[128];

		if(pElement != NULL && venta_getIdVenta(pAuxVenta,&idVenta) == 0 && venta_getNombreVenta(pAuxVenta, nombreVenta) == 0 &&
			venta_getIdCliente(pAuxVenta, &idCliente)== 0&& venta_getDestino(pAuxVenta,&destino)==0 &&
			venta_getCantidadAfiches(pAuxVenta,&cantidadAfiches) ==0 &&
			venta_getIsEmpty(pAuxVenta, &isEmpty) == 0)
		{
			if(isEmpty==0)
			{
				sprintf(estado,"A cobrar");
			}
			else
			{

				sprintf(estado,"Cobrado");
			}
			venta_convertirDestinoNumero(destino, destinoChar);
			printf("\n %-5d         %-14s         %-15d       %-15s       %-10d           %-10s  ",idVenta, nombreVenta, cantidadAfiches, destinoChar,idCliente,estado);
            retorno=0;
		}
        else
        {
            printf("*>Error\n");
        }

    return retorno;
}

/*
 * brief Imprime la venta si el campo IsEmpty == 1
 * param void* pElement Elemento de la lista enlazada de ventas
 * return 0 si salio todo bien -1 si hubo un error
 */
int venta_printVentaFiltrado(void* pElement)
{
    int retorno = -1;

    Venta* pAuxVenta=(Venta*)pElement;
    char nombreVenta[128];
    int cantidadAfiches;
    int destino;
    int idCliente;
	int idVenta;
	int isEmpty;
	char estado[128];
	char destinoChar[128];

		if(pElement != NULL && venta_getIsEmpty(pAuxVenta,&isEmpty)==0 && isEmpty == 0)
		{
			venta_getIdVenta(pAuxVenta,&idVenta);
			venta_getNombreVenta(pAuxVenta, nombreVenta);
			venta_getIdCliente(pAuxVenta, &idCliente);
			venta_getDestino(pAuxVenta,&destino);
			venta_getCantidadAfiches(pAuxVenta,&cantidadAfiches);
			sprintf(estado,"A cobrar");
			venta_convertirDestinoNumero(destino, destinoChar);

			printf("\n %-5d         %-14s         %-15d       %-15s       %-10d           %-10s  ", idVenta, nombreVenta, cantidadAfiches,destinoChar ,idCliente, estado);
            retorno=0;
		}

    return retorno;
}


/*
 * brief Busca la posicion de un empleado por el ID
 * param LinkedList this puntero a la lista enlazada a empleados
 * param int idABuscas ID a ser buscado
 * param int* index puntero donde devuelve el indice del ID busca
 * return (0)si salio todo bien (-1)si hubo un error
*/
int venta_buscarIndicePorId(LinkedList* this, int idABuscar,int* index)
{
	int retorno = -1;
	int i;
	int len;
	int idAux;
	Venta* bufferVenta;

	if(this!= NULL && idABuscar>0 && index!=NULL)
	{
		len = ll_len(this);
		if(len>0)
		{
			for(i=0;i<len;i++)
			{
				bufferVenta = ll_get(this, i);
				venta_getIdVenta(bufferVenta,&idAux);
				if(idAux == idABuscar)
				{
					*index = i;
					retorno=0;
				}
			}
		}
	}
	return retorno;
}

/*
 * brief Escribe segun el numero, una ubicacion
 * param int destino Numero a ser evaluado
 * param char* destinoChar Donde se va a devolver el resultado
 * return 0 si salio todo bien -1 si hubo un error
 */
int venta_convertirDestinoNumero(int destino,char* destinoChar)
{
	int retorno=-1;

	if(destinoChar!=NULL)
	{
		if(destino==1)
		{
			sprintf(destinoChar,"CABA");
		}
		else if(destino==2)
		{
			sprintf(destinoChar,"ZONA SUR");
		}
		else
		{
			sprintf(destinoChar,"ZONA OESTE");
		}
		retorno=0;
	}
	return retorno;
}

int venta_menu(int* pOpcion)
{
	int retorno;
	printf("\n\n*************BIENVENIDO*************\n\n");
	printf("****************************************\n\n");
	printf("*************Modificar Ventas*************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: Nombre del archivo.\n");
	printf("*>OPCION 2: Destino.\n");
	printf("*>OPCION 3: Cantidad de afiches.\n");
	printf("*>OPCION 4: Salir.\n");
	printf("********************************************");

	getInt("\nIngrese la opcion: ", "ERROR", &retorno, 3, 4, 1);
	*pOpcion=retorno;
	return retorno;
}

/*
 * brief Devuelve un 1 si el campo isEmpty == 1
 * param void* pElement puntero a un elemento de la lista enlazada de ventas
 * param int idCliente ID a buscar en la lista
 * return 0 si el campo IsEmpty no es == 1   11 si el campo IsEmpty == 1
 */
int venta_filtrarPorIsEmpty(void* pElement,int idCliente)
{
	int retorno=0;
	Venta* aux=(Venta*)pElement;
	int idClienteAux;
	int isEmpty;
	if(aux!=NULL && idCliente>0)
	{
		venta_getIdCliente(aux, &idClienteAux);
		venta_getIsEmpty(aux, &isEmpty);
		if(idClienteAux==idCliente)
		{
			if(isEmpty==1)
			{
				retorno=1;
			}
		}
	}
	return retorno;
}

/*
 * brief Acumula la cantidad de afiches con el campo IsEmpty == 1
 * param void* pElement puntero a un elemento de la lista enlazada de ventas
 * param int idCliente ID a buscar en la lista
 * return Retorna la cantidad de afiches
 */
int venta_acumularAfiches(void* pElement,int idCliente)
{
	int retorno=0;
	Venta* ventaAux=(Venta*)pElement;
	int isEmpty;
	int idAux;
	int cantidadAfiches;

	if(ventaAux!=NULL && idCliente>0)
	{
		venta_getIdCliente(ventaAux, &idAux);
		venta_getIsEmpty(ventaAux, &isEmpty);
		venta_getCantidadAfiches(ventaAux, &cantidadAfiches);
		if(idCliente==idAux)
		{
			if(isEmpty==1)
			{
				retorno=cantidadAfiches;
			}
		}
	}
	return retorno;
}
/*
 * brief Devuelve la posicion del elemento mediante el ID del cliente
 * param LinkedList* listaVentas punteron a la lista enlazada de ventas
 * param int idCliente ID a buscar en la lista
 * int* indice Direccion de memoria donde se escribira el resultado
 * return 0 si salio todo bien -1 si hubo un error
 */
int venta_encontrarVentaPorIdCliente(LinkedList* listaVentas,int idCliente,int* indice)
{
	int retorno=-1;
	Venta* ventaAux;
	int len=ll_len(listaVentas);
	int idAux;
	int estado;

	if(listaVentas != NULL && idCliente>0)
	{
		for(int i=0;i<len;i++)
		{
			ventaAux=ll_get(listaVentas,i);
			venta_getIsEmpty(ventaAux, &estado);
			venta_getIdCliente(ventaAux, &idAux);
			if(estado==1)
			{
				if(idAux==idCliente)
				{
					*indice=i;
					retorno=0;
					break;
				}
			}
		}
	}
	return retorno;
}
