#include<string>
#include<iostream>
#include <map>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#include<bitset>
#include<utility>
#include<cstring>
#include<climits>
#include<cassert>
using namespace std;
#define LL long long int
#define mfor(i,n) for(int i=0;i<n;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FORL(i,a,b) for(long long int i=a;i<=b;i++)
#define RFOR(i,a,b) for(int i=a;i>=b;i--)
#define SND(x) int (x); cin>>x;
#define SNF(x) float (x); cin>>x;
#define OPEN freopen("in.txt","r",stdin)
#define WRITE freopen("input.txt","w",stdout)
#define pb push_back
#define mp make_pair
#define IS_ODD( num ) ((num) & 1)
#define IS_EVEN( num ) (!IS_ODD( (num) ))
#define MEM(dest,val) memset(dest,val,sizeof(dest))
int num_of_nodes;
float X,Y,range,rangesqr;
vector<pair<int,int> >vec;
vector<pair<int,int> > ::iterator it;
vector<int>vi;
void initSet(){vi.assign(num_of_nodes,0);mfor(i,num_of_nodes)vi[i]=i;}
int findSet(int i) { return (vi[i] == i) ? i : (vi[i] = findSet(vi[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i,int j) { vi[findSet(i)] = findSet(j);}
int main(){
    OPEN;
    WRITE;
    cin>>num_of_nodes;//from 0 to n-1
    cout<<num_of_nodes<<endl;
    float x[num_of_nodes],y[num_of_nodes];
    cin>>range;
    rangesqr=range*range;
    int cnt=0;
    mfor(i,num_of_nodes)cin>>x[i]>>y[i];//scanning coordinates
    mfor(i,num_of_nodes)FOR(j,i+1,num_of_nodes-1){X=abs(x[j]-x[i]);Y=abs(y[j]-y[i]);if(((X*X)+(Y*Y))<=rangesqr)vec.pb(mp(i,j));  }
    //cout<<vec.size()<<endl;
    //int ct=0;
    initSet();
    for(it=vec.begin();it!=vec.end();it++){
        unionSet(it->first,it->second);
        //cout<<vi[it->first]<<"       "<<vi[it->second]<<endl;
    }
    map<int,int>mymap;
    map<int,int>::iterator mapit;
    //cout<<"size of vi: "<<vi.size()<<endl;
    mfor(i,vi.size()){
        int t=findSet(i);
        if(mymap.find(t)!=mymap.end())mymap[t]++;
        else mymap[t]=1;
    }
    set<int>nodeset;int mxnode=0,tar=-1;
    for(mapit=mymap.begin();mapit!=mymap.end();mapit++){
        //cout<<mapit->first<<" "<<mapit->second<<endl;
        if(mapit->second>=mxnode){mxnode=mapit->second;tar=mapit->first;}
    }
//    cout<<"maxnode:   "<<mxnode<<"      target   "<<tar<<endl;
    mfor(i,vi.size()){
        if(vi[i]==tar){nodeset.insert(i);}
    }
    set<int>::iterator setit1=nodeset.begin();
    /*cout<<"elements of nodeset"<<endl;
    for(;setit1!=nodeset.end();setit1++){
        cout<<*setit1<<endl;
    }*/
    cout<<nodeset.size()<<endl;
    set<pair<int,int> >setpair;
    set<pair<int,int> >::iterator pairit;
    for(it=vec.begin();it!=vec.end();it++){
        if(nodeset.find(it->first)!=nodeset.end()||nodeset.find(it->second)!=nodeset.end())
            setpair.insert(mp(it->first,it->second));
    }
    cout<<setpair.size()<<endl;
    for(pairit=setpair.begin();pairit!=setpair.end();pairit++){
        cout<<pairit->first<<" "<<pairit->second<<endl;                    //reqd to be uncommmented for program
    }
    /*set<int>::iterator setit=nodeset.begin();
    for(;setit!=nodeset.end();setit++){
        cout<<*setit<<"   ";
    }*/
    return 0;

}
