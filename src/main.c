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
#include "informe.h"

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

	cliente_hardcodeo(aCliente,0,"Gonzalo","Salinas",42038608,100);
	cliente_hardcodeo(aCliente,1,"Facundo","Salinas",424588608,222);
	cliente_hardcodeo(aCliente,2,"Franco","Alvarez",41587568,315);
	cliente_hardcodeo(aCliente,3,"Lucia","Pereyra",15889148,109);
	cliente_hardcodeo(aCliente,4,"Elias","Troncoso",4258746,503);

	aviso_hardcodeo( aAviso,0,"LALAAA",3,100,1);
	aviso_hardcodeo( aAviso,1,"GONZAAA",3,222,2);
	aviso_hardcodeo( aAviso,2,"LALAAA",3,100,3);
	aviso_hardcodeo( aAviso,3,"LALAAA",2,100,4);
	aviso_hardcodeo( aAviso,4,"LALAAA",2,503,5);

	do
	{
		switch(cliente_menu(&opcion))
		{
			case 1:
					if(cliente_alta(aCliente,QTY_CLIENTES)==0)
					{
						printf("\nALTA EXITOSA");
					}
				break;

			case 2:
					if(cliente_modificar(aCliente,QTY_CLIENTES)==0)
					{
						printf("\nMODIFICACION EXITOSA");
					}
				break;

			case 3:
					if(aviso_baja(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("\nBAJA EXITOSA");
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
						printf("\nSe modifico con exito");
					}
				break;
			case 6:
					if(aviso_estadoPublicacionActiva(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("\nSe modifico con exito");
					}
				break;
			case 7:
					if(aviso_imprimirClientesYAvisos(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES)==0)
					{
						printf("\n\n*Estos son los clientes con su cantidad de avisos activos*\n");
					}
				break;
			case 8:

					switch(informe_subMenu(&subMenu))
					{
						case 1:
							informe_imprimirClienteMayorCantidadAvisos(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES);
							break;
						case 2:
							informe_cantidadAvisosPausados(aAviso,QTY_AVISOS);
							break;
						case 3:
							informe_rubroMayorCantidadAvisos(aAviso,QTY_AVISOS);
							break;
						case 4:
							informe_imprimirClienteMayorCantidadAvisosPausados(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES);
							break;
						case 5:
							informe_imprimirClienteMayorCantidadAvisosActivos(aAviso,QTY_AVISOS,aCliente,QTY_CLIENTES);
							break;

					}
				break;
		}


	}while(opcion!=9);

	return EXIT_SUCCESS;
}
