#include<string>
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
#define SCAND(x)  scanf("%d",&x)
#define LL long long int
#define pb push_back
#define mp make_pair
#define IS_ODD( num ) ((num) & 1)
#define MEM(dest,val) memset(dest,val,sizeof(dest))
#define INF 1000000000
//-------------------------------structure of node-------------------------------//
/*struct NODE_INFO{
    int id;
    string color;
};*/
/*struct NODE{
    int id;
    string color;
};*/
//-------------------------------type definitions---------------------------------//
typedef pair<int,int>ii;
typedef vector<int>vi;
typedef vector<ii>vii;

//--------------------------------global variables---------------------------------------//
vector<vii>AdjListV;
vi p;
map<int,string> graph;
map<int,string>::iterator it;
map<int,set<int> > AdjList;
map<int,set<int> >::iterator adjIt;
set<int>WhiteClrSet,DominantSet;
set<int>::iterator setit,setit1;
map<pair<int,string>,int >AdjacentColor;
map<pair<int,string>,int >::iterator adjclriter;
int num_of_nodes,num_of_edges,failed;
int id,u,v,source,target;
string color;
void printPathandChngetoWhite(int u){
    graph[u]="white";
    if(u==source){printf("%d",u);return; }
    printPathandChngetoWhite(p[u]);
    printf(" %d\n",u);graph[u]="white";
}
void currentGraph(){
    //--------------------current color configuration------------------------------------//
    assert(graph.size()!=0);
    it=graph.begin();
    for(;it!=graph.end();it++){
        //cout<<it->first<<"       "<<it->second<<endl;
    }
}
void eraseFromAdjList(int node){
    adjIt =AdjList.begin();
    for(;adjIt!=AdjList.end();adjIt++){
        if(adjIt->second.find(node)!=adjIt->second.end()){
            adjIt->second.erase(node);
        }
    }
    AdjList.erase(AdjList.find(node));
}
void showAdjColorSet(){
    //cout<<"nodes and count of their adjacent nodes with different colors"<<endl;
    adjclriter=AdjacentColor.begin();
    for(;adjclriter!=AdjacentColor.end();adjclriter++){
        //cout<<adjclriter->first.first<<"           "<<adjclriter->first.second<<"          "<<adjclriter->second<<endl;
    }
}
void showAdjList(){
    //cout<<"nodes and their neighbors are "<<endl;
    for(adjIt=AdjList.begin();adjIt!=AdjList.end();adjIt++){
        //cout<<adjIt->first<<"=========>";
        for(setit=adjIt->second.begin();setit!=adjIt->second.end();setit++){
            //cout<<*setit<<"        ";
        }
        cout<<endl;
    }
}
void showDomSet(){
    //assert(DominantSet.size()!=0);
    cout<<"dominant set is"<<endl;
    for(setit=DominantSet.begin();setit!=DominantSet.end();setit++){
        cout<<*setit<<endl;
    }
}
void showWhiteColorSet(){
    if(WhiteClrSet.size()!=0)
    cout<<"white color set is"<<endl;
    setit=WhiteClrSet.begin();
    for(;setit!=WhiteClrSet.end();setit++){
        cout<<*setit<<endl;
    }
}
void updAjntClrandWhiteandDomSet(){
    //------------------updating white color set and finding the color of neighbours of each node----------------//
    assert(graph.size()!=0);
    WhiteClrSet.clear();
    DominantSet.clear();
    AdjacentColor.clear();
    adjIt=AdjList.begin();
    for(;adjIt!=AdjList.end();adjIt++){
        setit=adjIt->second.begin();
        int cnt1=0,cnt2=0,cnt3=0;
        for(;setit!=adjIt->second.end();setit++){
            if(graph[*setit]=="white"){cnt1++;WhiteClrSet.insert(*setit);}
            else if(graph[*setit]=="black"){cnt2++;DominantSet.insert(*setit);}
            else cnt3++;
        }
        AdjacentColor[mp(adjIt->first,"black")]=cnt2;
        AdjacentColor[mp(adjIt->first,"grey")]=cnt3;
        AdjacentColor[mp(adjIt->first,"white")]=cnt1;
        if((cnt1+cnt2+cnt3)==0){                       //node is not connected to the graph
            int temp=adjIt->first;
            AdjacentColor.erase(AdjacentColor.find(mp(temp,"black")));
            AdjacentColor.erase(AdjacentColor.find(mp(temp,"grey")));
            AdjacentColor.erase(AdjacentColor.find(mp(temp,"white")));
            graph.erase(graph.find(temp));
            eraseFromAdjList(temp);
        }
    }
}
int main(){
    SCANFILE;
    //OUTPUT;
    //-------------------reading nodes and their color (graph in CDS)---------------------//
    //printf("\t\nEnter the number of nodes\n");
    SCAND(num_of_nodes);//number of nodes start with 0
    mfor(i,num_of_nodes){
        cin>>id>>color;
        graph[id]=color;
    }
    printf("\n\tInitial color of nodes\n");
    currentGraph();
    //-------------------scanning the adjacency list-------------------------------------//
    //printf("\n\tEnter number of edges\n");
    SCAND(num_of_edges);
    mfor(i,num_of_edges){
        scanf("%d %d",&u,&v);
        AdjList[u].insert(v);
        AdjList[v].insert(u);//as graph is undirected, if it is directed no need to add this statement
    }
    updAjntClrandWhiteandDomSet();
    //cout<<"adjacency color set before deletion"<<endl;
    //showAdjColorSet();
    //showWhiteColorSet();
    showAdjList();
    //-------------------scanning id of failed node--------------------------------------//
    //printf("\t\nEnter the id of failed node\n");
    //SCAND(failed);
    set<int>CheckBlackSet(DominantSet.begin(),DominantSet.end());
    map<int,string>initgraph(graph.begin(),graph.end());
    for(setit1=CheckBlackSet.begin();setit1!=CheckBlackSet.end();setit1++){

    cout<<"fuck";
    //-----------------------------------removing failed from graph-------------------------------//
    graph.erase(graph.find(failed));
    //AdjList.erase(AdjList.find(failed));   //should n't erase its adjacent they are required in the next step to be turned white

    for(adjIt =AdjList.begin();adjIt!=AdjList.end();adjIt++){      //erasing link if it is connected to some other nodes
        if(adjIt->second.find(failed)!=adjIt->second.end()){
            adjIt->second.erase(failed);
        }
    }
    setit=AdjList[failed].begin();
    mfor(i,AdjList[failed].size()){
        if(graph[*setit]=="black" && AdjList[*setit].size()>1 && AdjacentColor[mp(*setit,"black")]>1);
                                            //color of an adjacent node is not changed if it is connected to more than 1 nodes and if it has at least
                                            //1 black adjacent node
        else { graph[*setit]="white"; }
        setit++;
    }
    //delete it from AdjacentColor and graph
    AdjList.erase(AdjList.find(failed));//erase failed node from the AdjList if it has some neighbours
    //printf("\n\tColor of nodes after deletion of failed node\n");
    //currentGraph();
    updAjntClrandWhiteandDomSet();
    //showAdjColorSet();
    showWhiteColorSet();
    showDomSet();
    //showAdjList();
    //---------------------------------------------------------------------all cleanup done------------------------------------------------//
    //-------------------------------------------starting BFS to find the closest member of dominating set---------------------------------//

    AdjListV.assign(num_of_nodes,vii());
    for(adjIt=AdjList.begin();adjIt!=AdjList.end();adjIt++){
        for(setit=adjIt->second.begin();setit!=adjIt->second.end();setit++){
            AdjListV[adjIt->first].pb(ii(*setit,0));
        }
    }

    //viewing new adjacency list vector
    /*mfor(i,AdjListV.size()){
        cout<<i<<"====>  ";
        mfor(j,AdjListV[i].size()){

            ii x=AdjListV[i][j];
            cout<<x.first<<"            ";
        }
        cout<<endl;
    }*/
    //now performing BFS reach to the nearest element of DS
    //first selecting a source
    //should be a white node connected to max nodes in order1.black 2.grey 3.white
    //traversing through whiteclrset set to make a vector containing white nodes
    vi WhiteSet;
    for(setit=WhiteClrSet.begin();setit!=WhiteClrSet.end();setit++){
        WhiteSet.pb(*setit);
    }
    //traversing through adjacent color set to find nodes of particular color
    int black=AdjacentColor[mp(WhiteSet[0],"black")];
    int grey=AdjacentColor[mp(WhiteSet[0],"grey")];
    int white=AdjacentColor[mp(WhiteSet[0],"white")];
    int tar1=WhiteSet[0],tar2=WhiteSet[0],tar3=WhiteSet[0];
    FOR(i,1,WhiteSet.size()-1){
        if(AdjacentColor[mp(WhiteSet[i],"black")]>black){tar1=WhiteSet[i];black=AdjacentColor[mp(WhiteSet[i],"black")];}
        if(AdjacentColor[mp(WhiteSet[i],"grey")]>grey){tar1=WhiteSet[i];grey=AdjacentColor[mp(WhiteSet[i],"grey")];}
        if(AdjacentColor[mp(WhiteSet[i],"white")]>white){tar1=WhiteSet[i];white=AdjacentColor[mp(WhiteSet[i],"white")];}
    }
    if(black>0)source=tar1;
    else if(grey>0)source=tar2;
    else if(white>0)source=tar3;
    cout<<"our source for breadth first search is      "<<source<<endl;
    //-------------------------starting bfs-------------------------------------//
    if(DominantSet.size()!=0){
            vi dist(num_of_nodes,1000000000);dist[source]=0;
            queue<int>q;q.push(source);
            p.assign(num_of_nodes,-1);
            int layer=-1;
            while(!q.empty()){
            int u=q.front();q.pop();
            if(dist[u]!=layer)printf("\nlayer %d:",dist[u]);
            layer=dist[u];
            printf("visit %d, ",u);
            mfor(j,AdjListV[u].size()){
                ii v=AdjListV[u][j];
                if(dist[v.first]==1000000000){
                    dist[v.first]=dist[u]+1;
                    p[v.first]=u;
                    if(DominantSet.find(v.first)!=DominantSet.end()){target=v.first;goto l;}//as soon as we find element of Dominating Set we break
                    q.push(v.first);
                }
            }
            }
    l:

        cout<<"target is"<<target<<endl;
        //change all the nodes white coming in path from source to target
        printPathandChngetoWhite(target);
        graph[target]="black";
    }
    updAjntClrandWhiteandDomSet();
    currentGraph();
    int c=0;
    for(it=initgraph.begin();it!=initgraph.end();it++){
        if(it->second=="white" && graph.find(it->first)->second=="black")c++;
    }
    cout<<"interesting value"<<c<<endl;
    graph.clear();

    graph.insert(initgraph.begin(),initgraph.end());
    }
    return 0;
}

