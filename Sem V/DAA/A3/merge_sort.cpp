#include <stdio.h>
#include <iostream>

using namespace std;

void merge(int array[],int l,int mid,int h){
    int n1,n2;
    n1 = mid-l+1;
    n2 = h-mid;
    
    //Create two arrays to copy data
    int temp1[n1], temp2[n2];
    
    //Copy data to the arrays
    for(int i=0;i<n1;i++){
        temp1[i] = array[l+i];
    }
    for(int i=mid+1;i<=h;i++){
        temp2[i-mid-1] = array[i];
    }
    
    //Sort data and put into original array
    int i=0,j=0,k=l;
    while(i<n1 && j<n2){
        if(temp1[i] < temp2[j]){
            array[k] = temp1[i];
            i++;
        }
        else{
            array[k] = temp2[j];
            j++;
        }
        k++;
    }
    
    //Put any remaining elements into the array
    while(i<n1){
        array[k] = temp1[i];
        i++;
        k++;
    }
    while(j<n2){
        array[k] = temp2[j];
        j++;
        k++;
    }
}

void mergesort(int array[], int l, int h, int n){
    if(l<h){
        int mid = (l+h)/2;
        mergesort(array,l,mid,n);
        mergesort(array,mid+1,h,n);
        merge(array,l,mid,h);
    }    
}

int main()
{
    int n, *array;
    cout<<"Enter the number of elements: ";
    cin>>n;
    array = new int[n];
    cout<<"\nEnter the elements: ";
    for(int i=0;i<n;i++){
        cin>>array[i];  
    }
    int l = 0;
    int h = n-1;
    mergesort(array,l,h,n);
    cout<<"\nThe sorted array is: ";
    for(int i=0;i<n;i++){
        cout<<array[i]<<"\t";
    }
    cout<<"\n"<<endl;
    return 0;
}
