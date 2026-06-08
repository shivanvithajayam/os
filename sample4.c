#include<stdio.h>
#include<stdbool.h>
bool main(){
    int arr[10]={1,1,2,2,3,3,4,5};
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            if(arr[i]==arr[j]){
                printf("duplicates found");
                return;
            }
        }
    }
}