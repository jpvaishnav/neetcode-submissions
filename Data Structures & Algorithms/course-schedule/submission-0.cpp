class Solution {
public:

    bool DFSRec(vector<vector<int>>& adjList, 
            vector<bool> & visited, 
            vector<bool> & ancestors, int i)
    {
        // mark as visited
        visited[i] = true;
        ancestors[i] = true;

        for(auto adj: adjList[i])
        {
            if(visited[adj] == true && ancestors[adj] == true)
            {
                return true; // cycle exists
            }
            if(visited[adj] == false)
            {
                bool exit_code = DFSRec(adjList, visited, ancestors, adj);
                if(exit_code)
                {
                    return true;
                }
            }
            // no condition if already visited, and does not belong to ancestors
            // it belongs to other disconnected graph in forest, which would be covered by another DFS
        }

        ancestors[i] = false;
        return false;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        /*
        Approach: Question description and test cases -> cycle detection in directed graph
        if cycle exists, then its a cyclic dependency of courses -> so can't take
        otherwise -> can be taken

        courses could also be disconnected and valid solution:
            like: [1,2] [3,4]

        cycle detection in directed graph:
            - u to v
            - if v is already visited, and v is one of ancestor of current node,
                - then v to ancestor connection is a back chain
                - and it is a cycle
        Apply for disconnected graph as 

        */

        // convert to adj list
        vector<vector<int>> adjList(numCourses);
        for(auto course: prerequisites)
        {
            // course b -> a => b is completed first, then a
            adjList[course[1]].push_back(course[0]);
        }

        vector<bool> visited(numCourses, false);
        vector<bool> ancestors(numCourses, false);

        for(int i=0; i<numCourses;i++)
        {
            if(visited[i]==false)
            {
                int exit_code = DFSRec(adjList, visited, ancestors, i);
                if(exit_code == true)
                {
                    // cycle detected
                    return false;
                }
            }
        }

        return true;
    }
};
