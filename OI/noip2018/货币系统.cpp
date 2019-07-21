#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=1e2+10;
const int maxw=3e4+10;

int t,n,maxx;
int a[maxn];
int from[maxw];
bool chuxian[maxw];

int main()
{
//	freopen("money.in","r",stdin);
//	freopen("money.out","w",stdout);
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++)
    {
        memset(from,0,sizeof(from));
        memset(chuxian,0,sizeof(chuxian));
        bool have1=false;
        maxx=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]==1)have1=true;
            maxx=max(maxx,a[i]);
        }
        sort(a+1,a+1+n);
    //	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
        if(have1)
        {
            printf("1\n");
            continue;
        }
        chuxian[0]=true;
        for(int i=1;i<=n;i++)
            for(int j=a[i];j<=maxw;j++)
                if(chuxian[j-a[i]])
                {
                    from[j]=max(from[j],j-a[i]);
                    chuxian[j]=true;
                }
        int cnt=0;
        for(int i=1;i<=n;i++)if(!from[a[i]])cnt++;
        printf("%d\n",cnt);
    //	for(int i=1;i<=n;i++)if(!from[a[i]])cout<<a[i]<<" ";
    }
    return 0;
}
/*
1
54
74 36 49 81 57 76 93 50 45 69 75 83 59 98 70 80 54 37 92 84 91 58 11 16 96 94 38 55 97 73 46 72 47 51 44 89 90 31 100 99 39 82 65 87 41 79 86 34 95 63 52 12 88 53
*/
