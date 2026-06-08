#include<stdio.h>
void main(){
    int arr[2][2]={{1,2},{3,4}};
    int temp;
    for(int i=0;i<2;i++){
        for(int j=i+1;j<2;j++){
            temp=arr[i][j];
            arr[i][j]=arr[j][i];
            arr[j][i]=temp;
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}