#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"




void cargarTipoNave(nave* nav)
{

    int operador = -1;
    char strOpcion[maxCaracteres];


    char tiposNave[cantTiposNave][maxCaracteres];
    menuTiposNave(tiposNave);

    printf("Seleccione el tipo de nave\n");
    mostrarTipoNave(tiposNave);

    fflush(stdin);
    printf("\nOPCION: ");
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantTiposNave);

        if (operador >= minimaCantidadOpciones && operador <= cantTiposNave)
        {
            strcpy(nav->tipoNave, tiposNave[operador - 1]);
            break;
        }
    }
}


void mostrarTipoNave(char tiposNaves[cantTiposNave][maxCaracteres])
{

    int i = 0;
    int pos = 1;

    while (i< cantTiposNave)
    {


        printf("|%i| %s \n",pos, tiposNaves[i]);

        pos++;
        i++;
    }
}



void menuTiposNave(char tiposNave[cantTiposNave][maxCaracteres])
{

    printf("\n");
    strcpy(tiposNave[0], "Starship");
    strcpy(tiposNave[1], "Falcon 9");
    strcpy(tiposNave[2], "Falcon Heavy");
}




void tiposEstado(char estados[cantEstados][maxCaracteres])
{
    printf("\n");
    strcpy(estados[0], "Mantenimiento");
    strcpy(estados[1], "Lista para su uso");
    strcpy(estados[2], "Mision");
    strcpy(estados[3], "De baja");
}



void mostrarEstados(char estados[cantEstados][maxCaracteres])
{

    int i = 0;
    int pos = 1;

    while (i < cantEstados)
    {


        printf("|%i| %s \n",pos, estados[i]);

        pos++;
        i++;
    }
}



void  cargarEstado(nave* nav)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    char estados[cantEstados][maxCaracteres];
    tiposEstado(estados);


    printf("Seleccione un numero asociado a un estado\n ESTADO: ");
    mostrarEstados(estados);

    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantEstados);

        if (operador >= minimaCantidadOpciones && operador <= cantEstados)
        {
            strcpy(nav->estado,estados[operador - 1]);
            break;
        }
    }


}




//----------------------------------------------------------------------------------------


int idBuscadoNave()
{

    int valido = 0;
    int operador = -1;
    char strOpcion[maxCaracteres];
    int maxIdNave =  ultimoIdNave() -1;

    valido = validacionIDNave(operador);


    while (valido == 0 && (operador < minIdNave || operador > maxIdNave))
    {

        printf("Inserte el ID de la nave\n ID NAVE: ");
        fflush(stdin);
        gets(strOpcion);

        operador = validacionNumeros(strOpcion,minIdNave,maxIdNave);

        valido = validacionIDAstro(operador);

        if (operador >= minIdNave && operador <= maxIdNave && valido == 1)
        {

            return operador;

        }
    }

}

int tamanoArchiNave()
{
    FILE *fich =fopen(archiNave,"rb");

    fseek(fich, 0, SEEK_END);
    fclose(fich);
    return ftell(fich)/sizeof(stMision);

}
int ultimoIdNave()
{
    nave aux;

    FILE *archi = fopen(archiNave,"rb");
    if(archi == NULL || tamanoArchiNave() == 0)
    {
        fclose(archi);
        return 1;
    }

    fseek(archi,(sizeof(nave) * -1),SEEK_END);
    fread(&aux,sizeof(nave),1,archi);

    return aux.ID + 1;

}

int validacionIDNave(int id)
{


    FILE* archi;

    archi = fopen(archiNave, "rb");

    nave aux;

    while(fread(&aux, sizeof(nave), 1, archi) > 0)
    {

        if(id == aux.ID)
        {

            return 1;
        }

    }


}


void mostrarIDNave()
{

    int ID = ultimoIdNave();
    printf("\nID: %i", ID );

}





void cargarNuevaNave(nave* nav)
{

    FILE* archi = fopen(archiNave, "ab");

    nav->ID = ultimoIdNave();
    mostrarIDNave();
    cargarTipoNave(nav);
    strcpy(nav->estado, "Lista para su uso");
    nav->cantVuelosRealizados  = 0;
    nav->horasAcumuladasVuelo = 0;

    mostrarDatosNave(*nav);
    fwrite(nav, sizeof(nave),1, archi);



    fclose(archi);
}



void mostrarNaves()
{


    int operador = -1;
    char strOpcion[maxCaracteres];

    mostrarListaOpcionesMostrarNave();

    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantEstadosNave);

        if (operador > minimaCantidadOpciones && operador < cantEstadosNave)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        mostrarArchivoNaves();
        break;
    case 2:
        mostrarNavesEnMision();
        break;
    case 3:
        mostrarNavesEnMantenimiento();
        break;
    case 4:
        mostrarNavesListas();
        break;
    case 5:
        mostrarNavesRetiradas();
        break;

    }
}

void mostrarArchivoNaves()
{

    FILE * archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        mostrarDatosNave(nav);

    }

    fclose(archi);
}

void mostrarNavesEnMision()
{

    int veces = 0;
    FILE * archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        if(strcmp(nav.estado,"Mision") == 0)
        {

            mostrarDatosNave(nav);
            veces++;
        }

    }
    if(veces ==0)
    {
        printf("\nNo hay ninguna nave en mision\n");
    }

    fclose(archi);
}


void mostrarNavesEnMantenimiento()
{
    int veces = 0;
    FILE * archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        if (strcmp(nav.estado, "Mantenimiento") == 0)
        {
            mostrarDatosNave(nav);
            veces++;

        }
    }

    if(veces == 0)
    {
        printf("\nActualmente no hay naves en mantenimiento\n");
    }

    fclose(archi);
}

void mostrarNavesRetiradas()
{
    int veces = 0;
    FILE * archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {
        if(strcmp(nav.estado,"De baja") == 0)

            mostrarDatosNave(nav);
        veces++;

    }
    if(veces == 0)
    {

        printf("\nActualmente no hay naves dadas de baja\n");
    }

    fclose(archi);
}

void mostrarNavesListas()
{
    int veces = 0;
    FILE * archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        if(strcmp(nav.estado, "Lista para su uso") == 0)
        {
            mostrarDatosNave(nav);
            veces++;
        }
    }

    if (veces == 0)
    {
        printf("\nActualmente no hay naves listas para usar\n");
    }

    fclose(archi);
}


void mostrarListaOpcionesMostrarNave()
{
    printf("\n Seleccione la opcion que desee\n");
    printf("|1| Mostrar todas las naves\n");
    printf("|2| Mostrar naves en mision\n");
    printf("|3| Mostrar naves en mantenimiento\n");
    printf("|4| Mostrar naves listas\n");
    printf("|5| Mostrar naves retiradas\n");
}


//------------------MOSTRAR DATOS NAVE------------------------------------------------

void mostrarDatosNave(nave nav)
{

    printf("\n\nID------------------------------ %i", nav.ID);
    printf("\nTIPO DE NAVE---------------------- %s", nav.tipoNave);
    printf("\nESTADO---------------------------- %s", nav.estado);
    printf("\nHORAS ACUMULADAS------------------ %i", nav.horasAcumuladasVuelo);
    printf("\nVUELOS REALIZADOS----------------- %i\n\n", nav.cantVuelosRealizados);

}


void buscarNavePorId()
{
    menuIDNave();
    int id = idBuscadoNave();


    FILE* archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {
        if(nav.ID == id)
        {

            mostrarDatosNave(nav);
            break;
        }
    }
    fclose(archi);
}




void mostrarListaIDNave()
{
    FILE* archi = fopen(archiNave, "rb");
    nave nav;

    while (fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        printf("ID: %i\n", nav.ID);
    }

    fclose(archi);
}



void menuIDNave()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    printf("\nInsertar operacion a realizar: \n");

    printf("\n|1|  Para ver menu de id \n|2|  Para seguir\n");
    fflush(stdin);

    printf("\nOPCION: ");
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadMenu);

        if (operador > minimaCantidadOpciones && operador < maxCantidadMenu)
        {
            break;
        }
    }


    if (operador == 1)
    {
        printf("\n");

        mostrarListaIDNave();

        printf("\n");
    }

    else if (operador == 2)
    {
        return;

    }


}




void menuModificacionesNave()
{


    printf("\n|1| Modificar tipo de Nave \n");
    printf(  "|2| Modificar Estado\n");
    printf(  "|3| Modificar cantidad de vuelos realizados\n");
    printf(  "|4| Modificar horas de vuelo acumuladas\n");


}


void modificarNave()
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    FILE * archi = fopen(archiNave, "r+b");

    printf("Seleccione el aspecto que desea modificar de la nave: ");
    menuModificacionesNave();
    fflush(stdin);

    printf("\nOPCION: ");
    gets(strOpcion);

    while(operador < 0)
    {
        operador = -1;
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadModificacionesNave);

        if (operador > minimaCantidadOpciones && operador < maxCantidadModificacionesNave)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        cambiarTipoNave();
        break;

    case 2:
        cambiarEstadoNave();
        break;

    case 3:
        cambiarVuelosHechosNave();
        break;

    case 4:
        cambiarHorasVueloAcumuladasNave();
        break;


    default:
        printf("El numero ingresado no corresponde con las opciones");
        break;
    }

    fclose(archi);
}


void cambiarTipoNave()
{
    menuIDNave();
    int id = idBuscadoNave();
    nave nav;

    FILE * archi = fopen(archiNave, "r+b");

    while (fread(&nav, sizeof(nave),1, archi) > 0)
    {

        if(nav.ID == id)
        {

            fseek(archi,sizeof(nave) * -1, SEEK_CUR);

            cargarTipoNave(&nav);

            fwrite(&nav, sizeof(nave),1, archi);

            mostrarDatosNave(nav);
            break;

        }
    }

    fclose(archi);
}





void cambiarHorasVueloAcumuladasNave()
{
    menuIDNave();
    int id = idBuscadoNave();
    nave nav;
    FILE * archi = fopen(archiNave, "r+b");

    while (fread(&nav, sizeof(nave),1, archi))
    {

        if(nav.ID == id)
        {

            fseek(archi,sizeof(nave) * -1, SEEK_CUR);

            cargarHorasVueloAcumuladasNave(&nav);

            fwrite(&nav, sizeof(nave),1, archi);

            mostrarDatosNave(nav);
            break;
        }
    }

    fclose(archi);
}



void cargarHorasVueloAcumuladasNave(nave* nav)
{

    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nCantidad de horas de vuelo acumuladas\n HORAS:  ");
    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadHoras);

        if (operador >= minimaCantidadOpciones && operador < maxCantidadHoras)
        {
            nav->horasAcumuladasVuelo = operador;
            break;
        }
    }
}




void cargarCantVuelosHechosNave(nave* nav)
{

    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nCantidad de vuelos realizados\n VUELOS ");
    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxcantidadViajes);

        if (operador >= minimaCantidadOpciones && operador < maxcantidadViajes)
        {
            nav->cantVuelosRealizados = operador;
            break;
        }
    }
}


void cambiarVuelosHechosNave()
{
    menuIDNave();
    int id = idBuscadoNave();
    nave nav;
    FILE * archi = fopen(archiNave, "r+b");

    while (fread(&nav, sizeof(nave),1, archi))
    {

        if(nav.ID == id)
        {

            fseek(archi,sizeof(nave) * -1, SEEK_CUR);

            cargarCantVuelosHechosNave(&nav);

            fwrite(&nav, sizeof(nave),1, archi);

            mostrarDatosNave(nav);
            break;
        }
    }

    fclose(archi);
}




void menuOpcionesFuncionesNave()
{


    printf("|1| CARGAR NUEVA NAVE\n");
    printf("|2| BUSCAR NAVE POR ID\n");
    printf("|3| CAMBIAR ESTADO NAVE\n");
    printf("|4| MODIFICAR NAVE\n");
    printf("|5| MOSTRAR NAVES \n");
    printf("|6| CONSULTAR NAVE\n");

}

void funcionNaves()
{
    nave nav;


    char valor[] = "si";
    int operador;
    char strOpcion[maxCaracteres];

    while(strcmp(valor, "si") == 0)
    {

        operador = -1;

        printf("\nInsertar operacion a realizar \n");

        menuOpcionesFuncionesNave();
        fflush(stdin);

        printf("\nOPCION: ");
        gets(strOpcion);


        while(operador < 0)
        {
            operador = validacionNumeros(strOpcion,minimaCantidadOpciones,6);

            if (operador > minimaCantidadOpciones && operador <= 6)
            {
                break;
            }
        }


        switch(operador)
        {

        case 1:
            cargarNuevaNave(&nav);

            break;

        case 2:
            buscarNavePorId();
            break;

        case 3:
            cambiarEstadoNave();
            break;

        case 4:
            modificarNave();
            break;

        case 5:
            mostrarNaves();
            break;
        case 6:
            consultarNaves();

            break;
        }

        printf("\n Ingrese 'si', para hacer una nueva operacion con naves\n Ingrese 'no', para dejar de operar con naves\n ");
        fflush(stdin);
        printf("\nRESPUESTA: ");
        gets(valor);


        while (strcmp(valor, "si") != 0 && strcmp(valor, "no") != 0 )
        {
            printf("Ingrese una opcion valida\n ");
            fflush(stdin);

            printf("\nRESPUESTA: ");
            gets(valor);
        }
    }

}

void consultarNaves()
{

    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");

    menuConsultasNave();
    fflush(stdin);

    printf("\nOPCION: ");
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,5);

        if (operador > minimaCantidadOpciones && operador < 5)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        buscarNavePorId();
        break;

    case 2:
        buscarNavePorTipo();
        break;

    case 3:
        buscarNavePorVuelos();
        break;

    case 4:
        buscarNavePorHoras();
        break;

    case 5:
        buscarNavesPorEstado();
        break;


    default:
        printf("El numero ingresado no corresponde con las opciones");
        break;
    }


}

void menuConsultasNave()
{

    printf("\n|1| Buscar nave por ID\n");
    printf("|2| Buscar nave por Tipo\n");
    printf("|3| Buscar nave por Vuelos\n");
    printf("|4| Buscar nave por Horas\n");
    printf("|5| Buscar nave por Estado\n");

}


void buscarNavesPorEstado()
{

    nave nav;
    nave aux;
    int veces = 0;


    cargarEstado(&aux);

    FILE * archi = fopen(archiNave, "rb");

    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        if (strcmp(nav.estado, aux.estado) == 0)
        {

            mostrarDatosNave(nav);
            veces++;
        }

    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }

}

void buscarNavePorTipo()
{

    nave nav;
    nave aux;
    int veces = 0;

    cargarTipoNave(&aux);

    FILE * archi = fopen(archiNave, "rb");

    while (fread(&nav, sizeof(nave), 1, archi) >0)
    {

        if (strcmp(nav.tipoNave, aux.tipoNave) == 0)
        {

            mostrarDatosNave(nav);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }

    fclose(archi);
}



void buscarNavePorVuelos()
{


    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");

    menuConsultaViajesAstro();
    printf("\nOPCION: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantidadTipoBusquedaEdad);

        if (operador > minimaCantidadOpciones && operador < cantidadTipoBusquedaEdad)
        {
            break;
        }
    }

    switch(operador)
    {

    case 1:
        consultarVuelosExactoNave();
        break;

    case 2:
        consultarMayoresVuelosNave();
        break;
    case 3:
        consultarMenoresVuelosNAve();
        break;

    }

}


void consultarVuelosExactoNave()
{

    int valido = 0;
    nave nav;
    nave aux;
    int veces = 0;

    FILE* archi = fopen(archiNave,"rb");


    mostrarListaVuelosNave();

    while (valido == 0)
    {
        cargarCantVuelosHechosNave(&aux);
        valido = validarVuelosNave(aux.cantVuelosRealizados);

    }
    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {


        if ( nav.cantVuelosRealizados == aux.cantVuelosRealizados)
        {

            mostrarDatosNave(nav);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }

}

int validarVuelosNave(int vuelos)
{

    FILE * archi = fopen(archiNave, "rb");
    nave nav;

    while (fread(&nav, sizeof(nave),1, archi) > 0)
    {


        if (nav.cantVuelosRealizados == vuelos)
        {

            return 1;
        }

    }
    return 0;
}

void mostrarListaVuelosNave()
{

    nave nav;
    FILE * archi = fopen(archiNave, "rb");


    printf("\nLista de Cantidad de Vuelos Realizados \n");

    while (fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        printf("- %i\n", nav.cantVuelosRealizados);

    }

    fclose(archi);

}


void consultarMayoresVuelosNave()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la cantidad de vuelos minima\n VUELOS: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadHoras);

        if (operador > minimaCantidadOpciones && operador < maxCantidadHoras)
        {

            break;
        }
    }
    FILE *archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi))
    {



        if (nav.cantVuelosRealizados >= operador)
        {

            mostrarDatosNave(nav);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }
    fclose(archi);
}

void consultarMenoresVuelosNAve()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la maxima cantidad de vuelos\n VUELOS: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadHoras);

        if (operador > minimaCantidadOpciones && operador < maxCantidadHoras)
        {

            break;
        }
    }
    FILE *archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi))
    {



        if (nav.cantVuelosRealizados <= operador)
        {

            mostrarDatosNave(nav);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }
    fclose(archi);
}



void buscarNavePorHoras()
{


    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");

    menuConsultasHorasNave();

    printf("\nOPCION: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantidadTipoBusquedaEdad);

        if (operador > minimaCantidadOpciones && operador < cantidadTipoBusquedaEdad)
        {
            break;
        }
    }

    switch(operador)
    {

    case 1:
        consultarHorasExactoNave();
        break;

    case 2:
        consultarMayoresHorasNave();
        break;
    case 3:
        consultarMenoresHorasNave();
        break;

    }

}

void menuConsultasHorasNave()
{

    printf("\n|1| Buscar Horas de vuelo Exactas\n");
    printf("|2| Buscar Horas de vuelo mayores\n");
    printf("|3| Buscar Horas de vuelo Menores\n");

}

void  consultarHorasExactoNave()
{

    int valido = 0;
    nave nav;
    nave aux;
    int veces = 0;

    FILE* archi = fopen(archiNave,"rb");


    mostrarListaHorasNave();

    while (valido == 0)
    {
        cargarHorasVueloAcumuladasNave(&aux);
        valido = validarHorasNave(aux.horasAcumuladasVuelo);

    }
    while(fread(&nav, sizeof(nave), 1, archi) > 0)
    {


        if ( nav.horasAcumuladasVuelo == aux.horasAcumuladasVuelo)
        {

            mostrarDatosNave(nav);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }

}

int validarHorasNave(int vuelos)
{

    FILE * archi = fopen(archiNave, "rb");
    nave nav;

    while (fread(&nav, sizeof(nave),1, archi) > 0)
    {


        if (nav.horasAcumuladasVuelo == vuelos)
        {

            return 1;
        }

    }
    return 0;
}

void mostrarListaHorasNave()
{

    nave nav;
    FILE * archi = fopen(archiNave, "rb");


    printf("\nLista de Cantidad de Horas en Vuelo \n");

    while (fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        printf("- %i\n", nav.horasAcumuladasVuelo);

    }

    fclose(archi);

}


void consultarMayoresHorasNave()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la cantidad de horas minima\n HORAS: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxcantidadViajes);

        if (operador > minimaCantidadOpciones && operador < maxcantidadViajes)
        {

            break;
        }
    }
    FILE *archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi))
    {



        if (nav.horasAcumuladasVuelo >= operador)
        {

            mostrarDatosNave(nav);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }
    fclose(archi);
}

void consultarMenoresHorasNave()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la maxima cantidad de horas\n HORAS: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxcantidadViajes);

        if (operador > minimaCantidadOpciones && operador < maxcantidadViajes)
        {

            break;
        }
    }
    FILE *archi = fopen(archiNave, "rb");

    nave nav;

    while(fread(&nav, sizeof(nave), 1, archi))
    {



        if (nav.horasAcumuladasVuelo <= operador)
        {

            mostrarDatosNave(nav);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }
    fclose(archi);
}





void cambiarEstadoNave()
{


    menuIDNave();
    int id = idBuscadoNave();
    nave nav;
    FILE * archi = fopen(archiNave, "r+b");

    while (fread(&nav, sizeof(nave),1, archi))
    {

        if(nav.ID == id)
        {

            fseek(archi,sizeof(nave) * -1, SEEK_CUR);

            cargarEstado(&nav);
            fwrite(&nav, sizeof(nave),1, archi);

            mostrarDatosNave(nav);
            break;
        }
    }

    fclose(archi);



}



void navesPredeterminadas()
{

    FILE * archi = fopen(archiNave, "wb");

    nave navPredeterminado1;


    navPredeterminado1.ID = 1001;
    strcpy(navPredeterminado1.tipoNave, "Starship");
    strcpy(navPredeterminado1.estado, "Mantenimiento");
    navPredeterminado1.horasAcumuladasVuelo = 114;
    navPredeterminado1.cantVuelosRealizados = 7;


    fwrite(&navPredeterminado1, sizeof(nave),1,archi);

    nave navPredeterminado2;

    navPredeterminado2.ID = 1002;
    strcpy(navPredeterminado2.tipoNave, "Falcon 9");
    strcpy(navPredeterminado2.estado, "Mision");
    navPredeterminado2.horasAcumuladasVuelo = 55;
    navPredeterminado2.cantVuelosRealizados = 3;


    fwrite(&navPredeterminado2, sizeof(nave),1,archi);


    nave navPredeterminado3;

    navPredeterminado3.ID = 1003;
    strcpy(navPredeterminado3.tipoNave, "Falcon Heavy");
    strcpy(navPredeterminado3.estado, "Mision");
    navPredeterminado3.horasAcumuladasVuelo = 200;
    navPredeterminado3.cantVuelosRealizados = 11;


    fwrite(&navPredeterminado3, sizeof(nave),1,archi);


    nave navPredeterminado4;


    navPredeterminado4.ID = 1004;
    strcpy(navPredeterminado4.tipoNave, "Falcon 9");
    strcpy(navPredeterminado4.estado, "De baja");
    navPredeterminado4.horasAcumuladasVuelo = 350;
    navPredeterminado4.cantVuelosRealizados = 17;


    fwrite(&navPredeterminado4, sizeof(nave),1,archi);



    fclose(archi);
}
