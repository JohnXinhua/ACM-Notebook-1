#include<stdio.h>
#include <list>
#include <stack>
#include <queue>
using namespace std;

list<int> L,G[100010];
stack<int> S;
int N, M, deg[100010], viz[100010], x, y;

void DFS(int v)
{
  viz[v]=1;

  for(list<int>::iterator it = G[v].begin(); it!=G[v].end();++it)
    if(viz[*it]==0)
      DFS(*it);
}

bool conex()
{

  return 0;
  return 1;
}

bool eulerian()
{
  DFS(1);

  for(int i=1;i<=N;++i)
    if(deg[i]%2==1 || viz[i]==0)
      return 0;

  return 1;
}

void sterg(int v, int w)
{
  --deg[v];
  --deg[w];
  G[v].pop_front();
  for(list<int>::iterator it = G[w].begin(); it!=G[w].end();++it)
    if(*it==v)
    {
      G[w].erase(it);
      break;
    }
}

void euler(int v)
{
  while(!G[v].empty())
  {
    int w = G[v].front();
    S.push(v);
    sterg(v,w);
    v=w;
  }
}

void solve()
{
  int v=1;
  do
  {
    euler(v);
    v=S.top();
    S.pop();
    L.push_back(v);

  } while(!S.empty());
}

int main()
{
  freopen("ciclueuler.in","r",stdin);
  freopen("ciclueuler.out","w",stdout);
  scanf("%d%d",&N,&M);
  for(int i=1;i<=M;++i)
  {
    scanf("%d%d",&x,&y);
    G[x].push_back(y);
    G[y].push_back(x);
    ++deg[x];
    ++deg[y];
  }

  if(!eulerian())
  {
    printf("%d",-1);
    return 0;
  }

  solve();

  for(list<int>::iterator it = L.begin(); it!=L.end();++it)
    printf("%d ",*it);
  return 0;
}
