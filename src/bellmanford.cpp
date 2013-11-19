#include<stdio.h>
#define INF 99999999
#define Nmax 50500
int coad[Nmax*10],viz[Nmax],nrviz[Nmax],x,y,z,N,M,S=1,k,st,ok=1,best[Nmax];
struct Nod{
  int cost,val,nrmuchie;
  Nod *next;} *l[Nmax];
void adauga(int x,int y,int z)
{
  Nod *q=new Nod;
  q->val=y;
  q->cost=z;
  q->next=l[x];
  l[x]=q;
}
void make_bell(int p)
{
  viz[p]=0;
  for(Nod *it=l[p];it!=NULL;it=it->next)
  {

    if(best[it->val]>best[p]+(it->cost))
    {
      best[it->val]=best[p]+it->cost;
      if(viz[it->val]==0)
      {
        viz[it->val]=1;
        coad[k++]=it->val;
        ++nrviz[it->val];
        if(nrviz[it->val]==N+1)
          ok=0;
      }
    }
  }
}
int main()
{
  freopen("bellmanford.in","r",stdin);
  freopen("bellmanford.out","w",stdout);
  scanf("%d%d",&N,&M);
  for(int i=1;i<=M;++i)
  {
    scanf("%d%d%d\n",&x,&y,&z);
    adauga(x,y,z);
  }
  for(int i=1;i<=N;++i)
    best[i]=INF;
  coad[k++]=S;
  viz[S]=1;
  best[S]=0;
  nrviz[S]=1;
  while(st<k&&ok)
  {
    make_bell(coad[st]);
    ++st;
  }
  if(ok)
  {
    for(int i=2;i<=N;++i)
      printf("%d ",best[i]);
    return 0;
  }
  printf("Ciclu negativ!");
  return 0;

}
