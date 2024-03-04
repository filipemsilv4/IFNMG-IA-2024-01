#include <iostream>
#include <vector>
#include <utility>

#define MATRIX_SIDE 3
#define MATRIX_SIZE 9
#define EMPTY_VALUE 0

typedef pair<int,int> action;

using namespace std;

class Node{
    private:
        vector<int> state;
        Node *parent;
        action action_applied;

    public:
        vector<int> get_state(){ return this->state; }
        Node *get_parent(){ return this->parent; }
        action get_action_applied(){ return this->action_applied; }

        Node(Node *parent, pair<int,int> action_to_be_applied){
            this->state = parent->get_state();
            swap(this->state[action_to_be_applied.first],
                 this->state[action_to_be_applied.second]);
            this->parent = parent;
            this->action_applied = action_to_be_applied;
        }

        bool same_state_as(Node n){
            return n.get_state() == this->get_state();
        }
};

vector<int> res;
// Cima, Baixo, Esquerda, Direita
vector<int> deslocamento{ -MATRIX_SIDE, MATRIX_SIDE, -1, +1};

// acoes
// resultado

vector<pair<int,int>> acoes(vector<int> m){

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

vector<int> apply_action(vector<int> state, pair<int, int> action){
    swap(state[action.first], state[action.second]);
}

vector<int> solve(vector<int> m){
    
}

int main(){
    vector<int> matrix;
    
    // Answer
    for (int i = 0; i < MATRIX_SIZE; i++){
        res.push_back(i);
    }

    // Reading input matrix
    int tmp;
    for (int i = 0; i < MATRIX_SIZE; i++){
        cin >> tmp;
        matrix.push_back(tmp);
    }

    vector<int> maybe_solved = solve(matrix);

    // Printing result
    for(int i = 0; i < maybe_solved.size(); i++){
        cout << maybe_solved[i] << " ";
        if (i % MATRIX_SIDE == 0){
            cout << endl;
        }
    }
    
    
}