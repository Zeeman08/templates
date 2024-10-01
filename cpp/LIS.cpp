int find_lis(vector<ll> a) {
    if(a.size() == 0) return 0;
    vector<ll> dp;
    for (ll i : a) {
        int pos = upper_bound(dp.begin(), dp.end(), i) - dp.begin();  // lower_bound = increasing, upper_bound = non-decreasing
        if (pos == (int)dp.size()) {
            // we can have a new, longer increasing subsequence!
            dp.push_back(i);    
        } else {
            // oh ok, at least we can make the ending element smaller
            dp[pos] = i;
        }
    }
    return dp.size();
}
