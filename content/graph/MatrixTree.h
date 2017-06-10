/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * Source: Wikipedia
 * Description: To count the number of spanning trees in an undirected graph $G$:
 * create an $N\times N$ matrix \texttt{mat}, and for each edge $(a, b) \in G$, do
 * \texttt{mat[a][a]++, mat[b][b]++, mat[a][b]--, mat[b][a]--}.
 * Remove the last row and column, and take the determinant.
 */
