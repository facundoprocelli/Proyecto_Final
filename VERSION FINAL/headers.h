
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//-------------------CONSTANTES---------------------------------
#define maxCaracteres         100
#define cantNacionalidades    213
#define cantEspecialidades    5
#define cantidadOpciones 6
#define cantTiposNave         3
#define cantEstados           4
#define minimaCantidadOpciones 1
#define maxCantidadMenu 2
#define maxCantidadOpciones 3
#define maxCantidadModificacionesAstro 10
#define edadMaxima 100
#define edadMinima 18
#define maxCantidadHoras 10000
#define maxcantidadViajes 500
#define maxCantidadModificacionesNave 4
#define minIdAstro 101
#define minIdNave 1001
#define cantidadTipoBusquedaEdad 3
#define cantEstadosNave 5
#define detalleDeMision 200
#define cantCargamentos 6
#define cantDestinos 6
#define maxTripulates 3
#define maxCantidadModificacionesMision 6
#define minIdMision 1
#define cantEstadosMision 5
#define cantOpcionesMostrarMisiones 4
#define estadiaEnIEE 200


//---------------------------ARCHIVOS----------------------------

#define archiAstronauta "astronauta.bin"
#define archiNave "nave.bin"
#define archiMision "mision.bin"


//-------------------ESTRUCTURAS------------------------------------
//------------------ASTRONAUTA--------------------------------------
typedef struct
{
    int  ID;
    char nombre[maxCaracteres];
    char apellido[maxCaracteres];
    char apodo[maxCaracteres];
    int  edad;
    char nacionalidad[maxCaracteres];
    char especialidad[maxCaracteres];
    int  horasVueloAcumuladas;
    int  misionesEspacialesRealizadas;
    int  horasAcumuladasEEI;
    int  estado;
} astronauta;


//-------------------------NAVE------------------------
typedef struct
{

    int  ID;
    char tipoNave[maxCaracteres];
    int  cantVuelosRealizados;
    int  horasAcumuladasVuelo;
    char estado[maxCaracteres];
} nave;

//--------------------------MISIONES---------------------



typedef struct
{

    int  ID;
    int  iDNave;
    char estado[maxCaracteres];
    char cargamento[maxCaracteres];
    char destino[maxCaracteres];
    int  tripulacion[maxTripulates];
    char detalleMision[detalleDeMision];

} stMision;


//-------------------DECLARACION DE FUNCIONES-------------------------------------------
void funcionAstronautas();
void funcionNaves();

//------------------CARGAR ITEMS------------------------
void cargarNombre(astronauta* astro);

void cargarAstronautaNuevo(astronauta* astro);

void cargarApellido(astronauta* astro);

void cargarApodo(astronauta* astro);

void cargarNacionalidad(astronauta* astro);

void cargarEdad(astronauta* astro);

void cargarEspecialidad(astronauta* astro);

void astronautasPredeterminados();

void buscarAstronautaPorId();

void cargarHorasVueloAcumuladas();

void cargarHorasEnEEI(astronauta *astro);

void cargarMisionesEspaciales(astronauta *astro);


//---------------------MOSTRAR COSAS------------------

void mostrarDatosAstronauta(astronauta astronauta);

void mostrarCatalogoNacionalidades(char nacionalidades[66][maxCaracteres]);

void mostrarEspecialidades(char especialidades[][maxCaracteres]);

void baseNacionalidades(char nacionalidades[cantNacionalidades][maxCaracteres]);

void especialidadesAstronauta(char especialidades[][maxCaracteres]);

void mostrarAstronautaArchivo();

void menuModificacionesAstro();

void menuOpcionesFunciones();

void menuIDAstro();

void mostrarListaIDAstro();


void mostrarAstronautas();

void mostrarListaOpcionesMostrar();

void mostrarAstronautasRetirados();

void mastrarAstronautasActivos();

void mostrarAstronautasActivos();

void mostrarIDAstro();



//----------------------VALIDACIONES------------------------

int  validacionEdad(int edad);

int  validacionString(char string[maxCaracteres]);

int validacionEspecialidad (int seleccion);

int validacionNacionalidad(char nacionalidad[maxCaracteres], char nacionalidades[cantNacionalidades][maxCaracteres]);

void validacionRespuesta(char valor);

int validacionHoras(int horas);

int confirmarID(int idBuscado, int *confirm );

int validacionNumeros(char str[100], int min, int max);

int validacionIDAstro(int id);

//-----------------DATOS DE RELEVANCIA-------------------

int ultimoIdAstro();

int tamanoArchiAstro();

int idBuscadoAstro();

//----------------MENUES-------------------------------

void menuConsultasAstro();

void menuConsultaEdadesAstro();

//--------------------MODIFICAR DATOS DEL ASTRONAUTA------------

void cambiarEstadoAstronauta();

void modificarAstronauta();

void cambiarNombreAstronauta();

void cambiarApellidoAstronauta();

void cambiarApodoAstronauta();

void cambiarEdadAstronauta();

void cambiarNacionalidadAstronauta();

void cambiarEspecialidadAstronauta();

void cambiarHorasVueloAcumuladasAstronauta();

void cambiarHorasEnEEI();

void cambiarMisionesEspaciales();

void reiniciarSistema();

//-------------CONSULTAR DATOS ASTRONAUTA-----------------------------


void consultarAstronauta();

void buscarAstronautaPorNombre();

int  validarNombreConsulta(char nombre[]);

void mostrarListaNombres();



void buscarAstronautaPorApellido();

int  validarApellidoConsulta(char apellido[]);

void mostrarListaApellido();



void buscarAstronautaPorApodo();

int  validarApodoConsulta(char apodo[]);

void mostrarListaApodo();



void buscarAstronautaPorEdad();



void consultarEdadExacta();

int validarEdadConsulta(int edad);

void mostrarListaEdades();

void consultarMenores();

void consultarMayores();

void buscarAstronautaPorNacionalidad();

void buscarAstronautaPorEspecialidad();

void  buscarAstronautaPorHorasAcumuladas();

int validarHorasConsulta(int horas);

void consultarHorasExactas();

void consultarMayoresHoras();

void consultarMenoresHoras();

void mostrarListaHoras();

void buscarAstronautaPorHorasEnIEE();

void consultarHorasIEEExacta();

int validarHorasIEEConsulta(int horas);

void mostrarListaIEE();

void consultarMayoresIEE();

void consultarMenoresIEE();

void    menuConsultaHorasIEEAstro();

void buscarAstronautaPorViajes();

void consultarViajesExacto();

int validarViajesAstro(int misiones);

void mostrarListaViajesAstro();

void consultarMayoresViajesAstro();

void consultarMenoresViajesAstro();

void    menuConsultaViajesAstro();


//----------------------------SALUDO FINAL---------------------

void saludoFinal(char valor[2]);

void mostrarOpcionesPrincipales();

//-------------------------------------------------------------------------------------------------------------------
//------------------------NAVES-----------------------------


//-----------------------TIPO DE NAVE--------------------------
void cargarTipoNave(nave* nav);

void mostrarTipoNave(char tiposNaves[cantTiposNave][maxCaracteres]);

void menuTiposNave(char tiposNave[cantTiposNave][maxCaracteres]);

int validacionTipoNave (int seleccion);

int validarVuelosNave(int vuelos);

int validarHorasNave(int vuelos);



//---------------------ESTADO----------------------------
void tiposEstado(char estados[cantEstados][maxCaracteres]);

void mostrarEstados(char estados[cantEstados][maxCaracteres]);

int validacionEstado(int seleccion);

void cargarEstado(nave* nav);


//------------------------------ID-------------------------
int ultimoIdNave();

int tamanoArchiNave();

void menuIDNave();

int idBuscadoNave();

int validacionIDNave(int id);


//NAVES PREDETERMINADAS
void navesPredeterminadas();

//-------------------------MOSTRAR COSAS---------------------
void mostrarDatosNave(nave nav);

void mostrarArchivoNaves();

void mostrarListaIDNave();

void mostrarListaOpcionesMostrarNave();

void mostrarNavesEnMision();

void mostrarNavesEnMantenimiento();

void mostrarNavesListas();

void mostrarNavesRetiradas();

void mostrarListaVuelosNave();

void mostrarListaHorasNave();

void mostrarArchivoMisiones();


//-----------------------MODIFICACIONES NAVES---------------------
void cambiarEstadoNave();

void menuModificacionesNave();

void cambiarEstadoNave();

void cambiarTipoNave();

void cambiarHorasVueloAcumuladasNave();

void cargarHorasVueloAcumuladasNave(nave* nav);

void cargarCantVuelosHechosNave(nave* nav);

void cambiarVuelosHechosNave();

void menuOpcionesFuncionesNave();

//---------------------------CONSULTAR NAVES----------------------

void menuConsultasNave();

void menuConsultasHorasNave();

void consultarNaves();

void consultarVuelosExactoNave();

void consultarMayoresVuelosNave();

void consultarMenoresVuelosNAve();

void consultarHorasExactoNave();

void consultarMayoresHorasNave();

void consultarMenoresHorasNave();

//---------------------BSUCAR NAVES------------------------
void buscarNavePorTipo();

void buscarNavePorVuelos();

void buscarNavePorHoras();

void buscarNavesPorEstado();



//---------------------------MISIONES-------------------------------
void misionPredeterminada();

void funcionMisiones();

int ultimoIdMision();

//-------------------MOSTRAR MISIONES---------------------

int mostrarListaTripulantesActivos(int tripulantes[]);
int mostrarNavesDisponibles(int idDisponibles[]);
void mostrarMenuCargamento(char menuCargamentoMision[][maxCaracteres]);

void mostrarListaIDMision();

void mostrarMisiones();

void mostrarDatosMision(stMision * misio);

void mostrarListaOpcionesMostrarMisiones();

void mostrarMenuDestino(char menuDestinoMision[][maxCaracteres]);

void mostrarDosEstados(char estadosMision[][maxCaracteres]);

int mostrarMisionesListas();

int mostrarMisionesEnVuelo();

//------------------CONSULTAR MISIONES----------------------

void consultarMisiones();


//-------------------CARGAR NAVES----------------------------
int cargarIdNaveMision(stMision* misio);

void cargarCargamentoMision(stMision * misio);

void cargarDestinoMision(stMision * misio);

int cargarTripulantesMision(stMision * misio);

void cargarDetalleMision(stMision * misio);




//--------------------MENUES------------------------

void menuCargamento(char menuCargamentoMision[][maxCaracteres]);

void menuHorasDeViaje(int horasDeViaje[]);

void menuModificacionesMision();

void menuDestino(char menuDestinoMision[][maxCaracteres]);

void menuIDMision();

//---------------------BUSCAR-----------------------------


void buscarMisionPorId();

int buscarPosicionLugar(char cargamentos[][maxCaracteres], char lugar[]);

void buscarMisionPorCargamento();

void buscarMisionPorDestino();

void buscarMisionPorEstado();

void buscarMisionPorTipoNave();

void tiposEstadoMisionModificacionListo(char estadosMision[2][maxCaracteres]);

void tiposEstadoMisionModificacionEnVuelo(char estadosMision[2][maxCaracteres]);

void tiposEstadoMisionModificacion(char estadosMision[cantEstadosMision][maxCaracteres]);

int idBuscadoMision();



//--------------------VALIDAR----------------------

int validarIdAstronautaMision(int tripulates[], int operador, int validos);


int confirmacion(int dato);


int validarIdNaveMision(int idDisponibles[], int operador, int validos);

//----------------------MODIFICAr----------------------------
void cambiarEstadoNaveEnMision(int id);

void cambiarHorasDeVueloAstro(char lugar[], int id, int id1, int id2);

void modificarMision();

void cambiarHorasAstronautas(int posicion, int id);

void cambiarHorasDeVueloNave(int id, char lugar[]);

void cambiarVuelosHechosAstronauta(int id);

void cambiarVuelosHechosNaveMision(int id);

void cambiarEstadoMision();

void cambiarEstadoNaveEnMision(int id);

void cambiarHorasNaveMisio(int posicion, int id);

void cambiarDestinoMision();

void cambiarCargamentoMision();

void cambiarDetalleMision();

void  cargarEstadoModificacionMision(stMision* misio);

int elegirMisionLista();

void cambiarEstadoDesdeListo(int id) ;

int elegirMisionEnMision();

void cambiarEstadoDesdeEnVuelo(int id);

void  cargarEstadoModificacionMisionEnMision(stMision* misio);

void  cargarEstadoModificacionMisionListo(stMision* misio);

int cargarNuevaMision(stMision * misio);

void cambiarNaveALista();

void cambiarNaveAMision();
