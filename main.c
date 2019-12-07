#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    char archivo[100];
    char newArchivo[100];
    int escalar = 0;
    printf("ESCRIBA EL NOMBRE DE SU ARCHIVO:\n");
    scanf("%s", archivo);

    while(!archivo_valido(archivo)){
      printf("ARCHIVO INVALIDO, VUELVA A INGREAR EL NOMBRE:\n");
      scanf("%s", archivo);
      fflush(stdin);
    }
    printf("Nombre del archivo: %s\n", archivo);

    //CREAR EL ARREGLO DE VERTICES
    Vertex* vertices = create_vertex(archivo);
    //CREAR EL ARREGLO DE CARAS
    Face* faces = create_face(archivo);
    //NUMERO DE VERTICES
    int num_vertices = vertex_number(archivo);
    int num_caras = face_number(archivo);

    //PRINT EL ARREGLO DE VERTICES
    print_vertex(vertices, num_vertices);
    //PRINT EL ARREGLO DE CARAS
    print_face(faces,  num_caras);

    Table t = create_table(num_vertices);
    iniciar_lista(t, faces, num_caras);
    print_table(t, num_vertices);

    printf("VAMO A CRECER SU FIGURA, INTRODUZCA UN NUMERO POSITIVO MAYOR QUE 0:\n");
    scanf("%d", &escalar);
    while(escalar <= 0){
    printf("NUMERO INCORRECTO, VUELVA A ESCRIBIR EL NUMERO\n");
    scanf("%d", &escalar);
    }
    increase(vertices, escalar,num_vertices);

    //VOLVER A IMPRIMIR
    print_vertex(vertices, num_vertices);
    printf("PARA CREAR SU NUMERO ARCHIVO ESCRIBA SU NOMBRE:\n");
    scanf("%s", newArchivo);
    new_ply_file(newArchivo, vertices, faces, num_vertices, num_caras);

  return 0;
}
