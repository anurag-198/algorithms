//1 = Start task and 1 Exit task
#include<bits/stdc++.h>
using namespace std;
int c[1000][1000];
int w[1000][1000];
int W[1000];
int RANK[1000];
int arr_sorted_index[1000];

void func_to_sort_indexes(int task){
    vector<pair<int,int> >v;
    int i;
    for(i = 0; i < task; i++){
        v.push_back(make_pair(RANK[i],i));
    }
    sort(v.begin(),v.end());
    for(i = 0; i < task; i++){
        arr_sorted_index[i] = v[task - 1 - i].second;
    	cout << arr_sorted_index[i] <<" ";
    }
    /*for(i = 0; i < task; i++){
        cout<<arr_sorted_index[i]<<" ";
    }*/
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
        W[i] = W[i] / pro;
    }
}
void HEFT(int task,int edge,int pro, int exit_task){
    calc_avg_execution_cost(task,pro);
    calc_rank(0,exit_task,task);
    int i,j;
    func_to_sort_indexes(task);
    

}
int main(){
    int task;
    //cout<<"ENTER THE NUMBER OF TASKS:\n";
    cin>>task;
    int edge;
    //cout<<"ENTER THE NUMBER OF EDGES:\n";
    cin>>edge;
    int i;
    int j;
    //cout<<"ENTER THE COMMUNICATION COST:\n";
    int x,y,comm;
    for(i = 0; i < task; i++){
        for(j = 0; j < task; j++){
            c[i][j] = -1;
        }
    }
    for(i = 0; i < edge; i++){
        cin>>x>>y>>comm;
        x--;
        y--;
        c[x][y] = comm;
    }
    
    int exit_task;
    int sum = 0;
    for(i = 0; i < task; i++){
        sum = 0;
        for(j = 0; j < task; j++){
            sum = sum + c[i][j];
        }
        if(sum ==0){
            exit_task = i;
            break;
        }
    }
   // cout<<"ENTER THE NUMBER OF PROCESSORS:\n";
    int pro;
    cin>>pro;
  //  cout<<"ENTER THE COMPUTATION COST MATRIX:\n";
    for(i = 0; i < task; i++){
        for(j = 0; j < pro; j++){
            cin>>w[i][j];
        }
    }
    for(i = 0; i < task; i++){
        W[i] = 0;
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


/**
1 2 1
1 3 7
1 4 5
1 5 5
2 6 7
3 6 2
4 6 5
5 6 5
**/
