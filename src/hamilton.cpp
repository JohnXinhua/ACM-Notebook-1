#include<stdio.h>
#include<vector>
using namespace std;

const int inf = 1000000000;
int N,M,x,y,z,Sol,b[262150][22],c[22][22];
vector<int> a[22];

int best(int conf, int last)
{
  if(b[conf][last]>=0)
    return b[conf][last];

  b[conf][last]=inf;
  for(int i=0;i<a[last].size();++i)
    if(conf & (1<<a[last][i]))
    {
      if(a[last][i]==0 && conf!=(1<<last)+1)
        continue;
      if(b[conf][last] > best(conf^(1<<last),a[last][i])+c[a[last][i]][last])
        b[conf][last] = best(conf^(1<<last),a[last][i])+c[a[last][i]][last];
    }

  return b[conf][last];

}

int main()
{
  freopen("hamilton.in","r",stdin);
  freopen("hamilton.out","w",stdout);

  scanf("%d%d",&N,&M);

  for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
      c[i][j]=inf;

  for(int i=0;i<262150;++i)
    for(int j=0;j<20;++j)
      b[i][j]=-1;

  b[1][0]=0;

  Sol = inf;

  for(int i=1;i<=M;++i)
  {
    scanf("%d%d%d",&x,&y,&z);
    c[x][y]=z;
    a[y].push_back(x);
  }

  for(int i=0;i<a[0].size();++i)
  {
    if(c[a[0][i]][0] + best((1<<N)-1 , a[0][i]) < Sol)
      Sol = c[a[0][i]][0] + best((1<<N)-1,a[0][i]);
  }

  if(Sol==inf)
    printf("Nu exista solutie\n");

  else
    printf("%d\n",Sol);
}
