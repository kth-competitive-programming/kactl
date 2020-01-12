/**
 * Author: Simon Lindholm
 * Date: 2018-07-15
 * License: CC0
 * Source: Wikipedia
 * Description: Given $N$ and a real number $x \ge 0$, finds the closest rational approximation $p/q$ with $p, q \le N$.
 * It will obey $|p/q - x| \le 1/qN$.
 *
 * For consecutive convergents, $p_{k+1}q_k - q_{k+1}p_k = (-1)^k$.
 * ($p_k/q_k$ alternates between $>x$ and $<x$.)
 * If $x$ is rational, $y$ eventually becomes $\infty$;
 * if $x$ is the root of a degree $2$ polynomial the $a$'s eventually become cyclic.
 * Time: O(\log N)
 * Status: stress-tested for n <= 300
 */

typedef double d; // for N ~ 1e7; long double for N ~ 1e9
pair<ll, ll> approximate(d x, ll N) {
	ll LP = 0, LQ = 1, P = 1, Q = 0, inf = LLONG_MAX; d y = x;
	for (;;) {
		ll lim = min(P ? (N-LP) / P : inf, Q ? (N-LQ) / Q : inf),
		   a = (ll)floor(y), b = min(a, lim),
		   NP = b*P + LP, NQ = b*Q + LQ;
		if (a > b) {
			// If b > a/2, we have a semi-convergent that gives us a
			// better approximation; if b = a/2, we *may* have one.
			// Return {P, Q} here for a more canonical approximation.
			return (abs(x - (d)NP / (d)NQ) < abs(x - (d)P / (d)Q)) ?
				make_pair(NP, NQ) : make_pair(P, Q);
		}
		if (abs(y = 1/(y - (d)a)) > 3*N) {
			return {NP, NQ};
		}
		LP = P; P = NP;
		LQ = Q; Q = NQ;
	}
}
