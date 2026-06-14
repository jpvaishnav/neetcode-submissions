class Solution {
public:

    class Node
    {
        public:
        string val;
        vector<Node*> adjacents;
        bool visited;
        Node(string value)
        {
            val = value;
            visited = false;
            // adjacents = new vector<Node*> (); by default, it is empty
        }
    };

    bool areAdjacents(string s1, string s2)
    {
        int diff_chars = 0;
        for(int i = 0; i < s1.size(); i++)
        {
            if (s1[i] != s2[i])
            {
                diff_chars++;
            }
            if(diff_chars > 1)
            {
                return false;
            }
        }
        if(diff_chars == 1)
        {
            return true;
        }
        return false;
    }

    vector<Node*> constructGraph(vector<string> & wordList, string beginWord)
    {
        // also include source node in graph

        vector<Node*> graphNodes;
        Node* sourceNode = new Node(beginWord);
        graphNodes.push_back(sourceNode);
        for(int i = 0; i < wordList.size(); i++)
        {
            string curr = wordList[i];
            Node* currNode = new Node(curr);
            for(int j = 0; j < graphNodes.size(); j++)
            {
                Node* graphNode = graphNodes[j];
                if(areAdjacents(currNode->val, graphNode->val))
                {
                    currNode->adjacents.push_back(graphNode);
                    graphNode->adjacents.push_back(currNode);
                }
            }
            graphNodes.push_back(currNode);
        }
        return graphNodes;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // naive solution:
        // pick source node, for each index
        // substitute value from a to z, and check if next word exists
        // if yes, then track next word
        // backtracking
        // if(isSolution()) {return count;}

        // graph approach:
        // construct a graph based on distance between 2 words
        // 1 distance nodes are adjacents
        // get distance between source and destination using BFS

        // graph construction
        // adjancent list or adjenct matrix not possible, because index is string
        // vector<vector<int>> -- xx
        // creating custom graph node and maintaining adjancents in each graph as list
        // maintaining all nodes inside another list
        
        vector<Node*> graphNodes = constructGraph(wordList, beginWord);

        Node* sourceNode;
        // apply BFS
        for(int i = 0; i < graphNodes.size(); i++)
        {
            if(graphNodes[i]->val == beginWord)
            {
                sourceNode = graphNodes[i];
            }
        }

        if (sourceNode == NULL)
        {
            return 0;
        }

        // start BFS
        // queue< pair < Node, distance from source >> q;
        queue<pair<Node*, int>> q;
        // bool<Node*> visited; // not supported, so put visited flag in node itself
        q.push(make_pair(sourceNode, 1));
        sourceNode->visited = true;
        while(q.empty() == false)
        {
            pair<Node*, int> top = q.front();
            q.pop();
            for(auto adjNode: top.first->adjacents)
            {
                if(adjNode->val == endWord)
                {
                    return top.second+1;
                }
                if(adjNode->visited == false)
                {
                    q.push(make_pair(adjNode, top.second+1));
                    adjNode->visited = true;
                }
            }
        }
        return 0;
    }
};
