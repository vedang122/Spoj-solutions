Approach -

Find and store all shortest paths by running Dijkstra’s algorithm only once.
Delete all edges of all shortest paths from adjacency list.
Run Dijkstra’s algorithm again after deletion

In Dijkstra’s algorithm, during relaxation ancestor (or parent) of a vertex in shortest path(SP) can be stored and kept updating in an array or any similar container i.e. index represents a vertex and value at index represents it’s ancestor in SP. When multiple ancestor of a vertex yield paths of same length, then we can store all of them in array of containers like: vector, set etc. Then that array of containers will become an adjacency list for shortest paths(SPs) for all (ancestor-successor) vertexes in any SP

The set<int>parent[V], container is an adjacency list for SPs. Run Dijaktra from destination index to find source index and store the path. Thus, store all shortest paths in the container. Delete those SPs from the actual adjacency list using recursion (util code in my code). After deletion, run actual Dijkstra’s algorithm to find the length of Almost Shortest path.

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

int gp [1000][1000];   // each vertex has all the connected vertices with the edges weights
int dist [1000];
set<int> parent[1000];
bool visited [1000];
lli n,m,x,y;
void dijkstra(int src)
{
    // set the vertices distances as infinit
    dist[src] = 0;
    multiset < pair < int , int > > s;          // multiset do the job as a min-priority queue
    s.insert({0 , src});
    //show(parent,n);// insert the source node with distance = 0
    while(!s.empty())
    {
        pair <int , int> p = *s.begin();        // pop the vertex with the minimum distance
        s.erase(s.begin());
        int x = p.Sc;
        int wei = p.Fs;
        if( visited[x] )
            continue;                  // check if the popped vertex is visited before
        visited[x] = true;
        for(int i = 0; i < n; i++)
        {
            if(gp[x][i]!=-1)
            {
                int e = i;
                int w = gp[x][e];
                //debug3(dist[x], dist[e], e);
                if(!visited[e]&&dist[x] + w <= dist[e])
                {
                    if(dist[x] + w < dist[e])
                    {            // check if the next vertex distance could be minimized
                        //debug2(x, e);
                        parent[e].clear();
                        parent[e].insert(x);// insert the next vertex with the updated distance
                    }
                    else
                        parent[e].insert(x);
                    dist[e] = dist[x] + w;
                    s.insert({dist[e],  e} );
                }
            }
        }
    }
       // show(parent,n);
}
void dijkstra1(int src)
{
    // set the vertices distances as infinit
    dist[src] = 0;
    multiset < pair < int , int > > s;          // multiset do the job as a min-priority queue
    s.insert({0 , src});
    //show(parent,n);// insert the source node with distance = 0
    while(!s.empty())
    {
        pair <int , int> p = *s.begin();        // pop the vertex with the minimum distance
        s.erase(s.begin());
        int x = p.Sc;
        int wei = p.Fs;
        if( visited[x] )
            continue;                  // check if the popped vertex is visited before
        visited[x] = true;
        for(int i = 0; i < n; i++)
        {
            if(gp[x][i]!=-1)
            {
                int e = i;
                int w = gp[x][e];
                //debug3(dist[x], dist[e], e);
                if(dist[x] + w < dist[e])
                {
                    dist[e] = dist[x] + w;
                    s.insert({dist[e],  e} );
                }
            }
        }
    }
    // show(parent,n);
}
void util(int src)
{
    if(src==x)
        return;
    for(auto i: parent[src])
    {
        gp[i][src]=-1;
        util(i);
    }
}
int main()
{
    while(1)
    {
        cin>>n>>m;
        if(n==0&&m==0)
            break;
        cin>>x>>y;
        mem(gp, -1);
        lli a,b,wt;
        fr(i,0,m)
        {
            cin>>a>>b>>wt;
            gp[a][b]=wt;
        }
        /*
        fr(i,0,n)
        {
            fr(j,0,n)
            cout<<gp[i][j]<<" ";
            cout<<endl;
        }
         */
        fr(i,0,n)
        {
            visited[i]=false;
            dist[i]=2e9;
        }
        dijkstra(x);
        //show(parent,n+1);
        util(y);
        fr(i,0,n)
        {
            visited[i]=false;
            dist[i]=2e9;
        }
        dijkstra1(x);
        if(visited[y]==false)
            cout<<-1<<endl;
        else
            cout<<dist[y]<<endl;
    }
    return 0;
}




