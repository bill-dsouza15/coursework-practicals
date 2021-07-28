#include <bits/stdc++.h>

#define INF 111
#define fori(s,e) for(int i=(int)s;i<(int)e;i++)
#define forj(s,e) for(int j=(int)s;j<(int)e;j++)

using namespace std;

struct distance{
    int dist;
    int node;
};

int** create(int n, int** adj, int* level){
    //Checking conditions of input
    int start=0, end, cost;
    while(start<n-1){
        cout<<start<<" -> ";
        cin>>end;
        if(end>=0){
            //Check if start==end(self directed edge) or level[end]-level[start]!=1(end node is more than one level away)
            bool test = !((start==end) || (level[end]-level[start]!=1)); 
            if(end<n && test){
                cout<<"Cost : ";
                cin>>cost;
                //Check if cost is positive
                if(cost >= 0){
                    adj[start][end] = cost;
                }
                else{
                    cout<<"Violation : Cost < 0\n";
                }
            }
            else{
                cout<<"Violation : End node\n";
            }
        }
        else{
            cout<<"Done : Node "<<start<<"\n\n";
            start++;
        }
    }
    return adj;
}

struct distance* minCostPath(int** adj, int n){
    //Distance array
    struct distance* d;
    d = new struct distance[n];
    //prev for tracking change in value of d[i] and changing the node
    int prev;
    
    //Distance of nth node is 0
    d[n-1].dist = 0;
    d[n-1].node = n-1;
    
    for(int i=n-2; i>=0; i--){
        //The dist of i->dest is set to INF
        d[i].dist = INF;
        prev = INF;
        
        for(int j=i; j<n; j++){
            //Continue if there is no edge
            if(adj[i][j] == INF){
                continue;
            }
            //Distance of i->dest is 
            //minimum(current dist of i->dest, dist of i->j + dist of j->dest)
            d[i].dist = min(d[i].dist, adj[i][j]+d[j].dist);
            if(d[i].dist != prev){
                d[i].node = j;
                prev = d[i].dist;
            }
        }
    }
    return d;
}

int main()
{
    int n;
    cout<<"Enter the number of nodes : ";
    cin>>n;
    
    //Allocation onto heap
    int** adj = new int*[n];
    fori(0,n){
        adj[i] = new int[n];
        forj(0,n){
            adj[i][j] = INF;
        }
    }
    
    //Level of each node in the graph
    int* level = new int[n];
    cout<<"The level of nodes\n";
    fori(0,n){
        cout<<"For node "<<i<<" : ";
        cin>>level[i];
    }
    
    //Creating the adjacency matrix while checking multistage graph conditions
    cout<<"Create the adjacency matrix\n";
    adj = create(n, adj, level);
    
    //Printing adjacency matrix
    cout<<"Adjacency matrix\n";
    fori(0,n){
        forj(0,n){
            cout<<adj[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    //Calculating minimum cost path
    struct distance* res;
    res = new struct distance[n];
    res = minCostPath(adj, n);
    
    //Print results
    int i=0;
    cout<<"\nMinimum cost : "<<res[0].dist<<endl;
    cout<<"Path : ";
    cout<<i<<" -> ";
    while(res[i].node!=n-1){
        cout<<res[i].node<<" -> ";
        i = res[i].node;
    }
    cout<<n-1;
    
    //Deleting from heap to prevent leaks
    delete level;
    delete adj;
    delete res;
    return 0;
}
