#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"
#include "controller.h"
#include "pelicula.h"

int menu();

int main()
{
    srand(time(NULL));
    char salir = 'n';
    char path [50];

    int flagDuracion = 0;

    LinkedList* listaPelis = ll_newLinkedList();
    LinkedList* listaMapeada = NULL;
    LinkedList* listaGenero = NULL;
    LinkedList* listaOrdenada = NULL;

    do
    {
        switch(menu())
        {
            case 1:
                system("cls");
                printf("Nombre del archivo principal: movies.csv\n\n");
                printf("Ingrese nombre del archivo para abrirlo: ");
                fflush(stdin);
                gets(path);
                if(controller_loadFromText(path, listaPelis))
                {
                    printf("\nArchivo cargado con exito!\n\n");
                }
                break;

            case 2:
                if(ll_isEmpty(listaPelis) == 0)
                {
                    system("cls");
                    controller_listarPelis(listaPelis);
                }
                else
                {
                    printf("\nNo se ha cargado ningun archivo!\n\n");
                }
                break;

            case 3:
                if(ll_isEmpty(listaPelis) == 0)
                {
                    listaMapeada = ll_map(listaPelis, peli_asignarDuracion);
                    if(listaMapeada != NULL)
                    {
                        printf("\nDuraciones asignadas!\n\n");
                        flagDuracion = 1;
                    }
                }
                else
                {
                    printf("\nNo se ha cargado ningun archivo!\n\n");
                }

                break;
            case 4:

                if(flagDuracion)
                {

                    listaGenero = ll_filter(listaPelis, filtradorGenero);
                    if(listaGenero != NULL)
                    {
                        system("cls");
                        printf("\n      *** LISTA DE GENERO SELECCIONADO  ***\n\n");
                        controller_listarPelis(listaGenero);
                        if(controller_saveAsText("listaGenero.csv", listaGenero))
                        {
                            printf("\nSe guardo el archivo listaGenero.csv con exito!\n\n");
                        }
                    }
                }
                else
                {
                    printf("\nNo se han cargado ningun archivo o sus estadisticas!\n\n");
                }
                break;

            case 5:
                if(flagDuracion && !ll_sort(listaPelis, peli_cmpDuracion, 0))
                {
                    if(!ll_sort(listaPelis, peli_cmpGenero, 1))
                    {
                        system("cls");
                        printf("\n      *** LISTA DE PELIS ORDENADA GENERO / DURACION  ***\n\n");
                        controller_listarPelis(listaPelis);
                    }
                }
                else
                {
                    printf("\nNo se han cargado ningun archivo o sus estadisticas!\n\n");
                }
                break;

            case 6:
                if(flagDuracion && listaOrdenada==NULL)
                {
                    listaOrdenada = ll_clone(listaPelis);
                    controller_listarPelis(listaOrdenada);
                    printf("\nSe ha clonado la lista de Peliculas correctamente.\n\n");

                    if(controller_saveAsText("listaOrdenada.csv", listaOrdenada))
                    {
                        printf("Se guardo el archivo listaOrdenada.csv con exito!\n\n");
                    }

                }
                else
                {
                    printf("\nNo se ha podido clonar la lista de Peliculas.\n\n");
                }
                break;

            case 7:
                printf("\nConfirma salida? (s/n): ");
                fflush(stdin);
                salir=getchar();
                if(salir != 'n' && salir != 's')
                {
                    printf("\nOpcion Invalida!\n\n");
                }
                break;

            default:
            printf("\nOpcion Invalida!\n\n");
        }
        system("pause");
    }while(salir != 's');

    ll_deleteLinkedList(listaPelis);
    ll_deleteLinkedList(listaMapeada);
    ll_deleteLinkedList(listaGenero);
    ll_deleteLinkedList(listaOrdenada);

    return 0;
}

int menu()
{
    int opcion;

    system("cls");
    printf("              ***MOVIES***\n\n");
    printf("  1. Cargar Archivo.\n");
    printf("  2. Imprimir lista.\n");
    printf("  3. Asignar tiempos:\n");
    printf("  4. Filtrar por tipo: (INCOMPLETO)\n");
    printf("  5. Mostrar GENEROS/DURACIONES ordenadas:\n");
    printf("  6. Guardar lista de peliculas:\n");
    printf("  7. Salir.\n\n");

    printf("Ingrese opcion: ");

    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}
