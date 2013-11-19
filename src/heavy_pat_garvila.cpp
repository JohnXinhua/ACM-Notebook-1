#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

#define MAXN 100010

int N, M, nL;
int v[MAXN], fol[MAXN], niv[MAXN], w[MAXN], l[MAXN];
int aint[4*MAXN];
int lTata[MAXN], lNiv[MAXN], lDim[MAXN], lPoz[MAXN];
vector<int> G[MAXN], P[MAXN];
pair<int, pair<int, int> > op[MAXN];

void citire()
{
  scanf("%d%d", &N, &M);
  for(int i = 1; i <= N; ++i)
    scanf("%d", &v[i]);

  int a, b;
  for(int i = 1; i < N; ++i)
  {
    scanf("%d%d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  int t, x, y;
  for(int i = 1; i <= M; ++i)
  {
    scanf("%d%d%d", &t, &x, &y);
    op[i] = make_pair(t, make_pair(x, y));
  }
}

void df(int nod)
{
  fol[nod] = 1;
  w[nod] = 1;

  int hN = -1, frunza = 1;

  for(vector<int> :: iterator it = G[nod].begin(); it != G[nod].end(); ++it)
  {
    if(fol[*it])
      continue;

    frunza = 0;
    niv[*it] = niv[nod] + 1;

    df(*it);

    w[nod] += w[*it];

    if(hN == -1)
      hN = *it;
    else
      if(w[hN] < w[*it])
        hN = *it;
  }

  if(frunza)
  {
    l[nod] = ++nL;
    lDim[nL]=1;
    P[nL].push_back(nod);
    return;
  }

  l[nod] = l[hN];
  ++lDim[l[nod]];
  P[l[nod]].push_back(nod);

  for(vector<int> :: iterator it = G[nod].begin(); it != G[nod].end(); ++it)
  {
    if((*it) == hN || niv[*it] < niv[nod])
      continue;

    lTata[l[*it]] = nod;
    lNiv[l[*it]] = niv[nod];
  }
}

void build(int nod, int left, int right, int decalaj, int lant)
{
  if(left == right)
  {
    aint[nod + decalaj] = v[ P[lant][left - 1] ];
    return;
  }

  int med = (left + right) / 2;

  build(nod * 2, left, med, decalaj, lant);
  build(nod * 2 + 1, med+1, right, decalaj, lant);

  aint[nod + decalaj] = max(aint[nod * 2 + decalaj], aint[nod * 2 + 1 + decalaj]);
}

void make_paths()
{
  niv[1] = 1;
  df(1);

  for(int i = 1; i <= nL; ++i)
  {
    reverse(P[i].begin(), P[i].end());

    if(i > 1)
      lPoz[i] = lPoz[i-1] + lDim[i-1] * 4;

    build(1, 1, lDim[i], lPoz[i], i);
  }
}

void update(int nod, int left, int right, int poz, int val, int decalaj)
{
  if(left == right)
  {
    aint[nod + decalaj] = val;
    return;
  }

  int med = (left + right) / 2;

  if(poz<=med)
    update(nod * 2, left, med, poz, val, decalaj);
  else
    update(nod * 2 + 1, med+1, right, poz, val, decalaj);

  aint[nod + decalaj] = max(aint[nod * 2 + decalaj], aint[nod * 2 + 1 + decalaj]);
}

int query(int nod, int left, int right, int qleft, int qright, int decalaj)
{
  if(qleft <= left && right <= qright)
    return aint[nod + decalaj];

  int med = (left + right) / 2, rez = 0;

  if(qleft <= med)
    rez = max(rez, query(nod * 2, left, med, qleft, qright, decalaj) );
  if(med < qright)
    rez = max(rez, query(nod * 2 + 1, med + 1, right, qleft, qright, decalaj) );

  return rez;
}

void solve()
{
  int t, x, y, sol = 0;

  for(int i = 1; i <= M; ++i)
  {
    t = op[i].first; x = op[i].second.first, y = op[i].second.second;
    if(t==0)
      update(1, 1, lDim[l[x]], niv[x] - lNiv[l[x]], y, lPoz[l[x]]);
    else
    {
      sol = 0;
      while(1)
      {
        if(l[x] == l[y])
        {
          if(niv[x] > niv[y])
            swap(x, y);
          sol = max(sol, query(1, 1, lDim[l[x]], niv[x] - lNiv[l[x]], niv[y] - lNiv[l[x]], lPoz[l[x]]) );
          break;
        }

        if(lNiv[l[x]] < lNiv[l[y]])
          swap(x, y);

        sol = max(sol, query(1, 1, lDim[l[x]], 1, niv[x] - lNiv[l[x]], lPoz[l[x]]) );

        x = lTata[l[x]];
      }
      printf("%d\n", sol);
    }
  }
}

int main()
{
  freopen("heavypath.in", "r", stdin);
  freopen("heavypath.out", "w", stdout);

  citire();
  make_paths();
  solve();

  return 0;
}
