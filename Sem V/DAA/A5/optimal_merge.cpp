#include <iostream>
#include <stdio.h>
#include <queue>

#define pq priority_queue<tree_node, vector<tree_node>, comparator>

using namespace std;

typedef struct Tree{
   int key;
   struct Tree *left;
   struct Tree *right;
} *tree_node;

struct comparator{
    bool operator() (tree_node node1, tree_node node2 ){
        return node1->key > node2->key;
    }      
};

void printHeight(tree_node root){
    tree_node sentinel;
    sentinel = new struct Tree();
    queue<tree_node> q;
    q.push(root);
    q.push(sentinel);
    while(q.size() > 0){
        cout<<q.front()->key<<" ";
        if(q.front()->left != NULL){
            q.push(q.front()->left);
        }
        if(q.front()->right != NULL){
            q.push(q.front()->right); 
        }
        q.pop();
        if(q.front() == sentinel){
            cout<<endl;
            if(q.size() > 1){
                q.push(sentinel);
            }
            q.pop();
        }
    }    
}

int mergeCost(pq costs){
    int sum, total = 0;
    while(costs.size() > 1){
        tree_node node;
        node = new struct Tree();
        
        node->left = costs.top();
        sum = costs.top()->key;
        costs.pop();
        
        node->right = costs.top();
        sum += costs.top()->key;
        costs.pop();
        
        node->key = sum;
        total += sum;
        costs.push(node);
    }
    cout<<"Tree : \n";
    printHeight(costs.top());
    cout<<endl;
    return total;
}

int main()
{
    int n;
    cout<<"Enter the number of nodes to be merged : ";
    cin>>n;
    
    int key, total;
    pq costs;
    cout<<"Enter the nodes : ";
    for(int i=0;i<n;i++){
        tree_node node;
        node = new struct Tree();
        node->left = NULL;
        node->right = NULL;
        cin>>key;
        node->key = key;
        costs.push(node);
    }
    total = mergeCost(costs);
    cout<<"\nThe optimal merge cost is = "<<total<<endl;
    return 0;
}
