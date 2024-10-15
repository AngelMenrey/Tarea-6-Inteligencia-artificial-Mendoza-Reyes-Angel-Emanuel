#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define NODOS 10
#define INFINITO INT_MAX 

typedef struct {
    int elementos[NODOS];
    int cima;
} Pila;

void inicializarPila(Pila* p) {
    p->cima = -1;
}

bool estaVacia(Pila* p) {
    return p->cima == -1;
}

void apilar(Pila* p, int valor) {
    if (p->cima < NODOS - 1) {
        p->elementos[++(p->cima)] = valor;
    }
}

int desapilar(Pila* p) {
    if (!estaVacia(p)) {
        return p->elementos[(p->cima)--];
    }
    return -1;
}

int distanciaMinima(int distancias[], bool visitado[]) {
    int minimo = INFINITO, indiceMinimo;
    for (int nodo = 0; nodo < NODOS; nodo++) {
        if (!visitado[nodo] && distancias[nodo] <= minimo) {
            minimo = distancias[nodo];
            indiceMinimo = nodo;
        }
    }
    return indiceMinimo;
}

void imprimirSolucion(int distancias[], int predecesores[]) {
    printf("+------+-------------------+-------------------+\n");
    printf("| Nodo | Distancia desde A | Ruta              |\n");
    printf("+------+-------------------+-------------------+\n");
    for (int nodo = 0; nodo < NODOS; nodo++) {
        printf("|  %c   |        %3d        | ", 'A' + nodo, distancias[nodo]);
        Pila pila;
        inicializarPila(&pila);
        int j = nodo;
        while (predecesores[j] != -1) {
            apilar(&pila, j);
            j = predecesores[j];
        }
        printf("A");
        while (!estaVacia(&pila)) {
            printf(" -> %c", 'A' + desapilar(&pila));
        }
        printf(" |\n");
    }
    printf("+------+-------------------+-------------------+\n");
}

void dijkstra(int grafo[NODOS][NODOS], int origen) {
    int distancias[NODOS];
    bool visitado[NODOS];
    int predecesores[NODOS];

    for (int i = 0; i < NODOS; i++) {
        distancias[i] = INFINITO;
        visitado[i] = false;
        predecesores[i] = -1;
    }

    distancias[origen] = 0;

    for (int i = 0; i < NODOS - 1; i++) {
        int u = distanciaMinima(distancias, visitado);
        visitado[u] = true;

        for (int v = 0; v < NODOS; v++) {
            if (!visitado[v] && grafo[u][v] && distancias[u] != INFINITO && distancias[u] + grafo[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + grafo[u][v];
                predecesores[v] = u;
            }
        }
    }

    imprimirSolucion(distancias, predecesores);
}

int main() {
    int grafo[NODOS][NODOS] = {
        {0, 3, 8, 5, 0, 0, 0, 0, 0, 0}, 
        {3, 0, 5, 0, 0, 7, 0, 0, 0, 0}, 
        {8, 5, 0, 2, 8, 5, 0, 0, 0, 0}, 
        {5, 0, 2, 0, 0, 0, 4, 0, 0, 0}, 
        {0, 0, 8, 0, 0, 5, 0, 1, 3, 0}, 
        {0, 7, 5, 0, 5, 0, 0, 6, 0, 0}, 
        {0, 0, 0, 4, 6, 0, 0, 0, 4, 0}, 
        {0, 0, 0, 0, 1, 6, 0, 0, 0, 2}, 
        {0, 0, 0, 0, 3, 0, 4, 0, 0, 6}, 
        {0, 0, 0, 0, 0, 0, 0, 2, 6, 0}  
    };

    dijkstra(grafo, 0);

    return 0;
}
