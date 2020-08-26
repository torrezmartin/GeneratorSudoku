#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para números random

int arrayGeneral[9][9];
void array0(int arr[9][9]);
void arrayMostrar(int arr[9][9]);
void numAleatorio(int arr[9][9]);

int checkRepetidoCuadrado(int arr[9][9], int numeroActual, int numeroFila, int numeroColumna);
int checkRepetidoFila(int arr[9][9], int numeroActual, int numeroFila, int numeroColumna);
int checkRepetidoColumna(int arr[9][9], int numeroActual, int numeroFila, int numeroColumna);
int cantidadIntentos = 1;
int numerosMaximos = 0;
time_t timeNow;
time_t timeNowUpdating;

int main(){
    time(&timeNow);
    time(&timeNowUpdating);
    srand(time(0)); //Para números random
    array0(arrayGeneral); //Seteamos a 0 para que no haya basura
    arrayMostrar(arrayGeneral); //Visualizamos la tabla para asegurarnos de que estén todos los valores con 0
    numAleatorio(arrayGeneral); //Comenzamos a generar los números
    return 0;
}

void array0(int arr[9][9]){
    for (int i = 0; i<9; i++){
        for (int j = 0; j<9; j++){
                arr[i][j] = 0;
        }
    }
}

void arrayMostrar(int arr[9][9]){
    printf("\n\nSUDOKU\n\n");

    for (int i = 0; i<9; i++){
        for (int j = 0; j<9; j++){
            printf("[%d]", arr[i][j]);
            printf(((j==2 || j==5 || j==8) ? " " : ""));
        }
        printf(((i==2 || i==5 || i==8) ? "\n\n" : "\n"));
    }
}

void numAleatorio(int arr[9][9]){
    int numeroActual = 0;
    int contador = 0;
    int checkRepetido = 0;
    int vecesRepetidas = 0;

    int numeroFila = 0;
    int numeroColumna = 0;

    int valorFila = 0;
    int valorColumna = 0;
    int valorCuadrado = 0;

    while(contador != 81){
        time(&timeNowUpdating);
        printf("Tiempo transcurrido:  %ld segundos\n", timeNowUpdating - timeNow); //Segundos transcurridos
        printf("\nIntentos globales:  %d", cantidadIntentos); //Veces que se resetea a 0 por incongruencias
        printf("\nVeces repetidas:  %d", vecesRepetidas); //Veces que se repite un número en fila, columna o cuadrado
        printf("\nContador: %d/81 (Maximo sin repetirse: %d)", (contador+1), (numerosMaximos+1)); //Cantidad de números ingresados sin repetirse y el valor máximo alcanzado

        if (numerosMaximos < contador){
            numerosMaximos = contador;
        }

        numeroActual = (rand() % 9) + 1; //Random del 1-9

        numeroFila = contador / 9;
        numeroColumna = contador % 9;

        valorCuadrado = checkRepetidoCuadrado(arr, numeroActual, numeroFila, numeroColumna);
        valorColumna = checkRepetidoColumna(arr, numeroActual, numeroFila, numeroColumna);
        valorFila = checkRepetidoFila(arr, numeroActual, numeroFila, numeroColumna);

        if (vecesRepetidas > 50){ //Si se repiten 50 veces se da por establecido que es imposible que el número vaya ahí entonces se reinicia
            cantidadIntentos++;
            array0(arr);
            numAleatorio(arr);
            break;
        }

        checkRepetido = valorColumna + valorFila + valorCuadrado;

        if (checkRepetido != 0){
            checkRepetido = 0;
            vecesRepetidas++;
        } else {
            arr[numeroFila][numeroColumna] = numeroActual;
            contador++;
            vecesRepetidas = 0;
        }
        arrayMostrar(arr);
        printf("\n# - # -  # -  # -  # -  # -  # -  # -  # -  #\n");
    }
}

int checkRepetidoFila(int arr[9][9], int numeroActual, int numeroFila, int numeroColumna){
    int checkRepetido = 0;

    for (int i = numeroFila; i<numeroFila+1; i++){
        for (int j = 0; j<9; j++){
            if (arr[i][j] == numeroActual){
                checkRepetido++;
            }
        }
    }

    return checkRepetido;
}

int checkRepetidoColumna(int arr[9][9], int numeroActual, int numeroFila, int numeroColumna){
    int checkRepetido = 0;

    for (int i = 0; i<9; i++){
        for (int j = numeroColumna; j<numeroColumna+1; j++){
            if (arr[i][j] == numeroActual){
                checkRepetido++;
            }
        }
    }

    return checkRepetido;
}

int checkRepetidoCuadrado(int arr[9][9], int numeroActual, int numeroFila, int numeroColumna){
    int checkRepetido = 0;

    for (int i = (numeroFila/3*3); i<(numeroFila/3*3)+3; i++){
        for (int j = (numeroColumna/3*3); j<(numeroColumna/3*3)+3; j++){
            if (arr[i][j] == numeroActual){
                checkRepetido++;
            }
        }
    }

    return checkRepetido;
}
