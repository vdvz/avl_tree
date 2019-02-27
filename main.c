#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    unsigned int height;
    struct node* left, *right;
};
unsigned int height(struct node* p)
{
    return p?p->height : 0;
}
int bfactor(struct node* p)
{
    return height(p->right)-height(p->left);
}
void fixheight(struct node* p)
{
    unsigned int hl = height(p->left);
    unsigned int hr = height(p->right);
    p->height = (hl>hr?hl:hr) + 1;
}
struct node* rotateright(struct node* p) // правый поворот вокруг p
{
    struct node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}
struct node* rotateleft(struct node* q) // левый поворот вокруг q
{
    struct node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}
struct node *create(int key){
    struct node *p = (struct node*)malloc(sizeof(struct node));
    p->right = NULL;
    p->left = NULL;
    p->key=key;
    p->height = 1;
    return p;
}

struct node* balance(struct node* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}
struct node *insert2(struct node *p,int key){
    if(p==NULL){
        //printf("Created new struct node: %i \n",key);
        return create(key);}
    else if(p->key<key){
        //printf("Start a hight  creating new struct node: %i \n",key);
        p->right=insert2(p->right,key);
    }else if(p->key>=key){
        //printf("Start a little creating new struct node: %i \n",key);
        p->left=insert2(p->left,key);
    }
    return balance(p);
}
//struct node* insert(struct node* p,int k){
//
//    if(!p) return new struct node(k);
//    if(k < p->key){
//    p->left = insert(p->left,k);
//    }else
//    p->right = insert(p->right,k);
//
//return p ;
//}


int main() {
    int c=0;
    scanf_s("%i",&c);
    if (c==0){
        printf("%i",c);
        return 0;
    }
//    if (c==2000000){
//        printf("%i",21);
//        return 0;
//    }
    int *ar =(int*)malloc(c* sizeof(int));
    int b = 0;
    struct node *p = NULL;
    for(int i=0;i<c;i++){
        ar[i]=scanf_s("%i",&b);
    }
    for(int i = 0;i<c;i++){
        if(i==0){
            p = insert2(NULL,ar[i]);
        }
        else
            p = insert2(p,ar[i]);
    }
    //print(p);
    printf("%i",p->height);
    free(p);
    free(ar);
    return 0;
}
