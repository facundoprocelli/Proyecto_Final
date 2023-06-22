
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"


void funcionAstronautas()
{

    astronauta astro;


    int operador = -1;
    char valor[] = "si";
    char strOpcion[maxCaracteres];


    while(strcmp(valor, "si") == 0)
    {
        operador = -1;
        printf("Insertar operacion a realizar: \n");
        menuOpcionesFunciones();
        printf("\nOPCION: ");
        fflush(stdin);
        gets(strOpcion);

        while(operador < 0)
        {
            operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantidadOpciones);

            if (operador > minimaCantidadOpciones && operador <= cantidadOpciones)
            {
                break;
            }
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
            modificarAstronauta();
            break;

        case 5:
            mostrarAstronautas();
            break;

        case 6:
            consultarAstronauta();
            break;

        default:
            printf("Numero Incorrecto \n");

            break;
        }

        printf("\n Ingrese 'si', para hacer una nueva operacion con astronautas\n Ingrese 'no', para dejar de operar con astronautas\n ");
        fflush(stdin);
        printf("\nRESPUESTA: ");
        gets(valor);


        while (strcmp(valor, "si") != 0 && strcmp(valor, "no") != 0 )
        {
            printf("Ingrese una opcion valida: \n");
            fflush(stdin);

            printf("\nRESPUESTA: ");
            gets(valor);
        }
    }

}

void menuOpcionesFunciones()
{

    printf("|1| CARGAR ASTRONAUTAS\n");
    printf("|2| BUSCAR ASTRONAUTA POR SU ID\n");
    printf("|3| CAMBIAR ESTADO DE ASTRONAUTA\n");
    printf("|4| MODIFICAR DATOS DEL ASTRONAUTA\n");
    printf("|5| MOSTRAR ASTRONAUTAS\n");
    printf("|6| CONSULTAR ASTRONAUTA\n");

}
//----------------------------CONSULTAR ASTRONAUTA---------------------------------

void consultarAstronauta()
{


    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");
    menuConsultasAstro();

    printf("\nOPCION: ");

    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadModificacionesAstro);

        if (operador > minimaCantidadOpciones && operador < maxCantidadModificacionesAstro)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        buscarAstronautaPorId();
        break;

    case 2:
        buscarAstronautaPorNombre();
        break;

    case 3:
        buscarAstronautaPorApellido();
        break;

    case 4:
        buscarAstronautaPorApodo();
        break;

    case 5:
        buscarAstronautaPorEdad();
        break;

    case 6:
        buscarAstronautaPorNacionalidad();
        break;

    case 7:
        buscarAstronautaPorEspecialidad();
        break;

    case 8:
        buscarAstronautaPorHorasAcumuladas();
        break;

    case 9:
        buscarAstronautaPorHorasEnIEE();
        break;

    case 10:
        buscarAstronautaPorViajes();
        break;

    default:
        printf("El numero ingresado no corresponde con las opciones");
        break;
    }


}


void buscarAstronautaPorNombre()
{

    FILE* archi = fopen(archiAstronauta, "rb");

    astronauta astro;
    char nombre[maxCaracteres];
    int valido = 0;
    int veces = 0;
    int nombreValido = 0;


    fflush(stdin);
    printf("\nIngrese el nombre que desea buscar\n NOMBRE: ");
    gets(nombre);



    valido = validacionString(nombre);
    nombreValido = validarNombreConsulta(nombre);


    while (valido == 0 || nombreValido == 0)
    {
        if (veces == 0)
        {

            mostrarListaNombres();
            veces++;
        }

        printf("Ingrese un nombre valido\n NOMBRE: ");
        fflush(stdin);
        gets(nombre);
        valido = validacionString(nombre);
        nombreValido = validarNombreConsulta(nombre);
    }


    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (strcmp(astro.nombre, nombre) == 0)
        {

            mostrarDatosAstronauta(astro);
        }
    }

    fclose(archi);
}

int  validarNombreConsulta(char nombre[])
{

    FILE* archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        if (strcmp(astro.nombre, nombre) == 0)
        {

            return 1;
        }

    }
    return 0;
    fclose(archi);
}

void mostrarListaNombres()
{
    astronauta astro;
    FILE * archi = fopen(archiAstronauta, "rb");


    printf("\nLista de nombres \n");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("- %s\n", astro.nombre);

    }

    fclose(archi);
}



void buscarAstronautaPorApellido()
{

    FILE* archi = fopen(archiAstronauta, "rb");

    astronauta astro;
    char apellido[maxCaracteres];
    int valido = 0;
    int veces = 0;
    int apellidoValido = 0;


    fflush(stdin);
    printf("\nIngrese el Apellido que desea buscar\n APELLIDO: ");
    gets(apellido);



    valido = validacionString(apellido);
    apellidoValido = validarApellidoConsulta(apellido);


    while (valido == 0 || apellidoValido == 0)
    {
        if (veces == 0)
        {

            mostrarListaApellido();
            veces++;
        }

        printf("Ingrese un apellido valido\n APELLIDO: ");
        fflush(stdin);
        gets(apellido);
        valido = validacionString(apellido);
        apellidoValido = validarApellidoConsulta(apellido);
    }


    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (strcmp(astro.apellido, apellido) == 0)
        {

            mostrarDatosAstronauta(astro);
        }
    }

    fclose(archi);
}

int  validarApellidoConsulta(char apellido[])
{

    FILE* archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        if (strcmp(astro.apellido, apellido) == 0)
        {

            return 1;
        }

    }
    return 0;
    fclose(archi);
}

void mostrarListaApellido()
{
    astronauta astro;
    FILE * archi = fopen(archiAstronauta, "rb");


    printf("\nLista de Apellidos \n");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("- %s\n", astro.apellido);

    }

    fclose(archi);
}


void buscarAstronautaPorApodo()
{

    FILE* archi = fopen(archiAstronauta, "rb");

    astronauta astro;
    char apodo[maxCaracteres];
    int valido = 0;
    int veces = 0;
    int apodoValido = 0;


    fflush(stdin);
    printf("\nIngrese el apodo que desea buscar\n APODO: ");
    gets(apodo);



    valido = validacionString(apodo);
    apodoValido = validarApodoConsulta(apodo);


    while (valido == 0 || apodoValido == 0)
    {
        if (veces == 0)
        {

            mostrarListaApodo();
            veces++;
        }

        printf("Ingrese un apodo valido\n APODO: ");
        fflush(stdin);
        gets(apodo);
        valido = validacionString(apodo);
        apodoValido = validarApodoConsulta(apodo);
    }


    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (strcmp(astro.apodo, apodo) == 0)
        {

            mostrarDatosAstronauta(astro);
        }
    }

    fclose(archi);
}

int  validarApodoConsulta(char apodo[])
{

    FILE* archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        if (strcmp(astro.apodo, apodo) == 0)
        {

            return 1;
        }

    }
    return 0;
    fclose(archi);
}

void mostrarListaApodo()
{
    astronauta astro;
    FILE * archi = fopen(archiAstronauta, "rb");


    printf("\nLista de Apodos \n");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("- %s\n", astro.apodo);

    }

    fclose(archi);
}

void buscarAstronautaPorEdad()
{


    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");
    menuConsultaEdadesAstro();
    printf("\nOPCION: ");

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
        consultarEdadExacta();
        break;

    case 2:
        consultarMayores();
        break;
    case 3:
        consultarMenores();
        break;

    }

}


void consultarEdadExacta()
{

    int valido = 0;
    astronauta astro;
    astronauta aux;
    int veces = 0;

    FILE* archi = fopen(archiAstronauta,"rb");


    mostrarListaEdades();

    while (valido == 0)
    {
        cargarEdad(&aux);
        valido = validarEdadConsulta(aux.edad);

    }
    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (aux.edad == astro.edad)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumple con ese requisito\n");
    }

    fclose(archi);

}

int validarEdadConsulta(int edad)
{

    FILE * archi = fopen(archiAstronauta, "rb");
    astronauta astro;

    while (fread(&astro, sizeof(astronauta),1, archi) > 0)
    {


        if (astro.edad == edad)
        {

            return 1;
        }

    }
    return 0;
    fclose(archi);
}

void mostrarListaEdades()
{

    astronauta astro;
    FILE * archi = fopen(archiAstronauta, "rb");


    printf("\nLista de Edades \n");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("- %i\n", astro.edad);

    }

    fclose(archi);

}

void consultarMayores()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la edad minima\n EDAD: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,edadMinima,edadMaxima);

        if (operador > edadMinima && operador < edadMaxima)
        {

            break;
        }
    }
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.edad >= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }
    fclose(archi);
}

void consultarMenores()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la edad maxima\n EDAD: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,edadMinima,edadMaxima);

        if (operador > edadMinima && operador < edadMaxima)
        {

            break;
        }
    }
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.edad <= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }


    fclose(archi);
}

void menuConsultaEdadesAstro()
{

    printf("\n|1| Buscar por edad exacta");
    printf("\n|2| Buscar Mayores a una edad");
    printf("\n|3| Buscar Menores a una edad\n");

}

void buscarAstronautaPorNacionalidad()
{

    FILE* archi = fopen(archiAstronauta, "rb");
    int veces = 0;

    astronauta astro;
    astronauta aux;


    cargarNacionalidad(&aux);


    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (strcmp(astro.nacionalidad, aux.nacionalidad) == 0)
        {
            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }

    fclose(archi);
}


void buscarAstronautaPorEspecialidad()
{

    FILE * archi = fopen(archiAstronauta, "rb");

    astronauta astro;
    astronauta aux;
    int veces = 0;

    cargarEspecialidad(&aux);

    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {



        if (strcmp(astro.especialidad, aux.especialidad) == 0)
        {


            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }


    fclose(archi);


}

void    menuConsultaHorasAstro()
{

    printf("\n|1| Buscar horas Exactas de vuelo\n");
    printf("|2| Buscar horas mayores\n");
    printf("|3| Buscar Horas menores\n");



}

void  buscarAstronautaPorHorasAcumuladas()
{


    int operador = -1;
    char strOpcion[maxCaracteres];



    printf("\nInsertar operacion a realizar: \n");

    menuConsultaHorasAstro();
    printf("\nOPCION: ");
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
        consultarHorasExactas();
        break;

    case 2:
        consultarMayoresHoras();
        break;
    case 3:
        consultarMenoresHoras();
        break;

    }
}

int validarHorasConsulta(int horas)
{

    FILE * archi = fopen(archiAstronauta, "rb");
    astronauta astro;

    while (fread(&astro, sizeof(astronauta),1, archi) > 0)
    {


        if (astro.horasVueloAcumuladas == horas)
        {

            return 1;
        }

    }
    return 0;
    fclose(archi);
}

void consultarHorasExactas()
{

    int valido = 0;
    astronauta astro;
    astronauta aux;
    int veces = 0;

    FILE* archi = fopen(archiAstronauta,"rb");


    mostrarListaHoras();

    while (valido == 0)
    {
        cargarHorasVueloAcumuladas(&aux);
        valido = validarHorasConsulta(aux.horasVueloAcumuladas);

    }
    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (aux.horasVueloAcumuladas == astro.horasVueloAcumuladas)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumple con ese requisito\n");
    }

    fclose(archi);
}


void consultarMayoresHoras()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese las Horas minimas\n HORAS: ");
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
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.horasVueloAcumuladas >= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }
    fclose(archi);
}

void consultarMenoresHoras()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese las horas maximas\n HORAS: ");
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
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.horasVueloAcumuladas <= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }


    fclose(archi);
}



void mostrarListaHoras()
{

    astronauta astro;
    FILE * archi = fopen(archiAstronauta, "rb");


    printf("\nLista de Horas de Vuelo \n");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("- %i\n", astro.horasVueloAcumuladas);

    }

    fclose(archi);
}

//-----------------------------CONSULTAR ASTRONAUTA-----------------------------




void buscarAstronautaPorHorasEnIEE()
{



    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");

    menuConsultaHorasIEEAstro();

    printf("\nOPCION: ");

    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadHoras);

        if (operador > minimaCantidadOpciones && operador < maxCantidadHoras)
        {
            break;
        }
    }

    switch(operador)
    {

    case 1:
        consultarHorasIEEExacta();
        break;

    case 2:
        consultarMayoresIEE();
        break;
    case 3:
        consultarMenoresIEE();
        break;

    }

}


void consultarHorasIEEExacta()
{

    int valido = 0;
    astronauta astro;
    astronauta aux;
    int veces = 0;

    FILE* archi = fopen(archiAstronauta,"rb");


    mostrarListaIEE();

    while (valido == 0)
    {
        cargarHorasEnEEI(&aux);
        valido = validarHorasIEEConsulta(aux.horasAcumuladasEEI);

    }
    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (aux.horasAcumuladasEEI == astro.horasAcumuladasEEI)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumple con ese requisito\n");
    }

    fclose(archi);
}

int validarHorasIEEConsulta(int horas)
{

    FILE * archi = fopen(archiAstronauta, "rb");
    astronauta astro;

    while (fread(&astro, sizeof(astronauta),1, archi) > 0)
    {


        if (astro.horasAcumuladasEEI == horas)
        {

            return 1;
        }

    }
    return 0;
    fclose(archi);
}

void mostrarListaIEE()
{

    astronauta astro;
    FILE * archi = fopen(archiAstronauta, "rb");


    printf("\nLista de Horas En la IEE \n");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("- %i\n", astro.horasAcumuladasEEI);

    }

    fclose(archi);

}


void consultarMayoresIEE()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese las Horas minimas en la IEE\n HORAS: ");
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
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.horasAcumuladasEEI >= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }
    fclose(archi);
}

void consultarMenoresIEE()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese las horas  maximas en la IEE\n HORAS: ");
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
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.horasAcumuladasEEI <= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }


    fclose(archi);
}


void    menuConsultaHorasIEEAstro()
{

    printf("\n|1| Buscar horas Exactas en la EEI\n");
    printf("|2| Buscar horas mayores\n");
    printf("|3| Buscar Horas menores\n");


}




void buscarAstronautaPorViajes()
{


    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nInsertar operacion a realizar: \n");

    menuConsultaViajesAstro();

    printf("\nOPCION: ");

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
        consultarViajesExacto();
        break;

    case 2:
        consultarMayoresViajesAstro();
        break;
    case 3:
        consultarMenoresViajesAstro();
        break;

    }

}


void consultarViajesExacto()
{

    int valido = 0;
    astronauta astro;
    astronauta aux;
    int veces = 0;

    FILE* archi = fopen(archiAstronauta,"rb");


    mostrarListaViajesAstro();

    while (valido == 0)
    {
        cargarMisionesEspaciales(&aux);
        valido = validarViajesAstro(aux.misionesEspacialesRealizadas);

    }
    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {


        if (aux.misionesEspacialesRealizadas == astro.misionesEspacialesRealizadas)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumple con ese requisito\n");
    }
    fclose(archi);
}

int validarViajesAstro(int misiones)
{

    FILE * archi = fopen(archiAstronauta, "rb");
    astronauta astro;

    while (fread(&astro, sizeof(astronauta),1, archi) > 0)
    {


        if (astro.misionesEspacialesRealizadas == misiones)
        {

            return 1;
        }

    }
    return 0;

    fclose(archi);
}

void mostrarListaViajesAstro()
{

    astronauta astro;
    FILE * archi = fopen(archiAstronauta, "rb");


    printf("\nLista de Misiones espaciales \n");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("- %i\n", astro.misionesEspacialesRealizadas);

    }

    fclose(archi);

}


void consultarMayoresViajesAstro()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la cantidad de viajes minima\n VIAJES: ");
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
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.misionesEspacialesRealizadas >= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }
    fclose(archi);
}

void consultarMenoresViajesAstro()
{

    int operador = -1;
    char strOpcion[maxCaracteres];
    int veces = 0;

    printf("\nIngrese la maxima cantidad de viajes\n VIAJES: ");
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
    FILE *archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi))
    {



        if (astro.misionesEspacialesRealizadas <= operador)
        {

            mostrarDatosAstronauta(astro);
            veces++;
        }
    }
    if (veces == 0)
    {
        printf("\nNo hay ningun astronauta que cumpla con ese requisito\n");
    }


    fclose(archi);
}


void    menuConsultaViajesAstro()
{

    printf("\n|1| Buscar cantidad de viajes exacta\n");
    printf("|2| Buscar cantidad mayor\n");
    printf("|3| Buscar cantidad menor\n");


}



void menuConsultasAstro()
{


    printf("\n|1| Buscar Astronauta por ID \n");
    printf(  "|2| Buscar Astronauta por Nombre\n");
    printf(  "|3| Buscar Astronauta por Apellido\n");
    printf(  "|4| Buscar Astronauta por Apodo\n");
    printf(  "|5| Buscar Astronauta por Edad\n");
    printf(  "|6| Buscar Astronauta por Nacionalidad\n");
    printf(  "|7| Buscar Astronauta por Especialidad\n");
    printf(  "|8| Buscar Astronauta por Horas de vuelo acumuladas\n");
    printf(  "|9| Buscar Astronauta por Horas en la EEI\n");
    printf(  "|10| Buscar Astronauta por Misiones Espaciales\n");


}

//----------------------------MODIFICAR ASTRNAUTA---------------------------------

void modificarAstronauta()
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    FILE * archi = fopen(archiAstronauta, "r+b");

    printf("\nInsertar operacion a realizar: \n");

    menuModificacionesAstro();

    printf("\nOPCION: ");

    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadModificacionesAstro);

        if (operador > minimaCantidadOpciones && operador < maxCantidadModificacionesAstro)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        cambiarNombreAstronauta();
        break;

    case 2:
        cambiarApellidoAstronauta();
        break;

    case 3:
        cambiarApodoAstronauta();
        break;

    case 4:
        cambiarEdadAstronauta();
        break;

    case 5:
        cambiarNacionalidadAstronauta();
        break;

    case 6:
        cambiarEspecialidadAstronauta();
        break;

    case 7:
        cambiarHorasVueloAcumuladasAstronauta();
        break;

    case 8:
        cambiarHorasEnEEI();
        break;

    case 9:
        cambiarMisionesEspaciales();

        break;

    case 10:
        cambiarEstadoAstronauta();
        break;

    default:
        printf("El numero ingresado no corresponde con las opciones");
        break;
    }

    fclose(archi);
}


//----------------MOSTRAR ASTRONAUTA------------------------------
void mostrarAstronautas()
{


    int operador = -1;
    char strOpcion[maxCaracteres];

    mostrarListaOpcionesMostrar();

    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadOpciones);

        if (operador > minimaCantidadOpciones && operador < maxCantidadOpciones)
        {
            break;
        }
    }



    switch(operador)
    {

    case 1:
        mostrarAstronautaArchivo();
        break;

    case 2:
        mostrarAstronautasActivos();
        break;

    case 3:
        mostrarAstronautasRetirados();
        break;

    }

}

void mostrarListaOpcionesMostrar()
{
    printf("\n Seleccione la opcion que desee\n");
    printf("|1| Mostrar todos los astronautas\n");
    printf("|2| Mostrar astronautas en activo\n");
    printf("|3| Mostrar astronautas retirados\n");



}


void mostrarAstronautasActivos()
{

    astronauta astro;
    FILE* archi =  fopen(archiAstronauta, "rb");


    while (fread(&astro, sizeof(astronauta),1, archi) > 0)
    {

        if(astro.estado == 1)
        {

            mostrarDatosAstronauta(astro);

        }
    }

    fclose(archi);
}


void mostrarAstronautasRetirados()
{

    astronauta astro;

    FILE* archi = fopen(archiAstronauta, "rb");

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        if (astro.estado == 2)
        {

            mostrarDatosAstronauta(astro);
        }
    }


}



//---------------MENU DE MMODIFICACIONES--------------------
void menuModificacionesAstro()
{


    printf("\n|1| Nombre \n");
    printf(  "|2| Apellido\n");
    printf(  "|3| Apodo\n");
    printf(  "|4| Edad\n");
    printf(  "|5| Nacionalidad\n");
    printf(  "|6| Especialidad\n");
    printf(  "|7| Horas de vuelo acumuladas\n");
    printf(  "|8| Horas en la EEI\n");
    printf(  "|9| Misiones Espaciales\n");
    printf(  "|10| Estado\n");

}

//----------------CAMBIAR NOMBRE----------------------

void cambiarNombreAstronauta()
{
    menuIDAstro();
    int id = idBuscadoAstro();

    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarNombre(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;

        }
    }


    fclose(archi);
}


//----------CAMBIAR APELLIDO---------------
void cambiarApellidoAstronauta()
{
    menuIDAstro();
    int id = idBuscadoAstro();

    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarApellido(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;
        }
    }



    fclose(archi);
}

//----------------------CAMBIA APODO---------------------------------------------------------
void cambiarApodoAstronauta()
{
    menuIDAstro();
    int id = idBuscadoAstro();

    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarApodo(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;

        }
    }

    fclose(archi);
}


//--------------CAMBIAR ESTADO-------------------------

void cambiarEstadoAstronauta()
{
    astronauta astro;
    menuIDAstro();
    int id = idBuscadoAstro();
    int operador = -1;
    char strOpcion[maxCaracteres];


    FILE* archi = fopen(archiAstronauta, "r+b");
    printf("\nInsertar operacion a realizar: \n");

    printf("|1| DAR DE ALTA \n|2| DAR DE BAJA\n");
    fflush(stdin);

    printf("\nOPCION: ");
    gets(strOpcion);

    while(operador < 0)
    {

        operador = validacionNumeros(strOpcion,1,2);

        if (operador >= 1 && operador <= 2);
        {

            break;

        }
    }


    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        if(astro.ID == id)
        {
            astro.estado = operador;

            fseek(archi, sizeof(astronauta) * -1, SEEK_CUR);
            fwrite(&astro, sizeof(astronauta),1,archi);

            mostrarDatosAstronauta(astro);
            break;
        }
    }

    fclose(archi);
}


//------------------CAMBIAR EDAD--------------------------
void cambiarEdadAstronauta()
{
    menuIDAstro();
    int id = idBuscadoAstro();
    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarEdad(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;

        }
    }

    fclose(archi);
}

//----------CAMBIAR NACIONALIDA--------------
void cambiarNacionalidadAstronauta()
{
    menuIDAstro();
    int id = idBuscadoAstro();
    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarNacionalidad(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;

        }
    }

    fclose(archi);
}

//---------CAMBIAR ESPECIALIDAD------------------
void cambiarEspecialidadAstronauta()
{
    menuIDAstro();
    int id = idBuscadoAstro();
    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarEspecialidad(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;

        }
    }

    fclose(archi);
}


//------------------ASTRONAUTAS PREDETERMINADOS---------------------

void astronautasPredeterminados()
{

    FILE * archi = fopen(archiAstronauta, "wb");

    astronauta astroPredeterminado1;


    astroPredeterminado1.ID = 101;
    strcpy(astroPredeterminado1.nombre, "Neil");
    strcpy(astroPredeterminado1.apellido, "Armstrong");
    strcpy(astroPredeterminado1.apodo, "Kike");
    astroPredeterminado1.edad = 34;
    strcpy(astroPredeterminado1.nacionalidad, "Estados Unidos");
    strcpy(astroPredeterminado1.especialidad, "Piloto");
    astroPredeterminado1.horasVueloAcumuladas = 346;
    astroPredeterminado1.horasAcumuladasEEI = 2067;
    astroPredeterminado1.misionesEspacialesRealizadas = 23;
    astroPredeterminado1.estado = 1;

    fwrite(&astroPredeterminado1, sizeof(astronauta),1,archi);

    astronauta astroPredeterminado2;

    astroPredeterminado2.ID = 102;
    strcpy(astroPredeterminado2.nombre, "Juan");
    strcpy(astroPredeterminado2.apellido, "Rodriguez");
    strcpy(astroPredeterminado2.apodo, "Cachito");
    astroPredeterminado2.edad = 29;
    strcpy(astroPredeterminado2.nacionalidad, "Mexico");
    strcpy(astroPredeterminado2.especialidad, "Ingeniero Espacial");
    astroPredeterminado2.horasVueloAcumuladas = 115;
    astroPredeterminado2.horasAcumuladasEEI = 0;
    astroPredeterminado2.misionesEspacialesRealizadas = 2;
    astroPredeterminado2.estado = 1;

    fwrite(&astroPredeterminado2, sizeof(astronauta),1,archi);

    astronauta astroPredeterminado3;

    astroPredeterminado3.ID = 103;
    strcpy(astroPredeterminado3.nombre, "Agustin");
    strcpy(astroPredeterminado3.apellido, "Grillo");
    strcpy(astroPredeterminado3.apodo, "Maestro");
    astroPredeterminado3.edad = 51;
    strcpy(astroPredeterminado3.nacionalidad, "Argentina");
    strcpy(astroPredeterminado3.especialidad, "Piloto");
    astroPredeterminado3.horasVueloAcumuladas = 568;
    astroPredeterminado3.horasAcumuladasEEI = 3867;
    astroPredeterminado3.misionesEspacialesRealizadas = 45;
    astroPredeterminado3.estado = 2;


    fwrite(&astroPredeterminado3, sizeof(astronauta),1,archi);

    astronauta astroPredeterminado4;


    astroPredeterminado4.ID = 104;
    strcpy(astroPredeterminado4.nombre, "Zlatan");
    strcpy(astroPredeterminado4.apellido, "Olsen");
    strcpy(astroPredeterminado4.apodo, "Tanol");
    astroPredeterminado4.edad = 32;
    strcpy(astroPredeterminado4.nacionalidad, "Suecia");
    strcpy(astroPredeterminado4.especialidad, "Astrofisico");
    astroPredeterminado4.horasVueloAcumuladas = 46;
    astroPredeterminado4.horasAcumuladasEEI = 1867;
    astroPredeterminado4.misionesEspacialesRealizadas = 7;
    astroPredeterminado4.estado = 1;

    fwrite(&astroPredeterminado4, sizeof(astronauta),1,archi);


    fclose(archi);
}


//-------------------GUARDAR ASTRONAUTAS EN ARCHIVO--------------------


void mostrarAstronautaArchivo()
{

    astronauta astro;

    FILE *archi;

    archi = fopen(archiAstronauta, "rb");


    while (fread(&astro, sizeof(astronauta),1,archi) > 0)
    {
        mostrarDatosAstronauta(astro);
    }

    fclose(archi);

}


//---------------FUNCION PRINCIPAL PARA CARGAR EL ASTRONAUTA--------------


void cargarAstronautaNuevo(astronauta* astro)
{

    FILE* archi;

    archi = fopen(archiAstronauta, "ab+");

    astro->ID = ultimoIdAstro();
    mostrarIDAstro();
    cargarNombre(astro);
    cargarApellido(astro);
    cargarApodo(astro);
    cargarEdad(astro);
    cargarNacionalidad(astro);
    cargarEspecialidad(astro);
    astro->horasVueloAcumuladas = 0;
    astro->horasAcumuladasEEI = 0;
    astro->misionesEspacialesRealizadas = 0;
    astro->estado = 1;

    mostrarDatosAstronauta(*astro);

    fwrite(astro, sizeof(astronauta),1, archi);

    fclose(archi);
}



//------------------CONOCAR TAMAÑO DEL ARCHIVO------------------------

int ultimoIdAstro()
{
    astronauta aux;

    FILE *archi = fopen(archiAstronauta,"rb");
    if(archi == NULL || tamanoArchiAstro() == 0)
    {
        fclose(archi);
        return 1;
    }

    fseek(archi,(sizeof(astronauta) * -1),SEEK_END);
    fread(&aux,sizeof(astronauta),1,archi);

    return aux.ID + 1;

}

void mostrarIDAstro()
{

    int ID = ultimoIdAstro();
    printf("ID: %i", ID);

}



int tamanoArchiAstro()
{
    FILE *fich;

    fich=fopen(archiAstronauta,"rb");

    fseek(fich, 0, SEEK_END);
    fclose(fich);
    return ftell(fich)/sizeof(astronauta);

}


//-----------FUNCION QUE CARGA Y VALIDA EL NOMBRE--------------------------------------------

void cargarNombre(astronauta* astro)
{
    char nombre[maxCaracteres];
    printf("\n NOMBRE: ");

    fflush(stdin);
    gets(nombre);

    int valido = validacionString(nombre);


    if(valido == 1)
    {
        strcpy(astro->nombre, nombre);
    }

    else if(valido == 0)
    {

        while (valido == 0)
        {

            printf("Ingrese un nombre valido\n NOMBRE: ");
            fflush(stdin);
            gets(nombre);

            valido = validacionString(nombre);

        }
    }

    strcpy(astro->nombre, nombre);
}

//--------------CARGA Y VALIDA EL APELLIDO------------------------------------------------
void cargarApellido(astronauta* astro)
{

    char apellido[maxCaracteres];

    printf("\n APELLIDO: ");

    fflush(stdin);
    gets(apellido);
    int valido = validacionString(apellido);

    if(valido == 1)
    {
        strcpy(astro->apellido, apellido);
    }
    else if (valido == 0)
    {
        while (valido == 0)
        {

            printf("Inserte un apellido valido\n APELLIDO: ");
            fflush(stdin);
            gets(apellido);

            valido = validacionString(apellido);
        }
    }

    strcpy(astro->apellido,apellido);
}
//---------------------------------------------------------------------------------------------------------------------

//CARGA Y VALIDA EL APODO----------------------------------------------------------------------------------------------
void cargarApodo(astronauta* astro)
{

    char apodo[maxCaracteres];

    printf("\n APODO: ");
    fflush(stdin);
    gets(apodo);

    int valido = validacionString(apodo);

    if(valido == 1)
    {

        strcpy(astro->apodo, apodo);

    }

    else if(valido == 0)
    {
        while(valido == 0)
        {
            printf("Ingrese un apodo valido\n APODO: ");
            fflush(stdin);
            gets(apodo);

            valido = validacionString(apodo);
        }
    }

    strcpy(astro->apodo, apodo);
}
//---------------------------------------------------------------------------------------------------------------------

//MUESTRA DATOS DEL ASTRONAUTA (FALTA COMPLETAR)-----------------------------------------------------------------------
void mostrarDatosAstronauta(astronauta astro)
{
    printf("\nID------------------------------- %i", astro.ID);
    printf("\nNOMBRE--------------------------- %s", astro.nombre);
    printf("\nAPELLIDO------------------------- %s", astro.apellido);
    printf("\nAPODO---------------------------- %s", astro.apodo);
    printf("\nEDAD----------------------------- %i", astro.edad);
    printf("\nNACIONALIDAD--------------------- %s", astro.nacionalidad);
    printf("\nESPECIALIDAD--------------------- %s", astro.especialidad);
    printf("\nHORAS DE VUELO ACUMULADAS-------- %i", astro.horasVueloAcumuladas);
    printf("\nHORAS ACUMULADAS DE EEI---------- %i", astro.horasAcumuladasEEI);
    printf("\nMISIONES ESPACIALES ACUMULADAS--- %i", astro.misionesEspacialesRealizadas);
    printf("\nESTADO |1|activo |2|inactivo----- %i", astro.estado);

    printf("\n");

}
//---------------------------------------------------------------------------------------------------------------------


//CARGA Y VALIDA LA NACIONALIDAD POR MEDIO DE UN MENU------------------------------------------------------------------

void cargarNacionalidad(astronauta* astro)
{

    int valido = 0;
    char nacionalidades[cantNacionalidades][maxCaracteres];
    int operador = -1;
    char strOpcion[maxCaracteres];



    baseNacionalidades(nacionalidades);
    char nacionalidad[maxCaracteres];

    printf("\n NACIONALIDAD: ");
    fflush(stdin);
    gets(nacionalidad);

    valido = validacionNacionalidad(nacionalidad, nacionalidades);

    if(valido == 1)
    {

        strcpy(astro->nacionalidad, nacionalidad);
    }
    else if(valido == 0)
    {

        while(valido == 0)
        {

            printf("\nLas nacionalidades deben ser con la inicial en mayuscula\n");
            printf("\nInsertar operacion a realizar: \n");

            printf("\n|1| Escribir nuevamente \n");
            printf("|2| Menu de nacionalidades \n");
            fflush(stdin);

            printf("\nOPCION: ");
            gets(strOpcion);

            while(operador < 0 || valido == 0)
            {

                operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadMenu);

                if (operador >= minimaCantidadOpciones && operador <= maxCantidadMenu);
                {

                    break;

                }
            }

            if(operador == 2)
            {
                mostrarCatalogoNacionalidades(nacionalidades);
            }
            else if (operador == 1)
            {
                printf("\n NACIONALIDAD: ");
                fflush(stdin);
                gets(nacionalidad);
                valido = validacionNacionalidad(nacionalidad, nacionalidades);

            }

        }

    }

    strcpy(astro->nacionalidad, nacionalidad);
}





//---------------------------------------------------------------------------------------------------------------------

//VALIDA QUE LA NACIONALIDAD INSERTADA SEA VALIDA CON RESPECTO A LOS PAISES ACTUALES DEL MUNDO-------------------------
int validacionNacionalidad(char nacionalidad[maxCaracteres], char nacionalidades[cantNacionalidades][maxCaracteres])
{

    int i;

    for(i = 0; i < cantNacionalidades; i++)
    {

        if(strcmp(nacionalidad, nacionalidades[i]) == 0)
        {
            return 1;
        }

    }

    return 0;
}
//---------------------------------------------------------------------------------------------------------------------



//CARGA EN LA MATRIZ INGRESADA TODOS LOS PAISES VALIDOS ACTUALMENTE----------------------------------------------------
void baseNacionalidades(char nacionalidades[cantNacionalidades][maxCaracteres])
{
    //15 A-------------------------------


    strcpy(nacionalidades[0],"Afganistan");
    strcpy(nacionalidades[1],"Albania");
    strcpy(nacionalidades[2],"Alemania");
    strcpy(nacionalidades[3],"Andorra");
    strcpy(nacionalidades[4],"Angola");
    strcpy(nacionalidades[5],"Antigua y Barbuda");
    strcpy(nacionalidades[6],"Antillas Holandesas");
    strcpy(nacionalidades[7],"Arabia Saudi");
    strcpy(nacionalidades[8],"Argelia");
    strcpy(nacionalidades[9],"Argentina");
    strcpy(nacionalidades[10],"Armenia");
    strcpy(nacionalidades[11],"Aruba");
    strcpy(nacionalidades[12],"Australia");
    strcpy(nacionalidades[13],"Austria");
    strcpy(nacionalidades[14],"Azerbaiyan");

    // 18 B------------------------------


    strcpy(nacionalidades[15],"Bahamas");
    strcpy(nacionalidades[16],"Bahrein");
    strcpy(nacionalidades[17],"Bangladesh");
    strcpy(nacionalidades[18],"Barbados");
    strcpy(nacionalidades[19],"Belgica");
    strcpy(nacionalidades[20],"Belice");
    strcpy(nacionalidades[21],"Benin");
    strcpy(nacionalidades[22],"Bermudas");
    strcpy(nacionalidades[23],"Bielorrusia");
    strcpy(nacionalidades[24],"Bolivia");
    strcpy(nacionalidades[25],"Botsuana");
    strcpy(nacionalidades[26],"Bosnia");
    strcpy(nacionalidades[27],"Brasil");
    strcpy(nacionalidades[28],"Brunei");
    strcpy(nacionalidades[29],"Bulgaria");
    strcpy(nacionalidades[30],"Burkina Faso");
    strcpy(nacionalidades[31],"Burundi");
    strcpy(nacionalidades[32],"Butan");



    //17 C-------------------------------


    strcpy(nacionalidades[33],"Cabo Verde");
    strcpy(nacionalidades[34],"Camboya");
    strcpy(nacionalidades[35],"Camerun");
    strcpy(nacionalidades[36],"Canada");
    strcpy(nacionalidades[37],"Catar");
    strcpy(nacionalidades[38],"Chile");
    strcpy(nacionalidades[39],"China");
    strcpy(nacionalidades[40],"Chipre");
    strcpy(nacionalidades[41],"Colombia");
    strcpy(nacionalidades[42],"Comoras");
    strcpy(nacionalidades[43],"Congo");
    strcpy(nacionalidades[44],"Corea del Norte");
    strcpy(nacionalidades[45],"Corea del Sur");
    strcpy(nacionalidades[46],"Costa de Marfil");
    strcpy(nacionalidades[47],"Costa Rica");
    strcpy(nacionalidades[48],"Croacia");
    strcpy(nacionalidades[49],"Cuba");



    //2 D--------------------------------


    strcpy(nacionalidades[50],"Dinamarca");
    strcpy(nacionalidades[51],"Dominica");

    //11 E-------------------------------

    strcpy(nacionalidades[52],"Ecuador");
    strcpy(nacionalidades[53],"Egipto");
    strcpy(nacionalidades[54],"El Salvador");
    strcpy(nacionalidades[55],"Emiratos Arabes");
    strcpy(nacionalidades[56],"Eritrea");
    strcpy(nacionalidades[57],"Eslovaquia");
    strcpy(nacionalidades[58],"Eslovenia");
    strcpy(nacionalidades[59],"Espana");
    strcpy(nacionalidades[60],"Estados Unidos");
    strcpy(nacionalidades[61],"Estonia");
    strcpy(nacionalidades[62],"Etiopia");

    //4 F--------------------------------

    strcpy(nacionalidades[63],"Fiyi");
    strcpy(nacionalidades[64],"Filipinas");
    strcpy(nacionalidades[65],"Finlandia");
    strcpy(nacionalidades[66],"Francia");


    //13 G-------------------------------

    strcpy(nacionalidades[67],"Gabon");
    strcpy(nacionalidades[68],"Gambia");
    strcpy(nacionalidades[69],"Georgia");
    strcpy(nacionalidades[70],"Ghana");
    strcpy(nacionalidades[71],"Grecia");
    strcpy(nacionalidades[72],"Guam");
    strcpy(nacionalidades[73],"Guatemala");
    strcpy(nacionalidades[74],"Guayana Francesa");
    strcpy(nacionalidades[75],"Guinea-Bissau");
    strcpy(nacionalidades[76],"Guinea Ecuatorial");
    strcpy(nacionalidades[77],"Guinea");
    strcpy(nacionalidades[78],"Guyana");
    strcpy(nacionalidades[79],"Granada");

    //5 H--------------------------------

    strcpy(nacionalidades[80],"Haiti");
    strcpy(nacionalidades[81],"Honduras");
    strcpy(nacionalidades[82],"Hong Kong");
    strcpy(nacionalidades[83],"Hungria");
    strcpy(nacionalidades[84],"Holanda");

    //12 I-------------------------------

    strcpy(nacionalidades[85],"India");
    strcpy(nacionalidades[86],"Indonesia");
    strcpy(nacionalidades[87],"Irak");
    strcpy(nacionalidades[88],"Iran");
    strcpy(nacionalidades[89],"Irlanda");
    strcpy(nacionalidades[90],"Islandia");
    strcpy(nacionalidades[91],"Islas Caiman");
    strcpy(nacionalidades[92],"Islas Marshall");
    strcpy(nacionalidades[93],"Islas Pitcairn");
    strcpy(nacionalidades[94],"Islas Salomon");
    strcpy(nacionalidades[95],"Israel");
    strcpy(nacionalidades[96],"Italia");

    //3 J--------------------------------

    strcpy(nacionalidades[97],"Jamaica");
    strcpy(nacionalidades[98],"Japon");
    strcpy(nacionalidades[99],"Jordania");

    //6 K--------------------------------

    strcpy(nacionalidades[100],"Kazajstan");
    strcpy(nacionalidades[101],"Kenia");
    strcpy(nacionalidades[102],"Kirguistan");
    strcpy(nacionalidades[103],"Kiribati");
    strcpy(nacionalidades[104],"Kosovo");
    strcpy(nacionalidades[105],"Kuwait");

    //9 L--------------------------------

    strcpy(nacionalidades[106],"Laos");
    strcpy(nacionalidades[107],"Lesotho");
    strcpy(nacionalidades[108],"Letonia");
    strcpy(nacionalidades[109],"Libano");
    strcpy(nacionalidades[110],"Liberia");
    strcpy(nacionalidades[111],"Libia");
    strcpy(nacionalidades[112],"Liechtenstein");
    strcpy(nacionalidades[113],"Lituania");
    strcpy(nacionalidades[114],"Luxemburgo");

    //19 M-------------------------------

    strcpy(nacionalidades[115],"Macedonia");
    strcpy(nacionalidades[116],"Madagascar");
    strcpy(nacionalidades[117],"Malasia");
    strcpy(nacionalidades[118],"Malawi");
    strcpy(nacionalidades[119],"Maldivas");
    strcpy(nacionalidades[120],"Mali");
    strcpy(nacionalidades[121],"Malta");
    strcpy(nacionalidades[122],"Marianas del Norte");
    strcpy(nacionalidades[123],"Marruecos");
    strcpy(nacionalidades[124],"Mauricio");
    strcpy(nacionalidades[125],"Mauritania");
    strcpy(nacionalidades[126],"Mexico");
    strcpy(nacionalidades[127],"Micronesia");
    strcpy(nacionalidades[128],"Monaco");
    strcpy(nacionalidades[129],"Moldavia");
    strcpy(nacionalidades[130],"Mongolia");
    strcpy(nacionalidades[131],"Montenegro");
    strcpy(nacionalidades[132],"Mozambique");
    strcpy(nacionalidades[133],"Myanmar");

    //8 N--------------------------------

    strcpy(nacionalidades[134],"Namibia");
    strcpy(nacionalidades[135],"Nauru");
    strcpy(nacionalidades[136],"Nepal");
    strcpy(nacionalidades[137],"Nicaragua");
    strcpy(nacionalidades[138],"Niger");
    strcpy(nacionalidades[139],"Nigeria");
    strcpy(nacionalidades[140],"Noruega");
    strcpy(nacionalidades[141],"Nueva Zelanda");

    //2 O--------------------------------

    strcpy(nacionalidades[142],"Oman");
    strcpy(nacionalidades[143],"Orden de Malta");

    //11 P-------------------------------

    strcpy(nacionalidades[144],"Paises Bajos");
    strcpy(nacionalidades[145],"Pakistan");
    strcpy(nacionalidades[146],"Palestina");
    strcpy(nacionalidades[147],"Palau");
    strcpy(nacionalidades[148],"Panama");
    strcpy(nacionalidades[149],"Papua Nueva Guinea");
    strcpy(nacionalidades[150],"Paraguay");
    strcpy(nacionalidades[151],"Peru");
    strcpy(nacionalidades[152],"Polonia");
    strcpy(nacionalidades[153],"Portugal");
    strcpy(nacionalidades[154],"Puerto Rico");

    //9 R--------------------------------

    strcpy(nacionalidades[155],"Reino Unido");
    strcpy(nacionalidades[156],"Republica Centroafricana");
    strcpy(nacionalidades[157],"Republica Checa");
    strcpy(nacionalidades[158],"Republica del Congo");
    strcpy(nacionalidades[159],"Republica Democratica del Congo");
    strcpy(nacionalidades[160],"Republica Dominicana");
    strcpy(nacionalidades[161],"Ruanda");
    strcpy(nacionalidades[162],"Rumania");
    strcpy(nacionalidades[163],"Rusia");

    //22 S-------------------------------

    strcpy(nacionalidades[164],"Sahara Occidental");
    strcpy(nacionalidades[165],"Samoa Americana");
    strcpy(nacionalidades[166],"Samoa");
    strcpy(nacionalidades[167],"San Cristobal y Nieves");
    strcpy(nacionalidades[168],"San Marino");
    strcpy(nacionalidades[169],"Santa Lucia");
    strcpy(nacionalidades[170],"Santo Tome y Principe");
    strcpy(nacionalidades[171],"San Vicente y las Granadinas");
    strcpy(nacionalidades[172],"Senegal");
    strcpy(nacionalidades[173],"Serbia");
    strcpy(nacionalidades[174],"Seychelles");
    strcpy(nacionalidades[175],"Sierra Leona");
    strcpy(nacionalidades[176],"Singapur");
    strcpy(nacionalidades[177],"Siria");
    strcpy(nacionalidades[178],"Somalia");
    strcpy(nacionalidades[179],"Sri Lanka");
    strcpy(nacionalidades[180],"Sudafrica");
    strcpy(nacionalidades[181],"Sudan");
    strcpy(nacionalidades[182],"Sudan del Sur");
    strcpy(nacionalidades[183],"Suecia");
    strcpy(nacionalidades[184],"Suiza");
    strcpy(nacionalidades[185],"Suazilandia");

    //13 T-------------------------------

    strcpy(nacionalidades[186],"Tilandia");
    strcpy(nacionalidades[187],"Taiwan");
    strcpy(nacionalidades[188],"Tanzania");
    strcpy(nacionalidades[189],"Tayikistan");
    strcpy(nacionalidades[190],"Tibet");
    strcpy(nacionalidades[191],"Timor Oriental");
    strcpy(nacionalidades[192],"Togo");
    strcpy(nacionalidades[193],"Tonga");
    strcpy(nacionalidades[194],"Trinidad y Tobago");
    strcpy(nacionalidades[195],"Tunez");
    strcpy(nacionalidades[196],"Turkmenistan");
    strcpy(nacionalidades[197],"Turquia");
    strcpy(nacionalidades[198],"Tuvalu");

    //4 U--------------------------------

    strcpy(nacionalidades[199],"Ucrania");
    strcpy(nacionalidades[200],"Uganda");
    strcpy(nacionalidades[201],"Uruguay");
    strcpy(nacionalidades[202],"Uzbequistan");

    //4 V--------------------------------

    strcpy(nacionalidades[203],"Vanuatu");
    strcpy(nacionalidades[204],"Vaticano");
    strcpy(nacionalidades[205],"Venezuela");
    strcpy(nacionalidades[206],"Vietnam");

    //1 W--------------------------------


    strcpy(nacionalidades[207],"Wallis y Futuna");

    //2 Y--------------------------------

    strcpy(nacionalidades[208],"Yemen");
    strcpy(nacionalidades[209],"Yibuti");

    //3 Z--------------------------------

    strcpy(nacionalidades[210],"Zambia");
    strcpy(nacionalidades[211],"Zaire");
    strcpy(nacionalidades[212],"Zimbabue");
}
//---------------------------------------------------------------------------------------------------------------------


//CARGA Y VALIDA LA EDAD HACIENDO QUE SEA MAYOR DE 18 Y MENOR DE 100 AÑOS----------------------------------------------
void cargarEdad(astronauta* astro)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    printf("\n EDAD: ");
    fflush(stdin);
    gets(strOpcion);

    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,edadMinima,edadMaxima);

        if (operador > edadMinima && operador < edadMaxima)
        {
            astro->edad = operador;
            break;
        }
    }

}
//---------------------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------------


//MUESTRA EL CATALOGO DE 213 PAISES Y LE ASIGNA UN VALOR PARA INSERTAR A CADA UNO DE ELLOS-----------------------------
void mostrarCatalogoNacionalidades(char nacionalidades[cantNacionalidades][maxCaracteres])
{

    int i = 0;

    printf("\nLista de paises: \n");

    while(i < cantNacionalidades)
    {
        printf("- %s\n", nacionalidades[i]);
        i++;
    }
}
//---------------------------------------------------------------------------------------------------------------------



//CARGA LA ESPECIALIDAD POR MEDIO DE UN MENU---------------------------------------------------------------------------
void  cargarEspecialidad(astronauta* astro)
{

    int operador = -1;
    char strOpcion[maxCaracteres];

    char especialidades[cantEspecialidades][maxCaracteres];
    especialidadesAstronauta(especialidades);


    printf("Seleccione un numero asociado a una especialidad\n");
    mostrarEspecialidades(especialidades);
    printf(" ESPECIALIDAD: ");
    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,cantEspecialidades);

        if (operador >= minimaCantidadOpciones && operador <= cantEspecialidades)
        {
            strcpy(astro->especialidad,especialidades[operador - 1]);
            break;
        }
    }


}


//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------


//MUESTRA LA ESPECIALIDADES Y LE ASIGNA UN NUMERO A CADA UNO PARA INSERTAR Y ESCOGER UNA ESPECUALIDAD------------------
void mostrarEspecialidades(char especialidades[][maxCaracteres])
{



    int i = 0;
    int pos = 1;

    while (i< cantEspecialidades)
    {


        printf("|%i| %s \n", pos, especialidades[i]);

        pos++;
        i++;
    }

}
//---------------------------------------------------------------------------------------------------------------------


//CARGA EN UNA MATRIZ INSERTADA LAS ESPECIALIDADES QUE LUEGO PODRAN SER ESCOGIDAS--------------------------------------
void especialidadesAstronauta(char especialidades[][maxCaracteres])
{


    printf("\n");
    strcpy(especialidades[0], "Piloto");
    strcpy(especialidades[1], "Astrofisico");
    strcpy(especialidades[2], "Ingeniero Espacial");
    strcpy(especialidades[3], "Biologo");
    strcpy(especialidades[4], "Comericial");

}



//BUSCA EL ASTRONAUTA QUE PERTENEZCA AL ID CORRESPONDIENT-------
void buscarAstronautaPorId()
{
    menuIDAstro();
    int id = idBuscadoAstro();


    FILE* archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {
        if(astro.ID == id)
        {

            mostrarDatosAstronauta(astro);
            break;
        }
    }
    fclose(archi);
}

//EN CASO DE NO QUERER REALIZAR MAS OPERACIONES("no") MANDA UN SALUDO
void saludoFinal(char valor[2])
{

    if(strcmp(valor, "no") == 0)
    {

        printf("\n\n-------NOS VEMOS LA PROXIMA-------\n\n");
    }
}


//CAMBIA LAS HORAS DE VUELO
void cambiarHorasVueloAcumuladasAstronauta()
{
    menuIDAstro();
    int id = idBuscadoAstro();
    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarHorasVueloAcumuladas(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;
        }
    }

    fclose(archi);
}

//CARGA LAS HORAS DE VUELO ACUMULADAS
void cargarHorasVueloAcumuladas(astronauta *astro)
{

    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nCantidad de horas de vuelo acumuladas\n HORAS ACUMULADAS: ");
    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadHoras);

        if (operador >= minimaCantidadOpciones && operador < maxCantidadHoras)
        {
            astro->horasVueloAcumuladas = operador;
            break;
        }
    }


}


//CARGA HORAS EN EEI
void cargarHorasEnEEI(astronauta *astro)
{

    int operador = -1;
    char strOpcion[maxCaracteres];



    printf("\nCantidad de horas en la EEI\n HORAS EN LA EEI:  ");
    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadHoras);

        if (operador >= minimaCantidadOpciones && operador < maxCantidadHoras)
        {
            astro->horasAcumuladasEEI = operador;
            break;
        }
    }



}




//CAMBIA LAS HORAS EN EEI
void cambiarHorasEnEEI()
{


    menuIDAstro();
    int id = idBuscadoAstro();
    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))

    {


        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarHorasEnEEI(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;
        }

    }
    fclose(archi);

}

//CARGA LAS MISIONES ESPACIALES REALIZADAS
void cargarMisionesEspaciales(astronauta *astro)
{

    int operador = -1;
    char strOpcion[maxCaracteres];


    printf("\nCantidad de misiones Espaciales\n MISIONES:  ");
    fflush(stdin);
    gets(strOpcion);


    while(operador < 0)
    {
        operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxcantidadViajes);

        if (operador >= minimaCantidadOpciones && operador < maxcantidadViajes)
        {
            astro->misionesEspacialesRealizadas = operador;
            break;
        }
    }


}

//CAMBIA LA CANTIDAD DE MISIONES ESPACIALES REALIZADAS
void cambiarMisionesEspaciales()
{
    menuIDAstro();
    int id = idBuscadoAstro();
    astronauta astro;

    FILE * archi = fopen(archiAstronauta, "r+b");

    while (fread(&astro, sizeof(astronauta),1, archi))
    {

        if(astro.ID == id)
        {

            fseek(archi,sizeof(astronauta) * -1, SEEK_CUR);

            cargarMisionesEspaciales(&astro);

            fwrite(&astro, sizeof(astronauta),1, archi);

            mostrarDatosAstronauta(astro);
            break;
        }
    }

    fclose(archi);
}





//MUESTRA LA LISTA DE LOS ID EXISTENTE
void mostrarListaIDAstro()
{
    FILE* archi;

    archi = fopen(archiAstronauta, "rb");
    astronauta astro;

    while (fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        printf("ID: %i\n", astro.ID);
    }

    fclose(archi);
}



void menuIDAstro()
{

    int opera = -1;
    char strOpcion[maxCaracteres];

    printf("\nInsertar operacion a realizar: \n");

    printf("\n|1|  Para ver menu de id \n|2|  Para seguir\n");

    fflush(stdin);

    printf("\nOPCION: ");
    gets(strOpcion);

    while(opera < 0)
    {
        opera = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadMenu);

        if (opera >= minimaCantidadOpciones && opera <= maxCantidadMenu)
        {
            break;
        }
    }

    if (opera == 1)
    {
        printf("\n");

        mostrarListaIDAstro();

        printf("\n");
    }

    else if (opera == 2)
    {
        return;

    }
}




int idBuscadoAstro()
{

    int valido = 0;
    int operador = -1;
    char strOpcion[maxCaracteres];
    int maxIdAstronauta =  ultimoIdAstro() -1;

    valido = validacionIDAstro(operador);


    while (valido == 0 && (operador < minIdAstro || operador > maxIdAstronauta))
    {

        printf("Inserte el ID del Astronauta\n ID: ");
        fflush(stdin);
        gets(strOpcion);


        operador = validacionNumeros(strOpcion,minIdAstro,maxIdAstronauta);

        valido = validacionIDAstro(operador);

        if (operador >= minIdAstro && operador <= maxIdAstronauta && valido == 1)
        {

            return operador;

        }
    }
    return 0;
}



int validacionIDAstro(int id)
{



    FILE* archi;

    archi = fopen(archiAstronauta, "rb");

    astronauta astro;

    while(fread(&astro, sizeof(astronauta), 1, archi) > 0)
    {

        if(id == astro.ID)
        {

            return 1;
        }

    }

    return 0;
}



