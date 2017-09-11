PHASES

STEPS:
1. Based on distances between different points (O(n^2)) we check that whether they are in the same cluster or not. 
2. If they are we assign them the same class identifier 
otherwise differnt. Finally we traverse through the map and find maximum number of points that are assigned the same identifier. So complexity of this code is O(n^2).
3. In the third program we are taking this generated output as input and take this in an adjacency list (map<int,set<int> >) and a current graph(map<int,string>). Then we use
Guha-Khuller Algorithm to construct a CDS. 
4. After constructing the CDS we remove its dominant elements one by one and check whether it leads to a disconnected graph. If it does 
we keep that node (because of the assumptions we have taken that graph we are working on is strongly connected). Otherwise we remove it and calculate the number of non-dominators which convert to dominators. We stop when the
required number of failures is reached.


step 1->  turn all the node white which was connected to the died dominator node except 
dominant nodes that are connected to at least two other nodes in which at least one black node.
.
	//this step ensures that there is at least one white node in the resulting graph

step 2-> pick one white node among them which is connected to most no of node with priority
      (1. black    2.grey    3.white)

step 3-> Search the nearest black node using breadth first search.

step 4-> turn all the nodes white that come in the path of that white node and nearest black node.

step 5-> apply guha and khuller algorithm from that black node.

step 6-> repeat step 2 untill there remains any one white node.
