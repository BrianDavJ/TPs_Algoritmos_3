#include <algorithm>
#include <iostream>
#include <vector> 
#include <tuple>
using namespace std;

int C;
vector<tuple<int,int,int>> Actividades;

void bucktsort(vector<tuple<int,int,int>>& Actividades){
  int longitud=Actividades.size();
  vector<vector<tuple<int,int,int>>> balde;

  for (int i = 0; i < 2*longitud; i++) {
    balde.push_back(vector<tuple<int,int,int>>(0));
  }

  for (int i = 0; i < longitud; i++) {
    int diff = (get<1>(Actividades[i]) - 1);
  
    if (diff == 0 && get<1>(Actividades[i]) != 1) {
      balde[((get<1>(Actividades[i]) - 1)) - 1].push_back(Actividades[i]);
    }
    else {
      balde[(get<1>(Actividades[i]) - 1)].push_back(Actividades[i]);
    }
  }

    int k = 0;
  for (vector<tuple<int,int,int>> lst : balde) {
    if (!lst.empty()) {
      for (tuple<int,int,int> i : lst) {
        Actividades[k] = i;
        k++;
      }
    }
  }
}

vector<tuple<int,int,int>> agarrarPrimerosSinSolapar(vector<tuple<int,int,int>> Arr){
    vector<tuple<int,int,int>> res(0);
    res.push_back(Arr[0]);
    for(int i=1;i<Arr.size();i++){
        if(get<1>(res[res.size()-1]) <= get<0>(Arr[i])){
            res.push_back(Arr[i]);
        }
    }
    return res;
}

int main(){
  cin >> C;

  int s_i;
  int t_i;

  for (int i = 0; i < C; i++){
    cin >> s_i;
    cin >> t_i;
    tuple<int,int,int> tup = make_tuple(s_i, t_i,i);
    Actividades.push_back(tup);
  }

  bucktsort(Actividades);
  vector<tuple<int,int,int>> actRes = agarrarPrimerosSinSolapar(Actividades);

  cout << actRes.size() << endl;

  for(int i = 0; i < actRes.size(); i++){
    cout << get<2>(actRes[i])+1 << endl;
  }

  return 0;
}