#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"




void menuOpcionesFuncionesMisiones()
{


    printf("|1| CARGAR NUEVA MISION\n");
    printf("|2| BUSCAR MISION POR ID\n");
    printf("|3| CAMBIAR ESTADO DE MISION\n");
    printf("|4| MODIFICAR MISION\n");
    printf("|5| MOSTRAR MISIONES \n");
    printf("|6| CONSULTAR MISION \n");

}

void funcionMisiones()
{
    stMision misio;


    char valor[] = "si";
    int operador;
    char strOpcion[maxCaracteres];

    while(strcmp(valor, "si") == 0)
    {

        operador = -1;
        printf("Insertar operacion a realizar:\n");

        menuOpcionesFuncionesMisiones();
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
            cargarNuevaMision(&misio);
            break;

        case 2:
            buscarMisionPorId();
            break;

        case 3:
            cambiarEstadoMision();
            break;

        case 4:
            modificarMision();
            break;

        case 5:
            mostrarMisiones();
            break;

        case 6:
            consultarMisiones();
            break;
        }

        printf("\n Ingrese 'si', para hacer una nueva operacion con misiones\n Ingrese 'no', para dejar de operar con misiones \n");
        fflush(stdin);
        printf("\nOPCION: ");
        gets(valor);


        while (strcmp(valor, "si") != 0 && strcmp(valor, "no") != 0 )
        {
            printf("Ingrese una opcion valida: ");
            fflush(stdin);
            printf("\nOPCION: ");
            gets(valor);
        }
    }

}





int cargarNuevaMision(stMision * misio)
{

    FILE * archi = fopen(archiMision, "ab");


    misio->ID = ultimoIdMision();
    printf("\nID: %i", misio->ID);

    int idNave = cargarIdNaveMision(misio);

    if (idNave == 0)
    {
        return 0;

    }

    strcpy(misio->estado,"Listo");
    printf("ID NAVE: %i\n", misio->iDNave);


    cargarCargamentoMision(misio);

    cargarDestinoMision(misio);


    int idAstros = cargarTripulantesMision(misio);

    if (idAstros == 0)
    {
        return 0;
    }

    cargarDetalleMision(misio);

    mostrarDatosMision(misio);

    fwrite(misio, sizeof(stMision), 1, archi);



    cambiarEstadoNaveEnMision(misio->iDNave);

    cambiarHorasDeVueloNave ( misio->iDNave, misio->destino );

    cambiarHorasDeVueloAstro(misio->destino, misio->tripulacion[0], misio->tripulacion[1], misio->tripulacion[2]);

    fclose(archi);
}

void cambiarHorasDeVueloAstro(char lugar[], int id, int id1, int id2)
{

    char ArrDestino[cantDestinos][maxCaracteres];
    menuDestino(ArrDestino);



    int posicion = buscarPosicionLugar(ArrDestino, lugar);

    cambiarVuelosHechosAstronauta(id);
    cambiarHorasAstronautas(posicion, id);
    cambiarVuelosHechosAstronauta(id1);
    cambiarHorasAstronautas(posicion, id1);
    cambiarVuelosHechosAstronauta(id2);
    cambiarHorasAstronautas(posicion, id2);


}


void cambiarHorasAstronautas(int posicion, int id)
{

    int horasViaje[100];
    menuHorasDeViaje(horasViaje);




    FILE * archi = fopen(archiAstronauta,"r+b");
    astronauta astro;

    int nuevaHora;
    int nuevoAcumulado;


    while(fread(&astro, sizeof(astronauta), 1, archi))
    {


        if (astro.ID == id)
        {

            if (posicion == 0)
            {

                nuevoAcumulado =  astro.horasAcumuladasEEI + estadiaEnIEE;
                astro.horasAcumuladasEEI = nuevoAcumulado;

            }

            nuevaHora = astro.horasVueloAcumuladas + horasViaje[posicion];

            astro.horasVueloAcumuladas = nuevaHora;

            fseek(archi, sizeof(astronauta) * -1, SEEK_CUR);
            fwrite(&astro, sizeof(astronauta),1,archi);
            break;

        }

    }
    fclose(archi);
}



void cambiarVuelosHechosAstronauta(int id)
{

    astronauta astro;
    int nuevoVuelo;

    FILE * archi = fopen(archiAstronauta,"r+b");

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {


        if (astro.ID == id)
        {

            nuevoVuelo = astro.misionesEspacialesRealizadas + 1;

            astro.misionesEspacialesRealizadas = nuevoVuelo;

            fseek(archi, sizeof(astronauta) * -1, SEEK_CUR);
            fwrite(&astro, sizeof(astronauta),1,archi);
            break;

        }
    }


    fclose(archi);

}

void menuDestino(char menuDestinoMision[][maxCaracteres])
{

    strcpy(menuDestinoMision[0], "Estacion Espacial Internacional");
    strcpy(menuDestinoMision[1], "Estratosfera");
    strcpy(menuDestinoMision[2], "Saturno");
    strcpy(menuDestinoMision[3], "Luna");
    strcpy(menuDestinoMision[4], "Marte");
    strcpy(menuDestinoMision[5], "El Inifinito y mas alla");


}

void menuHorasDeViaje(int horasDeViaje[])
{

    horasDeViaje[0] = 6;
    horasDeViaje[1] = 2;
    horasDeViaje[2] = 80;
    horasDeViaje[3] = 24;
    horasDeViaje[4] = 55;
    horasDeViaje[5] = 100;

}

int buscarPosicionLugar(char cargamentos[][maxCaracteres], char lugar[])
{

    int i = 0;

    for (i = 0; i < cantCargamentos; i++)
    {

        if (strcmp(cargamentos[i], lugar) == 0)
        {

            return i;
        }
    }
    return -1;
}




//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------






int cargarTripulantesMision(stMision * misio)
{


    int tripulantes[100];
    int i = 0 ;



    int validos = mostrarListaTripulantesActivos(tripulantes);



    if (validos < 3)
    {
        printf("No hay suficiente tripulacion como para hacer una mision");
        return 0;
    }


    while (i <= 2)
    {

        char strOpcion[maxCaracteres];
        int operador;
        printf("ID: ");
        fflush(stdin);
        gets(strOpcion);

        int maxIdAstronauta =  ultimoIdAstro() -1;

        operador = validacionNumeros(strOpcion, minIdAstro,maxIdAstronauta);

        if (operador >= minIdAstro && operador <= maxIdAstronauta)
        {
            int  valido = validarIdAstronautaMision(tripulantes, operador, validos);

            if (valido == 1)
            {
                misio->tripulacion[i] = operador;
            }
            else
            {
                printf("ID no disponible\n");
            }
        }
        i++;
    }
    return 1;
}

int validarIdAstronautaMision(int tripulates[], int operador, int validos)
{

    int i;

    for(i = 0; i< validos; i++)
    {

        if (operador == tripulates[i])
        {
            return 1;
        }
    }

    return 0;
}

int mostrarListaTripulantesActivos(int tripulantes[])
{

    FILE * archi = fopen(archiAstronauta, "rb");
    astronauta astro;
    int i = 0;

    printf("\nLista de ID de astronautas disponibles\n");
    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (astro.estado ==  1)
        {

            int valido = confirmacion(astro.ID);

            if (valido == 1)
            {
                printf("- %i\n", astro.ID);
                tripulantes[i] = astro.ID;
                i++;

            }


        }
    }

    fclose(archi);
    return i;
}

int confirmacion(int dato)
{

    FILE * archi = fopen(archiMision, "rb");
    stMision misio;
    int i = 0;
    while (fread(&misio, sizeof(stMision), 1, archi)> 0)
    {


        for(i = 0; i <= 2; i++)
        {
            if (misio.tripulacion[i] == dato && (strcmp(misio.estado,"Listo") == 0 || strcmp(misio.estado, "En vuelo") == 0 ))
            {
                fclose(archi);
                return 0;
            }
        }


    }
    fclose(archi);
    return 1;
}

int cargarIdNaveMision(stMision* misio)
{
    int valido = 0;
    int operador = -1;
    char strOpcion[maxCaracteres];
    int idDisponibles[100];
    int validos;

    int maxIdNave = ultimoIdNave() - 1;

    printf("\nIngrese el ID de la nave\n");
    validos = mostrarNavesDisponibles(idDisponibles);

    if (validos < 0)
    {
        return 0;
    }




    while (valido == 0)
    {
        printf("\nID: ");
        fflush(stdin);
        gets(strOpcion);

        operador = validacionNumeros(strOpcion, minIdNave, maxIdNave);

        if (operador >= minIdNave && operador <= maxIdNave)
        {
            valido = validarIdNaveMision(idDisponibles, operador, validos);

            if (valido == 1)
            {
                break;
            }
            else
            {
                printf("ID no disponible\n");
            }
        }
    }


    misio->iDNave = operador;

}



void cambiarEstadoNaveEnMision(int id)
{


    FILE * archi = fopen(archiNave, "r+b");
    nave nav;
    char estadoNuevo[maxCaracteres] = "Mision";

    while (fread(&nav, sizeof(nave), 1, archi) > 0)
    {

        if(nav.ID == id)
        {


            strcpy(nav.estado,estadoNuevo);

            fseek(archi, sizeof(nave) * -1, SEEK_CUR);
            fwrite(&nav, sizeof(nave),1,archi);

            break;
        }
    }

    fclose(archi);
}

void cambiarHorasDeVueloNave(int id, char lugar[])
{

    char ArrDestino[cantDestinos][maxCaracteres];
    menuDestino(ArrDestino);


    int posicion = buscarPosicionLugar(ArrDestino, lugar);

    cambiarVuelosHechosNaveMision(id);
    cambiarHorasNaveMisio(posicion, id);


}

void cambiarVuelosHechosNaveMision(int id)
{

    nave nav;
    int nuevoVuelo;

    FILE * archi = fopen(archiNave,"r+b");

    while(fread(&nav, sizeof(nave), 1, archi))
    {


        if (nav.ID == id)
        {

            nuevoVuelo = nav.cantVuelosRealizados + 1;

            nav.cantVuelosRealizados = nuevoVuelo;

            fseek(archi, sizeof(nave) * -1, SEEK_CUR);
            fwrite(&nav, sizeof(nave),1,archi);
            break;

        }
    }


    fclose(archi);

}


void cambiarHorasNaveMisio(int posicion, int id)
{

    int horasViaje[100];
    menuHorasDeViaje(horasViaje);




    FILE * archi = fopen(archiNave,"r+b");
    nave nav;

    int nuevaHora;


    while(fread(&nav, sizeof(nave), 1, archi))
    {


        if (nav.ID == id)
        {

            nuevaHora = nav.horasAcumuladasVuelo + horasViaje[posicion];

            nav.horasAcumuladasVuelo = nuevaHora;

            fseek(archi, sizeof(nave) * -1, SEEK_CUR);
            fwrite(&nav, sizeof(nave),1,archi);

            break;

        }
    }

    fclose(archi);
}


void mostrarDatosMision(stMision *misio)
{
    printf("\nID------------------------------- %i",misio->ID);
    printf("\nID NAVE-------------------------- %i",misio->iDNave);
    printf("\nESTADO--------------------------- %s",misio->estado);
    printf("\nDESTINO-------------------------- %s",misio->destino);
    printf("\nTRIPULACION---------------------- %i - %i - %i",misio->tripulacion[0], misio->tripulacion[1],misio->tripulacion[2]);
    printf("\nCARGAMENTO----------------------- %s",misio->cargamento);
    printf("\nDETALLE-------------------------- %s\n\n",misio->detalleMision);

}

void misionPredeterminada()
{

    FILE * archi = fopen(archiMision, "wb");

    stMision misio;

    misio.ID = 1;
    misio.iDNave = 1002;
    strcpy(misio.estado,"Listo");
    strcpy(misio.destino,"Saturno");
    strcpy(misio.cargamento,"Rober");
    misio.tripulacion[0] = 101;
    misio.tripulacion[1] = 102;
    misio.tripulacion[2] = 104;
    strcpy(misio.detalleMision,"El objetivo de la mision es poder descubrir nuevas tierras en otros planteas");


    fwrite(&misio, sizeof(stMision), 1, archi);

    fclose(archi);


}


int tamanoArchiMisio()
{
    FILE *fich =fopen(archiMision,"rb");

    fseek(fich, 0, SEEK_END);

    return ftell(fich)/sizeof(stMision);
    fclose(fich);
}

int ultimoIdMision()
{
    stMision aux;

    FILE *archi = fopen(archiMision,"rb");
    if(archi == NULL || tamanoArchiMisio() == 0)
    {
        fclose(archi);
        return 1;
    }

    fseek(archi,(sizeof(stMision) * -1),SEEK_END);
    fread(&aux,sizeof(stMision),1,archi);

    return aux.ID + 1;

}


int mostrarNavesDisponibles(int idDisponibles[])
{
    FILE* archi = fopen(archiNave, "rb");
    int i = 0;
    int veces = 0;
    nave nav;
    printf("Lista de naves disponibles\n");

    while (fread(&nav, sizeof(nave), 1, archi) > 0)
    {
        if (strcmp(nav.estado, "Lista para su uso") == 0)
        {
            printf("\n- %i", nav.ID);
            idDisponibles[i] = nav.ID;
            i++;
            veces++;
        }
    }

    if (veces == 0)
    {
        printf("\nNo hay naves disponibles en este momento");
        fclose(archi);
        return -1;
    }

    fclose(archi);
    return i;
}
int validarIdNaveMision(int idDisponibles[], int operador, int validos)
{

    int i = 0;

    for(i = 0; i< validos; i++)
    {
        if (operador == idDisponibles[i])
        {
            return 1;
        }
    }

    return 0;
}

void menuCargamento(char menuCargamentoMision[][maxCaracteres])
{

    strcpy(menuCargamentoMision[0], "Satelite");
    strcpy(menuCargamentoMision[1], "Recursos");
    strcpy(menuCargamentoMision[2], "Rober");
    strcpy(menuCargamentoMision[3], "Colectivo");
    strcpy(menuCargamentoMision[4], "StarLink");
    strcpy(menuCargamentoMision[5], "'Clasificado'");


}


void cargarCargamentoMision(stMision * misio)
{


    int operador = -1;
    char strOpcion[maxCaracteres];

    char cargamentos[cantCargamentos][maxCaracteres];
    menuCargamento(cargamentos);


    printf("Seleccione un numero asociado a un cargamento\n");
    mostrarMenuCargamento(cargamentos);

    fflush(stdin);

    printf("\nOPCION: ");
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantCargamentos);

        if (operador >= minimaCantidadOpciones && operador <= cantCargamentos)
        {
            strcpy(misio->cargamento,cargamentos[operador - 1]);

            break;
        }
    }


}



void mostrarMenuCargamento(char menuCargamentoMision[][maxCaracteres])
{

    int  i= 0;
    int pos = 1;

    for (i = 0; i< cantCargamentos; i++)
    {

        printf("\n|%i| %s", pos, menuCargamentoMision[i]);
        pos++;
    }
    printf("\n");

}



void cargarDestinoMision(stMision * misio)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    char destino[cantDestinos][maxCaracteres];
    menuDestino(destino);


    printf("Seleccione un numero asociado a un destino\n");
    mostrarMenuDestino(destino);
    fflush(stdin);

    printf("\nOPCION: ");
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantDestinos);

        if (operador >= minimaCantidadOpciones && operador <= cantDestinos)
        {
            strcpy(misio->destino,destino[operador - 1]);
            break;
        }
    }

}




void mostrarMenuDestino(char menuDestinoMision[][maxCaracteres])
{

    int  i;
    int j = 1;
    for (i = 0; i < cantDestinos; i++)
    {

        printf("\n|%i| %s", j, menuDestinoMision[i]);
        j++;
    }
    printf("\n");

}


void cargarDetalleMision(stMision * misio)
{

    char detalle[detalleDeMision];

    printf("Ingrese el detalle de la mision\n DETALLE: ");

    fgets(detalle, detalleDeMision,stdin);

    strcpy(misio->detalleMision, detalle);

}


void mostrarArchivoMisiones()
{



    stMision misio;
    FILE*archi = fopen(archiMision, "rb");

    while(fread(&misio, sizeof(stMision),1, archi) > 0)
    {

        printf("\n");
        mostrarDatosMision(&misio);
    }




    fclose(archi);
}


//--------------------BUSCAR POR ID----------------------

void buscarMisionPorId()
{
    menuIDMision();
    int id = idBuscadoMision();


    FILE* archi = fopen(archiMision, "rb");

    stMision misio;

    while(fread(&misio, sizeof(stMision), 1, archi) > 0)
    {
        if(misio.ID== id)
        {

            mostrarDatosMision(&misio);
            break;
        }
    }
    fclose(archi);
}


int idBuscadoMision()
{

    int valido = 0;
    int operador = -1;
    char strOpcion[maxCaracteres];
    int maxIdMision =  ultimoIdMision() -1;

    valido = validacionIDNave(operador);


    while (valido == 0 && (operador < minIdMision || operador > maxIdMision))
    {

        printf("Inserte el ID de la mision\n ID: ");
        fflush(stdin);
        gets(strOpcion);

        operador = validacionNumeros(strOpcion,minIdMision,maxIdMision);

        valido = validacionIDAstro(operador);

        if (operador >= minIdMision && operador <= maxIdMision && valido == 1)
        {

            return operador;

        }
    }

}


void menuIDMision()
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

        mostrarListaIDMision();

        printf("\n");
    }

    else if (operador == 2)
    {
        return;

    }


}


void mostrarListaIDMision()
{
    FILE* archi = fopen(archiMision, "rb");
    stMision misio;

    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {

        printf("ID: %i\n", misio.ID);
    }

    fclose(archi);
}


//-------------------------------CONSULTAS MISIONES------------------------------------





void menuConsultasMision()
{


    printf("\n|1| Buscar Mision por ID \n");
    printf(  "|2| Buscar Mision por estado\n");
    printf(  "|3| Buscar Mision por cargamento\n");
    printf(  "|4| Buscar Mision por destino\n");
    printf(  "|5| Buscar Mision por tipo de nave\n");

}


void consultarMisiones()
{


    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");

    menuConsultasMision();
    fflush(stdin);
    printf("\nOPCION: ");
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadModificacionesMision);

        if (operador > minimaCantidadOpciones && operador < maxCantidadModificacionesMision)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        buscarMisionPorId();
        break;

    case 2:
        buscarMisionPorEstado();
        break;

    case 3:
        buscarMisionPorCargamento();
        break;

    case 4:
        buscarMisionPorDestino();
        break;

    case 5:
        buscarMisionPorTipoNave();
        break;


    default:
        printf("El numero ingresado no corresponde con las opciones");
        break;
    }
}



void buscarMisionPorCargamento()
{

    FILE * archi = fopen(archiMision, "rb");

    stMision misio;
    stMision aux;
    int veces = 0;

    cargarCargamentoMision(&aux);

    while(fread(&misio, sizeof(stMision), 1, archi) > 0)
    {



        if (strcmp(misio.cargamento, aux.cargamento) == 0)
        {


            mostrarDatosMision(&misio);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna mision que cumpla con ese requisito\n");
    }


    fclose(archi);

}

void buscarMisionPorDestino()
{

    FILE * archi = fopen(archiMision, "rb");

    stMision misio;
    stMision aux;
    int veces = 0;

    cargarDestinoMision(&aux);

    while(fread(&misio, sizeof(stMision), 1, archi) > 0)
    {



        if (strcmp(misio.destino, aux.destino) == 0)
        {

            mostrarDatosMision(&misio);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna mision que cumpla con ese requisito\n");
    }


    fclose(archi);

}



int buscarMisionPorTipoAux(int iguales[])
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

            iguales[veces] = nav.ID;
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna nave que cumpla con ese requisito\n");
    }

    fclose(archi);

    return veces;
}



void buscarMisionPorTipoNave()
{
    int iguales[maxCantidadHoras];
    int valis = buscarMisionPorTipoAux(iguales);
    int i = 0;
    stMision misio;
    int oper = 0;

    FILE * archi = fopen(archiMision, "rb");



    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {

        while(i < valis)
        {

            if(iguales[i] == misio.iDNave)
            {

                mostrarDatosMision(&misio);
                oper++;
            }
            i++;
        }
        i = 0;
    }
    if(oper == 0)
    {
        printf("No hay misiones asociadas a naves de ese tipo.");
    }

    fclose(archi);
}

void tiposEstadoMision(char estadosMision[cantEstadosMision][maxCaracteres])
{
    printf("\n");
    strcpy(estadosMision[0], "Listo");
    strcpy(estadosMision[1], "En vuelo");
    strcpy(estadosMision[2], "Retornada");
    strcpy(estadosMision[3], "Cancelada");
    strcpy(estadosMision[4], "Fallida");
}

void mostrarEstadosMision(char estadosMision[cantEstadosMision][maxCaracteres])
{

    int i = 0;
    int pos = 1;

    while (i < cantEstadosMision)
    {


        printf("|%i| %s \n",pos, estadosMision[i]);

        pos++;
        i++;
    }
}


void  cargarEstadoMision(stMision* misio)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    char estadosMision[cantEstadosMision][maxCaracteres];
    tiposEstadoMision(estadosMision);


    printf("Seleccione un numero asociado a un estado\n");
    mostrarEstadosMision(estadosMision);

    fflush(stdin);
    printf("\nOPCION: ");
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantEstados);

        if (operador >= minimaCantidadOpciones && operador <= cantEstadosMision)
        {
            strcpy(misio->estado,estadosMision[operador - 1]);
            break;
        }
    }
}



void buscarMisionPorEstado()
{

    stMision misio;
    stMision aux;
    int veces = 0;


    cargarEstadoMision(&aux);

    FILE * archi = fopen(archiMision, "rb");

    while(fread(&misio, sizeof(stMision), 1, archi) > 0)
    {

        if (strcmp(misio.estado, aux.estado) == 0)
        {
            mostrarDatosMision(&misio);
            veces++;
        }

    }
    if (veces == 0)
    {
        printf("\nNo hay ninguna mision que cumpla con ese requisito\n");
    }

}




void mostrarMisiones()
{


    int operador = -1;
    char strOpcion[maxCaracteres];

    mostrarListaOpcionesMostrarMisiones();

    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantOpcionesMostrarMisiones);

        if (operador > minimaCantidadOpciones && operador < cantOpcionesMostrarMisiones)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        mostrarArchivoMisiones();
        break;
    case 2:
        buscarMisionPorEstado();
        break;
    case 3:
        buscarMisionPorCargamento();
        break;
    case 4:
        buscarMisionPorDestino();
        break;
    }
}




void mostrarListaOpcionesMostrarMisiones()
{
    printf("\n Seleccione la opcion que desee\n");
    printf("|1| Mostrar todas las misiones\n");
    printf("|2| Mostrar misiones por estado\n");
    printf("|3| Mostrar misiones por cargamento\n");
    printf("|4| Mostrar mostrar misiones por destino\n");
}



void modificarMision()
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    FILE * archi = fopen(archiMision, "r+b");

    printf("Seleccione el aspecto que desea modificar de la mision:\n");
    menuModificacionesMision();
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
        cambiarDestinoMision();
        break;

    case 2:
        cambiarCargamentoMision();
        break;

    case 3:
        cambiarDetalleMision();
        break;


    default:
        printf("El numero ingresado no corresponde con las opciones");
        break;
    }

    fclose(archi);
}


void menuModificacionesMision()
{


    printf("\n|1| Modificar Destino\n");
    printf(  "|2| Modificar Cargamento\n");
    printf(  "|3| Modificar Detalle\n");

}


void cambiarDestinoMision()
{
    menuIDMision();
    int id = idBuscadoMision();
    stMision misio;

    FILE * archi = fopen(archiMision, "r+b");

    while (fread(&misio, sizeof(stMision),1, archi))
    {

        if(misio.ID == id)
        {

            fseek(archi,sizeof(stMision) * -1, SEEK_CUR);

            cargarDestinoMision(&misio);

            fwrite(&misio, sizeof(stMision),1, archi);

            mostrarDatosMision(&misio);
            break;
        }
    }

    fclose(archi);
}

void cambiarCargamentoMision()
{
    menuIDMision();
    int id = idBuscadoMision();
    stMision misio;

    FILE * archi = fopen(archiMision, "r+b");

    while (fread(&misio, sizeof(stMision),1, archi))
    {

        if(misio.ID == id)
        {

            fseek(archi,sizeof(stMision) * -1, SEEK_CUR);

            cargarCargamentoMision(&misio);

            fwrite(&misio, sizeof(stMision),1, archi);

            mostrarDatosMision(&misio);
            break;
        }
    }

    fclose(archi);
}


void cambiarDetalleMision()
{
    menuIDMision();
    int id = idBuscadoMision();
    stMision misio;

    FILE * archi = fopen(archiMision, "r+b");

    while (fread(&misio, sizeof(stMision),1, archi))
    {

        if(misio.ID == id)
        {

            fseek(archi,sizeof(stMision) * -1, SEEK_CUR);

            cargarDetalleMision(&misio);

            fwrite(&misio, sizeof(stMision),1, archi);

            mostrarDatosMision(&misio);
            break;
        }
    }

    fclose(archi);
}


void cambiarEstadoMision()
{

    stMision aux;

    printf("\nSeleccione el estado actual de la nave que desea modificar\n");
    cargarEstadoModificacionMision(&aux);


    if (strcmp(aux.estado,"Listo" ) == 0)
    {
        int  id = elegirMisionLista();
        printf("\n");
        if (id > 0)
        {

            cambiarEstadoDesdeListo(id);
        }


    }

    else if (strcmp(aux.estado,"En vuelo" ) == 0)
    {
        int id = elegirMisionEnMision();
        printf("\n");
        if (id  > 0)
        {

            cambiarEstadoDesdeEnVuelo(id);
        }

    }

}

void  cargarEstadoModificacionMision(stMision* misio)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    char estadosMision[2][maxCaracteres];
    tiposEstadoMisionModificacion(estadosMision);


    printf("Seleccione un numero asociado a un estado\n");
    mostrarDosEstados(estadosMision);
    printf("\nOPCION: ");
    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,2);


        if (operador >= minimaCantidadOpciones && operador <= 2)
        {
            strcpy(misio->estado,estadosMision[operador - 1]);

            break;
        }
    }


}




void cambiarEstadoDesdeListo(int id)
{
    FILE* archi = fopen(archiMision, "r+b");

    stMision aux;
    stMision misio;
    stMision aux2;

    printf("\nSeleccione el estado que quiera\n");

    while(fread(&aux2, sizeof(stMision),1 ,archi) > 0){
        if(aux2.ID == id){

            aux.iDNave = aux2.iDNave;
            break;
        }

    }

    cargarEstadoModificacionMisionListo(&aux);




    fseek(archi,0, SEEK_SET);

    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {
        if (misio.ID == id)
        {

            fseek(archi, sizeof(stMision) * -1, SEEK_CUR);
            strcpy(misio.estado, aux.estado);

            fwrite(&misio, sizeof(stMision), 1, archi);
            mostrarDatosMision(&misio);


            break;
        }
    }

    fclose(archi);
}



void  cargarEstadoModificacionMisionListo(stMision* misio)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    char estadosMision[2][maxCaracteres];
    tiposEstadoMisionModificacionListo(estadosMision);

    printf("Seleccione un numero asociado a un estado\n");
    mostrarDosEstados(estadosMision);
    fflush(stdin);
    printf("\nOPCION: ");
    gets(strOpcion);

    char nuevaOpcion[maxCaracteres];


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,2);
        strcpy(nuevaOpcion, estadosMision[operador]);

        if (operador == 1)
        {
            strcpy(misio->estado,estadosMision[0]);
            cambiarNaveALista(misio);
        }

        if (operador == 2)
        {
            strcpy(misio->estado,estadosMision[1]);
            cambiarNaveAMision(misio);
        }
    }


}





void cambiarNaveAMision(stMision * misio)
{

int idNave = 1002;

FILE* archi = fopen(archiNave, "r+b");

nave nav;

while(fread(&nav, sizeof(nave),1,archi) > 0){


    if(nav.ID == idNave){

        strcpy(nav.estado, "Mision");
        fseek(archi, sizeof(nave)* - 1, SEEK_CUR);
        fwrite(&nav, sizeof(nave),1,archi);
        break;
    }

}

fclose(archi);
}


void tiposEstadoMisionModificacion(char estadosMision[cantEstadosMision][maxCaracteres])
{

    printf("\n");
    strcpy(estadosMision[0], "Listo");
    strcpy(estadosMision[1], "En vuelo");


}



int elegirMisionLista()
{


    int operador = -1;
    char strOpcion[maxCaracteres];
    int valido;
    printf("\nSeleccione la mision que desea modificar el estado\n");
    valido = mostrarMisionesListas();
    if (valido < 0)
    {
        return -1;
    }

    int maxIdMisio = ultimoIdMision() - 1;

    fflush(stdin);
    printf("\nID: ");
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minIdMision,maxIdMisio);

        if (operador >= minIdMision && operador <= maxIdMisio)
        {

            return operador;
        }
    }




}


int mostrarMisionesListas()
{

    FILE * archi = fopen(archiMision, "rb");
    stMision misio;
    int veces = 0;
    printf("Lista de Misiones Listas\n");
    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {


        if( strcmp(misio.estado, "Listo") == 0)
        {

            printf("\n- %i", misio.ID);
            veces++;
        }

    }
    if (veces == 0)
    {
        printf("Actualmente no hay misiones Listas \n");
        return -1;
    }
    printf("\n");
    fclose(archi);
}

void tiposEstadoMisionModificacionListo(char estadosMision[2][maxCaracteres])
{

    printf("\n");
    strcpy(estadosMision[0], "Cancelada");
    strcpy(estadosMision[1], "En vuelo");

}


void mostrarDosEstados(char estadosMision[][maxCaracteres])
{

    int i = 0;
    int pos = 1;

    while (i < 2)
    {

        printf("|%i| %s \n",pos, estadosMision[i]);

        pos++;
        i++;
    }
}


void cambiarEstadoAEnVuelo(int id)
{

    stMision misio;
    FILE * archi = fopen(archiMision, "r+b");


    char estadoNuevo[maxCaracteres] = "En vuelo";

    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {

        if(misio.ID == id)
        {

            strcpy(misio.estado,estadoNuevo);

            fseek(archi, sizeof(stMision) * -1, SEEK_CUR);
            fwrite(&misio, sizeof(stMision),1,archi);

            break;
        }
    }

    fclose(archi);


}



void cambiarEstadoACanselada(int id)
{

    stMision misio;
    FILE * archi = fopen(archiMision, "r+b");


    char estadoNuevo[maxCaracteres] = "Cancelada";

    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {

        if(misio.ID == id)
        {

            strcpy(misio.estado,estadoNuevo);

            fseek(archi, sizeof(stMision) * -1, SEEK_CUR);
            fwrite(&misio, sizeof(stMision),1,archi);

            break;
        }
    }

    fclose(archi);


}






void cambiarEstadoDesdeEnVuelo(int id)
{

    stMision aux;
    stMision misio;


    if (id == 0)
    {
        return 0;
    }

    printf("\nSeleccione el estado que quiera\n");
    cargarEstadoModificacionMisionEnMision(&aux);


    FILE* archi = fopen(archiMision, "r+b");


    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {
        if (misio.ID == id)
        {

            fseek(archi, sizeof(stMision) * -1, SEEK_CUR);
            strcpy(misio.estado, aux.estado);

            fwrite(&misio, sizeof(stMision), 1, archi);
            mostrarDatosMision(&misio);


            break;
        }
    }

    fclose(archi);
}

int elegirMisionEnMision()
{




    int operador = -1;
    char strOpcion[maxCaracteres];

    printf("\nSeleccione la mision que desea modificar el estado\n");
    int valido = mostrarMisionesEnVuelo();
    if (valido < 0)
    {
        return -1;
    }
    int maxIdMisio = ultimoIdMision() - 1;

    fflush(stdin);
    printf("\nOPCION: ");
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minIdMision,maxIdMisio);

        if (operador >= minIdMision && operador <= maxIdMisio)
        {

            return operador;
        }
    }

}


int mostrarMisionesEnVuelo()
{

    FILE * archi = fopen(archiMision, "rb");
    stMision misio;
    int veces = 0;
    printf("Lista de Misiones En Vuelo\n");
    while (fread(&misio, sizeof(stMision), 1, archi) > 0)
    {


        if( strcmp(misio.estado, "En vuelo") == 0)
        {

            printf("\n- %i", misio.ID);
            veces++;
        }

    }
    if (veces == 0)
    {
        printf("Actualmente no hay misiones en vuelo \n");
        return -1;
    }
    printf("\n");
    fclose(archi);
}


void  cargarEstadoModificacionMisionEnMision(stMision* misio)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    char estadosMision[2][maxCaracteres];
    tiposEstadoMisionModificacionEnVuelo(estadosMision);

    printf("Seleccione un numero asociado a un estado\n");
    mostrarDosEstados(estadosMision);
    fflush(stdin);
    printf("\nOPCION: ");
    gets(strOpcion);

    char nuevaOpcion[maxCaracteres];


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,2);
        strcpy(nuevaOpcion, estadosMision[operador]);

        if (operador == 1)
        {
            strcpy(misio->estado,estadosMision[0]);
            cambiarNaveALista(misio);

            break;
        }
        if (operador == 2)
        {
            strcpy(misio->estado,estadosMision[1]);
            cambiarNaveALista(misio);
        }
    }


}

void cambiarNaveALista(stMision * misio)
{

int idNave = misio->iDNave;

FILE* archi = fopen(archiNave, "r+b");

nave nav;

while(fread(&nav, sizeof(nave),1,archi) > 0){


    if(nav.ID == idNave){

        strcpy(nav.estado, "Lista para su uso");
        fwrite(&nav, sizeof(nave),1,archi);
        break;
    }

}

fclose(archi);
}

void tiposEstadoMisionModificacionEnVuelo(char estadosMision[2][maxCaracteres])
{

    printf("\n");
    strcpy(estadosMision[0], "Fallida");
    strcpy(estadosMision[1], "Retornada");

}


