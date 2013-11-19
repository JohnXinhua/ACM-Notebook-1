#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

const int MAXN = 1000020;

int N;
char s[MAXN];

int dp[2][MAXN];
long long res = 0;

int explode(int l, int r)
{
  int len = 0;
  for (; l >= 0 && r < N && s[l] == s[r]; --l, ++r, ++len);

  return len;
}

void odd_center()
{
  int last = -1, right = -1;
  for (int i = 0; i < N; ++i) {
    if (right >= i)
      dp[0][i] = min(dp[0][2 * last - i], right - i);

    int l = i - dp[0][i];
    int r = i + dp[0][i];
    dp[0][i] += explode(l, r);

    if (i + dp[0][i] > right) {
      last = i;
      right = i + dp[0][i];
    }
    res += (long long) dp[0][i];
  }
}

void even_center()
{
  int last = -1, right = -1;
  for (int i = 0; i < N; ++i) {
    if (s[i] != s[i + 1])
      continue;

    if (right > i)
      dp[1][i] = min(dp[1][2 * last - i], right - i - 1);

    int l = i - dp[1][i];
    int r = i + dp[1][i] + 1;
    dp[1][i] += explode(l, r);

    if (i + dp[1][i] + 1 > right) {
      last = i;
      right = i + dp[1][i] + 1;
    }
    res += (long long) dp[1][i];
  }
}

int main()
{
  freopen("pscpld.in", "r", stdin);
  freopen("pscpld.out", "w", stdout);

  scanf("%s", s);
  N = strlen(s);

  odd_center();
  even_center();

  printf("%lld\n", res);

  return 0;
}
