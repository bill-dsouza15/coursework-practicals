#include <iostream>
#include <stdio.h>
#include <string.h>
#define fors(v, s, e) for (int v = (int)s; v < (int)e; v++)

using namespace std;

// CHECK ADJACENT COLOR
bool check(int **graph, int n, int *res, int col, int v)
{
    fors(j, 0, n)
    {
        if (graph[v][j] && res[j] == col)
        {
            return false;
        }
    }
    return true;
}

// GRAPH COLORING UTIL
// graph ‐ adjacency matrix; n ‐ number of vertices; m ‐ number of colors; res ‐ resultant array; v ‐ vertice
bool graphcoloring(int **graph, int n, int m, int *res, int v)
{
    if (v == n)
    {
        fors(i, 0, n)
        {
            cout << "V" << i << " - " << res[i] << " | ";
        }
        cout << "\n"
             << endl;
        return true;
    }
    bool b = false;
    fors(i, 0, m)
    {
        if (check(graph, n, res, i, v))
        {
            //Color satisfies neighbourhood check. Assigned to vertice.
            res[v] = i;
            b = graphcoloring(graph, n, m, res, v + 1) || b;
            //If above returned false for v+1 then backtrack and assign ‐1 (to change color)
            res[v] = -1;
        }
    }
    return b;
}

// DRIVER CODE
int main()
{
    //Program for proper vertex coloring of a graph
    int n, i, j, Delta = 0, temp = 0, m;
    cout << "Enter the number of nodes: ";
    cin >> n;
    int **graph;
    graph = new int *[n];
    fors(i, 0, n)
    {
        graph[i] = new int[n];
        memset(graph[i], -1, sizeof(int) * n);
    }
    i = 0;
    int edge;
    cout << "Enter the adjacency matrix (0/1)" << endl;
    while (i < n)
    {
        j = 0;
        temp = 0;
        while (j < n)
        {
            if (i != j)
            {
                if (graph[i][j] == -1)
                {
                    cout << i << " <-> " << j;
                    cout << "\tEdge? : ";
                    cin >> edge;
                    if (edge == 0 || edge == 1)
                    {
                        temp = (edge) ? temp + 1 : temp;
                        graph[i][j] = edge;
                        graph[j][i] = edge;
                        j++;
                    }
                    else
                    {
                        cout << "Invalid edge choice!" << endl;
                    }
                }
                else
                {
                    temp = (graph[i][j]) ? temp + 1 : temp;
                    j++;
                }
            }
            else
            {
                graph[i][j] = 0;
                graph[j][i] = 0;
                j++;
            }
        }
        Delta = max(Delta, temp);
        i++;
    }
    cout << "\nAdjacency matrix" << endl;
    fors(i, 0, n)
    {
        fors(j, 0, n)
        {
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }

    //We can check for valid m using Brook's theorem : (chi(G) - chromatic number & Delta(G) - degree of vertice)
    //chi(G) <= Delta(G) [any vertex colorable graph G] or
    //chi(G) <= Delta(G)+1 [complete and odd length cyclic graph]
    //We'll constrain m such that 1 <= m <= Delta(G)+1
    cout << "\nMax degree of vertice : " << Delta << endl;
    while (true)
    {
        cout << "\nEnter the number of colors : ";
        cin >> m;
        if (m > 0)
        {
            if (m >= (Delta))
            {
                break;
            }
            else
            {
                cout << "Violation : Expected m >= Delta(G)" << endl;
            }
        }
        else
        {
            cout << "Violation : Expected m > 0" << endl;
        }
    }
    //Creating res array for storing colors (numerical)
    int *res = new int[n];
    memset(res, -1, sizeof(int) * n);
    if (!graphcoloring(graph, n, m, res, 0))
    {
        cout << "No solution exists!" << endl;
    }
    //Deleting from heap
    delete graph;
    delete res;
    return 0;
}