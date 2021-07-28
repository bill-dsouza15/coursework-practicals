#include <stdio.h>
#include <iostream>
#define fori(s,e) for(int i = (int) s;i < (int) e;i++)

using namespace std;

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int l, int h){
    
    //Pivot first element
    int pivot = array[l];
    int i = l+1;
    
    for(int j=l+1; j<=h; j++)  {
        if (array[j] < pivot) {
            swap(&array[i],&array[j]);
            i++;
        }
    }
    swap(&array[l],&array[i-1]) ;
    return i-1;
}

void quicksort(int array[], int l,int h){
    if(l<h){
        int pivot = partition(array,l,h);
        quicksort(array, l, pivot-1);
        quicksort(array, pivot+1, h);
    }
}

int main()
{
    int *array,n,l,h;
    cout<<"Enter the number of elements: ";
    cin>>n;
    array = new int[n];
    cout<<"Enter the array: ";
    fori(0,n){
        cin>>array[i];
    }
    
    l = 0;
    h = n-1;
    quicksort(array,l,h);
    cout<<"The sorted array is:\t";
    fori(0,n){
        cout<<array[i]<<"\t";
    }
    cout<<endl;
}
