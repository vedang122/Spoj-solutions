Following are some important observations --
(Use these as hints and try implementing after reading every hint if you can do this by your own. You will feel good.)
1. Since we have to find order relative to the realtions given, its a topological order problem.
2. Through some little changes we can accomadate this problem in our standard( ) Kahn's algo.
3. Basically we have been asked to print the level with the value of topological order of the DAG lexiographically.
4. For finding order lexiographically, we can use sets(not that tricky).
5. If you know the standard algorithm thoroughly, you would be wondering in this problems our levels are from right -> left and not left->right(as in standard algo). To accomodate this we reverse the all edges directions(a very simple yet wonderful trick).
    

#include <bits/stdc++.h>
using namespace std;
//using namespace std::chrono;
/////// ------ Main code starts here ------ /////
vector<int> gp[1000001];
vector<pair<int, int>>  top;
bool topsort(int n)
{
    vector<int> in_deg(n+1,0); //count of all incoming edges to vertices
    top.clear();
    for(int i=0;i<n;++i)
    {
        for(auto j : gp[i])
        {
            in_deg[j]++;
        }
    }
    set<pair<int, int>> q;
    for(int i=0;i<n;++i)
    {
        if(!in_deg[i])
        {
            q.insert({i,1});
        }
    }
    while(!q.empty())
    {
        pair<int, int> p=*q.begin();
        int u=p.F,r=p.S;
        q.erase(q.begin());
        top.push_back({r,u});
        for(auto i:gp[u])
        {
            in_deg[i]--;
            if(!in_deg[i])
            {
                q.insert({i,r+1});
            }
        }
    }
    return (top.size()==n); ///False if there is a cycle
}
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
    int n,m,ans,t,ind=1;
    cin>>t;
    while(t)
    {
        cin>>n>>m;
        for(int i=0;i<n+1;++i)
        {
            gp[i].clear();
        }
        int a,b;
        for(int i=0;i<m;++i)
        {
            cin>>a>>b;
            gp[b].pb(a);
        }
        bool fl=topsort(n);
        sort(top.begin(),top.end());
        cout<<"Scenario #"<<ind<<":"<<endl<<endl;
        ind++;
        for(int i=0;i<top.size();++i)
        {
            cout<<top[i].first<<" "<<top[i].second<<endl;
        }
        t--;
    }
    return 0;
}

