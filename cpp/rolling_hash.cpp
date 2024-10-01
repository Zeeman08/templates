class hashTable {
    public:
    int n, limit;
    string s;
    vector<vector<ll>>pref, suff;
    vector<ll> primes;
    vector<ll> m;
    vector<vector<ll>> p_pow, pinv_pow;
    /*
    use this:
    vector<ll> p = {773,709};
    vector<ll> mods = {281559881,398805713};
    */
    hashTable(int _n, string _s, int _limit=2, vector<ll> _primes={773,709}, vector<ll> _mods = {281559881,398805713}) {
        this->s = _s; //1 indexed
        this->n = _n;
        this->limit = _limit;
        this->primes = _primes;
        this->m = _mods;
        this->p_pow.resize(limit);
        this->pinv_pow.resize(limit);
        for(int i = 0; i < limit; i++) {
            p_pow[i].resize(n+2), pinv_pow[i].resize(n+2);
            p_pow[i][0] = pinv_pow[i][0] = 1;
            for(int j = 1;j <= n; j++) {
                p_pow[i][j] = (p_pow[i][j-1] * primes[i]) % m[i];
            }
            pinv_pow[i][1] = inv(primes[i], m[i]);
            for(int j = 2; j <= n; j++) {
                pinv_pow[i][j] = (pinv_pow[i][j-1] * pinv_pow[i][1]) % m[i];
            }
            // for(int j = 1; j <= n; j++) {
            //     printf("%lld ", p_pow[i][j]);
            // }
            // printf(" [%d]\n", i);
            // for(int j = 1; j <= n; j++) {
            //     printf("%lld ", pinv_pow[i][j]);
            // }
            // printf(" [%d]\n", i);
        }
        pref.resize(this->limit);
        suff.resize(this->limit);
        for(int i = 0; i < limit; i++) {
            pref[i].resize(n+2);
            suff[i].resize(n+2);
        }
        precompute();
    }   
    void precompute() {
        for(int ith_hash = 0; ith_hash < limit; ith_hash++) {
            ll hash_value = 0;
            for(int i = 1; i <= n; i++) {
                hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow[ith_hash][i-1]) % m[ith_hash];
                pref[ith_hash][i] = hash_value;
            }
            pref[ith_hash][0] = 0;
        }
        for(int ith_hash = 0; ith_hash < limit; ith_hash++) {
            ll hash_value = 0;
            for(int i = n; i >= 1; i--) {
                hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow[ith_hash][n-i]) % m[ith_hash];
                suff[ith_hash][i] = hash_value;
            }
            suff[ith_hash][n+1] = 0;
        }
    }
    ll get_pref(int l, int r, int ith_hash) {
        ll here = sub(pref[ith_hash][r], pref[ith_hash][l-1], m[ith_hash]);
        here = mult(here, pinv_pow[ith_hash][l-1], m[ith_hash]);   
        return here;
    }
    ll get_suff(int l, int r, int ith_hash) {
        ll here = sub(suff[ith_hash][l], suff[ith_hash][r+1], m[ith_hash]);
        here = mult(here, pinv_pow[ith_hash][n-r], m[ith_hash]);
        return here;
    }
    long long binpow(long long a, long long b, long long m) {
        a %= m;
        long long res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a % m;
            a = a * a % m;
            b >>= 1;
        }
        return res;
    }
    ll inv(ll x, ll m) {
        return binpow(x, m-2, m);
    }
    ll sub(ll x, ll y, ll m) {
        x %= m, y %= m;
        x-= y;
        if(x < 0) x += m;
        return x;
    }
    ll mult(ll x, ll y, ll m)  {
        x %= m, y %= m;
        return (x * y) % m;
    }
    bool is_palindrome(int l, int r) {
        if(get_pref(l, r, 0) == get_suff(l, r, 0) && get_pref(l, r, 1) == get_suff(l, r, 1)) return true;
        return false;
    }

};

