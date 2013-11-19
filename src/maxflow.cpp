#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

int flux[1010][1010];
int c[1010][1010];
int tata[1010];
int viz[1010],flow;
int coad[1015];
int Q,x,y,z,N,act,M,flow_min;

vector<int> g[1010];

int BF()
{
  for(int i=1;i<=N;++i) {
    viz[i]=0;
  }
  coad[0]=1;
  int st=0,dr=1;
  viz[1]=1;
  while(st<dr)
  {
    // printf("!");
    act=coad[st];
    if(act!=N)
      for(int i=0;i<g[act].size();++i)
      {

        Q = g[act][i];
        if(c[act][Q] == flux[act][Q] || viz[Q])
          continue;
        viz[Q]=1;
        coad[dr++]=Q;
        tata[Q]=act;

      }
    ++st;
  }
  return viz[N];
}

int main()
{
  freopen("maxflow.in","r",stdin);
  freopen("maxflow.out","w",stdout);
  scanf("%d%d",&N,&M);
  for(int i=1;i<=M;++i)
  {
    scanf("%d%d%d",&x,&y,&z);
    c[x][y]+=z;
    g[x].push_back(y);
    g[y].push_back(x);

  }

  for(flow=0; BF();)
  {//printf("!");
    for(int i=0;i<g[N].size();++i)
    {
      // printf("%d\n",flux);
      act=g[N][i];
      if(flux[act][N]==c[act][N] ||!viz[act])
        continue;
      tata[N]=act;

      flow_min=10101000;
      for(int nod=N;nod!=1;nod=tata[nod])
        flow_min=min(flow_min,c[tata[nod]][nod]-flux[tata[nod]][nod]);
      if(flow_min==0)
        continue;
      //   printf("%d\n",flow_min);
      for(int nod=N;nod!=1;nod=tata[nod])
      {
        flux[tata[nod]][nod]+=flow_min;
        flux[nod][tata[nod]]-=flow_min;
      }
      flow+=flow_min;
    }
  }
  printf("%d ",flow);
}
