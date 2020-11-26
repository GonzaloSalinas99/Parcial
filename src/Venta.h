#ifndef venta_H_
#define venta_H_
#define TRUE 1
#define FALSE 0
#include "LinkedList.h"

typedef struct
{
    char nombreVenta[128];
    int cantidadAfiches;
    int destino;
    int idCliente;
	int idVenta;
	int isEmpty;

}Venta;

Venta* venta_new(void);
Venta* venta_newParametros(char* nombreVenta,char* cantidadAfiches,char* destino,char* idCliente,char* idVenta,char*isEmpty);
void venta_borrar(Venta* this);

int venta_setIdVenta(Venta* this,int idVenta);
int venta_getIdVenta(Venta* this,int* idVenta);

int venta_setIdCliente(Venta* this,int idCliente);
int venta_getIdCliente(Venta* this,int* idCliente);

int venta_setNombreVenta(Venta* this,char* nombreVenta);
int venta_getNombreVenta(Venta* this,char* nombreVenta);

int venta_getDestino(Venta* this,int* destino);
int venta_setDestino(Venta* this,int destino);

int venta_setCantidadAfiches(Venta* this,int cantidadAfiches);
int venta_getCantidadAfiches(Venta* this,int* cantidadAfiches);

int venta_setIsEmpty(Venta* this,int isEmpty);
int venta_getIsEmpty(Venta* this,int* isEmpty);

int venta_generarId(LinkedList* this);;

int venta_printVenta(void* pElement);
int venta_printVentaFiltrado(void* pElement);

int venta_buscarIndicePorId(LinkedList* this, int idABuscar,int* index);

int venta_convertirDestinoNumero(int destino,char* destinoChar);

int venta_menu(int* pOpcion);


int venta_filtrarPorIsEmpty(void* pElement,int idCliente);
int venta_acumularAfiches(void* pElement,int idCliente);
int venta_encontrarVentaPorIdCliente(LinkedList* listaVentas,int idCliente,int* indice);

#endif /* venta_H_ */
