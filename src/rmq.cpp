#include<stdio.h>
#include<algorithm>

#define log 18
#define Nmax 100100

inline int min(int a,int b)
{
  if(a<b)
    return a;
  return b;
}

int rmq[log][Nmax],x,y,maxi,sh;
int v[Nmax];
int lg[Nmax],N,M;
int main()
{
  freopen("rmq.in","r",stdin);
  freopen("rmq.out","w",stdout);

  scanf("%d%d",&N,&M);
  for(int i=1;i<=N;++i)
    scanf("%d",&v[i]);
  for(int i=2;i<=N;++i)
    lg[i]=lg[i/2]+1;

  for(int i=1;i<=N;++i)
    rmq[0][i]=v[i];
  v[0]=-1;

  for(int i=1;(1<<i)<=N;++i)
  {
    for(int j=1;j+(1<<i)-1<=N;++j)
    {
      maxi=1<<(i-1);
      rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+maxi]);
    }
  }

  for(int i=1;i<=M;++i)
  {
    scanf("%d%d",&x,&y);
    maxi=lg[y-x+1];
    sh=y-x+1-(1<<maxi);
    printf("%d\n",min(rmq[maxi][x],rmq[maxi][x+sh]));
  }
}
