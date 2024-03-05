#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;

class Node {
    public:
        vector<vector<int>> state;
        int size;
        pair<int, int> emptyPos;

        Node(vector<vector<int>> initial) {
            state = initial;
            size = initial.size();
            findEmptyPosition();
        }

        bool operator==(const Node& other) const {
            return state == other.state;
        }

        bool operator!=(const Node& other) const {
            return !(*this == other);
        }

        void findEmptyPosition() {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if (state[i][j] == 0) {
                        emptyPos = {i, j};
                        return;
                    }
                }
            }
        }

        vector<Node> getNeighbors() const {
            vector<Node> neighbors;

            const int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

            for (int i = 0; i < 4; ++i) {
                int x = emptyPos.first + moves[i][0];
                int y = emptyPos.second + moves[i][1];

                if (x >= 0 && x < size && y >= 0 && y < size) {
                    vector<vector<int>> newState = state;
                    swap(newState[emptyPos.first][emptyPos.second], newState[x][y]);
                    Node neighbor(newState);
                    neighbors.push_back(neighbor);
                }
            }

            return neighbors;
        }
};

namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& n) const {
            size_t hashVal = 0;
            for (const auto& row : n.state) {
                for (int val : row) {
                    hashVal ^= hash<int>{}(val) + 0x9e3779b9 + (hashVal << 6) + (hashVal >> 2);
                }
            }
            return hashVal;
        }
    };
}

class Frontier {
    public:
        queue<Node> nodes;
        unordered_set<Node> visited;

        bool isEmpty() const {
            return nodes.empty();
        }

        int queueSize() const { return nodes.size(); }
        int visitedSize() const { return visited.size(); }

        void enqueue(const Node& node) {
            nodes.push(node);
            visited.insert(node);
        }

        Node dequeue() {
            Node front = nodes.front();
            nodes.pop();
            return front;
        }

        bool isVisited(const Node& node) const {
            return visited.count(node) > 0;
        }
};

bool isSolved(const Node& node) {
    int num = 1;
    for (int i = 0; i < node.size; ++i) {
        for (int j = 0; j < node.size; ++j) {
            if (node.state[i][j] != num % (node.size * node.size)) {
                return false;
            }
            num++;
        }
    }
    return true;
}

void printSolution(const Node& node, const int &steps) {
    cout << "Solution found with " << steps << " steps!" << endl;
    for (int i = 0; i < node.size; ++i) {
        for (int j = 0; j < node.size; ++j) {
            cout << node.state[i][j] << " ";
        }
        cout << endl;
    }
}

void solvePuzzle(const Node& initialNode) {
    Frontier frontier;
    frontier.enqueue(initialNode);
    int steps = 0;

    while (!frontier.isEmpty()) {
        Node current = frontier.dequeue();

        // cout << "frontier size: " << frontier.queueSize() << endl;
        // cout << "known states: " << frontier.visitedSize() << endl;

        steps++;

        if (isSolved(current)) {
            printSolution(current, steps);
            return;
        }

        vector<Node> neighbors = current.getNeighbors();
        for (const Node& neighbor : neighbors) {
            if (!frontier.isVisited(neighbor)) {
                frontier.enqueue(neighbor);
            }
        }
    }

    cout << "No solution found." << endl;
}

int main() {
    // Example 3x3 puzzle, you can change the size and initial configuration
    vector<vector<int>> initialConfig = {
        {7, 2, 4},
        {5, 0, 6},
        {8, 3, 1}
    };

    Node initialNode(initialConfig);
    solvePuzzle(initialNode);

    return 0;
}
