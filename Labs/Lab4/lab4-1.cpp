// PT: O objetivo desse programa é implementar o jogo da velha (Tic Tac Toe) com a IA usando o algoritmo Minimax.
// Para deixar as coisas mais interessantes, o jogo da velha é um pouco diferente do tradicional, pois cada jogador
// pode desfazer a jogada do jogador anterior.

// EN: The goal of this program is to implement the Tic Tac Toe game with the AI using the Minimax algorithm.
// To make things more interesting, the Tic Tac Toe game is a little different from the traditional one, because each
// player can undo the previous player's move.

#include <iostream>
#include <vector>
#include <climits>
#include <utility>

using namespace std;

enum class Player
{
    None,
    X,
    O
};

class TicTacToe
{
protected:
    vector<vector<Player>> board;

public:
    // #Inicializa o board
    TicTacToe()
    {
        board = {
            {Player::None, Player::None, Player::None},
            {Player::None, Player::None, Player::None},
            {Player::None, Player::None, Player::None}};
    }

    // Retorna o board
    vector<vector<Player>> getboard()
    {
        return board;
    }

    // #Retorna X ou O, dependendo de quem é o jogador atual
    // def jogador(board):
    Player jogador(vector<vector<Player>> board)
    {
        int x = 0;
        int o = 0;

        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                if (board[i][j] == Player::X)
                {
                    ++x;
                }
                else if (board[i][j] == Player::O)
                {
                    ++o;
                }
            }
        }

        return x <= o ? Player::X : Player::O;
    }

    // #Retorna todas as jogadas disponíveis
    // def acoes(board):
    vector<pair<int, int>> acoes(vector<vector<Player>> board)
    {
        vector<pair<int, int>> availableActions;

        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                if (board[i][j] == Player::None)
                {
                    availableActions.push_back({i, j});
                }
            }
        }

        return availableActions;
    }

    // #Retorna o board que resulta ao fazer uma jogada do vetor de ações
    // def resultado(board, acao):
    vector<vector<Player>> resultado(vector<vector<Player>> board, pair<int, int> acao)
    {
        vector<vector<Player>> novoboard = board;
        // Check if the action is valid
        if (novoboard[acao.first][acao.second] != Player::None)
        {
            cout << "Jogada inválida!" << endl;
            throw "Jogada inválida!";
        }

        novoboard[acao.first][acao.second] = jogador(board);

        return novoboard;
    }

    // #Retorna o ganhador, se houver
    // def ganhador(board):
    Player ganhador(vector<vector<Player>> board)
    {
        // Check the rows
        for (int i = 0; i < 3; ++i)
        {
            if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][0] == board[i][2])
            {
                return board[i][0];
            }
        }

        // Check the columns
        for (int i = 0; i < 3; ++i)
        {
            if (board[0][i] != Player::None && board[0][i] == board[1][i] && board[0][i] == board[2][i])
            {
                return board[0][i];
            }
        }

        // Check one diagonal
        if (board[0][0] != Player::None && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        {
            return board[0][0];
        }

        // Check other diagonal
        if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[0][2] == board[2][0])
        {
            return board[0][2];
        }

        return Player::None;
    }

    // #Retorna Verdadeiro se o jogo acabou, Falso caso contrário
    // def final(board):
    bool final(vector<vector<Player>> board)
    {
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                if (board[i][j] == Player::None)
                {
                    // The game may be over if someone has won
                    if (ganhador(board) != Player::None)
                    {
                        return true;
                    }
                    return false;
                }
            }
        }
        return true;
    }

    // #Retorna 1 se X ganhou, -1 se 0 ganhou, 0 caso contrário.
    // def custo(board):

    int custo(vector<vector<Player>> board, int depth = 0)
    {
        Player winner = ganhador(board);
        if (winner == Player::X)
        {
            return 1;
        }
        else if (winner == Player::O)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    // #Retorna a jogada ótima para o jogador atual
    // def minimax(board):
    // pair meaning: (score, (row, col))
    pair<int, pair<int, int>> minimax(vector<vector<Player>> board, int depth, int alpha, int beta, bool maximizingPlayer)
    {
        if (final(board) || depth == 0)
        {
            return {custo(board, depth), {-1, -1}};
        }

        vector<pair<int, int>> actions = acoes(board);
        pair<int, int> bestAction = {-1, -1};

        // Maximizing player
        if (maximizingPlayer)
        {
            int maxEval = -INT_MAX;
            for (int i = 0; i < actions.size(); ++i)
            {
                vector<vector<Player>> newBoard = resultado(board, actions[i]);
                int eval = minimax(newBoard, depth - 1, alpha, beta, false).first;
                if (eval > maxEval)
                {
                    maxEval = eval;
                    bestAction = actions[i];
                }
                alpha = max(alpha, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return {maxEval, bestAction};
        }
        else
        {
            int minEval = INT_MAX;
            for (int i = 0; i < actions.size(); ++i)
            {
                vector<vector<Player>> newBoard = resultado(board, actions[i]);
                int eval = minimax(newBoard, depth - 1, alpha, beta, true).first;
                if (eval < minEval)
                {
                    minEval = eval;
                    bestAction = actions[i];
                }
                beta = min(beta, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return {minEval, bestAction};
        }
    }

    // #Executar jogada da IA
    void AITurn()
    {
        // Player::X starts the game and is the maximizing player
        bool maximizingPlayer = jogador(board) == Player::X;
        pair<int, pair<int, int>> bestMove = minimax(board, INT_MAX, -INT_MAX, INT_MAX, maximizingPlayer);
        board = resultado(board, bestMove.second);
    }

    // #Executar jogada do jogador
    void playerTurn(int row, int col)
    {
        try
        {
            board = resultado(board, {row, col});
        }
        catch (const char *msg)
        {
            throw msg;
        }
    }

    // Print the board
    void printBoard()
    {
        cout << "\033[1;32m   1   2   3\033[0m" << endl;
        for (int i = 0; i < board.size(); ++i)
        {
            // Print the indexes
            cout << "\033[1;32m" << i + 1 << "  \033[0m";
            for (int j = 0; j < board[i].size(); ++j)
            {
                if (board[i][j] == Player::None)
                {
                    cout << "\033[1;37m \033[0m";
                }
                else if (board[i][j] == Player::X)
                {
                    cout << "\033[1;34mX\033[0m";
                }
                else
                {
                    cout << "\033[1;31mO\033[0m";
                }
                if (j < 2)
                {
                    cout << "\033[1;36m | \033[0m";
                }
            }
            cout << endl;
            if (i < 2)
            {
                cout << "\033[1;36m  ------------\033[0m" << endl;
            }
        }
    }
    // def maxValor(board):
    // def minValor(board):
};

// Implements the changes needed for the undo feature
class StrangeTicTacToe : public TicTacToe
{
private:
    vector<vector<vector<Player>>> history;

public:
    StrangeTicTacToe() : TicTacToe()
    {
        push_to_history(getboard());
    }

    void push_to_history(vector<vector<Player>> state)
    {
        history.push_back(state);
    }

    void playerTurnChange()
    {

        // printBoard();
        if ((jogador(board) == Player::X) && (history.size() > 1))
        {
            board = history[history.size() - 2]; // Get the previous state
            history.pop_back();
            int row, col;
            cout << "Vez do jogador (\033[1;34mX\033[0m) alterar jogada do jogador (\033[1;34mO\033[0m) " << endl
                 << "Escolha a linha que deseja alterar (1-3): ";
            cin >> row;
            cout << "Escolha a coluna que deseja alterar (1-3): " << endl;
            cin >> col;
            playerTurn(row - 1, col - 1);

            printBoard();
        }
    }

    void AITurn()
    {
        // Check if there is a previous state
        if (history.size() > 1)
        {
            board = history[history.size() - 2]; // Get the previous state
            history.pop_back();                  // Remove the current state

            // We need to find the worst move for the player, so if the player is the maximizing player, we need to find the move that minimizes the player's score
            bool maximizingPlayer = jogador(board) == Player::X; // Player::X starts the game and is the maximizing player
            pair<int, pair<int, int>> bestMove = minimax(board, INT_MAX, -INT_MAX, INT_MAX, !maximizingPlayer);
            board = resultado(board, bestMove.second);
            push_to_history(board);

            // Now we need to find the best move for the AI and make it
            bestMove = minimax(board, INT_MAX, -INT_MAX, INT_MAX, !maximizingPlayer);
            board = resultado(board, bestMove.second);
            push_to_history(board);
        }
        else
        {                                                        // If there is no previous state, just play normally
            bool maximizingPlayer = jogador(board) == Player::X; // Player::X starts the game and is the maximizing player
            pair<int, pair<int, int>> bestMove = minimax(board, INT_MAX, -INT_MAX, INT_MAX, maximizingPlayer);
            board = resultado(board, bestMove.second);
            push_to_history(board);
        }
    }

    void playerTurn(int row, int col)
    {
        try
        {
            board = resultado(board, {row, col});
            push_to_history(board);
        }
        catch (const char *msg)
        {
            throw msg;
        }
    }
};

int main()
{
    StrangeTicTacToe game;
    // clear the screen
    cout << "\033[2J\033[1;1H";

    while (!game.final(game.getboard()))
    {
        cout << "board atual: " << endl;
        vector<vector<Player>> board = game.getboard();
        game.printBoard();

        game.playerTurnChange();
        if (game.jogador(board) == Player::X)
        {
            int row, col;
            cout << "Vez do jogador (\033[1;34mX\033[0m)." << endl
                 << "Escolha a linha (1-3): ";
            cin >> row;
            cout << "Escolha a coluna (1-3): ";
            cin >> col;
            try
            {
                game.playerTurn(row - 1, col - 1);
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                continue;
            }
        }
        else
        {
            cout << "Vez da IA (\033[1;31mO\033[0m)." << endl;
            game.AITurn();
        }
        cout << "\033[1;36m-----------------\033[0m" << endl;
        // clear the screen
        cout << "\033[2J\033[1;1H";
    }
    game.printBoard();
    cout << "Fim de jogo!" << endl;

    // Who won?
    if (game.custo(game.getboard()) == 1)
    {
        cout << "Jogador (\033[1;34mX\033[0m) venceu!" << endl;
    }
    else if (game.custo(game.getboard()) == -1)
    {
        cout << "IA (\033[1;31mO\033[0m) venceu!" << endl;
    }
    else
    {
        cout << "Empate!" << endl;
    }

    return 0;
}
