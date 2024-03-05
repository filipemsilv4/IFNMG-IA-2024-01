#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <set>

#define MATRIX_SIDE 3
#define MATRIX_SIZE 9
#define EMPTY_VALUE 0

using namespace std;

class Node{
    private:
        vector<int> state;
        Node *parent;
        pair<int,int> action_applied;

    public:
        vector<int> get_state(){ return this->state; }
        Node *get_parent(){ return this->parent; }
        pair<int,int> get_action_applied(){ return this->action_applied; }

        Node(Node *parent, vector<int> parent_state, pair<int,int> action_to_be_applied){
            this->state = parent_state;
            swap(this->state[action_to_be_applied.first],
                 this->state[action_to_be_applied.second]);
            this->parent = parent;
            this->action_applied = action_to_be_applied;
        }

        bool same_state_as(Node n){
            return n.get_state() == this->get_state();
        }
};

class Frontier{
    private:
        queue<Node> frontier;
    public:
        void add(Node n){ this->frontier.push(n); }

        Node remove(){
            if (frontier.empty()){
                cout << "Error: can't remove from a empty frontier" << endl;
                throw "The frontier is empty.";
                exit(-1);
            }
            Node n = frontier.front();
            this->frontier.pop();
            return n; // returns the removed Node
        }

        bool contains_state(vector<int> state){
            queue<Node> frontier_copy = this->frontier;
            while(!frontier_copy.empty()){
                if (frontier_copy.front().get_state() == state) return true;
                frontier_copy.pop();
            }
            return false;
        }

        int size(){ return this->frontier.size(); }

        bool empty(){ return frontier.empty(); }
};

vector<int> res;
vector<int> error{-1, -2, -3, -4, 5, 6, 7, 8, 0};

vector<pair<int,int>> get_possible_actions(vector<int> m){
    // Cima, Baixo, Esquerda, Direita
    vector<int> deslocamento{ -MATRIX_SIDE, MATRIX_SIDE, -1, +1};

    vector<pair<int,int>> possibilidades; // vector<index, index_destino>

    for (int i = 0; i < MATRIX_SIZE; i++){
        for (auto d : deslocamento){
            int new_pos = i + d;
            // Se ultrapassar as bordas da matriz:
            if (new_pos >= MATRIX_SIZE || new_pos < 0) continue;

            // Verificar se o espaço tá vazio
            if (m[new_pos] != EMPTY_VALUE) continue;

            // Se o deslocamento for possível:
            possibilidades.push_back({i, new_pos});
        }
    }

    return possibilidades;
}

void apply_action(vector<int> state, pair<int, int> action){
    swap(state[action.first], state[action.second]);
}

bool is_goal(vector<int> g){

    if (g.size() == 0 || g.size() == 1) return true;

    if (g[g.size() - 1] != EMPTY_VALUE) return false; 

    for (int i = 1; i < g.size() - 1; i++){
        if (g[i] > g[i - 1]) continue;
        return false;
    }

    return true;
}

vector<int> solve(vector<int> m){
    Node initial_state(NULL, m, {0,0});
    Frontier frontier;
    frontier.add(initial_state);
    set<vector<int>> known_states;

    while(true){
        cout << "frontier size: " << frontier.size() << endl;
        cout << "known states: " << known_states.size() << endl;
        if (frontier.empty()){
            cout << "No solution: empty frontier" << endl;
            throw "No solution";
            exit(-2);
        }

        Node n = frontier.remove();

        // Check if Node is the Goal
        if (is_goal(n.get_state())){
            // Do something
            cout << "Goal found!" << endl;
            return n.get_state();
        }

        // Add state to the set of known ones
        known_states.insert(n.get_state());

        // Expand the node
        vector<pair<int,int>> possible_actions = get_possible_actions(n.get_state());

        for (auto u : possible_actions){
            Node new_node(&n, n.get_state(), u);

            // Se o frontier não contem esse estado e se esse estado ainda não foi explorado:
            if ((!frontier.contains_state(new_node.get_state())) && 
                (known_states.find(new_node.get_state()) == known_states.end())){
                frontier.add(new_node);
            }
        }
    }
    
    cout << "Reached end of solve() without a valid solution" << endl;
    throw "No solution";
    exit(-3);
}

int main(){
    vector<int> matrix;

    // Answer
    for (int i = 0; i < MATRIX_SIZE; i++){
        res.push_back(i);
    }

    // Reading input matrix
    cout << "Input the matrix:" << endl;
    int tmp;
    for (int i = 0; i < MATRIX_SIZE; i++){
        cin >> tmp;
        matrix.push_back(tmp);
    }

    cout << "Solving..." << endl;
    vector<int> maybe_solved = solve(matrix);

    cout << "Result:" << endl;
    // Printing result
    for(int i = 0; i < maybe_solved.size(); i++){
        cout << maybe_solved[i] << " ";
        if (i % MATRIX_SIDE == 0){
            cout << endl;
        }
    }
    
    
}