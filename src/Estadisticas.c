#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "Venta.h"
#include "utn.h"
#include "parser.h"
#include "controller.h"
#include <string.h>


int estadistica_ClienteMasAfiches(LinkedList* listaVentas,LinkedList* listaClientes)
{
	int retorno=-1;

	Cliente* clienteAux=NULL;
	int lenClientes=ll_len(listaClientes);
	Cliente* clienteMaximoAfiches;
	Cliente* clienteMinimoAfiches;
	int idCliente;
	int cantidadAfiches;
	int banderaMaximo=0;
	int banderaMinimo=0;

	int afichesMaximo=0;
	int afichesMinimo=0;

	Venta* ventaMaximoAfiches;
	Venta* aux;
	int idVenta;
	char cuitCliente[128];
	int indiceVenta;


	if(listaVentas!=NULL && ll_isEmpty(listaVentas)==0 && listaClientes!=NULL && ll_isEmpty(listaClientes)==0)
	{

		for(int i=0;i<lenClientes;i++)
		{
			clienteAux=(Cliente*)ll_get(listaClientes,i);
			cliente_getId(clienteAux, &idCliente);

			venta_encontrarVentaPorIdCliente(listaVentas, idCliente,&indiceVenta);
			aux=ll_get(listaVentas, indiceVenta);

			cantidadAfiches=ll_reduce(listaVentas, venta_acumularAfiches,idCliente);

			if(cantidadAfiches > 0)
			{
				if(banderaMaximo==0 || cantidadAfiches>afichesMaximo)
				{
					banderaMaximo=1;
					afichesMaximo=cantidadAfiches;
					clienteMaximoAfiches=clienteAux;
					ventaMaximoAfiches=aux;
				}
				if(banderaMinimo==0 || cantidadAfiches<afichesMinimo)
				{
					banderaMinimo=1;
					afichesMinimo=cantidadAfiches;
					clienteMinimoAfiches=clienteAux;
				}
			}
		}
	retorno=0;
	}

	printf("\n****** CLIENTE CON MAS AFICHES COMPRADOS********\n");
	printf("\nID             NOMBRE                  APELLIDO                 CUIT");
	cliente_imprimirUnCliente(clienteMaximoAfiches);
	printf("    AFICHES: %d",afichesMaximo);


	printf("\n\n\n****** CLIENTE CON MENOS AFICHES COMPRADOS********\n");
	printf("\nID             NOMBRE                  APELLIDO                 CUIT");
	cliente_imprimirUnCliente(clienteMinimoAfiches);
	printf("    AFICHES: %d",afichesMinimo);

	cliente_getCuit(clienteMaximoAfiches, cuitCliente);
	venta_getIdVenta(ventaMaximoAfiches, &idVenta);
	printf("\n\nLa venta con el ID: %d que tiene mas afiches vendidos es del cliente con el cuit: %s y tiene %d afiches vendidos.\n\n",idVenta,cuitCliente,afichesMaximo);


	return retorno;
}
