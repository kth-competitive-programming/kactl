// Returns an xor basis of a, sorted by decreasing first set bit;
// Each vector will be the only vector that has its first set bit set. 
vector<ll> xor_basis(vector<ll>& a){
    vector<ll> basis(64, 0);
    for(auto x : a){
        for(int i = 63; i >= 0; i--){
            if(!(x & (1ll << i)))
                continue;
            if(basis[i]){
                x ^= basis[i];
            } else {
                basis[i] = x;
                break;
            }
        }
    }
    vector<ll> ret;
    for(int i = 63; i >= 0; i--){
        if(basis[i]){
            for(auto& x : ret){
                if(x & (1ll << i)){
                    x ^= basis[i];
                }
            }
            ret.push_back(basis[i]);
        }
    }
    sort(all(ret));
    reverse(all(ret));
    return ret;
}
