#ifndef PARSER_H_
#define PARSER_H_
#include "LinkedList.h"

int parser_EnvioFromTextCliente(FILE* pFile , LinkedList* this);
int parser_EnvioFromTextVenta(FILE* pFile , LinkedList* this);

#endif /* PARSER_H_ */
