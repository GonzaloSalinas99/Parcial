int controller_loadFromTextCliente(char* path , LinkedList* this);
int controller_loadFromTextVenta(char* path , LinkedList* this);

int controller_saveAsTextCliente(char* path , LinkedList* this);
int controller_saveAsTextVentas(char* path , LinkedList* this);

int controller_saveInformeDeudas(LinkedList* this,LinkedList* this2);
int controller_saveInformeCobros(LinkedList* this,LinkedList* this2);

int controller_addCliente(LinkedList* listaClientes);
int controller_addVenta(LinkedList* listaVentas,LinkedList* listaClientes);

int controller_modificarVenta(LinkedList* listaVentas, LinkedList* listaClientes);
int controller_modificarCliente(LinkedList* listaClientes);

int controller_CobrarVenta(LinkedList* listaVentas, LinkedList* listaClientes);

int controller_imprimirCliente(LinkedList* listaClientes);
int controller_imprimirVenta(LinkedList* listaVentas);

int controller_removeCliente(LinkedList* listaCliente);
int controller_removeVenta(LinkedList* listaVenta);

int controller_sortEmployee(LinkedList* pArrayListEmployee);


int controller_menu(int* opcion);






