#include <string.h>
#include <stdlib.h>
#include "include/board.h"
#include "lib/io.h"
#include "lib/timer.h"
#include "libshield/libshield.h"
#include "lib/uart.h"

#define TIC_TAC_TOE

#ifdef TIC_TAC_TOE 

static char ticTacToe[3][3] = {
  {' ', ' ', ' '},
  {' ', ' ', ' '},
  {' ', ' ', ' '}
};

static int row_r = 0, col_r = 0;  // Global variables to store row and column we receive from the python client
static int row_s = 0, col_s = 0 ; // Global variables to store row and column we send to python cliente
static int game_over = 0;
static int winner = 0;

unsigned int my_rand() {
    static unsigned int my_rand_state = 12345; // Initial seed for random number generator
    my_rand_state = (my_rand_state * 1103515245 + 12345) & 0x7fffffff;
    return my_rand_state % 3;
}

int check_win(char player) {
    for (int i = 0; i < 3; ++i) {
        if ((ticTacToe[i][0] == player && ticTacToe[i][1] == player && ticTacToe[i][2] == player) ||
            (ticTacToe[0][i] == player && ticTacToe[1][i] == player && ticTacToe[2][i] == player)) {
            return 1;
        }
    }

    if ((ticTacToe[0][0] == player && ticTacToe[1][1] == player && ticTacToe[2][2] == player) ||
        (ticTacToe[0][2] == player && ticTacToe[1][1] == player && ticTacToe[2][0] == player)) {
        return 1;
    }

    return 0;
}

int check_draw() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ticTacToe[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int evaluate_board() {
    if (check_win('X')) {
        return -1; // Player X wins
    } else if (check_win('O')) {
        return 1; // Player O wins
    } else if (check_draw()) {
        return 0; // Draw
    } else {
        return -2; // Game is still ongoing
    }
}

int minimax(int depth, int is_maximizer) {
    int score = evaluate_board();

    if (score != -2) {
        return score;
    }

    if (depth == 9) {
        return 0; // Maximum depth reached, return neutral score
    }

    if (is_maximizer) {
        int best_score = -1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (ticTacToe[i][j] == ' ') {
                    ticTacToe[i][j] = 'O'; // AI's move
                    best_score = fmax(best_score, minimax(depth + 1, !is_maximizer));
                    ticTacToe[i][j] = ' '; // Undo move
                }
            }
        }
        return best_score;
    } else {
        int best_score = 1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (ticTacToe[i][j] == ' ') {
                    ticTacToe[i][j] = 'X'; // Player's move
                    best_score = fmin(best_score, minimax(depth + 1, !is_maximizer));
                    ticTacToe[i][j] = ' '; // Undo move
                }
            }
        }
        return best_score;
    }
}


void lcd_affichage_char(char c) {
    lcd_printf("%c", c);
}

void lcd_affichage() {
    cls();
    if (!game_over) {
        lcd_printf("row = %d, col = %d", row_s, col_s);
    } else {
        if (winner) {
            lcd_printf("Oh no! I'm the winner!");
        } else {
            lcd_printf("Oops, I lose.");
        }
    }
}


void ft_cb(char c) {

    // Handle special commands and invalid input
    if (c == ',') {
        return;
    } else if (c == 'l') {
        game_over = 1;
        return;
    } else if (c == 'w') {
        game_over = 1;
        winner = 1;
        return;
    } else if (c < '0' || c > '2') { // Invalid input
        return;
    }

    // Process player move
    if (row_r == 0) {
        row_r = c - '0';
    } else if (col_r == 0) {
        col_r = c - '0';
        if (ticTacToe[row_r][col_r] == ' ') {
            ticTacToe[row_r][col_r] = 'X';

            // Loop until the AI makes its move
            while (ticTacToe[row_s][col_s] == ' ') {
                // Find the best move for the AI
                int bestScore = -1000;
                int bestRow = -1;
                int bestCol = -1;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (ticTacToe[i][j] == ' ') {
                            ticTacToe[i][j] = 'O';
                            int score = minimax(0, 0);
                            ticTacToe[i][j] = ' ';

                            if (score > bestScore) {
                                bestScore = score;
                                bestRow = i;
                                bestCol = j;
                            }
                        }
                    }
                }

                if (bestRow != -1 && bestCol != -1) {
                    ticTacToe[bestRow][bestCol] = 'O'; // Place the AI move
                    row_s = bestRow;
                    col_s = bestCol;
                    char row_char = '0' + bestRow;
                    char col_char = '0' + bestCol;
                    uart_putc(_USART2, row_char);
                    uart_putc(_USART2, ',');
                    uart_putc(_USART2, col_char);
                    break; // Exit the loop after AI's move
                }
            }
        }
        row_r = 0;
        col_r = 0;
    }
}


int main() {
    lcd_reset();
    cls();
    uart_init(_USART2, 115200, UART_8N1, ft_cb);
    while (1) {
        lcd_affichage();
    }
    return 0;
}

#endif 
