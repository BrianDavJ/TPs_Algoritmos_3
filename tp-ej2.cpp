#include <iostream>
#include <vector>
#include <math.h>
#include <limits>

int C;

void operaciones(vector<int> v, int ind, int r, int m){

    int resto = v[0]%m;
    
    
    for(int i = ind; i < v.size(); i++){

    }

}


int main(){
    cout << "Introducir parametros";
    cin >> C;

    for (int i = 0; i < C; i++){
        int size, r, m;
        cin >> size;
        cin >> r;
        cin >> m;

        vector<int> v(size);

        for (int j = 0; j < size; j++){
            cin >> v[j];
        }

        operaciones(v,1,r,m);
    }

    return 0;
}