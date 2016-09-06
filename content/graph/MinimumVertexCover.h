/**
 * Author:
 * Date: 2009-04-17
 * Source: Wikipedia
 * Description: (König's thm) Consider a bipartite graph where the vertices are partitioned into left $L$ and right $R$ sets. Suppose there is a maximum matching which partitions the edges into those used in the matching $Em$ and those not $E0$. Let $T$ consist of all unmatched vertices from $L$, as well as all vertices reachable from those by going left-to-right along edges from $E0$ and right-to-left along edges from $Em$. This essentially means that for each unmatched vertex in $L$, we add into $T$ all vertices that occur in a path alternating between edges from $E0$ and $Em$.

Then $(L \backslash T) \cup (R \cap T)$ is a minimum vertex cover. Thus, the Hopcroft-Karp algorithm for finding maximum matchings in bipartite graphs may also be used to solve the vertex cover problem efficiently in these graphs.
 */
