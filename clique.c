// maximal num of ciques, by using Turan graph

#include<stdio.h>
#include<string.h>

int c[110][110];
int t[110][110];
int f[110][110][110];
int pow[110][110];


int main() {

	//power: i^j
	pow[0][0]=1;
	for(int i=1;i<=100;i++) {
		pow[i][0]=1;
		for(int j=1;j<=100;j++)
			pow[i][j]=pow[i][j-1]*i;
	}


	//C(i,j)
	for(int i=0;i<=100;i++)	{
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	}

	//num of edges of Turan graph Tn,k
	for(int i=1;i<=100;i++){
		for(int k=2;k<=i;k++){
			t[i][k]=(k-1)*i*i/(2*k);
		}
	}

	//function \binom{n}{k}_r = \sum_{i=0}{k}C(q,i)*C(r-q,k-i)*(p+1)^i*p^k-i
	for(int n=1;n<=100;n++){
		for(int k=2;k<=n;k++){
			for(int r=2;r<=100;r++){
				int p=n/r;
				int q=n%r;
				int ans=0;
				for(int i=0;i<=k && i<=r; i++)
					ans+=c[q][i]*c[r-q][k-i]*pow[p+1][i]*pow[p][k-i];
				f[n][k][r]=ans;
			}
		}
	}

	int n0,m,d;
	scanf("%d %d %d",&n0,&m,&d); //n0: num of vertices, m: num of edges, d: clique number
	int n;
	for(n=1;;n++) {
		if(t[n][d] > m)
			break;
	}
	n--;

	int m0=m-t[n][d]; //num of remaining edges
	int tmp=0;
	for(int k=3;k<=d;k++)
		tmp+=f[n][k][d]+f[m0][k-1][d-1]; //maximal num of k cliques, k>=3
	tmp+=n0+m+1;
	printf("%d\n",tmp);

	return 0;
}