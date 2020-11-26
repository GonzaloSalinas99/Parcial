#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "Venta.h"
#include "utn.h"
#include "parser.h"
#include "controller.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo a cargar
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error
 *
 */


int controller_loadFromTextCliente(char* path , LinkedList* this)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL && this != NULL)
	{
		pFile = fopen(path, "r");

		if(pFile != NULL && parser_EnvioFromTextCliente(pFile, this) == 0)
		{

			printf("*>Datos cargados con exito!\n\n");
			retorno = 0;
		}
		else
		{
			printf("*>No ha sido posible cargar los datos\n\n");
		}
	}
	else
	{
		printf("*>Error NULL\n\n");
	}
	fclose(pFile);
	return retorno;
}

int controller_loadFromTextVenta(char* path , LinkedList* this)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL && this != NULL)
	{
		pFile = fopen(path, "r");

		if(pFile != NULL && parser_EnvioFromTextVenta(pFile, this) == 0)
		{

			printf("*>Datos cargados con exito!\n\n");
			retorno = 0;
		}
		else
		{
			printf("*>No ha sido posible cargar los datos\n\n");
		}
	}
	else
	{
		printf("*>Error NULL\n\n");
	}
	fclose(pFile);
	return retorno;
}
/*
brief Guarda los datos de los Clientes en el archivo de texto.
*
* \param path char* Ruta del archivo en donde guardar los datos
* \param pArrayListEmployee LinkedList* puntero a la lista enlazada
* \return int (0) si salio todo bien (-1)si hubo un error
*/
int controller_saveAsTextCliente(char* path , LinkedList* this)
{
	int retorno = -1;
	FILE* pFile;
	Cliente* bufferCliente;
	char nombre[128];
	char apellido[128];
    int id;
    char cuit[LEN_CUIT];
	int len = ll_len(this);

	if(path!=NULL && this!=NULL)
	{
		pFile = fopen(path,"w");
		if(pFile!=NULL)
		{
			for(int i=0;i<len;i++)
			{
				bufferCliente=(Cliente*)ll_get(this,i);
				cliente_getNombre(bufferCliente, nombre);
				cliente_getApellido(bufferCliente, apellido);
				cliente_getId(bufferCliente, &id);
				cliente_getCuit(bufferCliente,cuit);
				fprintf(pFile,"%d,%s,%s,%s\n",id,nombre,apellido,cuit);
			}
		}
			retorno=0;
	}
	fclose(pFile);
    return retorno;
}
/*
brief Guarda los datos de las Ventas en el archivo de texto.
*
* \param path char* Ruta del archivo en donde guardar los datos
* \param pArrayListEmployee LinkedList* puntero a la lista enlazada
* \return int (0) si salio todo bien (-1)si hubo un error
*/
int controller_saveAsTextVentas(char* path , LinkedList* this)
{
	int retorno = -1;
	FILE* pFile;
	Venta* bufferVenta;
    char nombreVenta[128];
    int cantidadAfiches;
    int destino;
    int idCliente;
	int idVenta;
	int isEmpty;
	int len = ll_len(this);
	//char destinoChar[128];

	if(path!=NULL && this!=NULL)
	{
		pFile = fopen(path,"w");
		if(pFile!=NULL)
		{
			for(int i=0;i<len;i++)
			{
				bufferVenta=(Venta*)ll_get(this,i);
				venta_getNombreVenta(bufferVenta, nombreVenta);
				venta_getIdVenta(bufferVenta, &idVenta);
				venta_getIdCliente(bufferVenta, &idCliente);
				venta_getDestino(bufferVenta, &destino);
				//venta_convertirDestinoNumero(destino,destinoChar);
				//venta_convertirDestinoCadena(destinoChar, &destino);
				venta_getCantidadAfiches(bufferVenta, &cantidadAfiches);
				venta_getIsEmpty(bufferVenta, &isEmpty);
				fprintf(pFile,"%d,%s,%d,%d,%d,%d\n",idVenta,nombreVenta,cantidadAfiches,destino,idCliente,isEmpty);
			}
		}
			retorno=0;
	}
	fclose(pFile);
    return retorno;
}




/** \brief Alta de Cliente
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error
 *
 */

//PUNTO 1 AGREGAR CLIENTE
int controller_addCliente(LinkedList* listaClientes)
{
	int retorno=-1;
	Cliente* bufferCliente = cliente_new();
	char nombre[128];
	char apellido[128];
	char cuit [128];
	int id;

	if(listaClientes!=NULL)
	{
		if(getNombre("\n*>Nombre a ingresar: ","\nError",nombre,3,128)==0 &&
		getNombre("\n*>Apellido a ingresar: ","\nError",apellido,3,128)==0 &&
		getNumero("\n*>Ingrese el cuit: ","\nError",cuit, 3,10)==0)
		{
				if(cliente_buscarCuit(listaClientes,cuit)!=0)
				{
					id = cliente_generarId(listaClientes);
					cliente_setNombre(bufferCliente, nombre);
					cliente_setApellido(bufferCliente, apellido);
					cliente_setCuit(bufferCliente, cuit);
					cliente_setId(bufferCliente,id);
					ll_add(listaClientes, bufferCliente);
					printf("\n\nSu ID es: %d\n",id);
					retorno=0;
				}
				else
				{
					printf("El cuit ya existe\n");
				}
		}
	}
    return retorno;
}

/** \brief Alta de Venta
 * \param LinkedList* ListaVentas Puntero a la lista enlazada
 * \param LinkedList* ListaClientes Puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error
 *
 */
int controller_addVenta(LinkedList* listaVentas,LinkedList* listaClientes)
{
	int retorno=-1;
	Venta* bufferVenta = venta_new();
    char nombreVenta[128];
    char cantidadAfiches[128];
    char destinoChar[128];
    char idCliente[128];
	char idVenta[128];
	char isEmpty[128];
	int destino;

	if(listaVentas!=NULL && listaClientes!=NULL && ll_isEmpty(listaVentas)==0 && ll_isEmpty(listaClientes)==0)
	{
		controller_imprimirCliente(listaClientes);

		if(getNumero("\n\n*>Ingrese el ID del cliente: ","\nError",idCliente,3,128)==0 &&
				cliente_buscarPorId(listaClientes,atoi(idCliente))==0)
		{
			if(getNombre("\n*>Ingrese el nombre del afiche: \n", "\nError, vuelva a intentarlo..", nombreVenta, 3, 128)==0 &&
				getInt("\n*>Ingrese la ubicacion donde quiere colocar el afiche.\nOpcion 1: CABA\nOpcion 2: ZONA SUR\nOpcion 3: ZONA OESTE \nOPCION ELEGIDA: ", "\nError, vuelva a intentarlo..", &destino,2,3,1)==0	&&
				getNumero("\n*>Ingrese la cantidad de afiches: ", "\nError, vuelva a intentarlo..", cantidadAfiches, 3,128)==0)
			{
				sprintf(idVenta,"%d",venta_generarId(listaVentas));
				sprintf(isEmpty,"%d",FALSE);
				venta_convertirDestinoNumero(destino,destinoChar);
				bufferVenta=venta_newParametros(nombreVenta, cantidadAfiches, destinoChar, idCliente, idVenta, isEmpty);
				ll_add(listaVentas, bufferVenta);
				printf("\n\n*>El ID de la venta es: %s",idVenta);
				retorno=0;
			}
		}
	}
    return retorno;
}

//PUNTO 3 MODIFICAR VENTAS

/** \brief Modificar datos de Ventas
 * \param pArrayListEmployee LinkedList* puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error
 *
 */
int controller_modificarVenta(LinkedList* listaVentas, LinkedList* listaClientes)
{
	int retorno=-1;
	int idVenta;
	int opcion;
	Venta* aux;
	int indiceVenta;
	Cliente* clienteAux;
	int idCliente;
	int indiceCliente;
	char nombre[128];
	int destino;
	char cantidadAfiches[128];

	if(listaVentas!=NULL && ll_isEmpty(listaVentas)==0 && listaClientes!=NULL && ll_isEmpty(listaClientes)==0)
	{
		printf("\nID VEN         NOMBRE VENTA          CANTIDAD AFICHES      DESTINO            ID CLIENTE                ESTADO ");
		if(ll_map(listaVentas,venta_printVentaFiltrado)==0)
		{
			getInt("\n\n*>Ingrese el ID de la venta a modificar: ", "ERROR Vuelva a intentarlo...", &idVenta, 3, 80000000,1);
		}
		venta_buscarIndicePorId(listaVentas, idVenta, &indiceVenta);
		aux=ll_get(listaVentas, indiceVenta);
		venta_getIdCliente(aux, &idCliente);

		if(aux!=NULL)
		{
			cliente_buscarIndicePorId(listaClientes, idCliente, &indiceCliente);
			clienteAux=ll_get(listaClientes,indiceCliente);
			printf("\nID             NOMBRE                  APELLIDO                 CUIT");
			cliente_imprimirUnCliente(clienteAux);
			do
			{
				switch(venta_menu(&opcion))
				{
				case 1:
						if(getNombre("\n*>Ingrese el nombre para modificar: \n", "\nError, vuelva a intentarlo..", nombre, 3, 128)==0)
						{
							if(venta_setNombreVenta(aux, nombre)==0)
							{
								ll_set(listaVentas, indiceVenta, aux);
								break;
							}

						}
					break;

				case 2:
						if(getInt("\n*>Ingrese la ubicacion donde quiere colocar el afiche para modificar.\nOpcion 1: CABA\nOpcion 2: ZONA SUR\nOpcion 3: ZONA OESTE \nOPCION ELEGIDA: ", "\nError, vuelva a intentarlo..", &destino,2,3,1)==0)
						{
							if(venta_setDestino(aux, destino)==0)
							{
								ll_set(listaVentas, indiceVenta, aux);
								break;
							}
						}
					break;

				case 3:
						if(getNumero("\n*>Ingrese la cantidad de afiches para modificar: ", "\nError, vuelva a intentarlo..", cantidadAfiches, 3,128)==0)
						{
							if(venta_setCantidadAfiches(aux, atoi(cantidadAfiches))==0)
							{
								ll_set(listaVentas, indiceVenta, aux);
								break;
							}
						}
					break;
				}
				retorno=0;
			}while(opcion!=4);
		}
	}
	return retorno;
}



//PUNTO 3 MODIFICAR CLIENTE

/** \brief Modificar datos de Clientes
 * \param pArrayListEmployee LinkedList* puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error
 *
 */
int controller_modificarCliente(LinkedList* listaClientes)
{
	int retorno=-1;
	int opcion;
	Cliente* clienteAux;
	int idCliente;
	int indiceCliente;
	char nombre[128];
	char apellido[128];
	char cuit[128];


	if( listaClientes!=NULL && ll_isEmpty(listaClientes)==0)
	{
		printf("\nID             NOMBRE                  APELLIDO                 CUIT");
		if(ll_map(listaClientes,cliente_imprimirUnCliente)==0)
		{
			getInt("\n\n*>Ingrese el ID del cliente a modificar: ", "ERROR Vuelva a intentarlo...", &idCliente, 3, 80000000,1);
		}
		cliente_buscarIndicePorId(listaClientes, idCliente, &indiceCliente);
		clienteAux=ll_get(listaClientes, indiceCliente);

		if(clienteAux!=NULL)
		{
			printf("\nID             NOMBRE                  APELLIDO                 CUIT");
			cliente_imprimirUnCliente(clienteAux);
			do
			{
				switch(cliente_menu(&opcion))
				{
				case 1:
						if(getNombre("\n*>Ingrese el nombre para modificar: \n", "\nError, vuelva a intentarlo..", nombre, 3, 128)==0)
						{
							cliente_setNombre(clienteAux, nombre);
							break;
						}
					break;

				case 2:
						if(getNombre("\n*>Ingrese el apellido para modificar: ", "\nError, vuelva a intentarlo..", apellido,3,128)==0)
						{
							cliente_setApellido(clienteAux, apellido);
							break;
						}
					break;

				case 3:
						if(getNumero("\n*>Ingrese el cuit para modificar: ", "\nError, vuelva a intentarlo..", cuit, 3,LEN_CUIT)==0)
						{
							cliente_setCuit(clienteAux, cuit);
							break;
						}
					break;
				}
				retorno=0;
			}while(opcion!=4);
		}
	}
	return retorno;
}

/*
* \brief Cambia el isEmpty de la venta a 1 (cobrado)
 * param  LinkedList* listaVentas puntero a la lista enlazada de ventas
 * param LinkedList* ListaClientes puntero a la lista enlazada de clientes
 * \return int (0)si salio todo bien (-1)si hubo un error
*/
int controller_CobrarVenta(LinkedList* listaVentas, LinkedList* listaClientes)
{
	int retorno=-1;
	int idVenta;
	int confirmacion;
	Venta* aux;
	int indiceVenta;
	Cliente* clienteAux;
	int idCliente;
	int indiceCliente;

	if(listaVentas!=NULL && ll_isEmpty(listaVentas)==0 && listaClientes!=NULL && ll_isEmpty(listaClientes)==0)
	{
		printf("\nID VEN     NOMBRE VENTA      DESTINO     CANT AFICHES     ID CLIENTE       ESTADO ");
		ll_map(listaVentas,venta_printVentaFiltrado);
		getInt("\nIngrese el ID de la venta a cobrar: ", "ERROR Vuelva a intentarlo...", &idVenta, 3, 80000000,1);

		venta_buscarIndicePorId(listaVentas, idVenta, &indiceVenta);
		aux=ll_get(listaVentas, indiceVenta);
		venta_getIdCliente(aux, &idCliente);

		if(aux!=NULL)
		{
			cliente_buscarIndicePorId(listaClientes, idCliente, &indiceCliente);
			clienteAux=ll_get(listaClientes,indiceCliente);
			printf("\nID             NOMBRE                  APELLIDO                 CUIT");
			cliente_imprimirUnCliente(clienteAux);
			getInt("Ingrese.\n( 1 ) Si desea confirmar el cobro\n( 2 ) Si no desea confirmar el cobro\n Opcion elegida: ", "\nError Vuelva a intentarlo..", &confirmacion, 3, 2, 1);
			if(confirmacion==1)
			{
				venta_setIsEmpty(aux,1);
				retorno=0;
			}
		}
	}
	return retorno;
}
/*
* \brief Imprime lista de clientes
 * param  LinkedList* listaClientes puntero a la lista enlazada de clientes
 * \return int (0)si salio todo bien (-1)si hubo un error
*/
int controller_imprimirCliente(LinkedList* listaClientes)
{
	int retorno=-1;

	if(listaClientes!=NULL)
	{
		printf("\nID             NOMBRE                  APELLIDO                 CUIT");
		if(ll_map(listaClientes,cliente_imprimirUnCliente)==0)
		{
			printf("\n               *LISTA DE CLIENTES*\n");
		}
		retorno=0;
	}

	return retorno;
}

/*
* \brief Imprime lista de ventas
 * param  LinkedList* listaVentas puntero a la lista enlazada de ventas
 * \return int (0)si salio todo bien (-1)si hubo un error
*/
int controller_imprimirVenta(LinkedList* listaVentas)
{
	int retorno=-1;

	if(listaVentas!=NULL)
	{
		printf("\nID VEN         NOMBRE VENTA          CANTIDAD AFICHES      DESTINO            ID CLIENTE                ESTADO ");
		ll_map(listaVentas,venta_printVenta);
		retorno=0;
	}
	return retorno;
}






/*
* \brief Baja de cliente
 * \param  LinkedList* listaCliente puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error
*/
int controller_removeCliente(LinkedList* listaCliente)
{
	int retorno = -1;
	int idABuscar;
	int indiceABorrar;
	Cliente* bufferCliente;
	int len;

	if(listaCliente!=NULL)
	{
		printf("\nID             NOMBRE                  APELLIDO                 CUIT");
		ll_map(listaCliente, cliente_imprimirUnCliente);
		len=ll_len(listaCliente);
		if(len>0 && getInt("\n*>Ingrese el ID del cliente a borrar: ", "ERROR. No se encontro ese ID", &idABuscar,3, len, 0)==0)
		{
			if(cliente_buscarIndicePorId(listaCliente,idABuscar,&indiceABorrar)==0)
			{
				bufferCliente = ll_get(listaCliente, indiceABorrar);
				ll_remove(listaCliente, indiceABorrar);
				cliente_borrar(bufferCliente);
					printf("\n*>Cliente borrado con exito\n");
					retorno = 0;
			}
		}
	}

    return retorno;
}


/*
* \brief Baja de Venta
 * \param  LinkedList* listaVenta puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error
*/
int controller_removeVenta(LinkedList* listaVenta)
{
	int retorno = -1;
	int idABuscar;
	int indiceABorrar;
	Venta* bufferVenta;
	int len;

	if(listaVenta!=NULL)
	{
		printf("\nID VEN         NOMBRE VENTA          CANTIDAD AFICHES      DESTINO            ID CLIENTE                ESTADO ");
		ll_map(listaVenta, venta_printVenta);
		len=ll_len(listaVenta);
		if(len>0 && getInt("\n*>Ingrese el ID de la venta a borrar: ", "ERROR. No se encontro ese ID", &idABuscar,3, len, 0)==0)
		{
			if(venta_buscarIndicePorId(listaVenta,idABuscar,&indiceABorrar)==0)
			{
				bufferVenta = (Venta*)ll_get(listaVenta, indiceABorrar);
				ll_remove(listaVenta, indiceABorrar);
				venta_borrar(bufferVenta);
					printf("\n*>Venta borrada con exito\n");
					retorno = 0;
			}
		}
	}
    return retorno;
}

/*
* \brief Ordenar empleados
 * \param pArrayListEmployee LinkedList* puntero a la lista enlazada
 * \return int (0)si salio todo bien (-1)si hubo un error

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int orden;
	int opcion=0;
	if(pArrayListEmployee!=NULL)
	{
		employee_menuOrdenado();
		getInt("\nIngrese la opcion:", "ERROR.Numero invalido.", &opcion,3, 5, 1);
			switch(opcion)
			{
				case 1:
					if(getInt("\n*>Ingrese (1) Ascendente o (0) Descendente\n","Error",&orden,3,1,0)==0)
						{
							ll_sort(pArrayListEmployee, employee_ordenarPorNombre,orden);
						}
					break;
				case 2:
					if(getInt("\n*>Ingrese (1) Ascendente o (0) Descendente\n","Error",&orden,3,1,0)==0)
						{
							ll_sort(pArrayListEmployee, employee_ordenarPorId,orden);
						}
					break;
				case 3:
					if(getInt("\n*>Ingrese (1) Ascendente o (0) Descendente\n","Error",&orden,3,1,0)==0)
						{
							ll_sort(pArrayListEmployee, employee_ordenarPorHorasTrabajadas,orden);
						}
					break;
				case 4:
					if(getInt("\n*>Ingrese (1) Ascendente o (0) Descendente\n","Error",&orden,3,1,0)==0)
						{
							ll_sort(pArrayListEmployee, employee_ordenarPorSueldo,orden);
						}
					break;
			}
		retorno=0;
	}
    return retorno;
}

*/



/*
 * brief Menu de opciones
 * param int* puntero donde guardar el resultado obtenido
 * return int (0) si salio todo bien (-1)si hubo un error
 */
int controller_menu(int* pOpcion)
{
	int retorno=-1;

	printf("\n\n*************BIENVENIDO*************\n\n");
	printf("****************************************\n\n");
	printf("*INGRESE LA OPCION QUE DESEE\n");
	printf("*>OPCION 1: Agregar cliente.\n");
	printf("*>OPCION 2: Vender afiches.\n");
	printf("*>OPCION 3: Modificar venta.\n");
	printf("*>OPCION 4: Cobrar venta.\n");
	printf("*>OPCION 5: Generar informe de cobros.\n");
	printf("*>OPCION 6: Generar informe de deudas:.\n");
	printf("*>OPCION 7: Generar estadisticas.\n");
	printf("*>OPCION 8: Salir.\n");
	printf("********************************************");

	getInt("\ningresa la opcion: ","Error",&retorno,3,10,1);
	*pOpcion=retorno;
	return retorno;
}

/*
* \brief Guarda en forma de texto el informe de cobros
 * param  LinkedList* this puntero a la lista enlazada de ventas
 * param LinkedList* this2 puntero a la lista enlazada de clientes
 * \return int (0)si salio todo bien (-1)si hubo un error
*/
int controller_saveInformeCobros(LinkedList* this,LinkedList* this2)
{
	int retorno = -1;
	FILE* pFile;
	Cliente* bufferCliente;
	char nombre[128];
	char apellido[128];
    int id;
    char cuit[LEN_CUIT];
	int len = ll_len(this2);
	int acumuladorVentas;

	if(this!=NULL)
	{
		pFile = fopen("COBROS.txt","w");
		if(pFile!=NULL)
		{
			for(int i=0;i<len;i++)
			{
				bufferCliente=(Cliente*)ll_get(this2,i);
				cliente_getId(bufferCliente, &id);
				acumuladorVentas=ll_reduce(this, venta_filtrarPorIsEmpty,id);
				if(acumuladorVentas>0)
				{
					cliente_getNombre(bufferCliente, nombre);
					cliente_getApellido(bufferCliente, apellido);
					cliente_getCuit(bufferCliente,cuit);
					fprintf(pFile,"%d,%s,%s,%s,%d\n",id,nombre,apellido,cuit,acumuladorVentas);
				}
			}
		}
			retorno=0;
	}
	fclose(pFile);
    return retorno;
}

/*
* \brief Guarda en forma de texto el informe de deudas
 * param  LinkedList* this puntero a la lista enlazada de ventas
 * param LinkedList* this2 puntero a la lista enlazada de clientes
 * \return int (0)si salio todo bien (-1)si hubo un error
*/
int controller_saveInformeDeudas(LinkedList* this,LinkedList* this2)
{
	int retorno = -1;
	FILE* pFile;
	Cliente* bufferCliente;
	char nombre[128];
	char apellido[128];
    int id;
    char cuit[LEN_CUIT];
	int len = ll_len(this2);
	int acumuladorVentas;

	if(this!=NULL)
	{
		pFile = fopen("DEUDAS.txt","w");
		if(pFile!=NULL)
		{
			for(int i=0;i<len;i++)
			{
				bufferCliente=(Cliente*)ll_get(this2,i);
				cliente_getId(bufferCliente, &id);
				acumuladorVentas=ll_reduce(this, venta_filtrarPorIsEmpty,id);
				if(acumuladorVentas==0)
				{
					cliente_getNombre(bufferCliente, nombre);
					cliente_getApellido(bufferCliente, apellido);
					cliente_getCuit(bufferCliente,cuit);
					fprintf(pFile,"%d,%s,%s,%s,%d\n",id,nombre,apellido,cuit,acumuladorVentas);
				}
			}
		}
			retorno=0;
	}
	fclose(pFile);
    return retorno;
}
