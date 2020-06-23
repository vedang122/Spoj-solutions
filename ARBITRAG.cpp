Since multiplicative can be used directly for comparing whether it is greater than the dist[i][j] alreasy present we can just replace sum by multiplication in FLyod Marshall algo. and then check whether any dist[i][i] (cycle) is >1. 


#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
#define fr(i,j,n)   for(lli i=j;i<(n);++i)
#define bk(i,j,n)   for(lli i=j;i>=n;--i)
#define pb push_back
#define m_p make_pair
#define Fs first
#define Sc second
#define endl "\n"
#define MOD 1000000007
#define present(c,x)    ((c).find(x) != (c).end())
#define run ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ordered_set tree<lli, null_type,less<lli>, rb_tree_tag,tree_order_statistics_node_update>
#define debug1(x) cout<<#x<<" "<<x<<endl;
#define debug2(x,y) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<endl;
#define debug3(x,y,z) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<" "<<#z<<" "<<z<<endl;
#define mem(p,v) memset(p,(lli)v,sizeof p);
#define ub upper_bound
#define lb lower_bound
typedef long long int lli;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef vector<lli> vl;
typedef pair<lli,lli> pl;
inline lli max(lli a,lli b){ return a>b?a:b;}
inline lli min(lli a,lli b){ return a<b?a:b;}


vector < pair < int , double > > gp [1001];   // each vertex has all the connected vertices with the edges weights
double dist [1001][1001];
unordered_map<string, int> mp;
void bellman(lli n)
{
    // set the vertices distances as infinity
    fr(i,0,n+1)
    {
        fr(j,0,n+1)
        dist[i][j]=2e9;
    }
    fr(i,1,n+1)
    {
        dist[i][i]=0;
        for(auto j :gp[i])
        {
            dist[i][j.Fs]=j.Sc;
            //  debug3(i, j.Fs, j.Sc);
        }
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                dist[i][j] = max( dist[i][j], dist[i][k] * dist[k][j]);
            }
        }
    }
}
int main()
{
    lli n,m,x=1,y;
    while(1)
    {
        cin>>n;
        if(n==0)
            break;
        
        string s,s1;
        lli ind=1;
        fr(i,0,n)
        {
            cin>>s;
            mp[s]=ind;
            ind++;
        }
        for(int i=0;i<=n;++i)
        {
            gp[i].clear();
        }
        cin>>m;
        lli a,b;
        double wt;
        fr(i,0,m)
        {
            cin>>s>>wt>>s1;
            a=mp[s];
            b=mp[s1];
            //debug3(a, b, wt);
            gp[a].pb({b,wt});
        }
        bellman(n);
        bool ans=false;
        fr(i,1,n+1)
        {
            if(dist[i][i]>1)
            {
                ans=true;
            }
        }
        cout<<"Case "<<x<<": ";
        if(ans)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
        x++;
    }
    return 0;
}

