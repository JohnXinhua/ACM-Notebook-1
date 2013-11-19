#include <vector>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>

#define pb push_back

using namespace std;

vector<int> g[202020],gx[202020],last,stackx,viz,iss,low,aux,tare,gr_in;
vector<vector<int> > comp;
int N,index=1,k,Nn,M,x,y;
int rez[201010];
int notn(int x){
  if(x<=N){
    return x + N;
  }
  return x-N;
}

void df(int x){

  viz[x] = index;
  low[x] = index;
  stackx[++k] = x;
  iss[x] = 1;
  ++index;
  for(int i=0;i<g[x].size();++i){
    if(viz[g[x][i]] == 0){
      df(g[x][i]);
      low[x] = min(low[x],low[g[x][i]]);
    }
    else{
      if(iss[g[x][i]]){
        low[x] = min(low[x],low[g[x][i]]);
      }
    }
  }
  if(low[x] == viz[x]){

    aux.clear();

    do{
      aux.pb(stackx[k]);
      iss[stackx[k]] = 0;
      --k;
    }while(stackx[k+1] != x);

    comp.pb(aux);
  }
}

void init(){
  index = 1;
  stackx.resize(Nn+10);
  viz.resize(Nn+10);
  iss.resize(Nn+10);
  low.resize(Nn+10);
  tare.resize(Nn+10);
  last.resize(Nn+10);
  gr_in.resize(Nn+10);
}

void make_ctc(){
  Nn=2*N;
  init();
  for(int i=1;i<=Nn;++i){
    if(viz[i]==0){
      df(i);
      //  printf("%d\n",i);
    }
  }
  for(int i=0;i<comp.size();++i){
    for(int j=0;j<comp[i].size();++j){
      tare[comp[i][j]] = i+1;
    }
  }
}

void solve(){
  for(int i=1;i<=N;++i){
    if(tare[i] == tare[notn(i)]){
      printf("-1\n");
      return;
    }
  }

  int nod;

  for(int i=0;i<comp.size();++i){
    for(int j=0;j<comp[i].size();++j){
      nod = comp[i][j];

      for(int k=0;k<g[nod].size();++k){
        int compv = tare[g[nod][k]];
        if ( last[compv] != i+1 && compv != i+1 ){
          gx[i+1].pb(compv);
          ++gr_in[compv];
          last[compv]=i+1;
        }
      }
    }
  }
  queue<int> Q;
  //printf("%d\n\n",comp.size());
  for(int i=1;i<=comp.size();++i){
    if(gr_in[i]==0){
      Q.push(i);
      // printf("%d!\n",i);
    }
  }
  int nr = 0;
  while(!Q.empty()){
    ++nr;
    nod = Q.front(); Q.pop();
    // printf("%d\n",nod);
    for (int i=0;i<gx[nod].size();++i){
      int nodv = gx[nod][i];
      --gr_in[nodv];
      if (gr_in[nodv]==0)
        Q.push(nodv);
    }
    if ( last[nod] == -1 )  continue ;

    for (int i=0;i<comp[nod-1].size();++i){
      rez[comp[nod-1][i]] = 0;
      rez[notn(comp[nod-1][i])] = 1;
    }
    nod = tare[notn(comp[nod-1][0])];
    last[nod] = -1;
  }
  //printf("\n\n%d\n\n",nr);
  for(int i=1;i<=N;++i){
    printf("%d ",rez[i]);
  }
  return;
}

int main()
{
  freopen("2sat.in","r",stdin);
  freopen("2sat.out","w",stdout);
  scanf("%d%d",&N,&M);

  for(int i=1;i<=M;++i){
    scanf("%d%d",&x,&y);
    if(x<0){
      x = abs(x) + N;
    }
    if(y<0){
      y = abs(y) + N;
    }
    g[notn(x)].pb(y);
    g[notn(y)].pb(x);
  }
  make_ctc();
  solve();

  return 0;
}
