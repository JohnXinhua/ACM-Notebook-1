#include <iostream>
#include <cstdio>
#include <cstring>
#define ch (*s - 'a')

using namespace std;

struct Trie {
  int cnt, nrsons;
  Trie *son[26];

  Trie() {
    cnt = nrsons = 0;
    memset(son, 0, sizeof(son));
  }
};

Trie *T = new Trie;

void ins(Trie *node, char *s)
{
  if (*s == '\0') {
    node->cnt++;
    return;
  }

  if (node->son[ch] == 0) {
    node->son[ch] = new Trie;
    node->nrsons++;
  }

  ins(node->son[ch], s + 1);
}

int del(Trie *node, char *s)
{
  if (*s == '\0')
    node->cnt--;
  else if (del(node->son[ch], s + 1)) {
    node->son[ch] = 0;
    node->nrsons--;
  }

  if (node->cnt == 0 && node->nrsons == 0 && node != T) {
    delete node;
    return 1;
  }

  return 0;
}

int freq(Trie *node, char *s)
{
  if (*s == '\0')
    return node->cnt;
  if (node->son[ch])
    return freq(node->son[ch], s + 1);
  return 0;
}

int pref(Trie *node, char *s, int k)
{
  if (*s == '\0' || node->son[ch] == 0)
    return k;
  return pref(node->son[ch], s + 1, k + 1);
}

int main()
{
  char line[32];
  char word[32];
  int op;

  freopen("trie.in", "r", stdin);
  freopen("trie.out", "w", stdout);

  while (fgets(line, 32, stdin)) {
    sscanf(line, "%d %s", &op, word);
    switch(op) {
      case 0:
        ins(T, word);
        break;
      case 1:
        del(T, word);
        break;
      case 2:
        printf("%d\n", freq(T, word));
        break;
      case 3:
        printf("%d\n", pref(T, word, 0));
        break;
    }
  }

  return 0;
}
