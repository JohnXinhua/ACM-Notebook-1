#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <vector>

#define x first
#define y second

using namespace std;

typedef pair<double, double> pct;

int N;

pct v[121010];
pct stiv[121010];

double signc(pct a,pct b,pct c){
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int cmp(pct a, pct b){
  return signc(v[1],a,b)<0;
}

int k;

int main(){

  freopen("infasuratoare.in","r",stdin);
  freopen("infasuratoare.out","w",stdout);

  scanf("%d",&N);

  for(int i=1;i<=N;++i){
    scanf("%lf%lf",&v[i].x,&v[i].y);
  }
  int pos=1;
  for(int i=2;i<=N;++i){
    if(v[i]<v[pos]){
      pos = i;
    }
  }
  swap(v[pos],v[1]);

  sort(v+2,v+N+1,cmp);

  for(int i=1;i<=N;++i){
    while(k>=2 && signc(stiv[k-1],stiv[k],v[i]) > 0) --k;

    stiv[++k] = v[i];
  }
  printf("%d\n",k);

  for(int i=k;i>=1;--i){
    printf("%lf %lf\n",stiv[i].x,stiv[i].y);

  }

  return 0;
}
