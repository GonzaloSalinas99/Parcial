#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../inc/LinkedList.h"
#include "LinkedList.h"
#include "utn.h"
#include "Venta.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= (LinkedList*)malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
    	this->size=0;
    	this->pFirstNode=NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux=-1;
    if(this!=NULL)
    {
    	returnAux =this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
	Node* nodeAux = NULL;
	int len = ll_len(this);

	if(this!=NULL && nodeIndex>=0 && nodeIndex<len)
	{
		nodeAux=this->pFirstNode;
		for(i=0;i<nodeIndex;i++)
		{
			nodeAux=nodeAux->pNextNode;
		}
	}
    return nodeAux;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* newNode;
    Node* prevNode;
    int len=ll_len(this);

    if(this!=NULL && nodeIndex<=len && nodeIndex>=0)
    {
    	newNode=(Node*)malloc(sizeof(Node));
    	if(newNode!=NULL)
    	{
    		newNode->pElement=pElement;
    		newNode->pNextNode=NULL;

    		if(nodeIndex==0)
    		{
    			newNode->pNextNode=this->pFirstNode;
    			this->pFirstNode=newNode;
    		}
    		else if(nodeIndex==this->size)
    		{
    			prevNode=getNode(this,nodeIndex -1);
    			newNode->pNextNode=NULL;
    			prevNode->pNextNode=newNode;
    		}
    		else
    		{
    			prevNode=getNode(this,nodeIndex -1);
    			newNode->pNextNode=prevNode->pNextNode;
    			prevNode->pNextNode=newNode;
    		}

        	returnAux=0;
        	this->size++;
    	}
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);

    if(this!=NULL)
    {
    	addNode(this, len, pElement);
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    int len=ll_len(this);
    Node* nodeAux;
    if(this!=NULL && index>=0 && index<=len)
    {
    	nodeAux=getNode(this, index);
    	if(nodeAux!=NULL)
    	{
    		returnAux=nodeAux->pElement;
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);
    Node* nodeAux;
    if(this!=NULL && index>=0 && index<=len)
    {
    	nodeAux=getNode(this,index);
    	if(nodeAux!=NULL)
    	{
    		nodeAux->pElement=pElement;
			returnAux=0;
    	}
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int len=ll_len(this);
    Node* nodeAux=NULL;
    Node* nodePrev=NULL;

    if(this!=NULL && index>=0 && index<len)
    {
    	nodeAux=getNode(this,index);
    	if(nodeAux != NULL)
    	{
    		if(index==0)
    		{
    			this->pFirstNode = nodeAux->pNextNode;
    			//this->size--;
    			free(nodeAux);
    			returnAux=0;
    		}
    		else
    		{
    			nodePrev=getNode(this, index-1);
    			if(nodePrev!=NULL)
    			{
					nodePrev->pNextNode=nodeAux->pNextNode;
					//this->size--;
					free(nodeAux);
					returnAux=0;
    			}
    		}
    		this->size--;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
    int len=ll_len(this);
    if(this!=NULL)
    {
    	for(i=0;i<len;i++)
    	{
    		ll_remove(this,i);
    		returnAux=0;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    int i;
    int len=ll_len(this);

    if(this!=NULL)
    {
    	for(i=0;i<len;i++)
    	{
    		ll_remove(this,i);
    		returnAux=0;
    	}
    }
    free(this);
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);
    int i;
    Node* nodeAux;
    if(this!=NULL)
    {
    	for(i=0;i<len;i++)
    	{
    		nodeAux=getNode(this,i);
    		if(nodeAux!=NULL && nodeAux->pElement==pElement)
    		{
    			returnAux = i;
				break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int len=ll_len(this);

    if(this!=NULL)
    {
    	returnAux=1;
    	if(len>0)
    	{
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);

    if(this!=NULL && index>=0 && index<=len)
    {
    	if(addNode(this, index, pElement)==0)
    	{
    		returnAux=0;
    	}
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    int len=ll_len(this);

    if(this!=NULL && index>=0 && index<=len)
    {
    	returnAux=ll_get(this, index);
    	if(ll_remove(this,index)==-1)
    	{
    		returnAux=NULL;
    	}
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);
    int i;
    Node* nodeAux=NULL;

    if(this!=NULL)
    {
    	returnAux=0;
    	for(i=0;i<len;i++)
    	{
    		nodeAux=getNode(this,i);
    		if(nodeAux!=NULL && nodeAux->pElement==pElement)
    		{
    			returnAux=1;
    		}
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int len=ll_len(this2);
    Node* nodeAux=NULL;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;
        for(int i=0; i<len; i++)
        {
            nodeAux = ll_get(this2, i);
            if(ll_contains(this, nodeAux)==0)
            {
                returnAux = 0;
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int len=ll_len(this);
    int i;

    if(this!=NULL && from>=0 && from<=len && to>=0 && to<=len && from<=to)
    {
    	cloneArray=ll_newLinkedList();
    	if(cloneArray!=NULL)
    	{
			for(i=0;i<to;i++)
			{
					ll_add(cloneArray, ll_get(this,i));
			}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int len=ll_len(this);
    if(this!=NULL)
    {
    	cloneArray = ll_subList(this, 0, len);
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* pElementA;
    void* pElementB;
    int len=ll_len(this);
    int flagSwap=0;

    if(this!=NULL && pFunc!=NULL && (order==1 || order==0))
    {
    	printf("*>PROCESANDO LOS DATOS...");
    	do
    	{
    		flagSwap=1;
			for(int i=0;i<len-1;i++)
			{
				pElementA=ll_get(this, i);
				pElementB=ll_get(this, i+1);

				if(pElementA!=NULL && pElementB!=NULL)
				{
					if( (order==1 && pFunc(pElementA,pElementB)>0) ||
						(order==0 && pFunc(pElementA, pElementB)<0))
					{
						flagSwap=0;
						ll_set(this, i, pElementB);
						ll_set(this, i+1, pElementA);
					}
				}
			}
    	}while(flagSwap==0);
    	returnAux=0;
    }
    return returnAux;
}


int ll_map(LinkedList* this, int (*pFunc)(void* pElement))
{
	int returnAux=-1;
	void* pElement;
	int len=ll_len(this);

	if(this!=NULL && pFunc!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			pElement=ll_get(this,i);
			if(pFunc(pElement)==0)
			{
				returnAux=0;
			}
		}
	}
	return returnAux;
}

LinkedList* ll_filter(LinkedList* this, int(pFunc)(void*,char*),char* texto)
{

	int len=ll_len(this);
	void* pElementAux;
	LinkedList* listaAux =NULL;


	if(this!=NULL && pFunc!=NULL)
	{
		listaAux=ll_newLinkedList();
		for(int i=0;i<len;i++)
		{
			pElementAux=ll_get(this,i);
			if(pElementAux!=NULL && pFunc(pElementAux,texto)==0)
			{
				ll_add(listaAux, pElementAux);
			}
		}
	}
	return listaAux;
}

int ll_reduce(LinkedList* this, int (pFunc)(void*,int),int pResultado)
{
	//int output=-1;
	int acumulador=0;
	void* element;
	if(this!=NULL && pFunc!=NULL)
	{
		for(int i = 0; i< ll_len(this);i++)
		{
			element = ll_get(this, i);
			if(element!=NULL)
			{
				acumulador += pFunc(element,pResultado);
			}
		}
	}
	return acumulador;
}
