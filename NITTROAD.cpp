 This particular problem can be solved very easily and efficiently using a well-known data structure, Disjoint-set data structure . If you have spent quite a lot of time thinking in terms of removing the particular edge and then calculating the pair of disconnected nodes at each such step, you know by now that it's not an easy thing to do.

So, let's try to get deep into this question and apply some TRICK and make this problem simpler. What if we try to solve this problem backward..? Here comes the beauty of the problem. Yes, we can solve this problem backwards using Disjoint-set data structure. But HOW ??

Forward - REMOVE the given EDGE in the query and Print the PAIR of DISCONNECTED NODES whenever asked.

Backward - ADD the given EDGE in the query and Print the PAIR of DISCONNECTED NODES whenever asked.

Detailed Approach
1. Intialize root id to be i and size to be 1 for every node intially.
2. Initially, you are given a tree so the count of a pair of disconnected nodes (say count) = 0.
3. Store the set of queries in a stack or a vector to solve them backward. Mark the set of edges given in the QUERY of type "R x".
4. Using UNION and FIND connect the nodes with the help of those edges which are not marked in step 3. Update disconnected_cnt by the edges which are not marked true in the queries i.e these are the edges which are already present in the start of algorithm , do union too. Notice we are not starting with the n different components always.
5. Now we are all set to start solving the problem backwards..!! :) .. Start from the Last query. ADD the edge using UNION for the query of type "R x". When you add an edge, decrease the value of count. Store the value of count in a stack whenever you get the query of type "Q".
6. Print them backward after you finish with all the queries.

 Code strats here -
 
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

lli id[100001];
lli size[20001];
pl  p[100001];
bool mark[20001];
lli n,m,x,y;

lli root(lli x)
{
    while(id[x] != x)
    {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}
void union1(lli x, lli y)
{
    lli p = root(x);
    lli q = root(y);
    if(p!=q)
    {
        if(size[p]>size[q])
        {
            swap(p,q);
        }
        id[p] = id[q];
        size[q]+=size[p];
        size[p]=0;
    }
}


int main()
{
    lli t;
    cin>>t;
    while(t)
    {
        cin>>n;
        for(int i=1;i<n+1;++i)
        {
            id[i]=i;
            size[i]=1;
        }
        lli a,b,wt;
        fr(i,1,n)
        {
            cin>>a>>b;
            p[i]={a,b};
            mark[i]=false;
        }
        lli q,tmp;
        char c;
        cin>>q;
        stack<int> s;
        while(q)
        {
            cin>>c;
            if(c=='Q')
            {
                s.push(0); // to tell whether this is a query
            }
            else
            {
                cin>>tmp;
                s.push(tmp);
                mark[tmp]=true;
            }
            q--;
        }
        lli cnt=0;
        for (int i = 1; i <= n-1; i++)
        {
            if (mark[i] == false)
            {
                int ra = root(p[i].Fs);
                int rb = root(p[i].Sc);
                if (ra != rb)
                {
                    cnt += (size[ra] * size[rb]); // Keep counting the connected Pairs
                    union1(ra, rb);
                }
            }
        }
        cnt=(n*(n-1))/2-cnt;
        stack<int> ans;
        while(!s.empty())
        {
            q=s.top();
            s.pop();
            if(q==0)
            {
                ans.push(cnt);
            }
            else
            {
                lli x = p[q].first;
                lli y = p[q].second;
                lli ra=root(x);
                lli rb=root(y);
                if(ra!=rb)
                {
                    cnt-=size[ra]*size[rb];
                    union1(x, y);
                }
            }
        }
        while(!ans.empty())
        {
            cout<<ans.top()<<endl;
            ans.pop();
        }
        cout<<endl;
        t--;
    }
    return 0;
}
