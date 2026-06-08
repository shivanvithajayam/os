#include<stdio.h>
void main(){
    int arr[10]={1,2,3,4,5,6,7,8,9,10};
    int small=arr[0];
    int pos=0;
    for(int i=0;i<10;i++){
        if(arr[i]<small){
            small=arr[i];
            pos=i;
            
        }
    }
    printf("smallest element is %d at position %d",small,pos);
}