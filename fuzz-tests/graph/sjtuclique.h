typedef bool BB[n];
struct Maxclique {
	const BB* e; int pk, level; const float Tlimit;
	struct Vertex{ int i, d; Vertex(int i):i(i),d(0){} };
	typedef vector<Vertex> Vertices; typedef vector<int> ColorClass;
	Vertices V; vector<ColorClass> C; ColorClass QMAX, Q;
	static bool desc_degree(const Vertex &vi, const Vertex &vj){
		return vi.d > vj.d;
	}
	void init_colors(Vertices &v){
		const int max_degree = v[0].d;
		for(int i = 0; i < sz(v); i++) v[i].d = min(i, max_degree) + 1;
	}
	void set_degrees(Vertices &v){
		for(int i = 0, j; i < (int)v.size(); i++)
			for(v[i].d = j = 0; j < int(v.size()); j++)
				v[i].d += e[v[i].i][v[j].i];
	}
	struct StepCount{ int i1, i2; StepCount():i1(0),i2(0){} };
	vector<StepCount> S;
	bool cut1(const int pi, const ColorClass &A){
		for(int i = 0; i < (int)A.size(); i++) if (e[pi][A[i]]) return true;
		return false;
	}
	void cut2(const Vertices &A, Vertices &B){
		for(int i = 0; i < (int)A.size() - 1; i++)
			if(e[A.back().i][A[i].i])
				B.push_back(A[i].i);
	}
	void color_sort(Vertices &R){
		int j = 0, maxno = 1, min_k = max((int)QMAX.size() - (int)Q.size() + 1, 1);
		C[1].clear(), C[2].clear();
		for(int i = 0; i < (int)R.size(); i++) {
			int pi = R[i].i, k = 1;
			while(cut1(pi, C[k])) k++;
			if(k > maxno) maxno = k, C[maxno + 1].clear();
			C[k].push_back(pi);
			if(k < min_k) R[j++].i = pi;
		}
		if(j > 0) R[j - 1].d = 0;
		for(int k = min_k; k <= maxno; k++)
			for(int i = 0; i < (int)C[k].size(); i++)
				R[j].i = C[k][i], R[j++].d = k;
	}
	void expand_dyn(Vertices &R){// diff -> diff with no dyn
		S[level].i1 = S[level].i1 + S[level - 1].i1 - S[level].i2;//diff
		S[level].i2 = S[level - 1].i1;//diff
		while((int)R.size()) {
			if((int)Q.size() + R.back().d > (int)QMAX.size()){
				Q.push_back(R.back().i); Vertices Rp; cut2(R, Rp);
				if((int)Rp.size()){
					if((float)S[level].i1 / ++pk < Tlimit) degree_sort(Rp);//diff
					color_sort(Rp);
					S[level].i1++, level++;//diff
					expand_dyn(Rp);
					level--;//diff
				}
				else if((int)Q.size() > (int)QMAX.size()) QMAX = Q;
				Q.pop_back();
			}
			else return;
			R.pop_back();
		}
	}
	void mcqdyn(int* maxclique, int &sz){
		set_degrees(V); sort(V.begin(),V.end(), desc_degree); init_colors(V);
		for(int i = 0; i < (int)V.size() + 1; i++) S[i].i1 = S[i].i2 = 0;
		expand_dyn(V); sz = (int)QMAX.size();
		for(int i = 0; i < (int)QMAX.size(); i++) maxclique[i] = QMAX[i];
	}
	void degree_sort(Vertices &R){
		set_degrees(R); sort(R.begin(), R.end(), desc_degree);
	}
	Maxclique(const BB* conn, const int sz, const float tt = 0.025) \
	 : pk(0), level(1), Tlimit(tt){
		for(int i = 0; i < sz; i++) V.push_back(Vertex(i));
		e = conn, C.resize(sz + 1), S.resize(sz + 1);
	}
};