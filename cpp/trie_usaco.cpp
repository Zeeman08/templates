const int WMAX = 1e5 + 10;   //sum of length of all strings
int trie_s[WMAX][26];
int node_count;
bool stop[WMAX];
void insert(string word) {
	int node = 0;
	for (char c : word) {
		if (trie_s[node][c - 'a'] == 0) { trie_s[node][c - 'a'] = ++node_count; }
		node = trie_s[node][c - 'a'];
	}
	stop[node] = true;
}
