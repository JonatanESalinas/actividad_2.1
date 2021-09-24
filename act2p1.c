/*
    Actividad 2.1 Multiprocesadores

    Jonatan Emanuel Salinas Avila       A01731815
    24/Sept/2021

    Este codigo recorre una imagen .bpm y crea una imagen a escala de grises a partir de la original.
    Ademas, se obtienen los valores de cada canal (RGB) de cada pixel, y se guarda en un arreglo la
    frecuencia de cada valor de 0 a 255 en cada canal de la imagen, y en el unico canal de la imagen
    en escala de grises. Los valores de los arreglos se imprimen en un archivo de texto, y luego dichos
    valores se ocupan para construir el histograma de cada canal de la imagen, además del histograma
    de la imagen a escala de grises.
*/

#include <stdio.h>
#include <stdlib.h>

FILE * fptr;

void iniciaArreglos(int mi_array[]){
    for(int i=0; i<256; i++){
        mi_array[i] = 0;
    }
}

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("rocallosas.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("rocallosas_prueba.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    int valor_R[255];
    iniciaArreglos(valor_R);
    int valor_G[255];
    iniciaArreglos(valor_G);
    int valor_B[255];
    iniciaArreglos(valor_B);
    int valor_gris[255];
    iniciaArreglos(valor_gris);

    while(!feof(image)){                                  
       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       valor_R[r] = valor_R[r] + 1;
       valor_G[g] = valor_G[g] + 1;
       valor_B[b] = valor_B[b] + 1;

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       valor_gris[pixel] = valor_gris[pixel] + 1;

       fputc(pixel, outputImage);
       fputc(pixel, outputImage);
       fputc(pixel, outputImage);
    }

    fclose(image);
    fclose(outputImage);

    //Escribir datos de arreglo en txt:
    fptr=fopen("datos_histograma.txt","w");

    for(int i=0; i<256; i++){
        fprintf(fptr, "%d\t %d\t %d\t  %d\t\n", valor_R[i], valor_G[i], valor_B[i], valor_gris[i]);
    }

    fclose(fptr);
    return 0;
}
