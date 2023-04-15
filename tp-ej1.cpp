//
// Created by Brian on 11/4/2023.
//
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>

using namespace std;

vector<int> candidatos;
vector<int> sumas;
int cantidad=0;

int cuadradoMagicoConPodaK(vector<vector<int>> &cuadrado, int i, int j, vector<int> &numeros, int numMagico,int ordenL) {

    //Asumiendo que conozco el numero mágico
    // sumas es un vector donde los primeros n numeros son las sumas de las n filas, los proximos n son de las columnas y los ultimos 2 de las diagonales
    int n = cuadrado.size();
    if (j == n) return cuadradoMagicoConPodaK(cuadrado, i + 1, 0, numeros,numMagico,ordenL); // Voy a la próxima fila.
    if (i == n){
        cantidad+=1;
        return cantidad;}
    // Si se completó la matriz es porque pasó todas las podas.
    // Soluciones
    for (int k = 1; k <= n * n; k++) {
        if (numeros[k - 1] == 1) continue; // Corto si el numero k fue usado.

        if (sumas[i] + k > numMagico) continue; // Veo que la suma parcial no se pasó


        if ((j == n - 1) && (sumas[i] + k != numMagico))
            continue; //Si estoy por completar la fila veo si la suma de toda la fila da el número magico

        if (sumas[n + j] > numMagico)
            continue; // voy hasta la suma de la columna j y veo que la suma parcial no se pasó


        if (i == n - 1 && sumas[n + j] + k != numMagico)
            continue; //Si estoy por completar la fila veo si la suma de toda la fila da el número magico


        if (i == j && sumas[2 * n] > numMagico) continue; // Veo si la suma parcial de la diagonal (i,i) se pasa

        if (i == j && i == n - 1 && sumas[2 * n] + k != numMagico)
            continue; // Si estoy por completar la diagonal (i,i) confirmo que sume el número magico

        if (i == n - 1 - j && sumas[2 * n + 1] + k > numMagico)
            continue; // veo la suma parcial de la diagonal (i, n-1 -i) [ejemplo: la diagonal (1,n-1)]

        if (i == n - 1 - j && j == 0 && sumas[2 * n + 1] + k != numMagico)
            continue; // Si estoy por completar la diagonal (i,n-1 -i) confirmo que sume el número magico

        cuadrado[i][j] += k; // pongo k en la celda (i,j)
        numeros[k - 1] = 1; // marco que ya fue usado
        sumas[i] += k; // hago la suma parcial de  la fila "i"
        sumas[n + j] += k; // hago la suma parcial de  la columna "j"
        if (i == j) { sumas[2 * n] += k; } //hago la suma parcial de  la primera diagonal
        if (i == n - 1 - j) { sumas[2 * n + 1] += k; } // hago la suma parcial de la segunda diagonal
        cantidad = cuadradoMagicoConPodaK(cuadrado, i, j + 1, numeros, numMagico,ordenL);
        if (cantidad == ordenL) {

            return cantidad;
        }
        // reseteo los datos para la proxima rama
        cuadrado[i][j] -= k;
        numeros[k - 1] = 0;
        sumas[i] -= k;
        sumas[n + j] -= k;
        if (i == j) { sumas[2 * n] -= k; }
        if (j == n - 1 - i) { sumas[2 * n + 1] -= k; }

    }
    return cantidad;
}
vector<vector<int>> OrdenLex(int n, int k){
    int numM = (n*n*n + n)/2;
    sumas = vector<int> ((2*n)+2);
    vector<int> candidatos (n * n,0);
    vector<vector<int>> cuadrado(n, vector<int>(n));

    int CantCuadrados =cuadradoMagicoConPodaK(cuadrado,0,0,candidatos,numM,k);
    if (k > CantCuadrados || k < 1) {
        vector<vector<int>> invalido(1,vector<int>(1,-1));
        return invalido;
    }
    return cuadrado;
}
int main() {
    //Ejercicio 1
    int n;
    int k;
    // Inicializo los argumentos.
    cin >> n >> k;

    vector<vector<int>> r3 = OrdenLex(n, k);

    for (int i=0; i<r3.size();i++) {
        for (int j = 0; j < r3.size(); j++) {
            cout << r3[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
