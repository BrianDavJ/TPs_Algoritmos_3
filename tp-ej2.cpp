#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
using namespace std;

int C;
vector<vector<int>> mem;

int mod_bin_exp(int x, int y, int m) {
    if (y == 0) return 1;

    int partialres = mod_bin_exp(x, y/2, m);


    if (y % 2 == 0){
        return (partialres * partialres) % m;
    }
    else{
        return (partialres * partialres * x) % m;
    }
}

bool operaciones(vector<int> v, int r, int m, int index, int restoParcial,int op){
    
    if (index == v.size()) return (restoParcial % m == r);
    
    int temp;
    bool res = false;

    if(mem[index][restoParcial] == -1){

        switch (op)
        {
        case 0:
            temp = (restoParcial + v[index]) % m;
            break;
        case 1:
            temp = (restoParcial - v[index]) % m;
            break;
        case 2:
            temp = (restoParcial * v[index]) % m;
            break;
        case 3:
            temp = mod_bin_exp(restoParcial,v[index],m);
            break;
        }

        for(int i = 0; i < 4; i ++){
            res = res || operaciones(v, r, m, index+1, temp, i);
        }

        mem[index][restoParcial] = res;
        return res;
    }
    else return mem[index][restoParcial];

}


int main(){
    cin >> C;

    for (int i = 0; i < C; i++){
        int size, r, m;
        cin >> size;
        cin >> r;
        cin >> m;

        mem = vector<vector<int>>(size,vector<int>(m,-1));

        vector<int> v(size);

        for (int j = 0; j < size; j++){
            cin >> v[j];
        }

        bool res = operaciones(v,r,m,0,0,0);

        if (res) cout << "Si" << endl;
        else cout << "No" << endl;
    }

    return 0;
}