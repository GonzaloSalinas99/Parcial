/*
 ============================================================================
 Name        : PARCIAL.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aviso.h"
#include "utn.h"
#include "cliente.h"

#define QTY_CLIENTES 100
#define QTY_AVISOS 1000

int main(void) {

	setbuf(stdout,NULL);
	int opcion;
	int subMenu;
	Cliente aCliente[QTY_CLIENTES];
	Aviso aAviso[QTY_AVISOS];


	cliente_init(aCliente,QTY_CLIENTES);
	aviso_init(aAviso,QTY_AVISOS);
	cliente_hardcodeo(aCliente,0,"Gonzalo","Salinas",42038608,1);
	cliente_hardcodeo(aCliente,1,"Facundo","Salinas",424588608,2);
	cliente_hardcodeo(aCliente,2,"Franco","Alvarez",41587568,3);
	cliente_hardcodeo(aCliente,3,"Lucia","Pereyra",15889148,4);
	cliente_hardcodeo(aCliente,4,"Elias","Troncoso",4258746,5);
	do
	{
		switch(cliente_menu(&opcion))
		{
			case 1:
					if(cliente_alta(aCliente,QTY_CLIENTES)==0)
					{
						printf("ALTA EXITOSA");
					}
				break;

			case 2:
					if(cliente_modificar(aCliente,QTY_CLIENTES)==0)
					{
						printf("MODIFICACION EXITOSA");
					}
				break;

			case 3:
					if(aviso_baja(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("BAJA EXITOSA");
					}
				break;
			case 4:
					if(aviso_alta(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("\nALTA DE AVISO EXITOSA");
					}
				break;
			case 5:
					if(aviso_estadoPublicacionPausa(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("Se modifico con exito");
					}
				break;
			case 6:
					if(aviso_estadoPublicacionActiva(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("Se modifico con exito");
					}
				break;
			case 7:
					if(aviso_imprimirClientesYAvisos(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("Estos son los clientes con su cantidad de avisos");
					}
				break;
			case 8:
					informe_subMenu(subMenu);
					switch(subMenu)
					{
						case 1:
							informe_imprimirClienteMasCantidadAvisos(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES);
							break;
						case 2:
							informe_cantidadAvisosPausados(aAviso,QTY_AVISOS);
							break;
					}
				break;
		}


	}while(opcion!=9);

	return EXIT_SUCCESS;
}
