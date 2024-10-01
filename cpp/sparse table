class SparseTable {
    public:
    int ** st;
    int K;
    int n;
    SparseTable(vector<int>a) {
        n = a.size();
        K = __lg(n) + 1;
        st = new int*[K];
        for(int i = 0; i < K; i++) st[i] = new int[n];
        for(int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }
        for (int i = 1; i <= K; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    ~SparseTable() {
        for(int i = 0; i < K; i++) delete[] st[i];
        delete[] st;
    }
    int get(int L, int R) {
        int i = __lg(R - L + 1);
        int minimum = min(st[i][L], st[i][R - (1 << i) + 1]);
    }
};
