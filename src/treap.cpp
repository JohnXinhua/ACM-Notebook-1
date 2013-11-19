#include<stdio.h>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<time.h>
using namespace std;

struct T {
    int key, priority,nr;
    T *left, *right;
    T() {}
    T(int key, int priority, T* left, T* right) {
        this->key = key;
        this->priority = priority;
        this->left = left, this->right = right;
        this->nr = 0;
    }
} *R, *nil; // nil indica un nod 'gol'

void init(T* &R) {
    srand(unsigned(time(0)));
    R = nil = new T(0, 0, NULL, NULL);
}

void parc(T* n){
    if(n== nil)
        return;

    //printf("%d %d %d %d\n",n->key,n->nr,n->left->key,n->right->key);
    parc(n->left);
    parc(n->right);
}
inline void update(T* &n){
    if(n==nil)
        return;
    n->nr = n->left->nr + n->right->nr + 1;

}
int search(T* n, int key) {
    if (n == nil) return 0;
    if (key == n->key) return 1;
    if (key < n->key)
        return search(n->left, key);
    else
        return search(n->right, key);
    update(n->right);
    update(n->left);
    update(n);
}

void rotleft(T* &n) {
    T *t = n->left;
    n->left = t->right, t->right = n;
    n = t;
    update(t->right);
    update(t->left);
    update(t);
    update(n->right);
    update(n);
}

void rotright(T* &n) {

    T *t = n->right;
    n->right = t->left, t->left = n;
    n = t;
    update(t->right);
    update(t->left);
    update(t);
    update(n->left);
    update(n);
}

int nth(T* &n,int nr){

    if(n==nil)
    return -1;
    if(nr==0)
        return n->key;
    int leftval = n->left->nr;
   // cout<< n->nr <<" "<<n->key<<" "<<leftval<<" "<<nr<<"\n";
    if(nr-leftval == 1)
        return n->key;
    if(leftval >= nr)
        return nth(n->left,nr);
    return nth(n->right,nr-leftval-1);
}

void balance(T* &n) {
    if (n->left->priority > n->priority)
        rotleft(n);
    else if (n->right->priority > n->priority)
        rotright(n);

    update(n->right);
    update(n->left);
    update(n);
}

void insert(T* &n, int key, int priority) {
    if (n == nil) {
        n = new T(key, priority, nil, nil);
        n->nr=1;
        return;
    }
    (n->nr)++;
    if (key <= n->key)
        insert(n->left, key, priority);
    else if (key > n->key)
        insert(n->right, key, priority);

    balance(n);

}

int main()
{
freopen("sdo.in","r",stdin);
//freopen("sdo.out","w",stdout);

init(R);
int N,x,k;
cin>>N>>k;


for(int i=1;i<=N;++i){
    cin>>x;
    insert(R,x,rand()%10000000);
}
cout<<nth(R,k)<<"\n\n";


//parc(R);

return 0;
}
