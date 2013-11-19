#include<algorithm>
#include<stdio.h>

#define Nmax 101010

using namespace std;

int AIB[Nmax],v[Nmax],M,x,y,z;
int N,num;

inline int zeros(int x)
{
return ((x ^ (x - 1)) & x );
}

inline void Add(int x, int q)
{
    int i;

    for (i = x; i <= N; i += zeros(i))
        AIB[i]+=q;
}

inline int comp(int x)
{
    int i, ret = 0;

    for (i = x; i > 0; i -= zeros(i))
        ret +=AIB[i];
    return ret;
}

int main()
{
    freopen("aib.in","r",stdin);
    freopen("aib.out","w",stdout);
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)
    {
    scanf("%d",&v[i]);
    Add(i,v[i]);
    }
    for(int i=1;i<=M;++i)
    {
        scanf("%d%d",&x,&y);
        if(x==0)
        {   scanf("%d",&z);
            Add(y,z);
        }
        if(x==1)
        {   scanf("%d",&z);
            printf("%d\n",comp(z)-comp(y-1));
        }
        if(x==2)
        {
            int st=1,dr=N,mij,rez=-1;
            while(st<=dr)
            {
                mij=(st+dr)/2;
                //printf("%d !",mij);
                if(comp(mij)>y)
                {
                    dr=mij-1;
                    //rez=mij;
                }
                else if(comp(mij)==y)
                {
                    dr=mij-1;
                    rez=mij;
                }
                else st=mij+1;
            }
            printf("%d\n",rez);
        }
    }

}
