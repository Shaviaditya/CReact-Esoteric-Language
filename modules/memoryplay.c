#include<stdio.h>
#include<stdlib.h>
#define size 2
int cnt=0;
int *checkout(int counter,int *pre, int *ptr){
    if(counter==(*pre)){
        ptr = (int*)realloc(ptr,sizeof(int)*(*pre)*2);
        (*pre) = (*pre)*2;
    }
    return ptr;
}
void show(int *ptr, int counter)
{
    for (int i = 0; i < counter; i++)
    {
        printf("%d\t", *(ptr + i));
    }
    printf("\n");
}
int main(){
    int sz = size;
    int *ptr = (int *)malloc(sizeof(int)*cnt);
    int t = 1;
    while(t){
        printf("Enter the value to enter : ");
        int val;    scanf("%d",&val);
        ptr = checkout(cnt,&sz,ptr);
        *(ptr + cnt++) = val;
        printf("Do you want to enter more : ");
        scanf("%d",&t);
    }
    show(ptr,cnt);
    return 0;
}