class Solution {
public:

    bool DFS(vector<vector<int>> & adjList, 
            vector<bool> & visited, 
            vector<bool> & ancestors, 
            vector<int> & path, 
            int i)
    {
        // mark as visited, BFS queue entry visualisation
        visited[i] = true;
        ancestors[i] = true;
        path.push_back(i);

        for(auto adj: adjList[i])
        {
            if(visited[adj] == true && ancestors[adj] == true)
            {
                return true; // cycle exists
            }
            if(visited[adj] == false)
            {
                bool exit_code = DFS(adjList, visited, ancestors, path, adj);
                if(exit_code)
                {
                    return true;
                }
            }
        }

        ancestors[i] = false;
        return false;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        /*
        Approach: extension of course schedule question.
        cycle detection + store node orders(if no cycles, so that they can be returned as answer)

        traverse graph, and if along with visited, ancestors, maintain path array
            if cycle found -> return empty
            else -> return path, as all nodes are visited exactly once and inserted into path

        Went through failing test case - 
        prerequisites=[[1,0],[2,0],[3,1],[3,2]]
Your Output

[0,1,3,2]
Expected Output

[0,1,2,3]

And figured out from graph diagram that DFS traversal doesn't give correct path here
we need to apply topological sort algo here, because topological sort algo picks node with 0 dependeny and update child dependencies
        compute in degree of all nodes
        pick those nodes, whose in degree is 0, put them in queue
        pop queue top
            - put node in ans
            - reduce neighbor indegree and one of their parent depedency node is gone
            - if neighbor indegree becomes zero, then insert them in queue
        If entire q is processed, and some nodes still have non zero in degree node
            it means it is cycle, and exit

        time complexity of topological sort: O(V+E)
            - each node is visited exactly once
        */

        // convert to adj list
        vector<vector<int>> adjList(numCourses);
        vector<int> inDegree(numCourses, 0);

        for(auto course: prerequisites)
        {
            adjList[course[1]].push_back(course[0]);
            inDegree[course[0]]++;
        }

        queue<int> q;
        vector<int> ans;

        for(int i=0; i<numCourses;i++)
        {
            if(inDegree[i]==0)
            {
                q.push(i);
                ans.push_back(i);
            }
        }

        if(q.empty() == true)
        {
            return ans; // early exit
        }

        while(q.empty() == false)
        {
            // pick q top
            int t = q.front();
            q.pop();
            for(const auto & adj: adjList[t])
            {
                inDegree[adj]--;
                if(inDegree[adj] == 0)
                {
                    q.push(adj);
                    ans.push_back(adj);
                }
            }
        }

        // if nodes with non zero indegree exists, it means they are not processed
        // and have cyclic dependency, ex:[0,1] [1,0]
        // AI optimization: remove this loop. Simply check if all nodes are present in and array, 
        // if no, then the not present nodes are non zero in degree ones, and not inserted in queue ever
        for(auto id: inDegree)
        {
            if(id>0)
            {
                vector<int> emptyArray;
                return emptyArray;
            }
        }
        return ans;

        // vector<int> emptyArray;
        // return emptyArray;
        // return (ans.size() == numCourses) ? ans : emptyArray;        
    }
};
