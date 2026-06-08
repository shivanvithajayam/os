#include<stdio.h>
int main(){
    int arr[10]={1,2,3,4,5,6,7};
    int val;
    int pos;
    printf("enter element and position to insert");
    scanf("%d%d",&val,&pos);
    for (int i = 9; i > pos; i--) {
        arr[i] = arr[i-1];
    }
    arr[pos]=val;
    for(int i=0;i<10;i++){
        printf("%d",arr[i]);
    }
}