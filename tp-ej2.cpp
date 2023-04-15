#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
using namespace std;

int C;
vector<vector<vector<int>>> mem;

long long int mod_bin_expM(int x, int y, int m) {
    if (y == 0) return 1;

    long long int partialres = mod_bin_expM(x%m, (y/2)%m, m);


    if (y % 2 == 0){
        return (partialres * partialres) % m;
    }
    else{
        return (partialres * partialres * x) % m;
    }
}

bool operaciones(vector<int> v, int r, int m, int index, int restoParcial,int op){
    bool res = false;

    if(mem[index][restoParcial][op] == -1){
        long long temp;
        switch (op)
        {
            case 0:
                temp = (restoParcial + (v[index]%m)) % m;
                break;
            case 1:
                temp = (restoParcial - (v[index]%m)) % m;
                if (temp < 0) temp += m;
                break;
            case 2:
                temp = (restoParcial * (v[index]%m)) % m;
                break;
            case 3:
                temp = mod_bin_expM(restoParcial,v[index],m);
                break;
        }
        if (index==v.size()-1){
            mem[index][temp][op]=temp % m == r;
            return temp % m == r;
        }else{
            for(int i = 0; i < 4; i ++){
                res = res || operaciones(v, r, m, index+1, temp, i);
            }
        }
        mem[index][restoParcial][op] = res;
        return res;
    }
    else return mem[index][restoParcial][op];

}


int main(){
    cin >> C;

    for (int i = 0; i < C; i++){
        int size, r, m;
        cin >> size;
        cin >> r;
        cin >> m;

        mem = vector<vector<vector<int>>>(size,vector<vector<int>>(m,vector<int>(4,-1)));

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