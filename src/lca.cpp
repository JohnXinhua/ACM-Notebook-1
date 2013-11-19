#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int K, N, M, x, y, L[200010], H[200010], Lg[200010], First[100010], Rmq[20][400010];
vector<int> G[100010];

void dfs(int nod, int lev)
{
  H[++K] = nod;
  L[K] = lev;
  First[nod] = K;

  int z = G[nod].size();
  for(int i=0;i<z;++i)
  {
    dfs(G[nod][i],lev+1);
    H[++K] = nod;
    L[K] = lev;
  }
}

void rmq()
{
  for(int i=2;i<=K;++i)
    Lg[i] = Lg[i/2]+1;
  for(int i=1;i<=K;++i)
    Rmq[0][i]=i;

  for(int i=1;(1<<i) < K; ++i)
    for(int j=1;j<=K-(1<<i);++j)
    {
      int l = 1<< (i-1);
      Rmq[i][j] = Rmq[i-1][j];
      if(L[Rmq[i-1][j + l]] < L[Rmq[i][j]])
        Rmq[i][j] = Rmq[i-1][j + l];
    }
}

int lca(int x, int y)
{
  int a = First[x], b = First[y];
  if(a>b)
  {
    int c=a;
    a=b;
    b=c;
  }
  int diff = b - a + 1;
  int l = Lg[diff];
  int sol = Rmq[l][a];
  int sh = diff - (1 << l);
  if(L[sol] > L[Rmq[l][a + sh]])
    sol = Rmq[l][a + sh];
  return H[sol];
}

int main()
{
  freopen("lca.in","r",stdin);
  freopen("lca.out","w",stdout);
  scanf("%d%d",&N,&M);
  for(int i=2;i<=N;++i)
  {
    scanf("%d",&x);
    G[x].push_back(i);
  }

  dfs(1,0);
  rmq();

  for(int i=1;i<=M;++i)
  {
    scanf("%d%d",&x,&y);
    printf("%d\n",lca(x,y));
  }
  return 0;
}
