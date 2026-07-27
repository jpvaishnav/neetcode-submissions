/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        /*
        Approach:
            constraints:
                no duplicate edges
                no duplicate nodes: no self loops
                connected graph: every node is reachable to every other node
                undirected
        traverse the node and maintain a map of <index, newClonedNode>
        perform bfs traversal from given source,
            and if a node is not present in cloneMap, then create the cloned node
            while processing a node(), update its connectivity to all neighbors
        */

        if(node == NULL)
        {
            return NULL;
        }

        queue<Node*> q;
        map<int, Node*> m;

        q.push(node);
        Node* clone = new Node(1);
        m[1] = clone;

        while(q.empty() == false)
        {
            Node* t = q.front();
            q.pop();
            int v = t->val;

            Node* copyNode = m[v];

            // update copyNode neighbors
            for(auto neighborNode: t->neighbors)
            {
                // if neighborNode copy is created, then update link
                int neighborIndex = neighborNode->val;
                if(m.find(neighborIndex) == m.end())
                {
                    // create copyNode
                    Node* neighborNodeCopy = new Node(neighborIndex);
                    m[neighborIndex] = neighborNodeCopy;
                    q.push(neighborNode);
                    // it means neighborNode is not yet processed
                }
                copyNode->neighbors.push_back(m[neighborIndex]);
            }
        }

        return clone;
    }
};
