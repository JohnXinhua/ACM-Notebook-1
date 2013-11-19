#include <cstdio>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 50100;
const int INF = (int)(1e9 + 7);

int n, m;
int d[MAXN];
bool viz[MAXN];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
vector<int> G[MAXN], C[MAXN];

void dijkstra()
{
    for (int i = 2; i <= n; ++i)
        d[i] = INF;
    pq.push(make_pair(0, 1));
    while (!pq.empty()) {
        int x = pq.top().second;
        int val = pq.top().first;
        pq.pop();
        viz[x] = true;
        for (size_t i = 0; i < G[x].size(); ++i) {
            if (viz[G[x][i]])
                continue;
            if (C[x][i] + val < d[G[x][i]]) {
                d[G[x][i]] = val + C[x][i];
                pq.push(make_pair(d[G[x][i]], G[x][i]));
            }
        }
    }
}

int main()
{
    freopen("dijkstra.in", "r", stdin);
    freopen("dijkstra.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        G[a].push_back(b);
        C[a].push_back(c);
    }
    dijkstra();

    for (int i = 2; i <= n; ++i)
        printf("%d ", d[i] >= INF ? 0 : d[i]);
    printf("\n");

    return 0;
}
