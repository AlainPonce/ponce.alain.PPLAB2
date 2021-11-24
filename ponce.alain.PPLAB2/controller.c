#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "controller.h"
#include "pelicula.h"
#include "parser.h"

int controller_loadFromText(char* path , LinkedList* pListaPelis)
{
    int todoOk = 0;
    FILE* f = fopen(path, "r");

    if(f == NULL)
    {
        printf("\nNo se pudo abrir el archivo.\n\n");
    }
    else
    {
        parser_PeliFromText(f, pListaPelis);
        todoOk=1;
    }

    fclose(f);

    return todoOk;
}

int controller_saveAsText(char* path , LinkedList* pListaPelis)
{
    int auxId;
	char auxTitulo[128];
	char auxGenero[128];
	int auxDuracion;

    int todoOk = 0;

    ePeli* auxPeli;

    FILE* f;

    if(path!=NULL && pListaPelis!=NULL)
	{
		f = fopen(path,"w");
		if(f != NULL && ll_len(pListaPelis) >0)
        {
            fprintf(f,"id_peli,titulo,genero,duracion\n");

            for(int i= 0; i<ll_len(pListaPelis); i++)
            {
                auxPeli = ll_get(pListaPelis, i);

                if(auxPeli != NULL && get_Id(auxPeli, &auxId)
                                     && get_Titulo(auxPeli, auxTitulo)
                                     && get_Genero(auxPeli, auxGenero)
                                     && get_Duracion(auxPeli, &auxDuracion))
                {
                    fprintf(f, "%d,%s,%s,%d\n", auxId, auxTitulo, auxGenero, auxDuracion);
                    todoOk=1;
                    //break;
                }
                else
                {
                    ll_pop(pListaPelis, i);
                    printf("\nNo se pudo guardar el archivo");
                }
            }
        }
        else
        {
            printf("No se pudo abrir el archivo");
        }
    }

    fclose(f);

    return todoOk;
}
int controller_listarPelis(LinkedList* pListaPelis)
{
    int todoOk = 0;
    int tam;
    ePeli* auxPeli = NULL;
    if(pListaPelis != NULL)
    {
        tam = ll_len(pListaPelis);
        printf("  Id     Titulo                         Genero                Duracion\n");
        printf("----------------------------------------------------------------------\n");
        for(int i = 0; i < tam; i++)
        {
            auxPeli = (ePeli*) ll_get(pListaPelis,i);
            if(auxPeli != NULL)
            {
                controller_listarPeli(auxPeli);
            }
        }

        todoOk = 1;
    }
    return todoOk;
}

int controller_listarPeli(ePeli* unaPeli)
{
    int todoOk = 0;
    int id;
    char titulo[28];
    char genero[28];
    int duracion;

    if(unaPeli != NULL &&
            get_Id(unaPeli,&id) &&
            get_Titulo(unaPeli,titulo) &&
            get_Genero(unaPeli,genero) &&
            get_Duracion(unaPeli,&duracion))
    {
        printf(" %3d     %-30s %-11s           %d\n",
               id,
               titulo,
               genero,
               duracion);
        todoOk = 1;
    }
    return todoOk;
}
