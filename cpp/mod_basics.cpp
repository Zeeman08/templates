long long binpow(long long _a, long long _b, long long _m) {
    _a %= _m;
    long long res = 1;
    while (_b > 0) {
        if (_b & 1)
            res = res * _a % _m;
        _a = _a * _a % _m;
        _b >>= 1;
    }
    return res;
}
ll inv(ll _x, ll _m = MOD) {
    return binpow(_x, _m-2, _m);
}
ll sub(ll _x, ll _y, ll _m = MOD) {
    _x %= _m, _y %= _m;
    _x -= _y;
    if(_x < 0) _x += _m;
    return _x;
}
ll mult(ll _x, ll _y, ll _m = MOD)  {
    _x %= _m, _y %= _m;
    return (_x * _y) % _m;
}
ll add(ll _x, ll _y, ll _m = MOD) {
    return (_x + _y) % _m;
}
