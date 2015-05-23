#include <bits/stdc++.h>
#include <fstream>

using namespace std;
int c[1000][1000];
int w[1000][1000];
double W[1000];
double RANK[1000];
int arr_sorted_index[1000];
int t[1000] = {0};
int pred[1000][1000] = {0};
int AFT[1000] = {0};
int pro_sched[1000];

int calc_maxi(int task, int pro,int i,int j){
    int k;
    int m = 0;

    for(k = 0; k < task; k++){
        if(pred[i][k] == 1){
            if(pro_sched[k] == j){
                m = max(m,AFT[k]);
            }
            else{
                m = max(m,AFT[k] + c[k][i]);
            }
        }
    }
    return m;
}

int calc_EFT(int task,int pro){
    int j;
    int m = 1000;
    int x;
    int index;
    for(j = 0; j < pro; j++){
        x=w[arr_sorted_index[0]][j];
            if(x<m){
                    m=x;index=j;
            }
    }

    pro_sched[arr_sorted_index[0]]=index;
    AFT[arr_sorted_index[0]]=m;
    t[index]=m;
    int i;
    for(i = 1;i < task;i++){
            int m=1000;
            int eft=1000;
         for(j=0;j<pro;j++){
            int est = max(t[j],calc_maxi(task,pro,arr_sorted_index[i],j));
            x = w[arr_sorted_index[i]][j]+est;
            if(x<eft){
               eft=x;
               index=j;
            }
        }
        cout <<endl;
        pro_sched[arr_sorted_index[i]]=index;
        AFT[arr_sorted_index[i]]=eft;
        t[index]=eft;
        cout <<eft<<" "<<index;
    }
    cout <<endl;
    m=0;
    for(i=0;i<pro;i++) {
        m=max(m,t[i]);
    }
    cout <<m <<endl;
}
void func_to_sort_indexes(int task){
    vector<pair<double,int> >v;
    int i;
    for(i = 0; i < task; i++){
        v.push_back(make_pair(RANK[i],i));
    }
    sort(v.begin(),v.end());
    for(i = 0; i < task; i++){
        arr_sorted_index[i] = v[task - 1 - i].second;
    }
}
int calc_rank(int i,int exit_task,int task){
    if(i == exit_task){
        RANK[i] = W[exit_task];
        return RANK[i];
    }
    else{
        int j;
        int m = 0;
        for(j = 0; j < task; j++){
            if(c[i][j] != -1){
                m = max(m,c[i][j] + calc_rank(j,exit_task,task));
            }
        }
        RANK[i] = W[i] + m;
        return RANK[i];
    }
}
void calc_avg_execution_cost(int task,int pro){
    int i,j;
    for(i = 0; i < task; i++){
        for(j = 0; j < pro; j++){
            W[i] = W[i] + w[i][j];
        }
        W[i] = W[i] / (double)pro;
    }
}
void HEFT(int task,int edge,int pro, int exit_task){
    calc_avg_execution_cost(task,pro);
    calc_rank(0,exit_task,task);
    func_to_sort_indexes(task);
    calc_EFT(task,pro);
    int i;
}
int main(){
    int i,j,task;
    ifstream fin;
    fin.open("input.txt");
     int pro;
    //cin>>pro;
    fin >> pro;

    fin >>task;

    for(i = 0; i < task; i++){
        for(j = 0; j < pro; j++){
            fin>>w[i][j];
        }
    }
    for(i = 0; i < task; i++){
        W[i] = 0;
        pro_sched[i] = -1;
    }

    for(i = 0; i < task; i++) {
        for(j = 0; j < task; j++){
            c[i][j] = -1;
        }
    }

    int edge = 0;
    int p,q,r;

    while (1) {
        fin >> p;
        if (p == -1) {
            break;
        }
        else {
            edge++;
            fin >> q >> r;
            c[p][q] = r;
            pred[q][p] = 1;
        }
    }

    int x,y,comm;
    
    int exit_task;
    int sum = 0;
    for(i = 0; i < task; i++){
        sum = 0;
        for(j = 0; j < task; j++){
            sum = sum + c[i][j];
        }
        if(sum == (-1) * task){
            exit_task = i;
            break;
        }
    }
      
    HEFT(task,edge,pro,exit_task);
    return 0;
}
/**
10
15
1 2 18
1 3 12
1 4 9
1 5 11
1 6 14
2 8 19
2 9 16
3 7 23
4 8 27
4 9 23
5 9 13
6 8 15
7 10 17
8 10 11
9 10 13
3
14 16 9
13 19 18
11 13 19
13 8 17
12 13 10
13 16 9
7 15 11
5 11 14
18 12 20
21 7 16
**/


