class Solution {
public:

    int find(int u, vector<int> & parent)
    {
        if(u==parent[u])
        {
            return u;
        }
        return find(parent[u], parent);
    }

    // void union(int u, int v, vector<int> & parent)
    // {

    // }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        /*
        Approach:
            - since the question is asking to return the last edge which is redundant
                - hence we would have to use disjoint set here
                - otherwise if we convert it to adjacency list, we would loose out the order of edges
                ** Graph question where answer format gives hint of what Data structure to use
        Process each edge
            - if they are already connected(have common parent)
                - then the edge is redundant
                - no ops in union-find
                - but update ans
        Implementation of union-find:
            - parent[i] to track parent array
            - find(i) function to find representative of i
                - representative is a node n such that n == parent[n]
            - union(u,v):
                - get representative of u and v
                - Choose u as parent represenative
                    - represenative of v = u
        time complexity: O(V+ alpha * E)
        can be optimized further by using rank array
        */

        vector<int> ans(2);
        int n = edges.size();
        vector<int> parent(n+1); // nodes are from 1 to n; 0 will be ignored
        for(int i=0; i<=n; i++)
        {
            parent[i]=i;
        }

        for(auto edge: edges)
        {
            int u = edge[0];
            int v = edge[1];

            int rep_u = find(u, parent);
            int rep_v = find(v, parent);

            if(rep_u==rep_v)
            {
                ans[0] = u;
                ans[1] = v;
            }
            else
            {
                // union of u and v
                //union(u,v,parent);
                // since represenative are already available, so lets connect directly
                parent[rep_v] = rep_u;
            }
        }
        return ans;
    }
};
