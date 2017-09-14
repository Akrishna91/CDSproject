#include<string>
#include<cstdlib>
#include<queue>
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
//------------------------------defined tokens-----------------------------------//
#define mfor(i,n) for(int i=0;i<n;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define RFOR(i,a,b) for(int i=a;i>=b;i--)
#define SCANFILE freopen("input.txt","r",stdin)
#define OUTPUT freopen("output.txt","w",stdout)
#define pb push_back
#define mp make_pair
#define IS_ODD( num ) ((num) & 1)
#define MEM(dest,val) memset(dest,val,sizeof(dest))
#define INF 1000000000
//-------------------------------type definitions---------------------------------//
typedef pair<int,int>ii;
typedef vector<int>vi;
typedef vector<ii>vii;
typedef pair<int,string>is;
//--------------------------------global variables-------------------------------//

enum NodeColor {
    WHITE, BLACK, GRAY
};
class FaultRepair {
private:
    const Graph& graph;
    
public:
    void initCDS();
    

};

void initCDS() {
    Graph current_graph = graph;
    for(i : current_graph) {
        i.node_color = NodeColor::WHITE;
    }
    
}
