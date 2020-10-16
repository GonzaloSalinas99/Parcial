/*
 * employee.c
 *
 *  Created on: 25 sept. 2020
 *      Author: Gonzalo
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utn.h"
#include "cliente.h"
#include "aviso.h"


static int aviso_bajaTodasPublicaciones(Aviso* pArray,int len, int idCliente);
static int aviso_generarNuevoId (void);

/*
 * brief Inicia la lista en todas sus posiciones como VACIAS
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int aviso_init(Aviso * pArray, int limite)
{
	int retorno = -1;
	if (pArray != NULL && limite >0){
		for (int i = 0; i<limite; i++ )
		{
			pArray[i].isEmpty = TRUE;
			pArray[i].isActive = PAUSADO;
		}
		retorno = 0;
	}

	return retorno;
}

/*
 * brief Le da el ALTA al aviso luego de validar todos los datos
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param Cliente pArrayCliente Lista de clientes
 * param lenCliente Cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int aviso_alta(Aviso * pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int indice;
	int idABuscar;
	int indiceCliente;
	Aviso bufferAviso;


	if (pArray != NULL && limite >0 && pArrayCliente!=NULL && lenCliente>0)
	{
		cliente_imprimir(pArrayCliente,lenCliente);
		if(getInt("\n\ningrese el ID del cliente cargado para contratar el aviso: : ","ERROR",&idABuscar,3,1000,0)==0 &&
			cliente_buscarIndicePorId(pArrayCliente,lenCliente,idABuscar,&indiceCliente)==0)
		{
			if (aviso_buscarLibreRef (pArray, limite, &indice) == 0)
			{
					if (getTexto("Ingrese el texto del aviso: ", "error",bufferAviso.textoAviso,2,LONG_NOMBRE) == 0 &&
						getInt("A que rubro pertenece el aviso: ","ERROR",&bufferAviso.rubroAviso,3,1000,1) == 0)
					{
							pArray[indice] = bufferAviso;
							pArray[indice].idCliente = pArrayCliente[indiceCliente].idCliente;
							pArray[indice].idAviso = aviso_generarNuevoId();
							pArray[indice].isEmpty = FALSE;
							pArray[indice].isActive = FALSE;
							retorno=0;
							printf("El ID de esta publicacion es: %d",pArray[indice].idAviso);
					}
					else
					{
						printf("ERROR");
					}
			}
			else
			{
				printf(" \n No quedan espacios libres");
			}
		}
	}
		return retorno ;
}

/*
 * brief Le da el BAJA al aviso luego de validar todos los datos
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param Cliente pArrayCliente Lista de clientes
 * param lenCliente Cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */

int aviso_baja (Aviso* pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int idABorrar;
	int indiceABorrar;
	int confirmacion;

	if (pArray != NULL && limite>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		cliente_imprimir(pArrayCliente, lenCliente);
		if(getInt("\n\nIngrese ID de cliente a borrar: ","Error",&idABorrar,3,1000,0)==0 &&
				cliente_buscarIndicePorId(pArrayCliente,lenCliente,idABorrar,&indiceABorrar)==0)
		{
			aviso_imprimirPorId(pArray, limite,idABorrar);
			if( getInt("\n\nDesea confirmar la baja?? Ingrese 1-Si o 2-No :","ERROR",&confirmacion,3,2,1)== 0)
			{
				if(confirmacion==1)
				{
					aviso_bajaTodasPublicaciones(pArray,limite,idABorrar);
					pArrayCliente[indiceABorrar].isEmpty=TRUE;
					retorno=0;
				}
			}
		}
	}
	return retorno;
}

/*
 * brief Le modifica el campo de ESTADO al Aviso ACTIVO como PAUSADO
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param Cliente pArrayCliente Lista de clientes
 * param lenCliente Cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */

int aviso_estadoPublicacionPausa (Aviso * pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int idBuscar;
	int indiceAModificar;
	int confirmacion;

	if (pArray != NULL && limite>0 && pArrayCliente!= NULL && lenCliente>0)
	{
		aviso_imprimir(pArray,limite);
		if(getInt("\n\nIngrese el ID de la publicacion a modificar: ","ERROR",&idBuscar,3,1000,1)==0 &&
			aviso_buscarIndicePorId(pArray, limite, idBuscar, &indiceAModificar) == 0)
		{
			if(cliente_imprimirPorId(pArrayCliente, lenCliente,pArray[indiceAModificar].idCliente)==0)
			{
				if(getInt("\nEsta seguro de modificar esta publicacion?? Ingrese 1-Si o 2-No : ","Error",&confirmacion,3,2,1)==0)
				{
					if(confirmacion==1)
					{
						pArray[indiceAModificar].isActive = PAUSADO;
						retorno = 0;
					}
				}
				else
				{
					printf("\nSigue activa");
				}
			}
		}
	}
return retorno;
}

/*
 * brief Le modifica el campo ESTADO del Aviso PAUSADO como ACTIVO
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param Cliente pArrayCliente Lista de clientes
 * param lenCliente Cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */

int aviso_estadoPublicacionActiva(Aviso * pArray, int limite, Cliente* pArrayCliente, int lenCliente)
{
	int retorno = -1;
	int idBuscar;
	int indiceAModificar;
	int confirmacion;

	if (pArray != NULL && limite>0 && pArrayCliente!= NULL && lenCliente>0)
	{
		aviso_imprimir(pArray,limite);
		if(getInt("\n\nIngrese el ID de la publicacion a modificar: ","ERROR",&idBuscar,3,1000,1)==0 &&
			aviso_buscarIndicePorId(pArray, limite, idBuscar, &indiceAModificar) == 0)
		{
			if(cliente_imprimirPorId(pArrayCliente, lenCliente,pArray[indiceAModificar].idCliente)==0)
			{
				if(getInt("\nEsta seguro de modificar esta publicacion?? Ingrese 1-Si o 2-No : ","Error",&confirmacion,3,2,1)==0)
				{
					if(confirmacion==1)
					{
						pArray[indiceAModificar].isActive = ACTIVO;
						retorno = 0;
					}
				}
				else
				{
					printf("\nSigue en pausa");
				}
			}
		}
	}
return retorno;
}


/*
 * brief Busca en la lista de Aviso un lugar libre
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * return devuelve la posicion libre en la lista
 */
int aviso_buscarLibre (Aviso * pArray, int limite)
{

	int retorno = -1;
	int i ;

	if (pArray != NULL && limite >0)
	{
		for ( i = 0; i<limite; i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/*
 * brief Busca en la lista de Aviso un lugar libre
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param pIndice direccion de memoria donde se escribiria el resultado
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int aviso_buscarLibreRef (Aviso * pArray, int limite, int * pIndice){
	int retorno = -1;
	int i ;
		if (pArray != NULL && limite >0 && pIndice != NULL){
			for ( i = 0; i<limite; i++) {
				if(pArray[i].isEmpty == TRUE)
					{
						*pIndice = i;
						retorno = 0;
						break;
					}
			}
		}
	return retorno;
}
/*
 * brief Genera un ID unico e irrepetible
 * return Devuelve el ID generado
 */
static int aviso_generarNuevoId (void) {
	static int id = 0;
	id = id+1;
	return id;
}
/*
 * brief Busca en la lista de Aviso un indice a travez del ID
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param IdBuscar ID que es buscado en la lista de Avisos
 * param *pindice Direccion de memoria donde se escribira el indice encontrado
 * return devuelve la posicion libre en la lista
 */
int aviso_buscarIndicePorId (Aviso * pArray, int limite,int idBuscar,int * pIndice)
{
	int retorno = -1;
	int i ;
		if (pArray != NULL && limite >0 && pIndice != NULL && idBuscar >= 0)
		{
				for ( i = 0; i<limite; i++)
				{
					if(pArray[i].idAviso == idBuscar)
					{
						*pIndice = i;
						retorno = 0;
						break;
					}
				}
			}
			else
			{
				printf("errrror");
			}
		return retorno;
}
/*
 * brief Ordenar lista de Avisos de forma Ascendente o Descendente
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param orden Numero ingresado por el usuario para saber de que manera ordenar la lista
 * return (-1) si ocurrio un error (0) si se pudo ordenar
 */
int aviso_ordenarPorNombre (Aviso * pArray, int limite , int orden)
{
	int retorno = -1;
	int estadoDesordenado = 1;
	Aviso aux;
	if (pArray != NULL && limite >0)
	{
		while(estadoDesordenado)
		{
			estadoDesordenado = 0;
				for(int i = 0; i < (limite - 1); i++)
				{
					if((orden == 1 && strncmp(pArray[i].textoAviso, pArray[i + 1].textoAviso,LONG_NOMBRE)>0)
							||
					  (orden == 0 && strncmp(pArray[i].textoAviso, pArray[i + 1].textoAviso,LONG_NOMBRE)<0))
					{
						aux = pArray[i];
						pArray[i] = pArray[i + 1];
						pArray[i + 1] = aux;
						estadoDesordenado = 1;
					}
				}
		}
	retorno = 0;
	}
	return retorno;
}


/*
 * brief Imprime la lista de Avisos
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int aviso_imprimir(Aviso* pArray, int limite)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0)
	{
		printf("ID\tTEXTO DEL AVISO\t\t\tRUBRO\t\tESTADO 1 Pausado 0 Activo");
		for(int i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				printf("\n%d\t%s\t\t\t\t%d\t\t\t%d",pArray[i].idAviso,pArray[i].textoAviso,pArray[i].rubroAviso,pArray[i].isActive);

			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * brief Imprime la lista lista de Avisos por ID
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param idCliente ID del aviso el cual vamos a imprimir
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int aviso_imprimirPorId(Aviso* pArray,int limite,int idCliente)
{
	int retorno=-1;
	int i;

	if(pArray!=NULL && limite>0 && idCliente>0)
	{
		printf("\nPublicaciones del cliente con el ID: %d",idCliente);

		for(i=0;i<limite;i++)
		{
			if(pArray[i].idCliente==idCliente && pArray[i].isEmpty==FALSE)
			{
				printf("\nTEXTO DEL AVISO\t\tRUBRO\t\tID DEL AVISO\t\tESTADO");
				printf("\n%s\t\t\t%d\t\t\t%d\t\t\t%d",pArray[i].textoAviso,pArray[i].rubroAviso,pArray[i].idAviso,pArray[i].isActive);
				retorno=0;
			}
		}
	}

	return retorno;
}

/*
 *brief Menu de opciones
 *param int* pOpcion Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 *return (0) si se ingreso correctamente la opcion (-1) Si la opcion es invalida
 */
int aviso_menu(int* pOpcion)
{
	int retorno;

	printf("\n\n*************BIENVENIDO*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: ALTA A EMPLEADO.\n");
	printf("*>OPCION 2: MODIFICAR DATOS EMPLEADO.\n");
	printf("*>OPCION 3: BAJA A EMPLEADO.\n");
	printf("*>OPCION 4: INFORMAR.\n");
	printf("*>OPCION 5: SALIR.\n");

	getInt("\ningresa la opcion: ","Error",&retorno,3,5,1);
	*pOpcion=retorno;
	return retorno;
}
/*
 *brief Menu de informes del programa
 *param int* pOpcion Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 *return (0) si se ingreso correctamente la opcion (-1) Si la opcion es invalida
 */
int aviso_report(int* pOpcion)
{
	int retorno;
	printf("\n\n*************INFORMES*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: ORDENAR.\n");
	printf("*>OPCION 2: IMPRIMIR.\n");
	printf("*>OPCION 3: PROMEDIO SALARIO Y CUANTOS EMPLEADOS SUPERAN ESTE PROMEDIO.\n");
	printf("*>OPCION 4: VOLVER AL MENU PRINCIPAL.\n");


	getInt("\ningresa la opcion: ","Error",&retorno,3,4,1);
	*pOpcion=retorno;
	return retorno;
}


/*
 * brief Da de BAJA a todos los avisos de un Cliente
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param idCliente ID del Cliente el cual borraremos sus avisos
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
static int aviso_bajaTodasPublicaciones(Aviso* pArray,int limite, int idCliente)
{
	int retorno=-1;
	int i;
	if(pArray!=NULL && limite>0 && idCliente>0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].idCliente==idCliente)
			{
				pArray[i].isEmpty=TRUE;
				retorno=0;
			}
		}
	}
	return retorno;
}
/*
 * brief Contar la cantidad de avisos que tiene cada cliente
 * param Aviso* pArray lista de avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param idCliente ID del cliente para contar sus avisos
 * param *pResultado Direccion de memoria donde escribiremos el resultado obtenido
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int aviso_cantidadAvisos(Aviso* pArray,int limite,int idCliente,int *pResultado)
{
	int retorno=-1;
	int indiceAviso;
	int contadorAvisos=0;

	if(pArray!=NULL && limite>0 && idCliente>0 && pResultado!=NULL)
	{
		for(indiceAviso=0;indiceAviso<limite;indiceAviso++)
		{
			if(pArray[indiceAviso].isEmpty==FALSE && idCliente==pArray[indiceAviso].idCliente && pArray[indiceAviso].isActive==ACTIVO)
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
 * brief Imprime la lista lista de Clientes y la cantidad de avisos ACTIVOS que tienen
 * param Aviso* pArray lista de Avisos
 * param limite cantidad de posiciones que tiene la lista de Avisos
 * param Cliente* pArrayCliente lista de Clientes
 * param lenCliente cantidad de posiciones que tiene la lista de Clientes
 * return (-1) si ocurrio un error (0) si salio todo bien
 */
int aviso_imprimirClientesYAvisos(Aviso* pArray,int limite,Cliente* pArrayCliente,int lenCliente)
{
	int retorno=-1;
	//int cantidadAvisos;
	int i;
	int j;
	int contadorAvisos=0;
	if(pArray!=NULL && limite>0 && pArrayCliente!=NULL && lenCliente>0)
	{
		printf("ID\t NOMBRE \t\t\t\t APELLIDO \t\t\t\t CUIT \t\t AVISOS ACTIVOS");
		for(i=0;i<lenCliente;i++)
		{
			if(pArrayCliente[i].isEmpty==FALSE)
			{
				for(j=0;j<limite;j++)
				{
					if(pArray[j].idCliente==pArrayCliente[i].idCliente && pArray[j].isActive== ACTIVO)
					{
						contadorAvisos++;
					}
				}

				printf("\n%d\t %s  \t\t\t\t %s  \t\t\t\t %d\t %d",pArrayCliente[i].idCliente,pArrayCliente[i].nombreCliente,pArrayCliente[i].apellidoCliente,pArrayCliente[i].cuitCliente,contadorAvisos);
				contadorAvisos=0;
			}
		}
	}
	retorno=0;
	return retorno;
}
/*
 * brief Hardcodea la lista de Avisos
 * param Aviso* pArray lista de avisos
 * param indice Posicion de la lista
 * param *texto Texto a guardar
 * param rubro Rubro a guardar
 * param idcliente ID del cliente a guardar
 * param id ID del aviso a guardar
 */
void aviso_hardcodeo(Aviso* pArray,int indice, char* texto,int rubro,int idCliente,int id)
{
	strncpy(pArray[indice].textoAviso,texto,LIMITE_NOMBRE);
	pArray[indice].rubroAviso = rubro;
	pArray[indice].idCliente=idCliente;
	pArray[indice].idAviso=id;
	pArray[indice].isEmpty = FALSE;
	pArray[indice].isActive=ACTIVO;
}
