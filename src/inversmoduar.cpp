#include<stdio.h>
#include<algorithm>
using namespace std;
void euc(long long a,long long b,long long &d,long long &x,long long &y)
{
  if(b==0)
  {
    d=a;
    x=1;
    y=0;
  }
  else
  {
    long long x1,y1;
    euc(b,a%b,d,x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
  }
}

long long a,b,r;

int main()
{
  freopen("inversmodular.in","r",stdin);
  freopen("inversmodular.out","w",stdout);


  long long div=0,x=0,y=0;
  scanf("%lld%lld",&a,&b);
  euc(a,b,div,x,y);
  //  printf("%d! ",div);
  if(x<0)
    x+=b;
  printf("%lld\n",x);
}
