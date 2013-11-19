#include<stdio.h>
#include<algorithm>
#define Nmax 100100
using namespace std;
long long aint[4*Nmax+100],v[Nmax],maxim,M,x,z,y,indic;
long long up[4*Nmax+100];
long long ind[4*Nmax+100];
long long SUM,SUMI;
long long N;
long long inf = (long long)101010000*100;

inline void relax(int nod,int st,int dr)
{
    long long mij=(st+dr)/2;
    long long val=up[nod];
    if(st!=dr)
    {
        up[2*nod]+=val;
        up[2*nod+1]+=val;
    }
    if(st==dr)
        ind[nod]=st;
    aint[nod]+=up[nod];
    up[nod]=0;
}
void update(int nod,int ist,int idr,int st,int dr,long long val)
{
    if(ist<=st&&idr>=dr)
    {
        aint[nod]+=val;
        if(st!=dr)
        {
        up[2*nod]+=val;
        up[2*nod+1]+=val;
        }
        else ind[nod]=ist;
    }
    else
    {
        if(aint[nod]>0)
            relax(nod,st,dr);

        long long mij=(st+dr)/2;

        if(ist<=mij)
            update(2*nod,ist,idr,st,mij,val);

        if(idr>mij)
            update(2*nod+1,ist,idr,mij+1,dr,val);

        if(up[nod*2])
        relax(nod*2,st,mij);
        if(up[nod*2+1])
        relax(nod*2+1,mij+1,dr);
        if(aint[nod*2]>aint[nod*2+1])
        {
            aint[nod]=aint[2*nod+1];
            ind[nod]=ind[2*nod+1];
        }
        else
        {
            aint[nod]=aint[2*nod];
            ind[nod]=ind[2*nod];
        }
    }
    return;
}
int main()
{
freopen("biscuiti.in","r",stdin);
freopen("biscuiti.out","w",stdout);
    scanf("%lld",&N);
    for(long long i=1;i<=N;++i)
    {
        scanf("%lld",&v[i]);
        update(1,i,i,1,N,v[i]);
    }
    for(long long i=1;i<=N;++i)
    {
      //  printf("%d %d\n",aint[1],ind[1]);

        indic=ind[1];
        SUM+=(long long)-v[indic]+aint[1];
        update(1,ind[1],ind[1],1,N,inf);
    update(1,1,indic,1,N,i);

    }
    printf("%lld\n",SUM);

}
