#include <iostream>
using namespace std;

// Node structure for linked list
struct Node {
    char value;  // 'X', 'O', or ' ' (empty)
    int position; // Position (1-9)
    Node* next;

    Node(int pos) : value(' '), position(pos), next(nullptr) {}
};

// Function prototypes
void displayBoard(Node* head);
bool isWinner(Node* head, char player);
bool isDraw(Node* head);
void makeMove(Node* head, char player);

int main() {
    // Create the board as a linked list
    Node* head = new Node(1);
    Node* current = head;
    for (int i = 2; i <= 9; i++) {
        current->next = new Node(i);
        current = current->next;
    }

    char currentPlayer = 'X';
    cout << "Welcome to Tic-Tac-Toe!\n";
    displayBoard(head);

    while (true) {
        makeMove(head, currentPlayer);
        displayBoard(head);

        if (isWinner(head, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            break;
        }

        if (isDraw(head)) {
            cout << "It's a draw! Well played both players.\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Cleanup
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}

// Function to display the board
void displayBoard(Node* head) {
    cout << "\n";
    Node* current = head;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << current->value;
            if (j < 2) cout << " |";
            current = current->next;
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Function to check if the current player has won
bool isWinner(Node* head, char player) {
    int winningCombos[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, // Rows
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, // Columns
        {1, 5, 9}, {3, 5, 7}             // Diagonals
    };

    for (auto& combo : winningCombos) {
        bool win = true;
        for (int pos : combo) {
            Node* current = head;
            while (current && current->position != pos) {
                current = current->next;
            }
            if (!current || current->value != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}

// Function to check if the board is full (draw)
bool isDraw(Node* head) {
    Node* current = head;
    while (current) {
        if (current->value == ' ') return false;
        current = current->next;
    }
    return true;
}

// Function to make a move
void makeMove(Node* head, char player) {
    int pos;
    while (true) {
        cout << "Player " << player << ", enter your move (1-9): ";
        cin >> pos;

        if (pos < 1 || pos > 9) {
            cout << "Invalid position. Try again.\n";
            continue;
        }

        Node* current = head;
        while (current && current->position != pos) {
            current = current->next;
        }

        if (current && current->value == ' ') {
            current->value = player;
            break;
        } else {
            cout << "Position already taken. Try again.\n";
        }
    }
}
