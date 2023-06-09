#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "astronauta.h"

#define archiNave "archiNave.bin"

#define maxCaracteres  100
#define cantTiposDeNave  3
#define cantiTipoEstados 4

//INCREMENTAR LA CANTDEFUNCIONES


typedef struct{

    int ID;
    char tipoNave[maxCaracteres];
    int cantVuelosRealizados;
    int horasAcumuladasVuelo;
    int estado;
}nave;

//FUNCIONES

void cargarTipoNave(nave* nav);

void tiposDeNave(char naves[cantTiposDeNave][maxCaracteres]);

void mostrarTiposDeNave(char naves[cantTiposDeNave][maxCaracteres]);

int validacionTipoDeNave (int seleccion);

void menuOpcionesNave();

int validacionEstado (int seleccion);

void mostrarEstados(char estados[cantiTipoEstados][maxCaracteres]);

void tiposEstado(char estados[cantiTipoEstados][maxCaracteres]);

void cargarEstado(nave* nav);

int ultimoIde();

int tamanoArchin();


//---------------------------------MAIN--------------------------------------------------------------------------------





int main()
{
    astronauta astro;
    nave nav;

    int operador;
    char valor[] = "si";


    while(strcmp(valor, "si") == 0)
    {

        menuOpcionesFunciones();
        fflush(stdin);
        scanf("%i", &operador);

        while ( operador < 1 || operador > cantidadOpciones ) {

        printf("Ingrese una opcion valida \n");
        fflush(stdin);
        scanf("%i", &operador);
        }

        switch(operador)
        {

        case 1:

            cargarAstronautaNuevo(&astro);
            break;

        case 2:
            buscarAstronautaPorId();
            break;

        case 3:

            cambiarEstadoAstronauta();
            break;

        case 4:
            modificarAstronauta(&astro);
            break;

        case 5:
            mostrarAstronautas();
            break;

        case 6:
            cargarTipoNave(&nav);
            break;

        case 7:
            cargarEstado(&nav);
            break;

        default:
            printf("Numero Incorrecto \n");
            break;
        }

        printf("\n Ingrese 'si', para hacer una nueva operacion\n Ingrese 'no', para terminar el programa \n ");
        fflush(stdin);
        gets(valor);

        if(strcmp(valor, "no") == 0){

        reiniciarSistema();
        saludoFinal(valor);
        }

        while (strcmp(valor, "si") != 0 && strcmp(valor, "no") != 0 )
        {
            printf("Ingrese una opcion valida: ");
            fflush(stdin);
            gets(valor);
        }
    }
}


//CARGAR NAVE COMPLETA

void cargarNaveNueva(nave* nav)
{

    FILE* archi;

    archi = fopen(archiNave, "ab+");

   nav->ID = ultimoId();
   cargarTipoNave(nav);
   nav->horasAcumuladasVuelo = 0;
   nav->cantVuelosRealizados = 0;


    fwrite(nav, sizeof(nave),1, archi);

    fclose(archi);
}




//CARGAR TIPO DE LA NAVE

void cargarTipoNave(nave* nav)
{
    int seleccion;

    char naves[cantTiposDeNave][maxCaracteres];
    tiposDeNave(naves);

    printf("Seleccione el tipo de nave \n");
    mostrarTiposDeNave(naves);
    scanf("%i", &seleccion);

    int valido = validacionTipoDeNave(seleccion);

    if(valido == 1)
    {

        strcpy(nav->tipoNave,naves[seleccion - 1]);

    }
    else if (valido == 0)
    {

        while (valido == 0)
        {

            printf("Inserta un numero asociado a un tipo de nave\n TIPO DE NAVE: ");
            fflush(stdin);
            scanf("%i", &seleccion);

            valido = validacionTipoDeNave(seleccion);
        }
    }
    strcpy(nav->tipoNave,naves[seleccion - 1]);
}

//CARGA EN LA MATRIZ LOS TIPOS DE NAVE
void tiposDeNave(char naves[cantTiposDeNave][maxCaracteres])
{


    printf("\n");
    strcpy(naves[0], "Starship");
    strcpy(naves[1], "Falcon 9");
    strcpy(naves[2], "Falcon Heavy");

}

void mostrarTiposDeNave(char naves[cantTiposDeNave][maxCaracteres])
{

    int i = 0;
    int pos = 1;

    while (i < cantTiposDeNave)
    {

        printf( "%i = ", pos);
        printf("%s \n", naves[i]);

        pos++;
        i++;
    }
}

int validacionTipoDeNave (int seleccion)
{

    int valido = 0;

    if(seleccion <= cantTiposDeNave && seleccion > 0)
    {

        valido = 1;

    }
    else
    {

        valido = 0;
    }

    return valido;
}


void menuOpcionesNave()
{

    printf("|1| CARGAR NUEVA NAVE");

}

//----------------------------------------------------------------------------------------------------------
int ultimoIde()
{
    nave aux;

    FILE *archi = fopen(archiNave,"rb");
    if(archi == NULL || tamanoArchi() == 0)
    {
        fclose(archi);
        return 1;
    }

    fseek(archi,(sizeof(nave) * -1),SEEK_END);
    fread(&aux,sizeof(nave),1,archi);

    printf("ID: %i", aux.ID + 1);
    return aux.ID + 1;
}

int tamanoArchin()
{
    FILE *fich;

    fich=fopen(archiNave,"rb");

    fseek(fich, 0, SEEK_END);
    fclose(fich);
    return ftell(fich)/sizeof(nave);

}
//-----------------------------------------------------------------------------------------------------


void cargarEstado(nave* nav)
{
    int seleccion;

    char estado[cantiTipoEstados][maxCaracteres];
    tiposEstado(estado);

    printf("Seleccione el estado \n");
    mostrarEstados(estado);
    scanf("%i", &seleccion);

    int valido = validacionEstado(seleccion);

    if(valido == 1)
    {

        strcpy(nav->estado,estado[seleccion - 1]);

    }
    else if (valido == 0)
    {

        while (valido == 0)
        {

            printf("Inserta un numero asociado a un estado\n ESTADO: ");
            fflush(stdin);
            scanf("%i", &seleccion);

            valido = validacionEstado(seleccion);
        }
    }
    strcpy(nav->estado,estado[seleccion - 1]);
}

//CARGA EN LA MATRIZ LOS TIPOS DE NAVE
void tiposEstado(char estados[cantiTipoEstados][maxCaracteres])
{


    printf("\n");
    strcpy(estados[0], " Mantenimiento");
    strcpy(estados[1], " Lista para su uso");
    strcpy(estados[2], " Mision");
    strcpy(estados[3], " De baja");

}

void mostrarEstados(char estados[cantiTipoEstados][maxCaracteres])
{

    int i = 0;
    int pos = 1;

    while (i < cantiTipoEstados)
    {

        printf( "%i = ", pos);
        printf("%s \n", estados[i]);

        pos++;
        i++;
    }
}


int validacionEstado (int seleccion)
{

    int valido = 0;

    if(seleccion <= cantiTipoEstados && seleccion > 0)
    {

        valido = 1;

    }
    else
    {

        valido = 0;
    }

    return valido;
}
