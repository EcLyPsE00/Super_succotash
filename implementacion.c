#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define VERTEX 9
#define VERTEX_LIST 28
#define FACE 21
#define FACE_LIST 28+VERTEX

typedef struct strNode* Node;

struct strVertex{
    float x, y, z;
};

struct strFace{
    int v1, v2 ,v3;
};

struct strNode{
    int index;
    Node next;
};

struct strList{
    int size;
    Node first;
    Node last;
};

struct strTable{
    List *filas;
    int size;
    int capacidad;
};

bool archivo_valido(char *nombre){
    FILE *f = fopen(nombre, "r");
    if(!f){
        fclose(f);
        return FALSE;
    }
    fclose(f);
    return TRUE;
}

int vertex_number(char *nombre){
    FILE * f = fopen(nombre, "r");
    int vertex;
    if(!archivo_valido(nombre)){
        fclose(f);
        return -1;
    }
    for(int i = 0; i < VERTEX; i++){
        fscanf(f, "%*s");
    }
    fscanf(f, "%d", &vertex);
    fclose(f);
    return vertex;
}


int face_number(char *nombre){
    FILE * f = fopen(nombre, "r");
    int face;
    if(!archivo_valido(nombre)){
        fclose(f);
        return -1;
    }
    for(int i = 0; i < FACE; i++){
        fscanf(f, "%*s");
    }
    fscanf(f, "%d", &face);
    fclose(f);
    return face;
}


Vertex* create_vertex(char * nombre){
    FILE *f = fopen(nombre, "r");
    if(!archivo_valido(nombre)){
        return NULL;
    }
    int num_vertex = vertex_number(nombre);
    for(int i = 0; i < 28; i++){
        fscanf(f, "%*s");
    }
    Vertex* v = (Vertex*)calloc(num_vertex, sizeof(Vertex));
    for(int i = 0; i < num_vertex; i++){
        v[i] = (Vertex)calloc(1, sizeof(struct strVertex));
        fscanf(f, "%f %f %f", &v[i]->x, &v[i]->y, &v[i]->z);
    }
    fclose(f);
    return v;
}

Face * create_face(char* nombre){
    FILE * f = fopen(nombre, "r");
    if(!archivo_valido(nombre)){
        return NULL;
    }
    int num_face = face_number(nombre);
    int num_vertex = vertex_number(nombre);
    for(int i = 0; i < 28; i++){
        fscanf(f, "%*s");
    }
    for(int i = 0; i < num_vertex; i++){
        fscanf(f, "%*f %*f %*f");
    }
    Face * arrFace = (Face*)calloc(num_face, sizeof(Face));
    for(int i = 0; i < num_face; i++){
        arrFace[i] = (Face)calloc(1, sizeof(struct strFace));
        fscanf(f, "%*d %d %d %d", &arrFace[i]->v1, &arrFace[i]->v2, &arrFace[i]->v3);
    }
    return arrFace;
}

void print_vertex(Vertex *v, int vertex_num){
    if(v == NULL){
        return;
    }
    for(int i = 0; i < vertex_num; i++){
        printf("%f %f %f\n", v[i]->x, v[i]->y, v[i]->z);
    }
    return;
}

void print_face(Face *f, int face_num){
    if(f == NULL){
        return;
    }
    for(int i = 0; i < face_num; i++){
        printf("3 %d %d %d\n", f[i]->v1, f[i]->v2, f[i]->v3);
    }
    return;
}

Table create_table(int num_de_vertices){
    Table tabla=(Table)calloc(1,sizeof(struct strTable));
    tabla->size=num_de_vertices;
    tabla->capacidad=(int)(num_de_vertices)+(num_de_vertices/2);
    tabla->filas=(List*)calloc(tabla->capacidad,sizeof(List));

    for (int i=0;i<tabla->capacidad;i++){
        tabla->filas[i]=(List)calloc(1,sizeof(struct strList));
        tabla->filas[i]->size=0;
        tabla->filas[i]->first=NULL;
        tabla->filas[i]->last=NULL;
    }
    return tabla;
}

bool comparador_de_triangulos(Face f,Face v){
    if (f == NULL || v == NULL){
        return -1;
    }
    if(f->v1 == v->v1 || f->v2==v->v2 || f->v3 == v->v3){
        return 1;
    }
    else{
        return 0;
    }
};

void list_put(Table tabla, int face_index, int tabla_index){
    if(!tabla || face_index < 0 || tabla_index < 0){
        return;
    }
    Node n = (Node)calloc(1,sizeof(struct strNode));
    n->index = face_index;
    n->next = NULL;
    if(tabla->filas[tabla_index]->first==NULL){
        tabla->filas[tabla_index]->size++;
        tabla->filas[tabla_index]->first=n;
        tabla->filas[tabla_index]->last=n;
        return;
      }
    else{
        Node viajero = tabla->filas[tabla_index]->first;

        while(viajero->next != NULL){
          viajero = viajero->next;
        }
        viajero->next = n;
        tabla->filas[tabla_index]->last = n;
        tabla->filas[tabla_index]->size++;
        return;
      }
}

void iniciar_lista(Table tabla, Face *f, int caras){//funcion en desarrollo
    if(tabla == NULL || f == NULL){
        return;
    }
    for(int i = 0; i < tabla->size; i++) {
        for (int j = 0; j < caras; j++) {
            if (f[j]->v1 == i || f[j]->v2 == i || f[j]->v3 == i) {
                list_put(tabla, j, i);
            }
        }
    }
}

void print_table(Table t, int num_de_vertices){
    if(t == NULL || num_de_vertices < 0){
        return;
    }
    //CICLO PARA PASAR POR TODAS LOS INDICES DEL ARREGLO DE LISTAS
    for(int i = 0; i < num_de_vertices; i++){
        Node viajero = t->filas[i]->first;
        printf("Caras pertenecientes al vertice en el indice %d\n", i);
        while(viajero != NULL){
            printf("%d ", viajero->index);
            viajero = viajero->next;
        }
        printf("\n");
    }
    return;
}

void increase(Vertex *v, int escalar, int num_vertex){
    if(v == NULL || escalar <= 0){
        return;
    }
    for(int i = 1; i < num_vertex; i++){
        v[i]->x *= escalar;
        v[i]->y *= escalar;
        v[i]->z *= escalar;
    }
}

void decrease(Vertex *v, int escalar, int num_vertex){
    if(v == NULL || escalar >= 0){
        return;
    }
    for(int i = 1; i < num_vertex; i++){
        v[i]->x /= escalar;
        v[i]->y /= escalar;
        v[i]->z /= escalar;
    }
}

void new_ply_file(char* nombre, Vertex*v, Face*f, int num_vertex, int num_face){
    int len_Nombre = strlen(nombre);
    char newName[len_Nombre+4];
    strcat(newName, ".ply");
    FILE * file = fopen(newName, "w");
    if(v == NULL || f == NULL){
        return;
    }
    fprintf(file, "ply\n");
    fprintf(file, "format ascii 1.0\n");
    fprintf(file, "comment VCGLIB generated\n");
    fprintf(file, "element vertex %d\n", num_vertex);
    fprintf(file, "property float x\n");
    fprintf(file, "property float y\n");
    fprintf(file, "property float z\n");
    fprintf(file, "element face %d\n", num_face);
    fprintf(file, "property list uchar int vertex_indices\n");
    fprintf(file, "end_header\n");
    for(int i = 0; i < num_vertex; i++){
        fprintf(file, "%f %f %f\n", v[i]->x, v[i]->y, v[i]->z);
    }
    for(int i = 0; i < num_face; i++){
        fprintf(file, "3 %d %d %d\n", f[i]->v1, f[i]->v2, f[i]->v3);
    }
    fclose(file);
    return;
}

bool triangulo_vecino(Face f1, Face f2){
    int x=0;
    if(f1->v1 == f2->v1 || f1->v1 == f2->v2|| f1->v1 == f2->v3) {
        x++;
    }
    if(f1->v2 == f2->v1 || f1->v2 == f2->v2 || f1->v2 == f2->v3){
        x++;
    }
    if(f1->v3 == f2->v1 || f1->v3 == f2->v2 || f1->v3 == f2->v3){
        x++;
    }
    printf("%d\n",x);
    if(x == 2){
        return 1;
    }
    else return 0;
}


int get_vertex_index(Vertex* v, Vertex point){
    for (int i = 0; i < VERTEX; i++){
        if(v[i]->x == point->x && v[i]->y == point->y &&v[i]->z == point->z){
            return i;
        }
    }
    return -1;
}


void insertar_vecinos(int arr[3],Table t,int index){
    Node aux1=(Node)calloc(1,sizeof(struct strNode));
    Node aux2=(Node)calloc(1,sizeof(struct strNode));
    Node aux3=(Node)calloc(1,sizeof(struct strNode));
    aux1->index=arr[0];
    aux1->next=aux2;
    aux2->index=arr[1];
    aux2->next=aux3;
    aux3->index=arr[2];
    aux3->next=NULL;
    t->filas[index]->size=3;
    t->filas[index]->first=aux1;
    t->filas[index]->last=aux3;

}

Table tabla_de_vecinos(Face * arr,int size){
    Table t = calloc(1,sizeof(struct strTable));
    t->size = size;
    t->capacidad = (int)size+(size/2);
    t->filas = (List*)calloc(t->capacidad,sizeof(List));
    int x[3] = {0,0,0};
    int f=0;
    for(int i = 0; i < t->capacidad; i++){
        t->filas[i] = (List)calloc(1,sizeof(struct strList));
        t->filas[i]->size = 0;
        t->filas[i]->first = NULL;
        t->filas[i]->last = NULL;
    }
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(i != j && triangulo_vecino(arr[i], arr[j]) == 1){
                x[f] = j;
                f++;
            }
            insertar_vecinos(x,t,i);
        }
    }
    return t;
}

