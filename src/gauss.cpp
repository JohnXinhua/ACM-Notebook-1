#include<stdio.h>
#include<algorithm>

#define EPS 0.0000001

int i,j,k;
int N,M;
double A[303][303];
double X[303];

int main()
{
  freopen("gauss.in","r",stdin);
  freopen("gauss.out","w",stdout);
  scanf("%d%d",&N,&M);

  for(int i=1;i<=N;++i)
  {
    for(int j=1;j<=M+1;++j)
    {
      scanf("%lf",&A[i][j]);
    }
  }
  i=1,j=1;
  while(i<=N && j<=M)
  {
    for(k=i;k<=N;++k)
      if(A[k][j]<-EPS||A[k][j]>EPS)
        break;
    if(k==N+1)
    {
      ++j;
      continue;
    }
    if(k!=i)
    {
      for(int q=1;q<=M+1;++q)
      {
        double aux = A[i][q];
        A[i][q]= A[k][q];
        A[k][q]= aux;
      }
    }
    for(int q=j+1;q<=M+1;++q)
    {
      A[i][q]=A[i][q]/A[i][j];
    }
    A[i][j]=1;
    for(int u=i+1;u<=N;++u)
    {
      for(int q=j+1;q<=M+1;++q)
      {
        A[u][q]-=A[u][j]*A[i][q];
      }
      A[u][j]=0;
    }
    ++i;++j;
  }
  for(int i=N;i>0;--i)
    for(int j=1;j<=M+1;++j)
    {
      if(A[i][j]>EPS||A[i][j]<-EPS)
      {
        if(j==M+1)
        {
          printf("Imposibil\n");
          return 0;
        }

        X[j]=A[i][M+1];
        for(int k=j+1;k<=M;++k)
        {
          X[j]-=X[k]*A[i][k];
        }
        break;
      }

    }

  for(int i=1;i<=M;++i)
  {
    printf("%.8lf ",X[i]);
  }
  printf("\n");
  return 0;
}
