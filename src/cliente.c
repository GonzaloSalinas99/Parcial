#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Cliente.h"
#include "utn.h"
#include "LinkedList.h"
/*
 * brief Asigna un lugar en memoria para un empleado
 * return Puntero al empleado
 */
Cliente* cliente_new(void)
{
	return (Cliente*)malloc(sizeof(Cliente));
}
/*
 * brief Carga, a travez de variables, los campos de un empleado
 * param char* idStr Id a ser cargado
 * param char* nombreStr Nombre a ser cargado
 * param char* horasTrabajadasStr Horas a ser cargadas
 * param char* sueldo Sueldo a ser cargado
 * return Puntero al nuevo empleado
 */
Cliente* cliente_newParametros(char* nombre,char* apellido,char* id,char* cuit)
{
	Cliente* this = cliente_new();

	if(nombre !=NULL && apellido!=NULL && id!=NULL && cuit!= NULL)
	{
			cliente_setNombre(this, nombre);
			cliente_setApellido(this, apellido);
			cliente_setId(this, atoi(id));
			cliente_setCuit(this,cuit);
		}
	return this;
}
/*
 * brief Libera el espacio de memoria de un empleado
 */
void cliente_borrar(Cliente* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}


/*
 * brief Escribe en el campo ID
 * param Cliente* this puntero a cliente
 * param int id ID a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_setId(Cliente* this,int id)
{
    int retorno = -1;

    if(this != NULL && id >= 0)
    {
        this->id = id;
        retorno = 0;
    }
    return retorno;
}
/*
 * brief Duevuelve el ID
 * param Cliente* this puntero a cliente
 * param int* id puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_getId(Cliente* this,int* id)
{
    int retorno = -1;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        retorno = 0;
    }
    return retorno;
}

/*
 * brief Escribe en el campo Nombre
 * param Cliente* this puntero a cliente
 * param char* nombre Nombre a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_setNombre(Cliente* this,char* nombre)
{
    int retorno = -1;

    if(this != NULL && nombre != NULL)
    {
        if(esUnNombreValido(nombre, 128) == 1)
        {
            strncpy(this->nombre, nombre, 128);
            retorno = 0;
        }
    }
    return retorno;
}
/*
 * brief Devuelve nombre
 * param Cliente* this puntero a cliente
 * param char* nombre puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_getNombre(Cliente* this,char* nombre)
{
    int retorno = -1;
    // char aux[18]="GONZALO";
    if(this != NULL && nombre != NULL)// && esUnNombreValido(this->nombre,128) == 1)
    {
        strncpy(nombre,this->nombre, 128);
        retorno = 0;
    }
    return retorno;

}

/*
 * brief Escribe en el campo Apellido
 * param Cliente* this puntero a cliente
 * param char* apellido Apellido a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_setApellido(Cliente* this,char* apellido)
{
    int retorno = -1;

    if(this != NULL && apellido != NULL)
    {
        if(esUnNombreValido(apellido, 128) == 1)
        {
            strncpy(this->apellido, apellido, 128);
            retorno = 0;
        }
    }
    return retorno;
}
/*
 * brief Devuelve apellido
 * param Cliente* this puntero a cliente
 * param char* apellido puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_getApellido(Cliente* this,char* apellido)
{
    int retorno = -1;
    // char aux[18]="GONZALO";
    if(this != NULL && apellido != NULL && esUnNombreValido(this->apellido,128) == 1)
    {
        strncpy(apellido,this->apellido, 128);
        retorno = 0;
    }
    return retorno;
}

/*
 * brief Escribe en el campo Sueldo
 * param Cliente* this puntero a cliente
 * param char* cuit cuit a cargar
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_setCuit(Cliente* this,char* cuit)
{
    int retorno = -1;

    if(this != NULL)
    {
    	strncpy(this->cuit,cuit,LEN_CUIT);

    }
    return retorno;
}
/*
 * brief Devuelve el cuit
 * param Cliente* this puntero a empleado
 * param char* cuit puntero donde devuelve el valor
 * return (0) si salio todo bien (-1)si hubo un error
 */
int cliente_getCuit(Cliente* this,char* cuit)
{
    int retorno = -1;

    if(this != NULL && cuit != NULL)
    {
    	strncpy(cuit,this->cuit,LEN_CUIT);

    	retorno=0;
    }
    return retorno;
}
/*
 * brief Imprime la lista de empleados
 * param LinkedList pArrayListCliente puntero a la lista enlazada a empleados
 * param int index Indice del empleado a imprimir
 * return (0)si salio todo bien (-1)si hubo un error
 */
int cliente_imprimirUnCliente(void* pElement)
{
	int retorno=0;
	Cliente* aux=(Cliente*)pElement;
	int idCliente;
	char nombre[128];
	char apellido[128];
	char cuit[LEN_CUIT];

	if(pElement!=NULL)
	{
		cliente_getId(aux, &idCliente);
		cliente_getNombre(aux, nombre);
		cliente_getApellido(aux, apellido);
		cliente_getCuit(aux, cuit);
		printf("\n%-10d    %-20s     %-20s     %-10s",idCliente,nombre,apellido,cuit);
		retorno=0;

	}
	return retorno;
}

/*
 * brief Genera un ID Maximo
 * param LinkedList pArrayListCliente puntero a la lista enlazada a empleados
 * return (0)si salio todo bien (-1)si hubo un error
 */
int cliente_generarId(LinkedList* this)
{
    Cliente* auxiliar;
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
            cliente_getId(auxiliar, &auxId);
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
 * brief Busca la posicion de un empleado por el ID
 * param LinkedList this puntero a la lista enlazada a empleados
 * param int idABuscas ID a ser buscado
 * param int* index puntero donde devuelve el indice del ID busca
 * return (0)si salio todo bien (-1)si hubo un error
 */
int cliente_buscarIndicePorId(LinkedList* this, int idABuscar,int* index)
{
	int retorno = -1;
	int i;
	int len;
	int idAux;
	Cliente* bufferCliente;

	if(this!= NULL && idABuscar>0 && index!=NULL)
	{
		len = ll_len(this);
		if(len>0)
		{
			for(i=0;i<len;i++)
			{
				bufferCliente = ll_get(this, i);
				cliente_getId(bufferCliente,&idAux);
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
 * brief Ordena por nombre
 * param void* thisA puntero donde se recibira el primer empleado
 * param void* thisA puntero donde se recibira el segundo empleado
 * return (0)si salio todo bien (-1)si hubo un error
 */

/*
int cliente_ordenarPorNombre (void* thisA, void* thisB)
{
	int retorno;
	Cliente* auxA =(Cliente*)thisA;
	Cliente* auxB =(Cliente*)thisB;
	char nombreA[128];
	char nombreB[128];
	int respuesta;
	cliente_getNombre(auxA, nombreA);
	cliente_getNombre(auxB, nombreB);
	respuesta=strncmp(nombreA,nombreB,128);
	if(respuesta>0)
	{
		retorno=1;
	}
	else if(respuesta<0)
	{
		retorno=-1;
	}
	else
	{
		retorno = 0;
	}
	return retorno;
}
*/

/*
 * brief Verifica si el ID del Cliente, coincide con el ID pasado por parametro
 * param LinkedList this puntero a la lista enlazada a clientes
 * param int id ID a ser buscado
 * return (0)si salio todo bien (-1)si hubo un error
 */
int cliente_buscarPorId(LinkedList* this,int id)
{
	int retorno=-1;
	int idCliente;
	int len=ll_len(this);
	Cliente* aux;

	if(this!= NULL && id>0)
	{
		for(int i=0;i<len;i++)
		{
			aux=(Cliente*)ll_get(this,i);
			if(cliente_getId(aux,&idCliente)==0)
			{
				if(id==idCliente)
				{
					retorno=0;
					break;
				}
			}
		}
	}
	return retorno;
}

/*
 * brief Compara el cuit del cliente con el que le pasaron por parametro
 * param void*  puntero a un elemento
 * param void* cuit puntero a un cuit
 * return (0)si los cuits son diferentes (-1)si los cuits son iguales
 */
int cliente_estaRepetido(void* this,void* cuit)
{
	int retorno=0;
	Cliente* aux=(Cliente*)this;
	char cuitAVerificar[LEN_CUIT];

	if(this!=NULL && cuit!=NULL)
	{
		if(cliente_getCuit(aux, cuitAVerificar)==0 && strncmp(cuitAVerificar,cuit,LEN_CUIT)==0)
		{
			retorno=-1;
		}
	}
	return retorno;
}

/*
 * brief Recorre la lista para comparar los cuits
 * param LinkedList this puntero a la lista enlazada a empleados
 * param void* pElement puntero a un elemento
 * return (0)si salio todo bien (-1)si hubo un error en la comparacion
 */
int cliente_verificarCuit(LinkedList* this,void* pElement)
{
	int retorno=0;
	Cliente* auxiliar;

	if(this!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			auxiliar=ll_get(this,i);
			if(cliente_estaRepetido(auxiliar, pElement)!=0)
			{
				retorno=-1;
			}
		}
	}
	return retorno;
}

/*
 * brief Analiza si el cuit que le pasan por parametro esta repetido
 * param LinkedList this puntero a la lista enlazada a empleados
 * param void* pElement puntero a un elemento
 * return (0)si esta repetido(-1)si no esta repetido
 */
int cliente_buscarCuit(LinkedList* this,void*pElement)
{
	int retorno=-1;

	if(this!=NULL && ll_isEmpty(this)==0)
	{
		if(cliente_verificarCuit(this,pElement)!=0)
		{
			retorno=0;
		}
	}
	return retorno;
}

/*
 * brief Menu de opciones para modificar
 * param int* pOpcion Puntero a donde devuelve el resultado obtenido
 */
int cliente_menu(int* pOpcion)
{
	int retorno;
	printf("\n\n*************BIENVENIDO*************\n\n");
	printf("****************************************\n\n");
	printf("*************Modificar Cliente*************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: Nombre del cliente.\n");
	printf("*>OPCION 2: Apellido del cliente.\n");
	printf("*>OPCION 3: Cuit del cliente.\n");
	printf("*>OPCION 4: Salir.\n");
	printf("********************************************");

	getInt("\nIngrese la opcion: ", "ERROR", &retorno, 3, 4, 1);
	*pOpcion=retorno;
	return retorno;
}
