//  Profesor jesus Saturno
//  seccion 2
//  agenda telefonica usando listas enlazadas
//  Created by jhonny arana and Luis hernandez on 14/11/15.
//  Copyright © 2015 jhonny. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //libreria para manejar y copiar cadena de caracteres con strcpy(Valores_viejos,Valores_nuevos)

//definición de la estructura persona
typedef struct _Persona{
    struct  _Persona *siguiente;
    struct  _Persona *anterior;
    int     id;
    char	nombre[25];
    char 	apellido[25];
    char    direccion[50];
    char 	telefono[25];
}Persona;

//inicialización para los punteros de la lista
Persona *primera_persona = NULL;
Persona *ultima_persona = NULL;

//función para agregar una persona a la agenda
int agregar(){
    Persona *nuevaPersona;
    //reservo espacio de memoria con malloc
    nuevaPersona = (Persona *) malloc (sizeof (Persona));
    printf("\n------Agregando persona-----");
    printf("\nIngrese nombre:");
    scanf( "%s", nuevaPersona->nombre);
    printf("\nIngrese apellido:");
    scanf( "%s", nuevaPersona->apellido);
    printf("\nIngrese teléfono (ejemplo 0412-000000):");
    scanf( "%s", nuevaPersona->telefono );
    // se limpia la basura que trae el buffer del teclado
    while(getchar() != '\n');
    // se piden las palabras con espacios
    printf("\nIngrese dirección:");
    // se leen las palabras con espacios
    scanf( "%[^\n]", nuevaPersona->direccion );
    if(ultima_persona == NULL){
        primera_persona = ultima_persona = nuevaPersona;
        //si la lista esta vacia va a ser el primer id
        nuevaPersona->id = 1;
    } else {
        // si la lista no esta vacia va a ser el id anterior + 1
        nuevaPersona->id = ultima_persona->id + 1;
        ultima_persona->siguiente = nuevaPersona;
        nuevaPersona->anterior = ultima_persona;
        ultima_persona = nuevaPersona;
    }
    return 1;
}

//función para borrar una persona de la agenda
int borrar(){
    Persona *tempPersona = primera_persona;
    int id_borrar;
    printf("\n----Borrando persona de agenda----");
    printf("\n Introduzca el id persona a borrar de la agenda:");
    scanf("%d",&id_borrar);
    //while para recorrer la agenda
    do{
        //si la palabra clave a buscar coincide con el id de la persona
        if(id_borrar == tempPersona->id){
            //si la persona a borrar es la primera de la lista
            if (tempPersona == primera_persona){
                //si la primera persona no tiene ninguna en siguiente
                if(tempPersona->siguiente == NULL){
                    primera_persona = NULL;
                    ultima_persona = NULL;
                }else{
                    //asigno a la siguiente persona de la lista como primera si está existe
                    primera_persona = tempPersona->siguiente;
                    primera_persona->id = 1; // asigno id 1 si no tiene nada antes ni despues
                    primera_persona->anterior = NULL;
                 }
                return 1;
            }
            // si la persona a borrar es la ultima de la lista
            if(tempPersona == ultima_persona){
                ultima_persona = tempPersona->anterior;
                ultima_persona->siguiente = NULL;
                return 1;
            }
            
            //se re-organizan las posiciones
            tempPersona->siguiente->anterior = tempPersona->anterior;
            tempPersona->anterior->siguiente = tempPersona->siguiente;
            return 1;
            
        }
        
        tempPersona = tempPersona->siguiente;
        
    }while(tempPersona != NULL);
    
    primera_persona->id=1;

    return 0;
}

//función para modificar los datos de una persona que ya exista en la agenda
int modificar(){
    Persona *tempPersona = primera_persona;
    int id_temp, opcion;
    //variables para los datos nuevos
    char nombre_nuevo[25],apellido_nuevo[25],direccion_nueva[50],telefono_nuevo[25];
    printf("\n----Modificando datos----");
    printf("\nIngrese el id de la persona para modificar los datos en la agenda:");
    scanf("%d",&id_temp);
    // limpio pantalla de saltos de linea
    while(getchar() != '\n');
    //do para recorrer la agenda
    do{
        //si el id es igual a la buscada
        if(id_temp == tempPersona->id){
            printf("\nRegistros encontrados que coinciden con id %d:",id_temp);
            printf("\n Nombre: \t\t %s \n Apellido: \t %s \n Dirección: \t %s\n Teléfono: \t %s\n",tempPersona->nombre,tempPersona->apellido,tempPersona->direccion,tempPersona->telefono);
            printf("\nIndique la opcion de lo que desea modificar:");
            printf("\n Nombre \t\t --> 1\n Apellido \t --> 2\n Direccion \t --> 3\n Telefono \t --> 4 \n ");
            scanf("%d",&opcion);
            //pido los nuevos datos para el registro
            if (opcion==1) {
                printf("Ingrese el nuevo Nombre:");
                scanf( "%s", nombre_nuevo);
                strcpy(tempPersona->nombre, nombre_nuevo);
                //asigno los nuevos valores con strcpy
                return 1;
            }
            else if (opcion==2){
                printf("Ingrese el nuevo Apellido:");
                scanf( "%s", apellido_nuevo);
                strcpy(tempPersona->apellido, apellido_nuevo);
                //asigno los nuevos valores con strcpy
                return 1;
            }else if (opcion==3){
                printf("Ingrese el nuevo teléfono");
                scanf( "%s", telefono_nuevo);
                strcpy(tempPersona->telefono, telefono_nuevo);
                //asigno los nuevos valores con strcpy
                return 1;
            }else if (opcion==4){
                while(getchar() != '\n');
                printf("Ingrese la nueva dirección:");
                scanf( "%[^\n]", direccion_nueva);
                //asigno los nuevos valores con strcpy
                strcpy(tempPersona->direccion, direccion_nueva);
                return 1;
            }else{
                printf("opcion invalida");
                return 1;
            }
            
        }
        //avanzo al siguiente en la lista
        tempPersona = tempPersona->siguiente;
    }while(tempPersona != NULL);
    return 0;
}

//función que recorre toda la agenda completa mostrando todos los registros en pantalla
int ver_agenda_completa(){
    
    Persona *tempPersona=primera_persona;
    
    printf("\n----Mostrando agenda completa----");
    do{
        //muestro datos de la persona
        printf("\n\nid:%d\t",tempPersona->id);
        printf("Nombre:%s\t",tempPersona->nombre);
        printf("Apellido:%s\t",tempPersona->apellido);
        printf("Dirección:%s\t",tempPersona->direccion);
        printf("Teléfono:%s\n",tempPersona->telefono);
        //avanzo al siguiente en la lista
        tempPersona=tempPersona->siguiente;
    }while(tempPersona != NULL);
    
    return 1;
}
//funcion que reordena los id despues de borrar
int reordenar(){
    Persona *tempPersona = primera_persona->siguiente;
    do{
        tempPersona->id = tempPersona->anterior->id + 1 ;
        tempPersona = tempPersona->siguiente;
    }while (tempPersona!=NULL);
    
    return 0;
}
//función que valida la opción ingresada desde el menú
int valida_opcion(int opcion){
    if (opcion >= 1 && opcion <=5 )
    {
        return 1;
    }else{
        return 0;
    }
}

//función para comprobar si la lista está vacia
int lista_vacia(){
    //Si no hay personas que mostrar
    if(primera_persona == NULL){
        printf("\n\nNo hay registros en la agenda.");
        return 1;
    }else{
        return 0;
    }
}

//función para mostrar el menú principal de opciones de la agenda
int mostrar_menu(){
    int opcion;
    printf("\n\n\t\t\t\t\t\t----Menú principal----");
    printf("\n\t\t\tSeleccione una opción:");
    printf("\n\t\t\t\t1-añadir una persona");
    printf("\n\t\t\t\t2-eliminar a una persona");
    printf("\n\t\t\t\t3-Modificar datos de una persona existente en la agenda");
    printf("\n\t\t\t\t4-Ver toda la agenda");
    printf("\n\t\t\t\t5-Salir del programa");
    printf("\n\t\t\topcion:");
    scanf("%i",&opcion);
    while(getchar() != '\n');//limpio buffer
    if(valida_opcion(opcion)){
        switch(opcion){
            case 1:
                if(!agregar()){
                    printf("\nError en al agregar persona.");
                }
                break;
            case 2:
                if(lista_vacia()){break;}
                if(borrar()){
                    reordenar();
                }else{
                    printf("\nNo existen elementos con ese id");
                }
                break;
            case 3:
                if(lista_vacia()){break;}
                if(!modificar()){
                    printf("\nError al modificar persona.");
                }
                break;
            case 4:
                if(lista_vacia()){break;}
                ver_agenda_completa();
                break;
            case 5:
                printf("\nCerrando la agenda...");
                return 0;
                break;
            default:
                printf("Error en el menú");
        }
    }else{
        printf("\n Ingrese una opción correcta, presione ENTER para continuar");
    }
    return 1;
}
//función principal del programa
int main(){
    //false = 0
    // true = 1
    
    int exit = 0;
    // mientras la ejeucion de las funciones devuelva 0 se ejecutara el programa
    while(exit == 0){
        if(!mostrar_menu()){
            exit = 1; // devolvio 1 se sale del mientras
        }
    }
    printf("\nPrograma finalizado.\n");
    return 0;
}
