#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int getInt (int* pResultado);
static int getFloat (float* pResultado);
static int esNumerica(char* cadena, int limite);
static int esFlotante(char* cadena, int limite);


/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un maximo de
 * 		  'longitud -1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de lacadena
 * \return Retorna 0 (Exito) si se obtiene una cadena y -1 (error) si no
 */
int myGets(char* cadena, int longitud){

	int retorno = -1;
	char bufferString[4096];

	if(cadena != NULL && longitud >0){
		fflush(stdin);
		if(fgets(bufferString, sizeof(bufferString), stdin) != NULL){
			if(bufferString[strnlen(bufferString, sizeof(bufferString))-1] == '\n'){
				bufferString[strnlen(bufferString, sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString, sizeof(bufferString)) <= longitud){
				strncpy(cadena, bufferString, longitud);
				retorno = 0;
			}

		}
	}

	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es entera
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (exito) se se obtiene un numero entero y -1 (Error) si no
 */
static int getInt(int* pResultado){

	int retorno = -1;
	char bufferString[50];

	if(pResultado != NULL){
		if(myGets(bufferString, sizeof(bufferString)) == 0 && esNumerica(bufferString, sizeof(bufferString))){
			retorno = 0;
			*pResultado = atoi(bufferString);
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es flotante
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (exito) se se obtiene un numero flotante y -1 (Error) si no
 */
static int getFloat(float* pResultado){

	int retorno = -1;
	char bufferString[64];

	if(pResultado != NULL){
		if(myGets(bufferString, sizeof(bufferString)) == 0 && esFlotante(bufferString, sizeof(bufferString))){
			*pResultado = atof(bufferString);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \param limite Limite de la cadena
 * \return Retonar 1 (verdadero) si la cadena es numera y 0 (falso) si no lo es y -1 en caso de error
 */
static int esNumerica(char* cadena, int limite){

	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0){
		retorno = 1;
		for(i=0; i<limite && cadena[i] != '\0'; i++){
			if(i==0 &&  (cadena[i] == '+' || cadena[i] == '-')){
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0'){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es flotante
 * \param cadena Cadena de caracteres a ser analizada
 * \param limite Limite de la cadena
 * \return Retonar 1 (verdadero) si la cadena es flotante y 0 (falso) si no lo es y -1 en caso de error
 */
static int esFlotante(char* cadena, int limite){

	int retorno = -1;
	int i;
	int contadorPuntos =0;

	if(cadena != NULL && limite > 0){
		retorno = 1;
		for(i=0; i<limite && cadena[i] != '\0'; i++){
			if(i==0 &&  (cadena[i] == '+' || cadena[i] == '-')){
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0'){
				if(cadena[i] == '.' && contadorPuntos == 0){
					contadorPuntos++;
				}else{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita un caracter al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje que muertra
 * \param mensajeError Es el mensaje de error que muestra
 * \param minimo Es el caracter minimo a ser aceptado
 * \param maximo Es el caracter maximo a ser aceptado
 * \param reintentos Numero de reintentos permitidos
 * \return Retorna 0 si se obtuvo el caracter y -1 si no
 */
int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos){

	int retorno = -1;
	char buffer;

	while(reintentos >= 0){
			reintentos --;
			printf("%s", mensaje);
			if(myGets(&buffer, sizeof(buffer)) == 0 && buffer >= minimo && buffer <= maximo){
				*pResultado = buffer;
				retorno = 0;
				break;
			}
			printf("%s", mensajeError);
		}



	return retorno;
}

/**
 * \brief Solicita un numero al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje que muertra
 * \param mensajeError Es el mensaje de error que muestra
 * \param minimo Es el numero minimo a ser aceptado
 * \param maximo Es el numero maximo a ser aceptado
 * \param reintentos Numero de reintentos permitidos
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){

	int retorno = -1;
	int buffer;
	while(reintentos >= 0){
		reintentos --;
		printf("%s", mensaje);
		if(getInt(&buffer) == 0 && buffer >= minimo && buffer <= maximo){
			*pResultado = buffer;
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

/**
 * \brief Solicita un numero al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje que muertra
 * \param mensajeError Es el mensaje de error que muestra
 * \param minimo Es el numero minimo a ser aceptado
 * \param maximo Es el numero maximo a ser aceptado
 * \param reintentos Numero de reintentos permitidos
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos){

	int retorno = -1;
	float buffer;
	while(reintentos >= 0){
		reintentos --;
		printf("%s", mensaje);
		if(getFloat(&buffer) == 0 && buffer >= minimo && buffer <= maximo){
			*pResultado = buffer;
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}
/**
 * \brief Solicita un string, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje que muertra
 * \param mensajeError Es el mensaje de error que muestra
 * \param reintentos Numero de reintentos permitidos
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int utn_getString(char* pCadena, int longitud, char* mensaje, char* mensajeError, int reintentos){

	int retorno = -1;
	char bufferString[4096];

	while(reintentos >= 0){
		reintentos --;
		printf("%s", mensaje);
		if(myGets(bufferString, sizeof(bufferString)) == 0){
			strncpy(pCadena, bufferString, longitud);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

/**
 * \brief Inicializa un array
 * \param pArray Puntero al espacio de memoria del array
 * \param longitud Es el largo del array
 * \param valorInicial Es el valor con el cual se va a inicializar el array
 * \return Retorna 0 en caso de exito y -1 en caso de error
 */

int utn_initArrayInt(int* pArray, int longitud, int valorInicial){
	int retorno = -1;
	int i;

	if(pArray != NULL && longitud > 0 ){
		retorno = 0;
		for(i = 0; i< longitud; i++){
			pArray[i]= valorInicial;
		}
	}

	return retorno;
}


