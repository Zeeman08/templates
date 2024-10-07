template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {

    public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        //v is 1 indexed
        size = _n - 1;
        d = std::vector<S>(4 * _n + 5, e());
        lz = std::vector<F>(4 * _n + 5, id());
        arr = v;
        build(1, 1, size);
    }
    void build(int tv, int tl, int tr) {
        if(tl == tr) d[tv] = arr[tl];
        else {
            int tm = (tl + tr) >> 1;
            build(tv*2, tl, tm);
            build(tv*2+1, tm+1, tr);
            d[tv] = op(d[tv*2], d[tv*2 + 1]);
        }
    }
    void push(int tv, int tl, int tr) {
        if(lz[tv]==id()) return;
        d[tv] = mapping(lz[tv], d[tv]);
        if(tl < tr) {
            lz[tv*2] = composition(lz[tv*2], lz[tv]);
            lz[tv*2+1] = composition(lz[tv*2+1], lz[tv]);
        }
        lz[tv] = id();
    }
    void update(int l, int r, F f, int tv, int tl, int tr, int init) {
         //printf("now at %d %d\n", tl, tr);
        push(tv, tl, tr);
        if(r < l) return;
        if(l == tl && r == tr) {
            lz[tv] = f;
            push(tv, tl, tr);
        }
        else {
            int tm = (tl + tr) / 2;
            update(l, min(tm, r), f, tv*2, tl, tm, init);
            update(max(tm+1, l), r, f, tv*2+1, tm+1, tr, init);
            d[tv] = op(d[tv*2], d[tv*2+1]);
        }
    }
    S get(int l, int r, int tv, int tl, int tr) {
        push(tv, tl, tr);
        if(r < l) return e();
        if(l == tl && r == tr) {
            return d[tv];
        }
        else {
            int tm = (tl + tr) / 2;
            return op(get(l, min(tm, r), tv*2, tl, tm),
            get(max(tm+1, l), r, tv*2+1, tm+1, tr));
        }
    }
    void apply(int l, int r, F f) {
        update(l, r-1, f, 1, 1, size, l);
    }
    S prod(int l, int r) {
        return get(l, r-1, 1, 1, size);
    }


  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<S> arr;
    std::vector<F> lz;

    
};
