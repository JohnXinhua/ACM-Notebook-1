#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
int N,M,K;
int v[25000],x,p=0;
char car;
vector <int> g[25000];
int l[25000],r[25000],u[25000],was[25000],S;
int cupj(int q)
{
  if(was[q])
    return 0;
  was[q]=1;
  for(int i=0;i<g[q].size();++i)
  {
    if(!r[g[q][i]])
    {

      l[q]=g[q][i];
      r[g[q][i]]=q;
      return 1;
    }
  }
  for(int i=0;i<g[q].size();++i)
  {
    if(cupj(r[g[q][i]]))
    {
      l[q]=g[q][i];
      r[g[q][i]]=q;
      return 1;
    }
  }
  return 0;


}
int L,R,y;

int main()
{
  freopen("cuplaj.in","r",stdin);
  freopen("cuplaj.out","w",stdout);
  scanf("%d%d%d\n",&L,&R,&M);
  for(int i=1;i<=M;++i)
  {
    scanf("%d%d",&x,&y);
    g[x].push_back(y);
  }

  /* for(int i=1;i<=M;++i)
     {
     for(int j=0;j<g[i].size();++j)
     printf("%d ",g[i][j]);
     printf("\n");
     }*/
  int ok=1;
  while(ok)
  {
    ok=0;
    for(int i=0;i<=L;++i)
      was[i]=0;
    for(int i=1;i<=L;++i)
      if(!l[i])
      {
        ok|= cupj(i);
      }
  }
  for(int i=1;i<=L;++i)
    if(l[i]>0)
      ++S;
  printf("%d\n",S);
  for(int i=1;i<=M;++i)
    if(l[i]>0)
    {
      printf("%d %d\n",i,l[i]);
    }


}
