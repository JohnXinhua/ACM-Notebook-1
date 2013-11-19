#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define Nmax 2000002

char l[Nmax],v[Nmax];
int S1,S2,next[Nmax],rez[1234],r,ras;

void make()
{
    int k=0;
    next[1]=0;
    for(int x=2;x<=S1;++x)
    {
        while(k>=1&&v[k+1]!=v[x]) k=next[k];
            if(v[k+1]==v[x]) ++k;//,printf("%c %c\n",v[k],v[x]);
          //  printf("%d %d\n",k+1,x);
            next[x]=k;
    }

}

int main()
{
freopen("strmatch.in","r",stdin);
freopen("strmatch.out","w",stdout);
scanf("%s%s",v+1,l+1);
//printf("%s\n",v+1);
S1=strlen(v+1);
S2=strlen(l+1);
make();
    int k=0;
    for(int i=1;i<=S2;++i)
    {
        while(k>=1&&v[k+1]!=l[i])
            k=next[k];
        if(v[k+1]==l[i])
        ++k;
        if(k==S1)
        {
            k=next[k];
            ++ras;
  if(r<1000)
         rez[++r]=i-S1;
        }
    }
    printf("%d\n",ras);
    for(int i=1;i<=r;++i)
        printf("%d ",rez[i]);
}
