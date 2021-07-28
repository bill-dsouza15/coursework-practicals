#include <stdio.h>
#include <iostream>
#include <queue>
#include <cstring>
#include <iomanip>

#define fors(v,s,e) for(int v = (int)s; v < int(e); v++)
#define MAX 999999
using namespace std;

//struct for input
struct obj{
    float profit = -1;
    float weight = -1;
};

//struct for simulating state space tree
struct knapsack{
    int index=-1;       //level
    int type = -1;      //will the item be used or not
    float u=0;          //upper bound
    float c=0;          //cost
    float w=0;          //weight
};

//Compute upper bound and compute cost
struct knapsack computeUC(struct knapsack node, struct obj* catalog, int n, int m, int* res){
    fors(i,0,n){
        //If node is not to be included (type = 0) in knapsack then skip it
        if(node.index==i && node.type==0){
            continue;
        }
        if(node.w + catalog[i].weight <= m ){
            node.u += catalog[i].profit * res[i] * -1;
            node.w += catalog[i].weight * res[i];
            node.c += catalog[i].profit * res[i] * -1;
        }
        else{
            node.c += (m-node.w) * (catalog[i].profit/catalog[i].weight) * -1;
            break;
        }
    }
    return node;
}

void LCBBKnapsack(struct obj* catalog, int n, int m){
    //Create res array for showing inclusion or exclusion of item in knapsack (0/1)
    int *res;
    res = new int[n];
    fors(i,0,n){
        res[i] = 1;
    }
    
    float upper = MAX;
    queue<struct knapsack> q;
    
    //Create root node of state space tree
    struct knapsack node;
    node = computeUC(node, catalog, n, m, res);
    upper = node.u;
    q.push(node);
    
    while(!q.empty()){
        struct knapsack temp,a,b;
        temp = q.front();
        q.pop();
        if(temp.index==n-1){
            continue;
        }
        
        //Create node for INCLUDING index in state space tree
        b = temp;
        b.index = temp.index + 1;
        b.type = 1;
        if(b.u <= upper){
            upper = b.u;
            q.push(b);
            res[b.index] = b.type;
        }
        
        //Create node for NOT INCLUDING index in state space tree
        a.index = temp.index + 1;
        a.type = 0;
        a = computeUC(a, catalog, n, m, res);
        if(a.u <= upper){
            upper = a.u;
            q.push(a);
            res[a.index] = a.type;
        }
    }
    
    //Display solution
    int p = 0;
    float w = 0;
    cout<<"\nSolution"<<endl;
    fors(i,0,n){
        cout<<"I"<<i<<" -> "<<res[i]<<endl;
        p += catalog[i].profit*res[i];
        w += catalog[i].weight*res[i];
    }
    cout<<fixed<<setprecision(2)<<"\nProfit : "<<p;
    cout<<fixed<<setprecision(2)<<"\nWeight : "<<w;

    //Deleting from heap
    delete res;
}

int main()
{
    int n,i,m;
    cout<<"Enter the number of objects in catalog : ";
    cin>>n;
    
    //Create catalog from user input
    struct obj* catalog;
    catalog = new struct obj[n];
    i=0;
    while(i<n){
        cout<<"For object "<<i+1<<endl;
        if(catalog[i].weight == -1){
            cout<<"Weight : ";
            cin>>catalog[i].weight;
            if(catalog[i].weight < 0){
                cout<<"Violation : Expected object weight >= 0 ";
                catalog[i].weight = -1;
                continue;
            }
        }
        if(catalog[i].profit == -1){
            cout<<"Profit : ";
            cin>>catalog[i].profit;
            if(catalog[i].profit < 0){
                cout<<"Violation : Expected object profit >= 0 ";
                catalog[i].profit = -1;
                continue;
            }
        }
        i++;
    }
    cout<<"\nCatalog"<<endl;
    fors(i,0,n){
        cout<<"Item "<<i+1<<" -> ";
        cout<<fixed<<setprecision(2)<<"Weight : "<<catalog[i].weight<<" ";
        cout<<fixed<<setprecision(2)<<"Profit : "<<catalog[i].profit;
        cout<<endl;
    }
    
    cout<<"\nEnter capacity of knapsack (m) : ";
    cin>>m;
    
    //Create res array and call branch and bound function
    LCBBKnapsack(catalog, n, m);

    //Deleting from heap
    delete catalog;

    return 0;
}