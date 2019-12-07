#ifndef HEADER_H_
#define HEADER_H_

typedef enum {FALSE, TRUE} bool;
typedef struct strVertex* Vertex;
typedef struct strFace* Face;
typedef struct strList* List;
typedef struct strTable* Table;

//FUNCIONES CON LOS VERTICES
Vertex* create_vertex(char *nombre);
void print_vertex(Vertex *v, int vertex_num);

//FUNCIONES CON LAS CARAS
Face* create_face(char* nombre);
void print_face(Face *f, int face_num);

//FUNCIONES CON TABLAS
Table create_table(int num_de_vertices);
void print_table(Table t, int num_vertices);
Table tabla_de_vecinos(Face * arr, int size);


//FUNCIONES AUXILIARES
bool archivo_valido(char * nombre);
int vertex_number(char * nombre);
int face_number(char* nombre);
void create_list(Table t);

//FUNCIONES DE INICIALIZACION
void list_put(Table tabla, int face_index, int tabla_index);
void iniciar_lista(Table tabla, Face *f, int caras);

//ESCRITURA DEL ARCHIVO
void new_ply_file(char* nombre, Vertex*v, Face*f, int num_vertex, int num_face);
bool write_archive_name(char * nombre);

//FUNCIONES DE TRANSFORMACION
void increase(Vertex *v, int escalar, int num_vertex);
void decrease(Vertex *v, int escalar, int num_vertex);
#endif // HEADER_H_
