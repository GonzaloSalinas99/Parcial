/*
 ============================================================================
 Name        : ZZPARCIAL.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "LinkedList.h"
#include "Controller.h"
#include "Estadisticas.h"

int main(void) {

	setbuf(stdout,NULL);
	int opcionMenu;

	LinkedList* listaClientes=ll_newLinkedList();
	LinkedList* listaVentas=ll_newLinkedList();
	controller_loadFromTextCliente("CLIENTES.txt", listaClientes);
	controller_loadFromTextVenta("VENTAS.txt", listaVentas);

	if(listaClientes!=NULL && listaVentas!=NULL)
	{
		do
		{
			switch(controller_menu(&opcionMenu))
			{
				case 1:
						if(controller_addCliente(listaClientes)==0 && controller_saveAsTextCliente("CLIENTES.txt", listaClientes)==0)
						{
							printf("\n*>Cliente cargado con exito.");
						}
					break;
				case 2:
						if(controller_addVenta(listaVentas, listaClientes)==0 && controller_saveAsTextVentas("VENTAS.txt", listaVentas)==0)
						{
							printf("\n*>Venta cargada con exito");
						}
					break;
				case 3:
						if(controller_modificarVenta(listaVentas, listaClientes)==0 && controller_saveAsTextVentas("VENTAS.txt", listaVentas)==0)
						{
							printf("\n*>Venta modificada con exito.");
						}
					break;
				case 4:
						if(controller_CobrarVenta(listaVentas, listaClientes)==0 && controller_saveAsTextVentas("VENTAS.txt", listaVentas)==0)
						{
							printf("\n*>Venta cobrada con exito.");
						}
					break;
				case 5:
						if(controller_saveInformeCobros(listaVentas,listaClientes)==0)
						{
							printf("\n*>Informe de COBROS generado correctamente");
						}
					break;
				case 6:
						if(controller_saveInformeDeudas(listaVentas, listaClientes)==0)
						{
							printf("\n*>Informe de DEDUDAS generado correctamente");
						}
					break;
				case 7:
							estadistica_ClienteMasAfiches(listaVentas, listaClientes);
					break;
			}
		}while(opcionMenu!=8);

	}
}
