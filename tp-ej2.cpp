#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
using namespace std;

long long C;
vector<vector<vector<int>>> mem;

long long int mod_bin_expM(int x, int y, int m) {//Calcula mediante un algoritmo D&C, el resto de la potencia, sin exceder el tamanio de memoria del dato

    if (y == 0) return 1;//Sabemos que x != 0 por la guarda en nuestra funcion principal

    long long int partialRes = mod_bin_expM(x%m, (y/2)%m, m);

    if (y % 2 == 0){
        return (partialRes * partialRes) % m;
    }
    else{
        return (partialRes * partialRes * x) % m;
    }
}

bool operaciones(vector<long long > v, long long r, long long m, int index, long long int restoParcial,int op){
    bool res = false;


    //Si en la posicion correspondiente de la matriz tenemos NULL, realizamos el calculo recursivo
    if(mem[index][restoParcial][op] == -1){
        long long int temp;
        switch (op)//Realizamos la operacion indicada por parametro, asegurandonos de no conservar un resto negativo
        {
            case 0:
                temp = (restoParcial + (v[index]%m)) % m;
                if (temp < 0) temp += m;
                break;
            case 1:
                temp = (restoParcial - (v[index]%m)) % m;
                if (temp < 0) temp += m;
                break;
            case 2:
                temp = (restoParcial * (v[index]%m)) % m;
                if (temp < 0) temp += m;
                break;
            case 3:
                if (restoParcial == 0 && v[index] == 0){// 0 ^ 0 INDETERMINADO, no podemos realizar esta operacion
                    mem[index][restoParcial][op] = false;
                    return false;
                }
                temp = mod_bin_expM(restoParcial,v[index],m);
                break;
        }
        if (index==v.size()-1){
            mem[index][temp][op] = (temp % m == r);
            return temp % m == r;
        }else{
            for(int i = 0; i < 4; i ++){
                res = res || operaciones(v, r, m, index+1, temp, i);
            }
        }
        mem[index][temp][op] = res;
        return res;
    }

    //Si la matriz contenia un valor valido, este caso ya fue calculado y lo retorno
    else return mem[index][restoParcial][op];

}


int main(){//Ejercicio 2
    cin >> C;

    //Inicializo los argumentos para cada uno de los C casos de test.
    for (int i = 0; i < C; i++){
        long long size, r, m;
        cin >> size;
        cin >> r;
        cin >> m;

        //La memoria tiene dimensiones |v| * m * 4
        //En la posicion [n][r][k] de la matriz, se encuentra un "booleano" que nos indica si es posible llegar a la solucion deseada
        //desde la posicion n del vector, teniendo un resto parcial r, realizando la operacion k.
        //De haber un NULL, no ha sido calculado aun.
        mem = vector<vector<vector<int>>>(size,vector<vector<int>>(m,vector<int>(4,-1)));

        vector<long long> v(size);

        for (int j = 0; j < size; j++){
            cin >> v[j];
        }


        //El llamado inicial a la funcion recursiva se ejecuta desde la posicion 0 del vector, teniendo un resto parcial de 0 y realizando una suma (operacion 0).
        bool res = operaciones(v,r,m,0,0,0);

        if (res) cout << "Si" << endl;
        else     cout << "No" << endl;
    }
    return 0;
}