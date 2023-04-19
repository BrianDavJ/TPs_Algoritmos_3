#include <algorithm>
#include <iostream>
#include <vector> 
#include <tuple>
using namespace std;

void bucktsort(vector <tuple<int,int>> Actividades){
    int longitud=Actividades.size();
    int rango=(2*longitud-1)/longitud;
    vector<vector<tuple<int,int>>> balde;
     for (int i = 0; i < 2*longitud; i++) {
    balde.push_back(vector<tuple<int,int>>(0));
  }
  for (int i = 0; i < longitud; i++) {
    int diff = (get<1>(Actividades[i]) - 1) / rango;
  
    if (diff == 0 && get<1>(Actividades[i]) != 1) {
      balde[((get<1>(Actividades[i]) - 1) / rango) - 1].push_back(Actividades[i]);
    }
    else {
      balde[(get<1>(Actividades[i]) - 1) / rango].push_back(Actividades[i]);
    }
  }
   for (int i = 0; i < balde.size(); i++) {
    if (!balde[i].empty()) {
      sort(balde[i].begin(), balde[i].end());
    }
  }
    int k = 0;
  for (vector<tuple<int,int>>& lst : balde) {
    if (!lst.empty()) {
      for (tuple<int,int> i : lst) {
        Actividades[k] = i;
        k++;
      }
    }
  }
}


vector<tuple<int,int>> agarrarPrimerosSinSolapar(vector<tuple<int,int>> Arr){
    vector<tuple<int,int>> res(0);
    res.push_back(Arr[0]);
    for(int i=1;i<Arr.size();i++){
        if(get<1>(Arr[i-1]) <=get<0>(Arr[i])){
            res.push_back(Arr[i]);
        }
    }
    return res;
}


int main(){
    vector<tuple<int,int>> grandeGoloSO(vector <tuple<int,int>> Actividades){
        bucktsort(Actividades);
        return agarrarPrimerosSinSolapar(Actividades);
    }
    return 0;
}
