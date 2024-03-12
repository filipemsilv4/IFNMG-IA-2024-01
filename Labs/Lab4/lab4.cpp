#include <iostream>
#include <vector>
#include <climits>
#include <utility>

using namespace std;

enum class Player { None, X, O };

class TicTacToe {
    private:
        vector<vector<Player>> tabuleiro;
    public:
        // #Inicializa o tabuleiro
        TicTacToe() {
            tabuleiro = {
                {Player::None, Player::None, Player::None},
                {Player::None, Player::None, Player::None},
                {Player::None, Player::None, Player::None}
            };
        }

        // Retorna o tabuleiro
        vector<vector<Player>> getTabuleiro() {
            return tabuleiro;
        }

        // #Retorna X ou O, dependendo de quem é o jogador atual
        // def jogador(tabuleiro):
        Player jogador(vector<vector<Player>> tabuleiro) {
            int x = 0;
            int o = 0;

            for (int i = 0; i < tabuleiro.size(); ++i) {
                for (int j = 0; j < tabuleiro[i].size(); ++j) {
                    if (tabuleiro[i][j] == Player::X) {
                        ++x;
                    } else if (tabuleiro[i][j] == Player::O) {
                        ++o;
                    }
                }
            }

            return x <= o ? Player::X : Player::O;
        }

        // #Retorna todas as jogadas disponíveis
        // def acoes(tabuleiro):
        vector<pair<int, int>> acoes(vector<vector<Player>> tabuleiro) {
            vector<pair<int, int>> availableActions;

            for (int i = 0; i < tabuleiro.size(); ++i) {
                for (int j = 0; j < tabuleiro[i].size(); ++j) {
                    if (tabuleiro[i][j] == Player::None) {
                        availableActions.push_back({i, j});
                    }
                }
            }

            return availableActions;
        }

        // #Retorna o tabuleiro que resulta ao fazer uma jogada do vetor de ações
        // def resultado(tabuleiro, acao):
        vector<vector<Player>> resultado(vector<vector<Player>> tabuleiro, pair<int, int> acao) {
            vector<vector<Player>> novoTabuleiro = tabuleiro;
            novoTabuleiro[acao.first][acao.second] = jogador(tabuleiro);
            return novoTabuleiro;
        }

        // #Retorna o ganhador, se houver
        // def ganhador(tabuleiro):
        Player ganhador(vector<vector<Player>> tabuleiro) {
            // Check the rows
            for (int i = 0; i < 3; ++i) {
                if (tabuleiro[i][0] != Player::None && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2]) {
                    return tabuleiro[i][0];
                }
            }

            // Check the columns
            for (int i = 0; i < 3; ++i) {
                if (tabuleiro[0][i] != Player::None && tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i]) {
                    return tabuleiro[0][i];
                }
            }

            // Check one diagonal
            if (tabuleiro[0][0] != Player::None && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2]) {
                return tabuleiro[0][0];
            }

            // Check other diagonal
            if (tabuleiro[0][2] != Player::None && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[0][2] == tabuleiro[2][0]) {
                return tabuleiro[0][2];
            }

            return Player::None;
        }

        // #Retorna Verdadeiro se o jogo acabou, Falso caso contrário
        // def final(tabuleiro):
        bool final(vector<vector<Player>> tabuleiro) {
            for (int i = 0; i < tabuleiro.size(); ++i) {
                for (int j = 0; j < tabuleiro[i].size(); ++j) {
                    if (tabuleiro[i][j] == Player::None) {
                        // The game may be over if someone has won
                        if (ganhador(tabuleiro) != Player::None) {
                            return true;
                        }
                        return false;
                    }
                }
            }
            return true;
        }

        // #Retorna 1 se X ganhou, -1 se 0 ganhou, 0 caso contrário.
        // def custo(tabuleiro):

        int custo(vector<vector<Player>> tabuleiro) {
            Player winner = ganhador(tabuleiro);
            if (winner == Player::X) {
                return 1;
            } else if (winner == Player::O) {
                return -1;
            } else {
                return 0;
            }
        }

        // #Retorna a jogada ótima para o jogador atual
        // def minimax(tabuleiro):
        // pair meaning: (score, (row, col))
        pair<int, pair<int, int>> minimax(vector<vector<Player>> tabuleiro, int depth, int alpha, int beta, bool maximizingPlayer) {
            if (final(tabuleiro) || depth == 0) {
                return {custo(tabuleiro), {-1, -1}};
            }

            vector<pair<int, int>> actions = acoes(tabuleiro);
            pair<int, int> bestAction = {-1, -1};

            // Maximizing player
            if (maximizingPlayer) {
                int maxEval = -INT_MAX;
                for (int i = 0; i < actions.size(); ++i) {
                    vector<vector<Player>> newBoard = resultado(tabuleiro, actions[i]);
                    int eval = minimax(newBoard, depth - 1, alpha, beta, false).first;
                    if (eval > maxEval) {
                        maxEval = eval;
                        bestAction = actions[i];
                    }
                    alpha = max(alpha, eval);
                    if (beta <= alpha) {
                        break;
                    }
                }
                return {maxEval, bestAction};
            } else {
                int minEval = INT_MAX;
                for (int i = 0; i < actions.size(); ++i) {
                    vector<vector<Player>> newBoard = resultado(tabuleiro, actions[i]);
                    int eval = minimax(newBoard, depth - 1, alpha, beta, true).first;
                    if (eval < minEval) {
                        minEval = eval;
                        bestAction = actions[i];
                    }
                    beta = min(beta, eval);
                    if (beta <= alpha) {
                        break;
                    }
                }
                return {minEval, bestAction};
            }
        }

        // #Executar jogada da IA
        void jogadaIA() {
            pair<int, pair<int, int>> bestMove = minimax(tabuleiro, INT_MAX, -INT_MAX, INT_MAX, false);
            tabuleiro = resultado(tabuleiro, bestMove.second);
        }

        // #Executar jogada do jogador
        void jogadaJogador(int row, int col) {
            tabuleiro = resultado(tabuleiro, {row, col});
        }

        // Print the board
        void printBoard() {
            std::cout << "\033[1;32m   1   2   3\033[0m" << std::endl;
            for (int i = 0; i < tabuleiro.size(); ++i) {
                // Print the indexes
                std::cout << "\033[1;32m" << i + 1 << "  \033[0m";
                for (int j = 0; j < tabuleiro[i].size(); ++j) {
                    if (tabuleiro[i][j] == Player::None) {
                        std::cout << "\033[1;37m \033[0m";
                    } else if (tabuleiro[i][j] == Player::X) {
                        std::cout << "\033[1;34mX\033[0m";
                    } else {
                        std::cout << "\033[1;31mO\033[0m";
                    }
                    if (j < 2) {
                        std::cout << "\033[1;36m | \033[0m";
                    }
                }
                std::cout << std::endl;
                if (i < 2) {
                    std::cout << "\033[1;36m  ------------\033[0m" << std::endl;
                }
            }
        }
        // def maxValor(tabuleiro):
        // def minValor(tabuleiro):
};


int main() {
    TicTacToe game;
    // clear the screen
    std::cout << "\033[2J\033[1;1H";

    while (!game.final(game.getTabuleiro())) {
        std::cout << "Tabuleiro atual: " << std::endl;
        std::vector<std::vector<Player>> tabuleiro = game.getTabuleiro();
        game.printBoard();

        if (game.jogador(tabuleiro) == Player::X) {
            int row, col;
            std::cout << "Vez do jogador (\033[1;34mX\033[0m)." << std::endl << "Escolha a linha (1-3): ";
            std::cin >> row;
            std::cout << "Escolha a coluna (1-3): ";
            std::cin >> col;
            game.jogadaJogador(row - 1, col - 1);
        } else {
            std::cout << "Vez da IA (\033[1;31mO\033[0m)." << std::endl;
            game.jogadaIA();
        }
        std::cout << "\033[1;36m-----------------\033[0m" << std::endl;
        // clear the screen
        std::cout << "\033[2J\033[1;1H";
    }
    game.printBoard();
    std::cout << "Fim de jogo!" << std::endl;

    // Who won?
    if (game.custo(game.getTabuleiro()) == 1) {
        std::cout << "Jogador (\033[1;34mX\033[0m) venceu!" << std::endl;
    } else if (game.custo(game.getTabuleiro()) == -1) {
        std::cout << "IA (\033[1;31mO\033[0m) venceu!" << std::endl;
    } else {
        std::cout << "Empate!" << std::endl;
    }

    return 0;
}