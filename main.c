#include <stdio.h>
#include <stdlib.h>

#define EvNomtama  16
#define IDtama     10
#define EstNomtama 15
#define EstNum     20

typedef struct{
    char Nombre[EvNomtama];
    int puntos;
}EVALUACION;

typedef struct{
    char IDest[IDtama];
    char PrimNom[EstNomtama];
    char SegNom[EstNomtama];
    EVALUACION EvEst[5];
    float Calif;
}ESTUDIANTE;

FILE* abrir_archivo(char *nombre, char *modo);
void cerrar_archivo(FILE *archivo);
void ListaEstudiantil(ESTUDIANTE *Est);
int CapEstudiante(ESTUDIANTE *Est);
void leer_texto_archivo(char *nombre);
void escribir_estudiante_archivo(ESTUDIANTE *Est, char *nombre);

int main()
{
    ESTUDIANTE Est[EstNum];
    char NombreFILE[20] = "Lista_Est.txt";
    int Tecla = 0, i=0;

    while(Tecla != 5){
        printf("Opciones: \n [1] Agregar Estudiantes \n [2] Ver Estudientes \n [3] Imprimir calificaciones \n [4] Guardar \n [5] Salir \n");
        scanf("%d", &Tecla);
        if(Tecla == 1){
            CapEstudiante(&Est[i]);
            i++;
        }
        if(Tecla == 2){
            ListaEstudiantil(Est);
        }
        if(Tecla == 3){
            leer_texto_archivo(NombreFILE);
        }
        if(Tecla == 4){
            escribir_estudiante_archivo(Est, NombreFILE);
        }
    }

    return 0;
}

FILE* abrir_archivo(char *nombre, char *modo){
    FILE *archivo = fopen(nombre, modo);
    if(archivo == NULL){
        fputs("Archivo no abierto, verificar...", stderr);
        exit(-1);
    }
    printf("Archivo abierto\n");
    return archivo;
}

void cerrar_archivo(FILE *archivo){
    int cerrado = fclose(archivo);
    cerrado == 0 ? printf("Archivo Cerrado\n") : printf("Error Archivo No Cerrado\n");
}

void leer_texto_archivo(char *nombre){
    FILE *archivo = abrir_archivo(nombre, "r");
    printf("======= Información del archivo =========\n");
    char caracter;
    while ((caracter = fgetc(archivo)) != EOF){
        fputc(caracter, stdout);
    }
    printf("======= Fin Información del archivo =========\n");
    cerrar_archivo(archivo);
}

void escribir_estudiante_archivo(ESTUDIANTE *Est, char *nombre){
    FILE *archivo = abrir_archivo(nombre, "w");
    for(int i=0;i<EstNum;i++){
        fwrite(&Est[i], sizeof(ESTUDIANTE), 1, archivo);
    }
    cerrar_archivo(archivo);
}

int CapEstudiante(ESTUDIANTE *Est){
    printf("ID del Estudiante: ");
    fflush(stdin);
    gets(Est->IDest);
    printf("Primer Nombre del Estudiante: ");
    fflush(stdin);
    gets(Est->IDest);
    printf("Segundo Nombre del Estudiante: ");
    fflush(stdin);
    gets(Est->IDest);
    for(int i=0;i<5;i++){
        printf("Nombre de evaluacion %d: ", i+1);
        fflush(stdin);
        gets(Est->EvEst[i].Nombre);
        printf("Nota de evaluacion %d: ", i+1);
        scanf("%d", &Est->EvEst[i].puntos);

    }
}

void ListaEstudiantil(ESTUDIANTE *Est){
    int total;
    for(int i=0;i<EstNum;i++){
        for(int k=0;k<5;k++){
            total+=Est[i].EvEst[k].puntos;
        }
        Est[i].Calif = total/5;
        printf("%s \t%s %s \t%f\n", Est[i].IDest, Est[i].PrimNom, Est[i].SegNom, Est[i].Calif);
    }
    return *Est;
}
