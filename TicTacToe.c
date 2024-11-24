/*
Problem Statement: Dynamic Memory Allocation, Arrays, and Structures: Tic-Tac-Toe Game 
In this programming assignment, you will implement a Tic-Tac-Toe game in C that utilizes dynamic memory 
allocation, arrays, and structures. The game will be played between two players, 'X' and 'O', on a 3x3 grid. The 
program will dynamically allocate memory for the grid and use structures to represent the players and their moves. 
1. Create a structure named Player with the following attributes: 
a. char symbol: To store the player's symbol ('X' or 'O'). 
b. int score: To store the player's score (1 for win, 0 for loss). 
2. Implement a function named initializeGrid that dynamically allocates memory for a 3x3 grid. Initialize the grid 
with empty spaces (' '). 
3. Implement a function named printGrid that takes the dynamically allocated grid as input and prints the current 
state of the Tic-Tac-Toe grid. 
4. Implement a function named checkWin that checks if a player has won the game. It should take the grid and the 
current player's symbol as input and return 1 if the player has won, 0 otherwise. 
5. Implement the main function: 
a. Initialize two instances of the Player structure, one for 'X' and one for 'O'. 
b. Use a loop to alternate between players and allow them to make moves. 
c. For each move, prompt the current player to enter their row and column choices. 
d. Validate the inputs to ensure they are within the valid range and the chosen cell is not already occupied. 
e. After each move, update the grid and print its current state. 
f. Check if the current player has won using the checkWin function. 
g. If a player wins, update their score and display the winner. 
h. If the grid is full and no one has won, display a tie message. 
6. Properly deallocate the dynamically allocated memory for the grid at the end of the program. 
7. Use proper error handling and input validation to handle incorrect user inputs gracefully. 
Note: This assignment focuses on dynamic memory allocation, arrays and structures. Students have to write the 
program in the observation book by their own effort and execute in the lab
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

// Structure to represent a player
typedef struct 
{
    char symbol;  // 'X' or 'O'
    int score;    // 1 for win, 0 for loss
}Player;

// Function prototypes
char** initializeGrid();
void printGrid(char** grid);
void freeGrid(char** grid);
int checkWin(char** grid, char symbol);
int isDraw(char** grid);
int isValidMove(char** grid, int row, int col);
void playGame(Player* player1, Player* player2);
int getValidatedInput(char* prompt, int min, int max);

int main()
 {
    // Initialize two players
    Player player1 = {'X', 0};
    Player player2 = {'O', 0};

    // Start the game
    playGame(&player1, &player2);

    return 0;
}

// Function to dynamically allocate memory for the 3x3 grid
char **initializeGrid() 
{
    char** grid = (char**)malloc(SIZE * sizeof(char));
    if (!grid)
     {
        perror("Failed to allocate memory for grid");
        exit(EXIT_FAILURE);
    }
    int i,j;
    for (i = 0; i < SIZE; i++) 
    {
        grid[i] = (char*)malloc(SIZE * sizeof(char));
        if (!grid[i]) {
            perror("Failed to allocate memory for grid row");
            exit(EXIT_FAILURE);
        }
        for ( j = 0; j < SIZE; j++) 
        {
            grid[i][j] = ' '; // Initialize grid with empty spaces
        }
    }
    return grid;
}

// Function to print the grid
void printGrid(char** grid) 
{
	int i,j;
    printf("\n");
    for (i = 0; i < SIZE; i++) 
    {
        for ( j = 0; j < SIZE; j++) 
        {
            printf(" %c ", grid[i][j]);
            if (j < SIZE - 1) 
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < SIZE - 1) 
        {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

// Function to free the dynamically allocated memory for the grid
void freeGrid(char** grid)
 {
 	int i;
    for (i = 0; i < SIZE; i++) 
    {
        free(grid[i]);
    }
    free(grid);
}

// Function to check if a player has won
int checkWin(char** grid, char symbol)
 {
 	int i;
    for ( i = 0; i < SIZE; i++) 
    {
        // Check rows and columns
        if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
            (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol))
        {
            return 1;
        }
    }
    // Check diagonals
    if ((grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
        (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)) 
        {
        return 1;
    }
    return 0;
}

// Function to check if the game is a draw
int isDraw(char** grid) 
{
	int i,j;
    for ( i = 0; i < SIZE; i++)
     {
        for ( j = 0; j < SIZE; j++) 
        {
            if (grid[i][j] == ' ')
             {
                return 0; // Not a draw if there is an empty space
            }
        }
    }
    return 1; // Draw if no empty spaces
}

// Function to check if a move is valid
int isValidMove(char** grid, int row, int col) 
{
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || grid[row][col] != ' ')
     {
        return 0;
    }
    return 1;
}

// Function to get validated user input
int getValidatedInput(char* prompt, int min, int max) 
{
    int input;
    char term;
    while (1) 
    {
        printf("%s", prompt);
        if (scanf("%d%c", &input, &term) != 2 || term != '\n') 
        {
            while (getchar() != '\n'); // Clear invalid input
            printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
        } else if (input < min || input > max) 
        {
            printf("Input out of range! Please enter a number between %d and %d.\n", min, max);
        } else 
        {
            return input;
        }
    }
}

// Function to play the game
void playGame(Player* player1, Player* player2) 
{
    char** grid = initializeGrid(); // Create the game grid
    Player* currentPlayer = player1;
    int row, col;
    int game_over = 0;

    while (!game_over)
     {
        printGrid(grid);

        // Get validated input from the player
        row = getValidatedInput("Enter row (1-3): ", 1, 3) - 1;
        col = getValidatedInput("Enter column (1-3): ", 1, 3) - 1;

        // Check if the move is valid
        if (!isValidMove(grid, row, col)) 
        {
            printf("Invalid move! The cell is already occupied or out of range. Try again.\n");
            continue;
        }

        // Make the move
        grid[row][col] = currentPlayer->symbol;

        // Check for win or draw
        if (checkWin(grid, currentPlayer->symbol))
         {
            printGrid(grid);
            printf("Player %c wins!\n", currentPlayer->symbol);
            currentPlayer->score += 1;
            printf("Current score: Player X = %d, Player O = %d\n", player1->score, player2->score);
            game_over = 1;
        } 
        else if (isDraw(grid)) 
        {
            printGrid(grid);
            printf("It's a draw!\n");
            game_over = 1;
        } 
        else 
        {
            // Switch players
            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }
    }

    freeGrid(grid); // Free the dynamically allocated memory
}