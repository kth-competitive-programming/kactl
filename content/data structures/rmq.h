/**
* Description: RMQ structure
* Author: github
* Source: github
* Date: today
*/
#define N 1<<18
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int size, h[N][18], val[N];
void rmq_init()
{
	int i, j, l;
	for (i = 0; i < size; i++) h[i][0] = val[i];
	for (j = l = 1; l*2 <= size; j++, l <<= 1)
	{
		for (i = 0; i <= size-l*2; i++)
			h[i][j] = MIN(h[i][j-1], h[i+l][j-1]);
	}
}

inline int rmq_query(int start, int end)
{
	int j = 0, l = 1;
	while (2*l <= end-start+1)
	{
		j++;
		l <<= 1;
	}
	return MIN(h[start][j], h[end-l+1][j]);
}
