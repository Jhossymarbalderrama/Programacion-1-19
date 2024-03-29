#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "autos.h"

/** \brief  Harcodeo de Autos.
 * \param  eAuto vec[], int tam, int cantidad
 * \return int cont
 */
int hardcodearAutos( eAuto vec[], int tam, int cantidad)
{
    int cont = 0;

    eAuto suplentes[]=
    {
        { 100, "AA097DB", 1000, 5000,2016,0},
        { 101, "AUE883", 1003, 5004,2015,0},
        { 102, "MBV897", 1004, 5002,2010,0},
        { 103, "OCO641", 1002, 5000,2008,0},
        { 104, "AC186JB", 1001, 5002,2015,0},
        { 105, "JOL136", 1003, 5001,2011,0},
        { 106, "HOK782", 1004, 5003,2008,0},
        { 107, "AB148CV", 1003, 5002,2011,0},
        { 108, "AC192AB", 1003, 5000,2005,0},
        { 109, "GNQ963", 1002, 5002,2019,0}
    };

    if( cantidad <= 10 && tam >= cantidad)
    {
        for(int i=0; i < cantidad; i++)
        {

            vec[i] = suplentes[i];
            cont++;
        }
    }

    return cont;
}

/** \brief Inicializacion de Autos.
 * \param eAuto autos[], int tam
 * \return
 */
void inicializarAutos(eAuto autos[], int tam){
    for(int i = 0; i < tam; i++)
    {
        autos[i].isEmpty = 1;
    }
}

/** \brief Muestro un Auto
 * \param eAuto x, eMarca marcas[], int tam, eColor colores[]
 * \return
 */
void mostrarAuto(eAuto x, eMarca marcas[], int tam, eColor colores[])
{
    char descMarca[20];
    char descColor[20];

    cargarDescMarca(x.idMarca, marcas, tam, descMarca);
    cargarDescColor(x.idColor, colores, tam, descColor);
    printf("  %d    %10s   %10s   %s      %4d    \n",
           x.id,
           x.patente,
           descMarca,
           descColor,
           x.modelo
           );
}

/** \brief Muestro Autos
 * \param   eAuto autos[], int tam,  eColor colores[], int tamColor, eMarca marcas[], int tamMarcas
 * \return
 */
void mostrarAutos (eAuto autos[], int tam,  eColor colores[], int tamColor, eMarca marcas[], int tamMarcas)
{

    int flag = 0;
    system("cls");

    printf(" ID      Patente          Marca       Color       Modelo  \n\n");

    for(int i=0; i < tam; i++)
    {
        if( autos[i].isEmpty == 0)
        {
            mostrarAuto(autos[i],marcas,tam,colores);
            flag = 1;
        }
    }

    if( flag == 0)
    {
        printf("\nNo hay Autos que mostrar\n");
    }

    printf("\n\n");
}

/** \brief Alta de un Nuevo Auto en la Estructura
 * \param   int id,char patente[],int idMarca,int idColor,int modelo
 * \return
 */
eAuto newAuto(int id,char patente[],int idMarca,int idColor,int modelo)
{

    eAuto al;

    al.id = id;
    strcpy( al.patente, patente);
    al.idMarca = idMarca;
    al.idColor = idColor;
    al.modelo = modelo;
    al.isEmpty = 0;

    return al;
}

/** \brief Busco un Indice Vacio
 * \param   eAuto vec[], int tam
 * \return indice
 */
int buscarLibre(eAuto vec[], int tam)
{
    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if( vec[i].isEmpty == 1 )
        {
            indice = i;
            break;
        }
    }
    return indice;
}

/** \brief Alta de Auto
 * \param   eAuto autos[], int tam , eMarca marcas[], int tamMarcas, eColor colores[], int tamColores
 * \return  todoOk
 */
int altaAuto(eAuto autos[], int tam , eMarca marcas[], int tamMarcas, eColor colores[], int tamColores)
{
    int todoOk = 0;
    int indice;
    char patente[20];
    int idMarca;
    int idColor;
    int modelo;
    int id;
    int a;

    system("cls");

    printf("----- Alta Auto -----\n\n");

    indice = buscarLibre(autos, tam);

    if( indice == -1)
    {
        printf("\nSistema completo\n\n");
    }
    else
    {
        printf("Ingrese id del Auto: ");
        scanf("%d", &id);
        a = buscarIdAuto(id,autos,tam);
        if(a == -1){
        }else{

            do{
                printf("Ya Existe un vehiculo ingresado con esa ID:\n");
                printf("  ID        Patente        Marca     Color    Modelo  \n");
                mostrarAuto(autos[a],marcas,tam,colores);

                system("pause");
                system("cls");
                printf("Ingrese otro Id: ");
                scanf("%d", &id);
                a = buscarIdAuto(id,autos,tam);
            }while(a != -1);
        }

        printf("Ingrese patente: ");
        fflush(stdin);
        gets(patente);



        do{
        printf("\n");
        mostrarMarcas(marcas,tamMarcas);
        printf("Ingrese idMarca: ");
        scanf("%d", &idMarca);


        }while(idMarca < 1000 && idMarca > 1005);
        /*
    while(idMarca < 1000 && idMarca > 1005){
        printf("error.  id Marca incorrecto.\n");
        printf("Ingrese idMarca: ");
        fflush(stdin);
        scanf("%d", &idMarca);
    }
*/

        do{
        mostrarColores(colores,tamColores);
        printf("Ingrese idColor: ");
        fflush(stdin);
        scanf("%d", &idColor);
        }while(idColor < 5000 && idColor > 5005);
        /*
    while(idColor < 5000 && idColor > 5005){
        printf("error.  id color incorrecto.\n");
        printf("Ingrese idColor: ");
        fflush(stdin);
        scanf("%d", &idColor);
    }
*/

        printf("Ingrese modelo(anio): ");
        scanf("%d", &modelo);

        autos[indice] = newAuto(id,patente,idMarca,idColor,modelo);
        todoOk = 1;
        printf("Alta exitosa!!\n\n");
    }

    return todoOk;
}

/** \brief Busco un Auto Por Patente
 * \param   char patente[], eAuto autos[], int tam
 * \return indice
 */
int buscarPatente(char patente[], eAuto autos[], int tam)
{
    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if( strcmp(autos[i].patente,patente) == 0 && autos[i].isEmpty == 0)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

/** \brief Modificacion de Auto
 * \param   eAuto autos[], int tam,eColor colores[], int tamColores,eMarca marcas[],int tamMarcas
 * \return  todoOk
 */
int modificarAuto(eAuto autos[], int tam,eColor colores[], int tamColores,eMarca marcas[],int tamMarcas){

    int todoOk = 0;
    char patente[20];
    int indice;
    system("cls");
    printf("----- Modificar Auto -----\n\n");
    mostrarAutos(autos,tam,colores,tamColores,marcas,tamMarcas);
    printf("\nIngrese patente: ");
    fflush(stdin);
    gets(patente);
    int opcion;

    indice = buscarPatente(patente,autos,tam);

    if( indice == -1)
    {
        printf("No existe un auto con esa patente en el sistema\n\n");

    }else{
        system("cls");
        printf(" ID    Patente    Marca   Color  Modelo  \n\n");
        mostrarAuto(autos[indice],marcas,tam,colores);
        printf("\n\n");
        printf("1- Modificar Color\n");
        printf("2- Modificar Modelo\n");
        printf("3- Salir\n\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
    case 1:
            mostrarColores(colores,tamColores);
            printf("Ingrese nuevo id Color: ");
            fflush(stdin);
            scanf("%d",&autos[indice].idColor);
    while(autos[indice].idColor < 5000 && autos[indice].idColor > 5005){
        printf("error.  id Color incorrecto.\n");
        printf("Ingrese idColor: ");
        fflush(stdin);
        scanf("%d", &autos[indice].idColor);
        }

            break;
    case 2:
            printf("Ingrese Nuevo modelo: ");
            fflush(stdin);
            scanf("%d",&autos[indice].modelo);
            break;

    case 3:
            printf("Se ha cancelado la modificacion ");
            break;

    }
    todoOk = 1;
    system("cls");
    printf("\nModificacion excitosa!!\n\n");
}
    return todoOk;
}

/** \brief Baja de Auto
 * \param   eAuto autos[], int tam, eColor colores[], int tamColores,eMarca marcas[], int tamMarcas
 * \return todoOk
 */
int bajaAuto (eAuto autos[], int tam, eColor colores[], int tamColores,eMarca marcas[], int tamMarcas)
{
    int todoOk = 0;
    char patente[20];
    int indice;
    char confirma;
    system("cls");
    printf("----- Modificar Auto -----\n\n");
    mostrarAutos(autos,tam,colores,tamColores,marcas,tamMarcas);
    printf("\nIngrese patente: ");
    fflush(stdin);
    gets(patente);

    indice = buscarPatente(patente,autos,tam);

    if( indice == -1)
    {
        printf("No existe un Auto con esa patente\n\n");

    }
    else
    {
        mostrarAuto(autos[indice],marcas,tam,colores);

        printf("\nConfirma baja?");
        fflush(stdin);
        scanf("%c", &confirma);

        if( confirma == 's')
        {
            autos[indice].isEmpty = 1;
            todoOk = 1;
            printf("Baja exitosa!!!");
        }
        else
        {
            printf("Se ha cancelado la operacion");
        }
    }

    return todoOk;
}

/** \brief Busco la ID del Auto
 * \param   int id, eAuto autos[], int tam
 * \return indice
 */
int buscarIdAuto(int id, eAuto autos[], int tam)
{
    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if( autos[i].id == id && autos[i].isEmpty == 0)
        {
            indice = i;
            break;
        }
    }
    return indice;
}
