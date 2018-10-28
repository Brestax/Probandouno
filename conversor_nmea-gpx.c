#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAXIMO_CADENA_SECUENCIA 100
#define MAXIMO_CADENA_NAME 100
#define MAXIMO_CADENA_HORAS_SEPARADAS 3
#define MAXIMO_CADENA_MINUTOS 3
#define MAXIMO_CADENA_SEGUNDOS 50
#define MAXIMO_CADENA_YEAR_LOCAL 5
#define MAXIMO_CADENA_MES_LOCAL 6
#define MAXIMO_CADENA_DIA_LOCAL 3
#define MAXIMO_CADENA_HORA_LOCAL 3
#define MAXIMO_CADENA_MINUTO_LOCAL 3
#define MAXIMO_CADENA_SEGUNDO_LOCAL 3
#define LONGITUD_CADENA_YEAR 4
#define LONGITUD_CADENA_MES 2
#define LONGITUD_CADENA_DIA 2
#define MAXIMO_NUMERO_ENTERO_DOS_CIFRAS 99
#define MAXIMO_MES 12
#define MAXIMO_DIA 31
#define MAXIMO_HORAS 24
#define MAXIMO_MINUTOS_HORARIOS 60
#define MAXIMO_SEGUNDOS_HORARIOS 60
#define MAXIMO_CADENA_GRADOS 3
#define MINIMO_DIGITOS_DE_LONGITUD_PARTE_ENTERA 4
#define MAXIMO_DIGITOS_DE_LONGITUD_PARTE_ENTERA 5
#define MAXIMO_GRADOS_LATITUD 90
#define MAXIMO_GRADOS_LONGITUD 180
#define MAXIMO_MINUTOS_GEOGRAFICOS 60
#define MAXIMO_SEGUNDOS_GEOGRAFICOS 60
#define MAXIMA_CALIDAD_FIX 8
#define MAXIMA_CANTIDAD_SATELITES 12
#define MINIMO_DIGITOS_SATELITES 1
#define MAXIMO_DIGITOS_SATELITES 2
#define COMA_LATITUD 2
#define COMA_NORTE_SUR 3
#define COMA_LONGITUD 4
#define COMA_ESTE_OESTE 5
#define COMA_CALIDAD_FIX 6
#define COMA_CANTIDAD_SATELITES 7
#define COMA_HDOP 8
#define COMA_ELEVACION 9
#define COMA_SEPARACION_GEOIDE 11
#define MSJ_HELP "Los comandos de este programa son:\n    -h, --help     Muestra una ayuda\n    -n, --name     Indica el metadato nombre (name)\n    -f, --format   Indica la fecha, debe ser una secuencia de 8 digitos (yyyymmdd)\n    -Y, --year     Indica el anio, debe ser una secuencia de 4 digitos\n    -m, --month    Indica el mes\n    -d, --day      Indica el dia\n\nEl programa debe ser ejecutado con al menos un comando. \n\nPara empezar a leer una secuencia de datos, se debe ejecutar el comando -n/--name\n\nEn caso de no especificar la fecha, se tomara la del sistema.\n\nSi se quiere especificar la fecha utilizando -Y/--year, -m/--month, -d/--day, se deben escribir los tres comandos.\n\nNo es necesario escribir los comandos en un orden determinado\n\n\n"
#define MSJ_HELP_SE_ESCRIBIO_AYUDA_MUCHAS_VECES "Se ha ingresado el comando ayuda varias veces, sera mostrada solo una vez:"
#define MSJ_T "T"
#define MSJ_Z "Z"
#define GPX_ENCABEZADO "\n<? xml version =\"1.0 \" encoding =\"UTF -8\"?>\n"
#define GPX_OPEN_ELEMENTO "\n<gpx version=\"1.1\" creator=\"UADE.c\" xmlns=\"http://www.topografix.com/GPX/1/1\">"
#define GPX_ELEMENTO_OPEN_METADATA "\n\t<metadata>"
#define GPX_ELEMENTO_METADATA_OPEN_NAME "\n\t\t<name>"
#define GPX_ELEMENTO_METADATA_CLOSE_NAME "</name>"
#define GPX_ELEMENTO_METADATA_OPEN_TIME "\n\t\t<time>"
#define GPX_ELEMENTO_METADATA_CLOSE_TIME "</time>"
#define GPX_ELEMENTO_CLOSE_METADATA "\n\t</metadata>"
#define GPX_ELEMENTO_OPEN_TRK "\n\t<trk>"
#define GPX_ELEMENTO_TRK_OPEN_TRKSEG "\n\t\t<trkseg>"
#define GPX_ELEMENTO_TRK_TRKSEG_OPEN_TRKPT "\n\t\t\t<trkpt "
#define GPX_LATITUD "lat=\""
#define GPX_LONGITUD "\" lon=\""
#define GPX_CLOSE_LONGITUD "\">"
#define GPX_OPEN_ELEVACION "\n\t\t\t\t<ele>"
#define GPX_CLOSE_ELEVACION "</ele>"
#define GPX_OPEN_TIME "\n\t\t\t\t<time>"
#define GPX_CLOSE_TIME "</time>"
#define GPX_ELEMENTO_TRK_TRKSEG_CLOSE_TRKPT "\n\t\t\t</trkpt>"
#define GPX_ELEMENTO_TRK_CLOSE_TRKSEG "\n\t\t</trkseg>"
#define GPX_ELEMENTO_CLOSE_TRK "\n\t</trk>"
#define GPX_CLOSE_ELEMENTO "\n</gpx>"
#define MSJ_ERROR "Error: "
#define MSJ_ERROR_SIN_COMANDOS "Se debe ingresar al menos un comando. Para obtener ayuda, ingrese -h o --help"
#define MSJ_ERROR_SIN_COMANDOS_VALIDOS "Se debe ingresar al menos el comando -n/--name o el comando -h/--help."
#define MSJ_ERROR_VARIOS_NAMES "Se pasaron varios nombres de la secuencia por linea de comandos y solo se puede recibir uno."
#define MSJ_ERROR_NAMES_INESPERADO "Ocurrio un error con el comando -n/--name."
#define MSJ_ERROR_FECHA_INCOMPLETA "No se ingresaron las tres componentes de una fecha: dia, mes y anio."
#define MSJ_ERROR_FECHA_INVALIDA "La fecha ingresada no es valida."
#define MSJ_ERROR_NUMERO_VERIFICACION "El checksum no verifica, no ha llegado correctamente la cadena: "
#define MSJ_ERROR_HORA "Hubo un problema al obtener la hora de la cadena: "
#define MSJ_ERROR_LATITUD "Hubo un problema al obtener la latitud de la cadena: "
#define MSJ_ERROR_NS "Hubo un problema al obtener el hemisferio latitudinal de la cadena: "
#define MSJ_ERROR_LONGITUD "Hubo un problema al obtener la longitud de la cadena: "
#define MSJ_ERROR_EO "Hubo un problema al obtener el hemisferio longitudinal de la cadena: "
#define MSJ_ERROR_CALIDAD_FIX "Hubo un problema al obtener la calidad del fix de la cadena: "
#define MSJ_ERROR_CANTIDAD_DE_SATELITES "Hubo un problema al obtener la cantidad de satélites utilizados de la cadena: "
#define MSJ_ERROR_HDOP "Hubo un problema al obtener el HDoP de la cadena: "
#define MSJ_ERROR_ELEVACION "Hubo un problema al obtener la elevacion de la cadena: "
#define MSJ_ERROR_SEPARACION_GEOIDE "Hubo un problema al obtener la separacion del geoide de la cadena: "
#define MSJ_ERROR_DATO_INGRESADO "El dato ingresado es incorrecto, por favor intente otra vez."

typedef enum status_t {
	ST_OK,
	ST_ERROR
} status_t;

typedef enum status_name_t {
	ST_NO_NAME,
	ST_1_NAME,
	ST_VARIOS_NAMES,
	ST_NAME_ERROR
} status_name_t;

typedef enum status_help_t {
	ST_NO_SE_PIDIO_AYUDA,
	ST_SE_PIDIO_AYUDA_UNA_VEZ,
	ST_SE_PIDIO_AYUDA_MUCHAS_VECES
} status_help_t;

typedef enum status_fecha_t {
	ST_FECHA_OK,
	ST_FECHA_INVALIDA,
	ST_FECHA_INCOMPLETA,
	ST_FECHA_NO_INGRESADA
} status_fecha_t;

typedef struct{
	int dia;
	int mes;
	int anio;
	int horas;
	int minutos;
	double segundos;
}fecha_t;

typedef struct{
	int grados;
	double min;
}lat_t;

typedef struct{
	int grados_long;
	double min_long;
}long_t;

typedef struct{
	fecha_t fecha;
	lat_t latitud;
	long_t longitud;
	int calidad;
	int cantidad_satelites;
	double HDoP;
	double elevacion;
	double separacion_geoide;
}datos_t;

status_help_t pedir_ayuda(int nargumentos, char* argumentos[]) {

	char long_help[] = "--help";
	char short_help[] = "-h";

	int iterador_ldc=0;
	int verificador=0;

	while(iterador_ldc<nargumentos) {

		if (strcmp(argumentos[iterador_ldc], long_help)==0 || strcmp(argumentos[iterador_ldc], short_help)==0) {

			verificador++;
		}

		iterador_ldc++;
	}

	switch (verificador) {

		case 0:
			return ST_NO_SE_PIDIO_AYUDA;
		break;

		case 1:
			return ST_SE_PIDIO_AYUDA_UNA_VEZ;
		break;

		default:
			return ST_SE_PIDIO_AYUDA_MUCHAS_VECES;
	}

	return ST_SE_PIDIO_AYUDA_MUCHAS_VECES;
}

status_name_t obtener_nombre (int nargumentos, char* argumentos[], char nombre[]) {

	char long_name[] = "--name";
	char short_name[] = "-n";

	int iterador_ldc=0;
	int verificador=0;

	if (strcmp(argumentos[nargumentos-1], long_name)==0 || strcmp(argumentos[nargumentos-1], short_name)==0) {

		return ST_NAME_ERROR;
	}

	while(iterador_ldc<nargumentos) {

		if (strcmp(argumentos[iterador_ldc], long_name)==0 || strcmp(argumentos[iterador_ldc], short_name)==0) {

			if(argumentos[iterador_ldc+1][0]=='-') {

				return ST_NAME_ERROR;
			}

			strcpy(nombre, argumentos[iterador_ldc + 1]);

			verificador++;
		}

		iterador_ldc++;
	}

	switch(verificador) {

		case 0: 

			return ST_NO_NAME;
			break;

		case 1:

			return ST_1_NAME;

			break;

		default:
			return ST_VARIOS_NAMES;
	}

	return ST_NAME_ERROR;
}

status_fecha_t funcion_obtener_fecha (int nargumentos, char* argumentos[], int *year, int *mes, int *dia) {

	char long_fecha[] = "--format";
	char short_fecha[] = "-f";

	char long_year[] = "--year";
	char short_year[] = "-Y";

	char long_mes[] = "--month";
	char short_mes[] = "-m";

	char long_dia[] = "--day";
	char short_dia[] = "-d";

	char str_year[MAXIMO_CADENA_YEAR_LOCAL];
	char str_mes [MAXIMO_CADENA_MES_LOCAL];
	char str_dia [MAXIMO_CADENA_DIA_LOCAL];

	int iterador_argumentos=0;
	int iterador_validador=0;
	int iterador_de_copia=0;

	int verificador_year=0;
	int verificador_mes=0;
	int verificador_dia=0;

	if (strcmp(argumentos[nargumentos-1], long_fecha)==0 || strcmp(argumentos[nargumentos-1], short_fecha)==0) {

		return ST_FECHA_INVALIDA;
	}

	if (strcmp(argumentos[nargumentos-1], long_year)==0 || strcmp(argumentos[nargumentos-1], short_year)==0) {

		return ST_FECHA_INVALIDA;
	}

	if (strcmp(argumentos[nargumentos-1], long_mes)==0 || strcmp(argumentos[nargumentos-1], short_mes)==0) {

		return ST_FECHA_INVALIDA;
	}

	if (strcmp(argumentos[nargumentos-1], long_dia)==0 || strcmp(argumentos[nargumentos-1], short_dia)==0) {

		return ST_FECHA_INVALIDA;
	}

	while (iterador_argumentos<nargumentos) {

		if (strcmp(argumentos[iterador_argumentos], long_fecha)==0 || strcmp(argumentos[iterador_argumentos], short_fecha)==0) {

			if(argumentos[iterador_argumentos+1][0]=='-') {

				return ST_FECHA_INVALIDA;
			}

			if (strlen(argumentos[iterador_argumentos+1])!=(LONGITUD_CADENA_DIA+LONGITUD_CADENA_MES+LONGITUD_CADENA_YEAR)){

				verificador_year++;
				verificador_mes++;
				verificador_dia++;
			}

			for(iterador_validador=0; iterador_validador<(LONGITUD_CADENA_DIA+LONGITUD_CADENA_MES+LONGITUD_CADENA_YEAR); iterador_validador++) {

				if (isdigit(argumentos[iterador_argumentos+1][iterador_validador])==0) {

					verificador_year++;
					verificador_mes++;
					verificador_dia++;
				}
			}

			for (iterador_de_copia=0; iterador_de_copia<LONGITUD_CADENA_YEAR; iterador_de_copia++) {

				str_year[iterador_de_copia]=argumentos[iterador_argumentos+1][iterador_de_copia];

				*year=atoi(str_year);
			}

			for (iterador_de_copia=LONGITUD_CADENA_YEAR; iterador_de_copia<(LONGITUD_CADENA_YEAR+LONGITUD_CADENA_MES); iterador_de_copia++) {

				str_mes[iterador_de_copia -LONGITUD_CADENA_YEAR]=argumentos[iterador_argumentos+1][iterador_de_copia];

				*mes=atoi(str_mes);

				if (*mes>MAXIMO_MES || *mes<1) {
					verificador_mes++;
				}
			}

			for (iterador_de_copia=LONGITUD_CADENA_YEAR+LONGITUD_CADENA_MES; iterador_de_copia<LONGITUD_CADENA_YEAR+LONGITUD_CADENA_MES+LONGITUD_CADENA_DIA; iterador_de_copia++) {

				str_dia[iterador_de_copia -LONGITUD_CADENA_YEAR -LONGITUD_CADENA_MES]=argumentos[iterador_argumentos+1][iterador_de_copia];

				*dia=atoi(str_dia);

				if(*dia>MAXIMO_DIA || *dia<1) {
					verificador_dia++;
				}
			}

			verificador_year++;
			verificador_mes++;
			verificador_dia++;
		}

		if (strcmp(argumentos[iterador_argumentos], long_year)==0 || strcmp(argumentos[iterador_argumentos], short_year)==0) {

			if(argumentos[iterador_argumentos+1][0]=='-') {

				return ST_FECHA_INVALIDA;
			}

			if (strlen(argumentos[iterador_argumentos+1])!=LONGITUD_CADENA_YEAR) {

				verificador_year++;
			}

			for(iterador_validador=0; iterador_validador<strlen(argumentos[iterador_argumentos+1]); iterador_validador++) {

				if (isdigit(argumentos[iterador_argumentos+1][iterador_validador])==0) {

					verificador_year++;
				}
			}

			strcpy(str_year, argumentos[iterador_argumentos+1]);

			*year=atoi(str_year);

			verificador_year++;
		}

		if (strcmp(argumentos[iterador_argumentos], long_mes)==0 || strcmp(argumentos[iterador_argumentos], short_mes)==0) {

			if(argumentos[iterador_argumentos+1][0]=='-') {

				return ST_FECHA_INVALIDA;
			}

			if (strlen(argumentos[iterador_argumentos+1])>LONGITUD_CADENA_MES) {

				verificador_mes++;
			}

			for(iterador_validador=0; iterador_validador<strlen(argumentos[iterador_argumentos+1]); iterador_validador++) {

				if (isdigit(argumentos[iterador_argumentos+1][iterador_validador])==0) {

					verificador_mes++;
				}
			}			

			strcpy(str_mes, argumentos[iterador_argumentos+1]);

			*mes=atoi(str_mes);

			if (*mes>MAXIMO_MES || *mes<1) {

				verificador_mes++;
			}

			verificador_mes++;
		}

		if (strcmp(argumentos[iterador_argumentos], long_dia)==0 || strcmp(argumentos[iterador_argumentos], short_dia)==0) {

			if(argumentos[iterador_argumentos+1][0]=='-') {

				return ST_FECHA_INVALIDA;
			}

			if (strlen(argumentos[iterador_argumentos+1])>LONGITUD_CADENA_DIA) {

				verificador_dia++;
			}

			for(iterador_validador=0; iterador_validador<strlen(argumentos[iterador_argumentos+1]); iterador_validador++) {

				if (isdigit(argumentos[iterador_argumentos+1][iterador_validador])==0) {

					verificador_dia++;
				}
			}

			strcpy(str_dia, argumentos[iterador_argumentos+1]);

			*dia=atoi(str_dia);

			if(*dia>MAXIMO_DIA || *dia<1) {

				verificador_dia++;
			}

			verificador_dia++;
		}

		iterador_argumentos++;
	}

	if (verificador_dia>1 || verificador_mes>1 || verificador_year>1) {

		return ST_FECHA_INVALIDA;
	}

	if (verificador_dia+verificador_mes+verificador_year>0 && verificador_dia+verificador_mes+verificador_year!=3) {

		return ST_FECHA_INCOMPLETA;
	}

	if (verificador_dia==0 && verificador_mes==0 && verificador_year==0) {

		return ST_FECHA_NO_INGRESADA;
	}

	return ST_FECHA_OK;
}

status_t funcion_obtener_hora (char cadena[], int* hh, int* mm, double* ss){ 

	char horas_separadas[MAXIMO_CADENA_HORAS_SEPARADAS], minutos_separados[MAXIMO_CADENA_MINUTOS], segundos_separados[MAXIMO_CADENA_SEGUNDOS];

	int i=0, iterador_horas=0, iterador_minutos=0, iterador_segundos=0, contador_puntos=0;

	while (cadena[i]!=',') {
		i++;
	}

	i++;

	while (iterador_horas<MAXIMO_CADENA_HORAS_SEPARADAS-1) {

		horas_separadas [iterador_horas]=cadena[i];

		if(isdigit(horas_separadas[iterador_horas])==0) {

			return ST_ERROR;
		}

		i++;
		iterador_horas++;
	}

	*hh = atoi (horas_separadas);

	if(*hh>=MAXIMO_HORAS) {

		return ST_ERROR;
	}

	while (iterador_minutos<MAXIMO_CADENA_MINUTOS-1) {

		minutos_separados[iterador_minutos]=cadena[i];

		if(isdigit(minutos_separados[iterador_minutos])==0) {

			return ST_ERROR;
		}

		i++;
		iterador_minutos++;
	}

	*mm = atoi (minutos_separados);

	if (*mm>=MAXIMO_MINUTOS_HORARIOS) {

		return ST_ERROR;

	}

	while (cadena[i]!=',') {

		segundos_separados[iterador_segundos]=cadena[i];

		if(isdigit(segundos_separados[iterador_segundos])==0 && segundos_separados[iterador_segundos]!='.') {

			return ST_ERROR;
		}

		if(segundos_separados[iterador_segundos]=='.') {
			contador_puntos++;
		}

		iterador_segundos++;
		i++;
	}

	*ss = atof (segundos_separados);

	if (*ss>=MAXIMO_SEGUNDOS_HORARIOS) {

		return ST_ERROR;
	}

	if (contador_puntos!=1) {
		return ST_ERROR;
	}

	return ST_OK;
}

status_t funcion_obtener_latitud (char cadena[], int* gr_latitud, double* min_latitud){

	int iterador_cadena=0, iterador_comas=0, iterador_grados=0, iterador_minutos=0, contador_puntos=0;
	char grados_separados[MAXIMO_CADENA_SECUENCIA],min_separados[MAXIMO_CADENA_SECUENCIA];


	while(iterador_comas<COMA_LATITUD) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}


	while(iterador_grados<MAXIMO_CADENA_GRADOS-1){
		grados_separados[iterador_grados]=cadena[iterador_cadena];

		if(isdigit(grados_separados[iterador_grados])==0) {
			return ST_ERROR;
		}		

		iterador_cadena++;
		iterador_grados++;
	}

	*gr_latitud=atoi(grados_separados);

	if(*gr_latitud>=MAXIMO_GRADOS_LATITUD){
		return ST_ERROR;
	}

	while(cadena[iterador_cadena]!=','){
		min_separados[iterador_minutos]=cadena[iterador_cadena];

		if(isdigit(min_separados[iterador_minutos])==0 && min_separados[iterador_minutos]!='.') {
			return ST_ERROR;
		}

		if(min_separados[iterador_minutos]=='.') {
			contador_puntos++;
		}

		iterador_cadena++;
		iterador_minutos++;
	}

	*min_latitud=atof(min_separados);

	if(*min_latitud>=MAXIMO_MINUTOS_GEOGRAFICOS){
		return ST_ERROR;
	}

	if (contador_puntos!=1) {
		return ST_ERROR;
	}

	return ST_OK;
}

status_t funcion_norte_sur (char cadena[],char* n_s){

	int iterador_cadena=0, iterador_comas=0;

	while(iterador_comas<COMA_NORTE_SUR) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}

	if((cadena[iterador_cadena]=='N') && cadena[iterador_cadena+1]==',') {
		*n_s=cadena[iterador_cadena];
		return ST_OK;
	}else if((cadena[iterador_cadena]=='S') && cadena[iterador_cadena+1]==','){
		*n_s=cadena[iterador_cadena];
		return ST_OK;
	}
	return ST_ERROR;
}

status_t funcion_obtener_longitud (char cadena[], int* gr_longitud, double* min_longitud){

	int iterador_cadena=0, iterador_comas=0, iterador_grados=0, iterador_minutos=0, iterador_cadena_auxiliar, numero_de_digitos=0;
	char grados_separados_longitud[MAXIMO_CADENA_SECUENCIA],min_separados_longitud[MAXIMO_CADENA_SECUENCIA];

	while(iterador_comas<COMA_LONGITUD) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}


	iterador_cadena_auxiliar=iterador_cadena;

	for(;cadena[iterador_cadena_auxiliar]!='.';iterador_cadena_auxiliar++){
		numero_de_digitos++;
	}
	
	if(numero_de_digitos==MINIMO_DIGITOS_DE_LONGITUD_PARTE_ENTERA){

		while(iterador_grados<MAXIMO_CADENA_HORAS_SEPARADAS-1){

			grados_separados_longitud[iterador_grados]=cadena[iterador_cadena];

			if(isdigit(grados_separados_longitud[iterador_grados])==0) {
				return ST_ERROR;
			}	

			iterador_grados++;
			iterador_cadena++;
		}

		*gr_longitud=atoi(grados_separados_longitud);

		while(cadena[iterador_cadena]!=','){

			min_separados_longitud[iterador_minutos]=cadena[iterador_cadena];

			if(isdigit(min_separados_longitud[iterador_minutos])==0) {
				return ST_ERROR;
			}	

			iterador_cadena++;
			iterador_minutos++;
		}

		*min_longitud=atof(min_separados_longitud);

		if(*min_longitud>=MAXIMO_MINUTOS_GEOGRAFICOS){
			return ST_ERROR;
		}

		if(*gr_longitud==MAXIMO_NUMERO_ENTERO_DOS_CIFRAS && *min_longitud>0){
			return ST_ERROR;
		}

	}else if(numero_de_digitos==MAXIMO_DIGITOS_DE_LONGITUD_PARTE_ENTERA){

		while(iterador_grados<MAXIMO_CADENA_HORAS_SEPARADAS){

			grados_separados_longitud[iterador_grados]=cadena[iterador_cadena];
			iterador_grados++;
			iterador_cadena++;
		}

		*gr_longitud=atoi(grados_separados_longitud);

		if(*gr_longitud>MAXIMO_GRADOS_LONGITUD){
			return ST_ERROR;
		}

		while(cadena[iterador_cadena]!=','){
			min_separados_longitud[iterador_minutos]=cadena[iterador_cadena];
			iterador_cadena++;
			iterador_minutos++;
		}

		*min_longitud=atof(min_separados_longitud);
		if(*min_longitud>=MAXIMO_MINUTOS_GEOGRAFICOS){
			return ST_ERROR;
		}

		if(*gr_longitud==MAXIMO_GRADOS_LONGITUD && *min_longitud>0){
			return ST_ERROR;
		}
	}
	return ST_OK;
}

status_t funcion_este_oeste (char cadena[],char* e_w){

	int iterador_cadena=0, iterador_comas=0;

	while(iterador_comas<COMA_ESTE_OESTE) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}

	if((cadena[iterador_cadena]=='E') && cadena[iterador_cadena+1]==','){
		*e_w=cadena[iterador_cadena];
		return ST_OK;

	}else if((cadena[iterador_cadena]=='W') && cadena[iterador_cadena+1]==',') {
		*e_w=cadena[iterador_cadena];
		return ST_OK;
	}

	return ST_ERROR;

}

status_t funcion_obtener_calidad_fix (char cadena[], int* calidad){

	int iterador_cadena=0, iterador_comas=0,iterador_cadena_auxiliar=0;
	char cal_fix[MAXIMO_CADENA_SECUENCIA]={0};

	while(iterador_comas<COMA_CALIDAD_FIX) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}


	iterador_cadena_auxiliar=iterador_cadena;

	for(;cadena[iterador_cadena]!=',';iterador_cadena++){

		cal_fix[iterador_cadena_auxiliar]=cadena[iterador_cadena];
		
		if(isdigit(cal_fix[iterador_cadena_auxiliar])==0) {
			return ST_ERROR;
		}		

		iterador_cadena_auxiliar++;
	}
	
	*calidad=atoi(cal_fix);

	if(*calidad<0 || *calidad>MAXIMA_CALIDAD_FIX){
		return ST_ERROR;
	}

	return ST_OK;
}

status_t funcion_obtener_cantidad_satelites (char cadena[], int* cantidad){

	int iterador_cadena=0, iterador_comas=0, iterador_cadena_hdop=0, iterador_cadena_auxiliar, numero_de_digitos=0;
	char cant_satelites[MAXIMO_CADENA_SECUENCIA]={0};

	while(iterador_comas<COMA_CANTIDAD_SATELITES) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}

	iterador_cadena_auxiliar=iterador_cadena;

	for(;cadena[iterador_cadena_auxiliar]!=',';iterador_cadena_auxiliar++){
		numero_de_digitos++;
	}

	if(numero_de_digitos==MINIMO_DIGITOS_SATELITES){
		cant_satelites[iterador_cadena_hdop]=cadena[iterador_cadena];
	
	}else if(numero_de_digitos==MAXIMO_DIGITOS_SATELITES){
		for(;iterador_cadena_hdop<numero_de_digitos;iterador_cadena_hdop++){
			cant_satelites[iterador_cadena_hdop]=cadena[iterador_cadena];
			iterador_cadena++;
		}
	}

	*cantidad=atoi(cant_satelites);

	if(*cantidad<0 || *cantidad>MAXIMA_CANTIDAD_SATELITES){
		return ST_ERROR;
	}
	return ST_OK;
}

status_t funcion_obtener_HDoP(char cadena[],double* hdop){
	
	int iterador_cadena=0, iterador_comas=0, iterador_auxiliar=0, contador_puntos=0;
	char cadena_hdop[MAXIMO_CADENA_SECUENCIA];

	while(iterador_comas<COMA_HDOP) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}
	
	while(cadena[iterador_cadena]!=','){
		cadena_hdop[iterador_auxiliar]=cadena[iterador_cadena];

		if (cadena_hdop[iterador_auxiliar]=='.') {

			contador_puntos++;
		}

		if(isdigit(cadena_hdop[iterador_auxiliar])==0 && cadena_hdop[iterador_auxiliar]!='.') {
			return ST_ERROR;
		}		

		iterador_cadena++;
		iterador_auxiliar++;
	}

	if (contador_puntos!=1) {
		return ST_ERROR;
	}

	*hdop=atof(cadena_hdop);
	return ST_OK;
}

status_t funcion_obtener_elevacion(char cadena[],double* elev){
	
	int iterador_cadena=0, iterador_comas=0, iterador_cadena_elevacion=0, contador_puntos=0;
	char cadena_elevacion[MAXIMO_CADENA_SECUENCIA];

	while(iterador_comas<COMA_ELEVACION) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}
	
	while(cadena[iterador_cadena]!=','){
		cadena_elevacion[iterador_cadena_elevacion]=cadena[iterador_cadena];
		
		if(isdigit(cadena_elevacion[iterador_cadena_elevacion])==0 && cadena_elevacion[iterador_cadena_elevacion]!='.') {
			return ST_ERROR;
		}

		if(cadena_elevacion[iterador_cadena_elevacion]=='.') {
			contador_puntos++;
		}		

		iterador_cadena++;
		iterador_cadena_elevacion++;
	}

	if(contador_puntos!=1) {
		return ST_ERROR;
	}

	if(cadena[iterador_cadena+1]!='M' || cadena[iterador_cadena+2]!=',') {
		return ST_ERROR;
	}

	*elev=atof(cadena_elevacion);
	return ST_OK;
}

status_t funcion_obtener_separacion_del_geoide(char cadena[],double* separacion) {
	
	int iterador_cadena=0, iterador_comas=0, iterador_cadena_separacion_geoide=0, contador_puntos=0;
	char cadena_separacion_geoide[MAXIMO_CADENA_SECUENCIA];

	while(iterador_comas<COMA_SEPARACION_GEOIDE) {

		while(cadena[iterador_cadena]!=',') {
			iterador_cadena++;
		}
		
		iterador_cadena++;
		iterador_comas++;
	}

	while(cadena[iterador_cadena]!=','){

		cadena_separacion_geoide[iterador_cadena_separacion_geoide]=cadena[iterador_cadena];

		if(isdigit(cadena_separacion_geoide[iterador_cadena_separacion_geoide])==0 && cadena_separacion_geoide[iterador_cadena_separacion_geoide]!='.') {
			return ST_ERROR;
		}		

		if(cadena_separacion_geoide[iterador_cadena_separacion_geoide]=='.') {
			contador_puntos++;
		}

		iterador_cadena++;
		iterador_cadena_separacion_geoide++;
	}

	if (contador_puntos!=1){
		return ST_ERROR;
	}

	*separacion=atof(cadena_separacion_geoide);
	return ST_OK;
}

unsigned char checksum(const char* cadena){

	unsigned char suma=0;
	while(*cadena)
		suma ^= *cadena++;
	
	return suma;
}

double funcion_conversion_latitud(int grados_lat,double minutos_lat,char* norte_sur){
	if(*norte_sur=='N'){
		return grados_lat+minutos_lat/MAXIMO_MINUTOS_GEOGRAFICOS;
	}
	return (-1)*(grados_lat+minutos_lat/MAXIMO_MINUTOS_GEOGRAFICOS);
}

double funcion_conversion_longitud(int grados_long,double minutos_long,char* este_oeste){
	if(*este_oeste=='E'){
		return grados_long+minutos_long/MAXIMO_MINUTOS_GEOGRAFICOS;
	}
	return (-1)*(grados_long+minutos_long/MAXIMO_MINUTOS_GEOGRAFICOS);
} 

int main (int argc, char* argv[]) {

	char cadena_sentencia [MAXIMO_CADENA_SECUENCIA];

	char name[MAXIMO_CADENA_NAME];

	time_t t;
	struct tm *tm;
	char year_local[MAXIMO_CADENA_YEAR_LOCAL];
	char mes_local[MAXIMO_CADENA_MES_LOCAL];
	char dia_local[MAXIMO_CADENA_DIA_LOCAL];
	char hora_local[MAXIMO_CADENA_DIA_LOCAL];
	char minuto_local[MAXIMO_CADENA_MINUTO_LOCAL];
	char segundo_local[MAXIMO_CADENA_SEGUNDO_LOCAL];

	int year_trkpt;
	int mes_trkpt;
	int dia_trkpt;

	int horas_separadas_gp;
	int minutos_gp;
	double segundos_gp;

	char norte_sur;	
	int grados_separados_gp;
	double min_separados_gp;

	char este_oeste;
	int grados_separados_longitud_gp;
	double min_separados_longitud_gp;
	
	int calidad_fix;

	int cantidad_de_satelites;

	double hdop;

	double elev;

	double separacion;

	datos_t datos[MAXIMO_CADENA_SECUENCIA];

	int POSICION_CARACTER_1_TIPO_DE_SENTENCIA=3, POSICION_CARACTER_2_TIPO_DE_SENTENCIA=4, POSICION_CARACTER_3_TIPO_DE_SENTENCIA=5; 
	char CARACTER_INICIAL_DE_SENTENCIAS='$', CARACTER_1_DE_SENTENCIAS_GGA='G', CARACTER_2_DE_SENTENCIAS_GGA='G', CARACTER_3_DE_SENTENCIAS_GGA='A'; 

	t=time(NULL);
	tm=localtime(&t);
	strftime(year_local, MAXIMO_CADENA_YEAR_LOCAL, "%Y", tm);
	strftime(mes_local, MAXIMO_CADENA_MES_LOCAL, "%m", tm);
	strftime(dia_local, MAXIMO_CADENA_DIA_LOCAL, "%d", tm);
	strftime(hora_local, MAXIMO_CADENA_HORA_LOCAL, "%H", tm);
	strftime(minuto_local, MAXIMO_CADENA_MINUTO_LOCAL, "%M", tm);
	strftime(segundo_local, MAXIMO_CADENA_SEGUNDO_LOCAL, "%S", tm);
	int iterador_cadena_sentencia, iterador_cadena_sentencia_auxiliar, iterador_cadena_sentencia_auxiliar_2;
	char numero_verificacion[MAXIMO_CADENA_SECUENCIA], suma_verificacion[MAXIMO_CADENA_SECUENCIA];
	int flag, iterador_suma_verificacion, iterador_estructuras, primer_posicion;

	if (argc==1) {

		fprintf(stderr, "\n%s%s\n", MSJ_ERROR, MSJ_ERROR_SIN_COMANDOS);
	
		return EXIT_FAILURE;

	} else if (pedir_ayuda(argc, argv)==ST_NO_SE_PIDIO_AYUDA && obtener_nombre(argc, argv, name)==ST_NO_NAME) {

		fprintf(stderr, "\n%s%s\n", MSJ_ERROR, MSJ_ERROR_SIN_COMANDOS_VALIDOS);

		return EXIT_FAILURE;

	}

	switch (obtener_nombre(argc, argv, name)) {

		case ST_VARIOS_NAMES:
			fprintf(stderr, "\n%s%s\n", MSJ_ERROR, MSJ_ERROR_VARIOS_NAMES);
			return EXIT_FAILURE;
			break;

		case ST_NAME_ERROR:
			fprintf(stderr, "\n%s%s\n", MSJ_ERROR, MSJ_ERROR_NAMES_INESPERADO);
			return EXIT_FAILURE;
			break;

		case ST_NO_NAME:
			;

		case ST_1_NAME:
			;
	}

	switch (funcion_obtener_fecha(argc, argv, &year_trkpt, &mes_trkpt, &dia_trkpt)) {

		case ST_FECHA_INCOMPLETA:
			fprintf(stderr, "\n%s%s\n", MSJ_ERROR, MSJ_ERROR_FECHA_INCOMPLETA);
			return EXIT_FAILURE;
			break;

		case ST_FECHA_INVALIDA:
			fprintf(stderr, "\n%s%s\n", MSJ_ERROR, MSJ_ERROR_FECHA_INVALIDA);
			return EXIT_FAILURE;
			break;

		case ST_FECHA_NO_INGRESADA:
			year_trkpt=atoi(year_local);
			mes_trkpt=atoi(mes_local);
			dia_trkpt=atoi(dia_local);
			break;

		case ST_FECHA_OK:
			;
	}

	switch (pedir_ayuda(argc, argv)) {

		case ST_SE_PIDIO_AYUDA_MUCHAS_VECES:

			printf("%s\n\n", MSJ_HELP_SE_ESCRIBIO_AYUDA_MUCHAS_VECES);

		case ST_SE_PIDIO_AYUDA_UNA_VEZ:

			printf("%s\n\n", MSJ_HELP);

			if (obtener_nombre(argc, argv, name)!=ST_1_NAME) {

				return EXIT_SUCCESS;
			}

		case ST_NO_SE_PIDIO_AYUDA:
			;

	}

	fprintf(stdout, "%s%s%s%s%s%s%s%s-%s-%s%s%s:%s:%s%s%s%s%s%s", GPX_ENCABEZADO, GPX_OPEN_ELEMENTO, GPX_ELEMENTO_OPEN_METADATA, GPX_ELEMENTO_METADATA_OPEN_NAME, name, GPX_ELEMENTO_METADATA_CLOSE_NAME, GPX_ELEMENTO_METADATA_OPEN_TIME, year_local, mes_local, dia_local, MSJ_T, hora_local, minuto_local, segundo_local, MSJ_Z, GPX_ELEMENTO_METADATA_CLOSE_TIME, GPX_ELEMENTO_CLOSE_METADATA, GPX_ELEMENTO_OPEN_TRK, GPX_ELEMENTO_TRK_OPEN_TRKSEG);

	while(fgets(cadena_sentencia, MAXIMO_CADENA_SECUENCIA, stdin)!=NULL){
		
		flag=0;
		iterador_suma_verificacion=0;
		iterador_estructuras=0;
		primer_posicion=0;

		if(cadena_sentencia[primer_posicion]==CARACTER_INICIAL_DE_SENTENCIAS && cadena_sentencia[POSICION_CARACTER_1_TIPO_DE_SENTENCIA]==CARACTER_1_DE_SENTENCIAS_GGA && cadena_sentencia[POSICION_CARACTER_2_TIPO_DE_SENTENCIA]==CARACTER_2_DE_SENTENCIAS_GGA && cadena_sentencia[POSICION_CARACTER_3_TIPO_DE_SENTENCIA]==CARACTER_3_DE_SENTENCIAS_GGA){

			for(iterador_cadena_sentencia_auxiliar_2=0;cadena_sentencia[iterador_cadena_sentencia_auxiliar_2]!='*';iterador_cadena_sentencia_auxiliar_2++){}

			for(iterador_cadena_sentencia=1;iterador_cadena_sentencia<iterador_cadena_sentencia_auxiliar_2;iterador_cadena_sentencia++){
				suma_verificacion[iterador_suma_verificacion]=cadena_sentencia[iterador_cadena_sentencia];
				iterador_suma_verificacion++;
			}

			iterador_suma_verificacion=0;

			for(iterador_cadena_sentencia=0;cadena_sentencia[iterador_cadena_sentencia]!='*';iterador_cadena_sentencia++){}

			iterador_cadena_sentencia++;

			iterador_cadena_sentencia_auxiliar=iterador_cadena_sentencia;
		
			for(;iterador_cadena_sentencia<iterador_cadena_sentencia_auxiliar+2;iterador_cadena_sentencia++){
				numero_verificacion[iterador_suma_verificacion]=cadena_sentencia[iterador_cadena_sentencia];
				iterador_suma_verificacion++;
			}

			int numero=(int)strtol(numero_verificacion,NULL,16);
			int a=checksum(suma_verificacion);

			if(numero!=a){
				printf("\n%s%s%s%s", MSJ_ERROR, MSJ_ERROR_NUMERO_VERIFICACION, cadena_sentencia,GPX_ELEMENTO_TRK_TRKSEG_CLOSE_TRKPT);
			}else{

				if(funcion_obtener_hora(cadena_sentencia, &horas_separadas_gp, &minutos_gp, &segundos_gp)!=ST_OK) {
					fprintf(stderr, "\n%s%s%s\n", MSJ_ERROR, MSJ_ERROR_HORA, cadena_sentencia);
					flag++;
				}

				if(funcion_obtener_latitud(cadena_sentencia,&grados_separados_gp,&min_separados_gp)!=ST_OK){
					fprintf(stderr,"\n%s%s%s\n",MSJ_ERROR, MSJ_ERROR_LATITUD, cadena_sentencia);
					flag++;
				}
		
				if(funcion_norte_sur(cadena_sentencia,&norte_sur)!=ST_OK){
					fprintf(stderr,"%s%s%s\n",MSJ_ERROR, MSJ_ERROR_NS, cadena_sentencia);
					flag++;
				}

				if(funcion_obtener_longitud(cadena_sentencia,&grados_separados_longitud_gp,&min_separados_longitud_gp)!=ST_OK){
					fprintf(stderr,"\n%s%s%s\n",MSJ_ERROR, MSJ_ERROR_LONGITUD, cadena_sentencia);
					flag++;
				}

				if(funcion_este_oeste(cadena_sentencia,&este_oeste)!=ST_OK){
					fprintf(stderr,"%s%s%s\n",MSJ_ERROR, MSJ_ERROR_EO, cadena_sentencia);
					flag++;
				}

				if(funcion_obtener_calidad_fix(cadena_sentencia,&calidad_fix)!=ST_OK){
					fprintf(stderr,"%s%s%s\n",MSJ_ERROR, MSJ_ERROR_CALIDAD_FIX, cadena_sentencia);
					flag++;
				}

				if(funcion_obtener_cantidad_satelites(cadena_sentencia,&cantidad_de_satelites)!=ST_OK){
					fprintf(stderr,"%s%s%s\n",MSJ_ERROR, MSJ_ERROR_CANTIDAD_DE_SATELITES, cadena_sentencia);
					flag++;
				}

				if(funcion_obtener_HDoP(cadena_sentencia,&hdop)!=ST_OK){
					fprintf(stderr,"%s%s%s\n",MSJ_ERROR, MSJ_ERROR_HDOP, cadena_sentencia);
					flag++;
				}

				if(funcion_obtener_elevacion(cadena_sentencia,&elev)!=ST_OK){
					fprintf(stderr,"%s%s%s\n",MSJ_ERROR, MSJ_ERROR_ELEVACION, cadena_sentencia);
					flag++;
				}

				if(funcion_obtener_separacion_del_geoide(cadena_sentencia,&separacion)!=ST_OK){
					fprintf(stderr,"%s%s%s\n",MSJ_ERROR, MSJ_ERROR_SEPARACION_GEOIDE, cadena_sentencia);
					flag++;
				}

				if(flag==0) {

					datos[iterador_estructuras].fecha.anio=year_trkpt;
					datos[iterador_estructuras].fecha.mes=mes_trkpt;
					datos[iterador_estructuras].fecha.dia=dia_trkpt;
					datos[iterador_estructuras].fecha.horas=horas_separadas_gp;
					datos[iterador_estructuras].fecha.minutos=minutos_gp;
					datos[iterador_estructuras].fecha.segundos=segundos_gp;
					datos[iterador_estructuras].latitud.grados=grados_separados_gp;
					datos[iterador_estructuras].latitud.min=min_separados_gp;
					datos[iterador_estructuras].longitud.grados_long=grados_separados_longitud_gp;
					datos[iterador_estructuras].longitud.min_long=min_separados_longitud_gp;
					datos[iterador_estructuras].calidad=calidad_fix;
					datos[iterador_estructuras].cantidad_satelites=cantidad_de_satelites;
					datos[iterador_estructuras].HDoP=hdop;
					datos[iterador_estructuras].elevacion=elev;
					datos[iterador_estructuras].separacion_geoide=separacion;

					fprintf(stdout,"%s%s%lf%s%lf%s%s%f%s%s%04d-%02d-%02d%s%d:%d:%.3f%s%s%s", GPX_ELEMENTO_TRK_TRKSEG_OPEN_TRKPT,GPX_LATITUD, funcion_conversion_latitud(grados_separados_gp,min_separados_gp,&norte_sur),GPX_LONGITUD,funcion_conversion_longitud(grados_separados_longitud_gp,min_separados_longitud_gp,&este_oeste),GPX_CLOSE_LONGITUD, GPX_OPEN_ELEVACION, datos[iterador_estructuras].elevacion, GPX_CLOSE_ELEVACION, GPX_OPEN_TIME, datos[iterador_estructuras].fecha.anio,datos[iterador_estructuras].fecha.mes,datos[iterador_estructuras].fecha.dia,MSJ_T, datos[iterador_estructuras].fecha.horas, datos[iterador_estructuras].fecha.minutos, datos[iterador_estructuras].fecha.segundos, MSJ_Z, GPX_CLOSE_TIME, GPX_ELEMENTO_TRK_TRKSEG_CLOSE_TRKPT);

					iterador_estructuras++;
				}
			}
		}
	}

	fprintf(stdout, "%s%s%s", GPX_ELEMENTO_TRK_CLOSE_TRKSEG, GPX_ELEMENTO_CLOSE_TRK, GPX_CLOSE_ELEMENTO);

	return EXIT_SUCCESS;
}