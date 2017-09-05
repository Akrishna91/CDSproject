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
