#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "pelicula.h"
#include "parser.h"

ePeli* peli_new()
{
    ePeli* newPeli = (ePeli*) malloc(sizeof(ePeli));
    if(newPeli != NULL)
    {
        newPeli->id_peli = 0;
        strcpy(newPeli->titulo, " ");
        strcpy(newPeli->genero, " ");
        newPeli->duracion = 0;

    }
    return newPeli;
}

ePeli* peli_newParametros(int id, char* titulo, char* genero, int duracion)
{
    ePeli* newPeli = peli_new();
    if(newPeli != NULL)
    {
        if( !(set_Id(newPeli,id) &&
                set_Titulo(newPeli,titulo) &&
                set_Genero(newPeli,genero) &&
                set_Duracion(newPeli,duracion)))
        {
            peli_delete(newPeli);
            newPeli = NULL;
        }
    }
    return newPeli;
}
int peli_delete(ePeli* this)
{
    int todoOk = 0;
    if(this != NULL)
    {
        free(this);
        todoOk = 1;
    }
    return todoOk;
}

int set_Id(ePeli* this, int id)
{
    int todoOk;
    if(this != NULL && id > 0)
    {
        this->id_peli = id;
        todoOk = 1;
    }
    return todoOk;
}

int set_Titulo(ePeli* this, char* titulo)
{
    int todoOk = 0;
    if(this != NULL && titulo != NULL)
    {
        strcpy(this->titulo, titulo);
        todoOk = 1;
    }
    return todoOk;
}

int set_Genero(ePeli* this, char* genero)
{
    int todoOk = 0;
     if(this != NULL && genero != NULL)
    {
        strcpy(this->genero, genero);
        todoOk = 1;
    }
    return todoOk;
}

int set_Duracion(ePeli* this, int duracion)
{
    int todoOk = 0;
    if(this != NULL && duracion >= 0)
    {
        this->duracion = duracion;
        todoOk = 1;
    }
    return todoOk;
}

int get_Id(ePeli* this, int* id)
{
    int todoOk;
    if(this != NULL && id != NULL)
    {
        *id = this->id_peli;
        todoOk = 1;
    }
    return todoOk;
}

int get_Titulo(ePeli* this, char* titulo)
{
    int todoOk = 0;
    if(this != NULL && titulo != NULL)
    {
        strcpy(titulo, this->titulo);
        todoOk = 1;
    }
    return todoOk;
}

int get_Genero(ePeli* this, char* genero)
{
    int todoOk = 0;
    if(this != NULL && genero != NULL)
    {
        strcpy(genero, this->genero);
        todoOk = 1;
    }
    return todoOk;
}

int get_Duracion(ePeli* this, int* duracion)
{
    int todoOk = 0;
    if(this != NULL && duracion != NULL)
    {
        *duracion = this->duracion;
        todoOk = 1;
    }
    return todoOk;
}

void* peli_asignarDuracion(void* pPeli)
{
    int duracion;
    ePeli* auxPeli = NULL;
    if(pPeli != NULL)
    {

        duracion = rand() % (240 - 100 + 1) + 100;
        auxPeli = (ePeli*) pPeli;
        set_Duracion(auxPeli,duracion);

    }
    return auxPeli;
}

int filtradorGenero(void* pElement) //FUNCION INCOMPLETA
{
    int todoOk = 0;
    //char* genero;
    //ePeli* unaPeli = NULL;

    printf("Ingrese genero de peliculas que desea ver: \nAction\nAdventure\nComedy\nDocumentary\nDrama\nHorror\nMusical\nRomance\nThriller\nWestern");
    fflush(stdin);
    //gets(genero);

    if(pElement != NULL)
    {
        /*unaPeli = (ePeli*) pElement;
        if(unaPeli->genero == genero)
        {
            todoOk = 1;
        }*/
    }
    return todoOk;
}

int peli_cmpDuracion(void* peli1, void* peli2)
{
    int todoOk = 0;

    ePeli* auxPeli1 = NULL;
    ePeli* auxPeli2 = NULL;

    if(peli1 != NULL && peli2 != NULL)
    {
        auxPeli1 = (ePeli*) peli1;
        auxPeli2 = (ePeli*) peli2;

        if(auxPeli1->duracion > auxPeli2->duracion)
        {
            todoOk = 1;
        }
        else
        {
            if(auxPeli1->duracion < auxPeli2->duracion)
            {
                todoOk = -1;
            }
        }
    }
    return todoOk;
}

int peli_cmpGenero(void* peli1, void* peli2)
{
    int todoOk = 0;

    ePeli* auxPeli1 = NULL;
    ePeli* auxPeli2 = NULL;

    if(peli1 != NULL && peli2 != NULL)
    {
        auxPeli1 = (ePeli*) peli1;
        auxPeli2 = (ePeli*) peli2;

        if(strcmp(auxPeli1->genero, auxPeli2->genero)> 0)
        {
            todoOk = 1;
        }
        else
        {
            if(strcmp(auxPeli1->genero, auxPeli2->genero) <0)
            {
                todoOk = -1;
            }
        }
    }
    return todoOk;
}

