#include<stdio.h>
#include<stdlib.h>
#include<time.h>
# include <string.h>



struct pokemon
{
float vida;
int tipo;
};

struct pokemon **matNew( size_t rows, size_t cols ) {
    struct pokemon **m = malloc(sizeof(struct pokemon*)*rows);

    if (NULL == m) {
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        m[i] = malloc(cols * sizeof(struct pokemon));
        if (NULL == m[i]) {
            while (i--) {
                free(m[i]);
            }
            free(m);
            return NULL;
        }
    }
    return m;
}
void generacionMatriz(int f,int c,struct pokemon **matriz)
{
    
    srand (time(NULL));
    float vidaInicial=10.0;
    for (int i=0;i<f;i++)
    {
        for (int j=0;j<c;j++)
        {
            matriz[i][j].vida=vidaInicial;
            matriz[i][j].tipo=rand()%3; 
        }
    }
    
}
void danioPorPosicion(int f,int c,int a, int d,struct pokemon **matriz){
    /*0 es fuego
      1 es agua
      2 es planta
      d=1 es derecha, d=-1 es izquierda, d=0 es medio
      a=1 es arriba, a=-1 es abajo, d=0 es medio
    */
    float nve=0.5;
    int ve=2;    
        if (matriz[f][c].tipo==0){
            if (matriz[f-a][c+d].tipo==0){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-nve;
            }
            if (matriz[f-a][c+d].tipo==1){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-nve;
            }
            if (matriz[f-a][c+d].tipo==2){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-ve;
            }
        }
        if (matriz[f][c].tipo==1){
            if (matriz[f-a][c+d].tipo==0){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-ve;
            }
            if (matriz[f-a][c+d].tipo==1){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-nve;
            }
            if (matriz[f-a][c+d].tipo==2){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-nve;
            }
        }
        if (matriz[f][c].tipo==2){
            if (matriz[f-a][c+d].tipo==0){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-nve;
            }
            if (matriz[f-a][c+d].tipo==1){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-ve;
            }
            if (matriz[f-a][c+d].tipo==2){
                matriz[f-a][c+d].vida=matriz[f-a][c+d].vida-nve;
            }
        
        }
    }
void danioPorRonda(int f,int c,struct pokemon **matriz){
    for (int i=0;i<f;i++){
        for (int j=0;j<c;j++){
            if (i!=0 && j!=0 && i!=f-1 && j!=c-1){
                /*daño que hacen las posiciones centrales*/
                danioPorPosicion(i,j,0,1,matriz);
                danioPorPosicion(i,j,0,-1,matriz);
                danioPorPosicion(i,j,1,0,matriz);
                danioPorPosicion(i,j,-1,0,matriz);
            }
            if (i==0 && j!=0 && j!=c-1){
                /*daño que hacen las posiciones de la primera fila exeptuando a los corners*/
                danioPorPosicion(i,j,0,1,matriz);
                danioPorPosicion(i,j,0,-1,matriz);
                danioPorPosicion(i,j,-1,0,matriz);
            }
            if (i==f-1 && j!=0 && j!=c-1){
                /*daño que hacen las posiciones de la ultima fila exeptuando a los corners*/
                danioPorPosicion(i,j,0,1,matriz);
                danioPorPosicion(i,j,0,-1,matriz);
                danioPorPosicion(i,j,1,0,matriz);
            }
            if (j==0 && i!=0 && i!=f-1){
                /*daño que hacen las posiciones de la primera columna exeptuando a los corners*/
                danioPorPosicion(i,j,0,1,matriz);
                danioPorPosicion(i,j,1,0,matriz);
                danioPorPosicion(i,j,-1,0,matriz);
            }
            if (j==c-1 && i!=0 && i!=f-1){
                /*daño que hacen las posiciones de la primera columna exeptuando a los corners*/
                danioPorPosicion(i,j,0,-1,matriz);
                danioPorPosicion(i,j,1,0,matriz);
                danioPorPosicion(i,j,-1,0,matriz);
            }
            if (i==0 && j==0){
                /*daño que hace la esquina izquierda superior*/
                danioPorPosicion(i,j,0,1,matriz);
                danioPorPosicion(i,j,-1,0,matriz);
            }
            if (i==f-1 && j==0){
                /*daño que hace la esquina izquierda inferior*/
                danioPorPosicion(i,j,0,1,matriz);
                danioPorPosicion(i,j,1,0,matriz);
            }
            if (i==0 && j==c-1){
                /*daño que hace la esquina derecha superior*/
                danioPorPosicion(i,j,0,-1,matriz);
                danioPorPosicion(i,j,-1,0,matriz);
            }
            if (i==f-1 && j==c-1){
                /*daño que hace la esquina derecha inferior*/
                danioPorPosicion(i,j,0,-1,matriz);
                danioPorPosicion(i,j,1,0,matriz);
            }
        }
    }   
}
void chequeoDeMuertos(int f,int c,struct pokemon **matriz)
{
    float vidaNueva=10.0;
    for (int i=0;i<f;i++){
        for (int j=0;j<c;j++){
            if (matriz[i][j].vida<=0){
                if (j!=c-1){
                    matriz[i][j].vida=vidaNueva;
                    matriz[i][j].tipo=matriz[i][j+1].tipo;
                }
                else{
                    matriz[i][j].vida=vidaNueva;
                    matriz[i][j].tipo=matriz[i][j-1].tipo;
                }
            }
        }
    }
}
void cicloDeRondas(int f,int c,int r,struct pokemon **matriz)
{
    for (int i=0;i<r;i++){
        danioPorRonda(f,c,matriz);
        chequeoDeMuertos(f,c,matriz);
    }
}
void save(int f,int c,struct pokemon **matriz) {
    FILE *filePointer ;
    
    
    
    filePointer = fopen("foto.ppm", "w") ;
    fprintf(filePointer, "%s\n", "P3");
    fprintf(filePointer, "%i %i\n255\n", f,c);
    
    if ( filePointer == NULL ) {
        printf( "File failed to open." ) ;
    } else {
        printf("The file is now opened.\n") ;
         
            for (int i=0;i<f;i++){
                for(int j=0;j<c;j++){
                    if (matriz[i][j].tipo==0) {
                        fprintf(filePointer,"%s","255 0 0 ");
                    }
                    if (matriz[i][j].tipo==1) {
                        fprintf(filePointer,"%s", "0 0 255 ");
                    }
                    if (matriz[i][j].tipo==2) {
                        fprintf(filePointer,"%s", "0 255 0 ");
                    }
                }
                fputs("\n",filePointer);
            }        
        } 
         
        fclose(filePointer);
        printf("The file is now closed.\n");
    


}



int main(void)
{
   struct pokemon **matriz;
   matriz=matNew(30,40);
   generacionMatriz(30,40,matriz);
   for (int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            printf("%f ",(matriz[i][j]).vida);
        }
        printf("\n");
    }
   cicloDeRondas(30,40,1000,matriz);
   printf("\n\n");
   for (int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            printf("%f ",(matriz[i][j]).vida);
        }
        printf("\n");
    }
    save(30,40,matriz);
   return 0; 
}
