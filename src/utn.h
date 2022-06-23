

#ifndef UTN_H_
#define UTN_H_

int myGets(char* cadena, int longitud);
int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_initArrayInt(int* pArray, int longitud, int valorInicial);
int utn_getString(char* pCadena, int longitud, char* mensaje, char* mensajeError, int reintentos);

#endif /* UTN_H_ */
