#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int n,*array,key;
    cout<<"Enter the number of elements: ";
    cin>>n;
    array = new int[n];
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++){
        cin>>array[i];
    }
    cout<<"Enter the key: ";
    cin>>key;
    for(int i=0;i<n;i++){
        if(array[i]==key){
            cout<<"The key is found at index "<<i+1<<endl;
            break;
        }
        else if(array[i]!=key && i==n-1){
            cout<<"The key is not found!"<<endl;
        }
    }
    return 0;
}

