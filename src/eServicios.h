#ifndef ESERVICIOS_H_
#define ESERVICIOS_H_

#define DESCRIPCION_LEN 100

typedef struct
{
	int id;
	char descripcion[DESCRIPCION_LEN];
	int tipo;
	float precioUnitario;
	int cantidad;
	float totalServicio;
}eServicio;

eServicio* eServicio_new();
eServicio* eServicio_newParametros(char* idStr,char* descripcionStr,char* tipoStr,char* precioUnitarioStr,char* cantidadStr, char* totalServicioStr);
void eServicio_delete(eServicio* this);

int eServicio_setId(eServicio* this,int id);
int eServicio_getId(eServicio* this,int* id);
int eServicio_setIdTxt(eServicio* this, char* id);
int eServicio_getIdTxt(eServicio* this, char* id);

int eServicio_setDescripcion(eServicio* this,char* descripcion);
int eServicio_getDescripcion(eServicio* this,char* descripcion);

int eServicio_setTipo(eServicio* this,int tipo);
int eServicio_getTipo(eServicio* this,int* tipo);
int eServicio_setTipoTxt(eServicio* this, char* tipo);
int eServicio_getTipoTxt(eServicio* this, char* tipo);

int eServicio_setPrecio(eServicio* this,float precio);
int eServicio_getPrecio(eServicio* this,float* precio);
int eServicio_setPrecioTxt(eServicio* this, char* precio);
int eServicio_getPrecioTxt(eServicio* this, char* precio);

int eServicio_setCantidad(eServicio* this,int cantidad);
int eServicio_getCantidad(eServicio* this,int* cantidad);
int eServicio_setCantidadTxt(eServicio* this, char* cantidad);
int eServicio_getCantidadTxt(eServicio* this, char* cantidad);

int eServicio_setTotal(eServicio* this,float total);
int eServicio_getTotal(eServicio* this,float* total);
int eServicio_setTotalTxt(eServicio* this, char* total);
int eServicio_getTotalTxt(eServicio* this, char* total);

int eServicio_imprimir(eServicio* this);
void eServicio_CalcularTotal(void* this);
int eServicio_filtrarMinorista(void* this);
int eServicio_filtrarMayorista(void* this);
int eServicio_filtrarExportar(void* this);
int eServicio_sortByDescripcion(void* servicio1, void* servicio2);

#endif /* ESERVICIOS_H_ */
