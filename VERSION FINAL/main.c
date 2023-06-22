#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"


//---------------------------------MAIN--------------------------------------------------------------------------------

int main()
{

    //navesPredeterminadas();
    //astronautasPredeterminados();
    //misionPredeterminada();


    char valor[] = "si";
    int operador;
    char strOpcion[maxCaracteres];

    while(strcmp(valor, "si") == 0)
    {

        operador = -1;
        printf("Insertar operacion a realizar: \n");
        mostrarOpcionesPrincipales();
        printf("\nOPCION: ");
        gets(strOpcion);

        while(operador < 0)
        {
            operador = validacionNumeros(strOpcion,minimaCantidadOpciones,maxCantidadOpciones);

            if (operador > minimaCantidadOpciones && operador <= maxCantidadOpciones)
            {
                break;
            }
        }



        switch(operador)
        {


        case 1:
            funcionAstronautas();
            break;

        case 2:
            funcionNaves();
            break;

        case 3:
            funcionMisiones();
            break;

        default:
            printf("Opcion invalida");
            break;



        }

        printf("\n\nDesea Seguir operando?\n|'si'| Seguir operando\n|'no'| Dejar de operar\n");
        fflush(stdin);
        printf("\nRESPUESTA: ");
        gets(valor);


        while(strcmp(valor, "si") != 0 && strcmp(valor, "no") != 0)
        {

            printf("Ingresa opcion valida\n");
            fflush(stdin);
            printf("\nRESPUESTA: ");
            gets(valor);

        }

        if(strcmp(valor, "no") == 0)
        {
            reiniciarSistema();
            saludoFinal(valor);
        }
    }

    return 0;
}
//-----------------VALIDACION NUMEROS------------------------

int validacionNumeros(char str[100], int min, int max)
{
    char *endptr;
    long num = strtol(str, &endptr, 10);
    int valido =0;
    int conv;

    conv = (int)num;
    if (*endptr == '\0' && conv >= min && conv <= max )
    {
        valido = 1;
    }
    else
    {
        while (valido == 0)
        {
            printf("Ingrese un numero valido\n NUMERO:");
            gets(str);
            num = strtol(str, &endptr, 10);
            conv = (int)num;
            if (*endptr == '\0' && conv >= min && conv <= max)
            {
                valido = 1;

            }
        }
    }
    conv = (int)num;
    return conv;
}


//---------MOSTRAR OPCIONES PRINCIPALES---------------------

void mostrarOpcionesPrincipales()
{

    printf("\n|1| ASTRONAUTAS");
    printf("\n|2| NAVES");
    printf("\n|3| MISIONES\n");

}



//--------------------REINICIAR SISTEMA-------------------------

void reiniciarSistema()
{
    int operador = -1;
    char strOpcion[maxCaracteres];
    printf("|1| Reiniciar sistema\n|2| Seguir con los datos cargados\n");

    fflush(stdin);
    printf("\nOPCION: ");
    gets(strOpcion);

    while (operador < 0)
    {
        operador = validacionNumeros(strOpcion, 1, 2);

        if (operador >= 1 && operador <= 2)
        {
            break;
        }
    }

    int operador2 = -1;
    char confirmacion[maxCaracteres]; // Variable 'confirmacion' estaba faltando
    char strOpcion2[maxCaracteres];

    while (operador == 1)
    {
        printf("Escriba CONFIRMAR para continuar:\n");
        fflush(stdin);
        printf("\nRESPUESTA: ");
        gets(confirmacion);

        if (strcmp(confirmacion, "CONFIRMAR") == 0)
        {
            astronautasPredeterminados();
            navesPredeterminadas();
            misionPredeterminada();
            operador = 2;
        }
        else
        {
            printf("\nAsegurese de escribir CONFIRMAR de forma idéntica\n");
            printf("\n|1| Intentar nuevamente\n|2| Cerrar programa con datos guardados \n");

            printf("\nOPCION: ");
            fflush(stdin);
            gets(strOpcion2);

            while (operador2 < 0)
            {
                operador2 = validacionNumeros(strOpcion2, 1, 2);

                if (operador2 >= 1 && operador2 <= 2)
                {
                    break;
                }
            }

            if (operador2 == 1)
            {
                operador = 1;
            }
            else if (operador2 == 2)
            {
                operador = 2;
            }
        }
    }
}


//----------------VALIDA QUE EL STRING INGRESADO NO TENGA NUMEROS Y SEA UNICAMENTE LETRAS-----------
int validacionString(char string[maxCaracteres])
{

    int cantidadCaracteres = strlen(string);
    int i;

    for (i = 0; i < cantidadCaracteres; i++)
    {
        char caracter = string[i];

        if (isalpha(caracter) == 0)
        {
            return 0;
        }
    }

    return 1;
}
//---------------------------------------------------------------------------------------------------------------------







//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------NAVES----------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//----------------------------------------MISIONES-----------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------






