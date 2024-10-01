vector<vector<int>> adj(N);
bool is_removed[N];
int subtree_size[N];
vector<vector<pair<int, int>>> ancestors(N);

/** DFS to calculate the size of the subtree rooted at `node` */
int get_subtree_size(int node, int parent = -1) {
    subtree_size[node] = 1;
    for (int child : adj[node]) {
        if (child == parent || is_removed[child]) { continue; }
        subtree_size[node] += get_subtree_size(child, node);
    }
    return subtree_size[node];
}

/**
 * Returns a centroid (a tree may have two centroids) of the subtree
 * containing node `node` after node removals
 * @param node current node
 * @param tree_size size of current subtree after node removals
 * @param parent parent of u
 * @return first centroid found
 */
int get_centroid(int node, int tree_size, int parent = -1) {
    for (int child : adj[node]) {
        if (child == parent || is_removed[child]) { continue; }
        if (subtree_size[child] * 2 > tree_size) {
            return get_centroid(child, tree_size, node);
        }
    }
    return node;
}

/**
 * Calculate the distance between current `node` and the `centroid` it belongs
 * to. The distances between a node and all its centroid ancestors are stored
 * in the vector `ancestors`.
 * @param cur_dist the distance between `node` and `centroid`
 */
void get_dists(int node, int centroid, int parent = -1, int cur_dist = 1) {
    for (int child : adj[node]) {
        if (child == parent || is_removed[child]) { continue; }
        cur_dist++;
        get_dists(child, centroid, node, cur_dist);
        cur_dist--;
    }
    ancestors[node].push_back({centroid, cur_dist});
}

/** Build up the centroid decomposition recursively */
void build_centroid_decomp(int node = 1) {
    int centroid = get_centroid(node, get_subtree_size(node));

    // do something, for example, here we have taken the ancestors and their distances to the 
    // current node. We often need to Keep ancestors.
    /*
     * For all nodes in the subtree rooted at `centroid`, calculate their
     * distances to the centroid
     */
    for (int child : adj[centroid]) {
        if (is_removed[child]) { continue; }
        get_dists(child, centroid, centroid);
    } 

    is_removed[centroid] = true;

    for (int child : adj[centroid]) {
        if (is_removed[child]) { continue; }
        build_centroid_decomp(child);
    }
}
