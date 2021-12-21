#include<bits/stdc++.h>

using namespace std;

// reusable func. called recursively 
void merge(int* arr, int start, int mid, int end) {
    int len = (end - start) + 1;

    // temp array used in merge sort
    int temp[len];
    int cur = 0;
    
    int i = start;
    int j = mid + 1;
    while(i <= mid && j <= end){
        if(arr[i] < arr[j]) {
            temp[cur] = arr[i];
            cur++;
            i++;
        }
        else {
            temp[cur] = arr[j];
            cur++;
            j++;
        }
    }
    if(i <= mid) {
        while(i <= mid) {
            temp[cur] = arr[i];
            i++;
            cur++;
        }
    }
    
    else if(j <= end) {
        while(j <= end) {
            temp[cur] = arr[j];
            j++;
            cur++;
        }
    }
    
    cur = 0;
    for(i=start; i<=end; i++) {
        arr[i] = temp[cur];
        cur++;
    }

}

// main caller method
void mergeSort(int *arr, int start, int end) {
    if(start < end) {
        // avoid overflow
	int mid = start + (end-start) / 2;
        

	mergeSort(arr, start, mid);
	mergeSort(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}

int main(int argc, char *argv[]) {
    int size = 100000;
    int a[size];
    
    //double start = 0, end = 0;
    
    for(int i=0; i<size; i++) {
        a[i] = rand()% 1000;
    }
    
    //int a[]= {7,33,5,5,23,111,75,34,77,121,120};
    
    cout<<"Input list:  ";
    for(int i=0; i<size; i++) 
        cout<<a[i]<<" ";
    cout<<endl<<endl;
	
	clock_t start, end;

    start = clock();
    
    mergeSort(a, 0, size-1);

    end = clock();
    
    cout<<"Merge Sorted List(serial):  ";
    
    for(int i=0; i<size; i++)
      	cout<<a[i]<<" ";
    cout<<endl<<endl;
    
    cout<<"Execution time(serial) = "<<double(end - start) / double(CLOCKS_PER_SEC)<<" seconds"<<endl;
    
    return 0;
}

