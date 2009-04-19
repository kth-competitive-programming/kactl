/**
 * Author:
 * Date: 2009-04-17
 * Source: wikipedia
 * Description: N/A
 * Status: Unknown
 */

int maximumFlow() {

/*
 1   if (source = sink)
 2     totalflow = Infinity
 3     DONE 

 4   totalflow = 0 

 5   while (True)
 6 # find path with highest capacity from
   # source to sink 
 7 # uses a modified djikstra's algorithm
 8     for all nodes i
 9       prevnode(i) = nil
10       flow(i) = 0
11       visited(i) = False
12     flow(source) = infinity 

13     while (True)
14       maxflow = 0
15       maxloc = nil 
16       # find the unvisited node with
         # the highest capacity to it
17       for all nodes i
18         if (flow(i) > maxflow AND
                          not visited(i))
19           maxflow = flow(i)
20           maxloc = i
21       if (maxloc = nil)
22         break inner while loop
23       if (maxloc = sink)
24         break inner while loop
24a      visited(maxloc) = true
25       # update its neighbors
26       for all neighbors i of maxloc
27         if (flow(i) < min(maxflow,
                      capacity(maxloc,i)))
28           prevnode(i) = maxloc
29           flow(i) = min(maxflow,
                    capacity(maxloc,i)) 

30     if (maxloc = nil)         # no path
31       break outer while loop 

32     pathcapacity = flow(sink)
33     totalflow = totalflow + pathcapacity 

   # add that flow to the network,
   # update capacity appropriately
35     curnode = sink
         # for each arc, prevnode(curnode),
         # curnode on path:
36     while (curnode != source)       
38       nextnode = prevnode(curnode)
39       capacity(nextnode,curnode) =
           capacity(nextnode,curnode) - 
40                           pathcapacity
41       capacity(curnode,nextnode) =
           capacity(curnode,nextnode) + 
42                           pathcapacity
43       curnode = nextnode 
*/

}

