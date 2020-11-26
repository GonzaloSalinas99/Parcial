#ifndef cliente_H_INCLUDED
#define cliente_H_INCLUDED

#define TRUE 1
#define FALSE 0
#include "LinkedList.h"
#define LEN_CUIT 11

typedef struct
{
	char nombre[128];
	char apellido[128];
    int id;
    char cuit[LEN_CUIT];
}Cliente;

Cliente* cliente_new();
Cliente* cliente_newParametros(char* nombre,char* apellido,char* id,char* cuit);
void cliente_borrar(Cliente* this);

int cliente_setId(Cliente* this,int id);
int cliente_getId(Cliente* this,int* id);

int cliente_setNombre(Cliente* this,char* nombre);
int cliente_getNombre(Cliente* this,char* nombre);

int cliente_setApellido(Cliente* this,char* apellido);
int cliente_getApellido(Cliente* this,char* apellido);

int cliente_setCuit(Cliente* this,char* cuit);
int cliente_getCuit(Cliente* this,char* cuit);

int cliente_imprimirUnCliente(void* pElement);
int cliente_generarId(LinkedList* this);
int cliente_buscarIndicePorId(LinkedList* this, int idABuscar,int* index);
int cliente_ordenarPorNombre (void* thisA, void* thisB);

int cliente_buscarPorId(LinkedList* this,int id);
int cliente_estaRepetido(void* this,void* cuit);
int cliente_verificarCuit(LinkedList* this,void* pElement);
int cliente_buscarCuit(LinkedList* this,void*pElement);

int cliente_menu(int* pOpcion);

#endif // cliente_H_INCLUDED
