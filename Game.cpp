// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      Project by Abdullah Maqbool(L1F23BSSE0391) TO MAM: ROHA IRFAN!   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <fstream>
using namespace std;

//````````````````````````````````````````````````````````````` Constants Declared: ```````````````````````````````````````````````````````
const int MAX_LIVES = 3;
const char* SCORE_FILE = "scores.txt";
const char* SAVE_FILE = "game_save.txt";


//````````````````````````````````````````````````````````````` Functions Declared `````````````````````````````````````````````````````````
void start_game();
void show_menu();
void show_rules();
void play_game(char name[], char levelChoice[], char** maze, int mazeSize, int position[], int& score, int& lives);
char** load_Maze(char filename[], int& mazeSize, int position[]);
char** allocate_maze(int size);
void deallocate_maze(char** maze, int size);
void showMaze(char** maze, int mazeSize);
void move_Rat(char** maze, int mazeSize, int position[], int& score, int& lives, char direction);
bool is_valid_move(char** maze, int mazeSize, int row, int col);
void update_score(char** maze, int row, int col, int& score, int& lives);
void save_user_score(const char* name, int score);
void show_scores();
void save_game_state(const char name[], const char level[], char** maze, int mazeSize, int position[], int score, int lives);
bool load_game_state(char name[], char level[], char**& maze, int& mazeSize, int position[], int& score, int& lives);
void concatenate(char* filename, char levelChoice[]);
void update_and_show_achievments(int lives, int moves_count, char levelChoice[]);
void end_game();
void getfeedback(char name[]);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~````
int main() {
    char name[20];
    int lives = MAX_LIVES;
    int position[2] = { 0, 0 }; // Current Position
    int score = 0;
    char** maze = nullptr;
    int mazeSize = 0;
    char levelChoice[10]; // Easy,Hard or Medium

    start_game();

    cout << "\n\n\n\t Enter your name: ";
    cin.getline(name, 20);
    char choice;
    do {
        /////////////////////////// MENU  ////////////////////////////
        do {

            show_menu();
            cout << "\n\n\t\t Please Select one of the Following Options(a,b,c,d or f): " << endl;
            cin >> choice;

        } while ((choice != 'a') && (choice != 'b') && (choice != 'c') && (choice != 'd') && (choice != 'e') && (choice != 'f'));

        if ((choice == 'a') || (choice == 'A')) {

            /////////////////////  START NEW GAME  ///////////////////////

            char filename[20];

            do {
                cout << "\n\t\t Select Level: " << endl;
                cout << "\033[32m" << "\t\t\t Easy " << "\033[32m" << endl;
                cout << "\033[36m" << "\t\t\t Medium " << "\033[0m" << endl;
                cout << "\033[91m" << "\t\t\t Hard " << "\033[0m" << endl;
                cin >> levelChoice;
                if ((levelChoice[0] == 'E') || (levelChoice[0] == 'M') || (levelChoice[0] == 'H') || (levelChoice[0] == 'e') || (levelChoice[0] == 'm') || (levelChoice[0] == 'h')) {
                    concatenate(filename, levelChoice);
                    break;
                }
                else {
                    cout << " Invalid Option!\n Please Try again: " << endl;
                }
            } while (true);

            maze = load_Maze(filename, mazeSize, position);
            if (maze == nullptr) {
                cout << "\t\t\t Failed to load maze." << endl;
                return -1;
            }
            play_game(name, levelChoice, maze, mazeSize, position, score, lives);
        }

        /////////////////////  RESUME GAME  ///////////////////////

        else if ((choice == 'b') || (choice == 'B'))
        {
            if (!load_game_state(name, levelChoice, maze, mazeSize, position, score, lives)) {
                cout << "Unable to Load Maze State! " << endl;
                return -1;
            }
            play_game(name, levelChoice, maze, mazeSize, position, score, lives);
        }

        /////////////////////  SHOW SCORE TABLE  ///////////////////////

        else if ((choice == 'c') || (choice == 'C')) {
            show_scores();
        }

        /////////////////////  Game Rules  /////////////////////////////
        else if ((choice == 'd') || (choice == 'D')) {
            show_rules();
        }

        ////////////////////////////  EXIT  ////////////////////////////

        else if ((choice == 'e') || (choice == 'E')) {
            end_game();
            return 0;
        }
        else if ((choice == 'f') || (choice == 'f')) {
            getfeedback(name);
        }
        else
            cout << " \t\t Invalid Option! " << endl;

        deallocate_maze(maze, mazeSize);

        cout << "\033[33m" << "\n\n\n\t Do you want to play? (y/n): \n\n\n" << "\033[0m" << endl;
        cin >> choice;
        if ((choice == 'N') || (choice == 'n')) {
            end_game();
        }
    } while ((choice == 'Y') || (choice == 'y'));

    return 0;
}

//```````````````````````````````````````````````` Function to start Game `````````````````````````````````````````````````````````
void start_game() {
    cout << "\n\n\n";
    cout << "\033[36m" << "\t\t\t\t\t\t        ############################ " << "\033[0m" << endl;
    cout << "\033[36m" << "\t\t\t\t\t\t       <                            >" << "\033[0m" << endl;
    cout << "\033[36m" << "\t\t\t\t\t\t~~~~~~      Welcome to Maze Game!     ~~~~~~" << "\033[0m" << endl;
    cout << "\033[36m" << "\t\t\t\t\t\t       <                            >" << "\033[0m" << endl;
    cout << "\033[36m" << "\t\t\t\t\t\t        ############################ " << "\033[0m" << endl;
    cout << "\n\n";
}

//``````````````````````````````````````````````` Function to show Menu ```````````````````````````````````````````````````````````````````
void show_menu() {
    cout << "\033[92m" << "\t\t\t\t\t\t\t     ~: Main MENU :~                                            " << "\033[0m" << endl << endl;
    cout << "\t\t\t\t  \t   ____________________________________________________  " << endl;
    cout << "\t\t\t\t  \t  |                                                    |" << endl;
    cout << "\033[33m" << "\t\t\t\t   \t> |                 a. Start new Game                  | <" << "\033[0m" << endl;
    cout << "\t\t\t\t \t  |____________________________________________________| " << endl;
    cout << "\t\t\t\t \t   ____________________________________________________  " << endl;
    cout << "\t\t\t\t \t  |                                                    |" << endl;
    cout << "\033[33m" << "\t\t\t\t   \t> |     b. Resume Game(start from where you left)      | <" << "\033[0m" << endl;
    cout << "\t\t\t\t \t  |____________________________________________________| " << endl;
    cout << "\t\t\t\t \t   ____________________________________________________  " << endl;
    cout << "\t\t\t\t \t  |                                                    |" << endl;
    cout << "\033[33m" << "\t\t\t\t   \t> |               c. Show Score Table                  | <" << "\033[0m" << endl;
    cout << "\t\t\t\t \t  |____________________________________________________| " << endl;
    cout << "\t\t\t\t \t   ____________________________________________________  " << endl;
    cout << "\t\t\t\t \t  |                                                    |" << endl;
    cout << "\033[33m" << "\t\t\t\t   \t> |           d. Watch rules to Play Games             | <" << "\033[0m" << endl;
    cout << "\t\t\t\t \t  |____________________________________________________| " << endl;
    cout << "\t\t\t\t \t   ____________________________________________________  " << endl;
    cout << "\t\t\t\t \t  |                                                    |" << endl;
    cout << "\033[33m" << "\t\t\t\t   \t> |                     e. Exit                        | <" << "\033[0m" << endl;
    cout << "\t\t\t\t \t  |____________________________________________________| " << endl;
    cout << "\t\t\t\t\t  |                                                    |" << endl;
    cout << "\033[33m" << "\t\t\t\t   \t> |                 f. Give Feedback                   | <" << "\033[0m" << endl;
    cout << "\t\t\t\t \t  |____________________________________________________| " << endl;

}

//````````````````````````````````````````````````` Function To Concatenate Filename with user choice ````````````````````````````````````````
void concatenate(char* filename, char levelChoice[]) {
    char extension[] = ".txt";
    int i, j;
    for (i = 0; levelChoice[i] != '\0'; i++) {
        filename[i] = levelChoice[i];
    }
    for (j = 0; extension[j] != '\0'; j++) {
        filename[i + j] = extension[j];
    }
    filename[i + j] = '\0';
}

//`````````````````````````````````````````````````````` Function to show Game Rules ``````````````````````````````````````````````````````
void show_rules() {
    cout << "\t\t\t\t\t\t\t ~: RULES :~                                             " << endl << endl;
    cout << "\t\t\t\t      ____________________________________________________     " << endl;
    cout << "\t\t\t\t   > |                                                    | <   " << endl;
    cout << "\t\t\t\t   > |" << "\033[92m" << "                  MAZE GAME RULES         " << "\033[0m" << "          | <   " << endl;
    cout << "\t\t\t\t     |____________________________________________________|    " << endl;
    cout << "\t\t\t\t   > |                                                    | <   " << endl;
    cout << "\t\t\t\t   > | 1. Use the following keys to move the rat:         | <   " << endl;
    cout << "\t\t\t\t   > |    -> Up: 'U' or 'u'                               | <   " << endl;
    cout << "\t\t\t\t   > |    -> Down: 'D' or 'd'                             | <   " << endl;
    cout << "\t\t\t\t   > |    -> Left: 'L' or 'l'                             | <   " << endl;
    cout << "\t\t\t\t   > |    -> Right: 'R' or 'r'                            | <   " << endl;
    cout << "\t\t\t\t   > | 2. Avoid obstacles (represented by '0' or 'M')     | <   " << endl;
    cout << "\t\t\t\t   > | 3. Moving into a monster (represented by 'M')      | <   " << endl;
    cout << "\t\t\t\t   > |    will decrease your score and lives              | <   " << endl;
    cout << "\t\t\t\t   > | 4. Your goal is to navigate the maze and reach     | <   " << endl;
    cout << "\t\t\t\t   > |    the destination (bottom-right corner)           | <   " << endl;
    cout << "\t\t\t\t   > | 5. You have a maximum of 3 lives                   | <   " << endl;
    cout << "\t\t\t\t   > | 6. Press 'S' to save your current game state       | <   " << endl;
    cout << "\t\t\t\t   > |____________________________________________________|    " << endl;
    cout << "\t\t\t\t      ____________________________________________________     " << endl;
    cout << "\t\t\t\t   > |" << "\033[92m" << "                    GOODLUCK!           " << "\033[0m" << "            | <   " << endl;
    cout << "\t\t\t\t     |____________________________________________________|    " << endl;
}

//````````````````````````````````````````````````````` Function to Run game `````````````````````````````````````````````````````````````
void play_game(char name[], char levelChoice[], char** maze, int mazeSize, int position[], int& score, int& lives) {
    char direction;
    int moves_count = 0;
    while (lives > 0) {
        showMaze(maze, mazeSize);
        cout << " \n\tEnter Your Direction (Left(L), Right(R), Up(U) or Down(D)): " << endl;
        cout << "\033[32m" << "\n\t\t Or, Press 'S' to save Game State: " << "\033[0m" << endl;
        cin >> direction;
        if ((direction == 'S') || (direction == 's')) {
            save_game_state(name, levelChoice, maze, mazeSize, position, score, lives);
            break;
        }
        else {
            moves_count++;
        }
        move_Rat(maze, mazeSize, position, score, lives, direction);
        if (position[0] == mazeSize - 1 && position[1] == mazeSize - 1) {

            cout << "\033[32m" << "\t\t\t\t\t __________________________________________________________" << "\033[0m" << endl;
            cout << "\033[32m" << "\t\t\t\t\t|  ______________________________________________________  |" << "\033[0m" << endl;
            cout << "\033[32m" << "\t\t\t\t\t| |>>>>>>>>>>>>>>     CONGRATULATIONS!     <<<<<<<<<<<<<<| |" << "\033[0m" << endl;
            cout << "\033[32m" << "\t\t\t\t\t| |>>>>>>>>      RAT reached the DESTINATION     <<<<<<<<| |" << "\033[0m" << endl;
            cout << "\033[32m" << "\t\t\t\t\t| |______________________________________________________| |" << "\033[0m" << endl;
            cout << "\033[32m" << "\t\t\t\t\t|__________________________________________________________|" << "\033[0m" << endl;
            cout << "\033[95m" << "\n\n\t\t\t\t\t\t     Game Over! Your score: " << score << "\033[0m" << "\n\n\n\n" << endl;

            update_and_show_achievments(lives, moves_count, levelChoice);

            break;
        }
    }
    save_user_score(name, score);
}

//````````````````````````````````````````````````` Function to Allocate Maze Dynamically ````````````````````````````````````````````````
char** allocate_maze(int size) {
    char** maze = new char* [size];
    for (int i = 0; i < size; i++) {
        maze[i] = new char[size];
    }
    return maze;
}

//```````````````````````````````````````````````````` Function to De_Allocate Maze ```````````````````````````````````````````````````````
void deallocate_maze(char** maze, int size) {
    for (int i = 0; i < size; i++) {
        delete[] maze[i];
    }
    delete[] maze;
}

//``````````````````````````````````````````````````````` Function to load maze ```````````````````````````````````````````````````````````
char** load_Maze(char filename[], int& mazeSize, int position[]) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        file >> mazeSize;
        char** maze = allocate_maze(mazeSize);

        // Filling Array:
        for (int i = 0; i < mazeSize; i++) {
            for (int j = 0; j < mazeSize; j++) {
                file >> maze[i][j];
                if (maze[i][j] == 'R') {
                    position[0] = i;
                    position[1] = j;
                }
            }
        }
        file.close();
        return maze;
    }
    else {
        cout << "\t\t\tUnable to open " << filename << " file." << endl;
        return nullptr;
    }
}


//`````````````````````````````````````````````````` Function to Show Maze on console ``````````````````````````````````````````````````````
void showMaze(char** maze, int mazeSize) {
    cout << "\n" << endl;
    cout << "\033[32m" << "\t\t\t\t\t\t  _______________" << "\033[0m" << endl;
    cout << "\033[32m" << "\t\t\t\t\t\t | _____________ |" << "\033[0m" << endl;
    for (int i = 0; i < mazeSize; i++) {
        cout << "\033[32m" << "\t\t\t\t\t\t | | " << "\033[0m";
        // "If statements" is to assign  different colors
        for (int j = 0; j < mazeSize; j++) {
            if (maze[i][j] == 'R')
                cout << "\033[35m" << maze[i][j] << " " << "\033[0m";
            if (maze[i][j] == 'M')
                cout << "\033[91m" << maze[i][j] << " " << "\033[0m";
            if (maze[i][j] == '0')
                cout << "\033[97m" << maze[i][j] << " " << "\033[0m";
            if (maze[i][j] == '1')
                cout << "\033[34m" << maze[i][j] << " " << "\033[0m";
            if (maze[i][j] == 'D')
                cout << "\033[92m" << maze[i][j] << " " << "\033[0m";
        }
        cout << "\033[32m" << "| |" << "\033[0m" << endl;
    }
    cout << "\033[32m" << "\t\t\t\t\t\t | |___________| |" << "\033[0m" << endl;
    cout << "\033[32m" << "\t\t\t\t\t\t |_______________|" << "\033[0m" << endl;
    cout << "\n\n" << endl;
}

//``````````````````````````````````````````````````` Function to move Rat ```````````````````````````````````````````````````````````````
void move_Rat(char** maze, int mazeSize, int position[], int& score, int& lives, char direction) {
    int row = position[0];
    int col = position[1];
    int prev_row = row;
    int prev_col = col;
    if ((direction == 'U') || (direction == 'u')) {
        row -= 1;
    }
    else if ((direction == 'D') || (direction == 'd')) {
        row += 1;
    }
    else if ((direction == 'L') || (direction == 'l')) {
        col -= 1;
    }
    else if ((direction == 'R') || (direction == 'r')) {
        col += 1;
    }
    else {
        cout << "\t\t\t\t*** Invalid direction ***" << endl;
        return;
    }

    if (is_valid_move(maze, mazeSize, row, col)) {
        // Shifting Rat Position:
        if (maze[row][col] != '0' && maze[row][col] != 'M') {
            position[0] = row;
            position[1] = col;
            maze[prev_row][prev_col] = maze[row][col];
            maze[row][col] = 'R';
        }
        update_score(maze, row, col, score, lives);
    }
    else {
        cout << "\033[95m" << "\n\t\t#############################  Invalid move to position (" << row + 1 << ", " << col + 1 << ")  #############################" << "\033[0m" << endl;
        if (maze[row][col] == '0') {
            cout << "\033[91m" << "\n\n \t\t\t\t\t Score decreasd by 1! \n\n\n " << "\033[0m" << endl;
        }
        else if (maze[row][col] == 'M') {
            cout << "\033[36m" << "\n \t\t\t\t\t\t Killed By Monster! \n " << "\033[0m" << endl;
            cout << "\033[91m" << "\n \t\t\t\t\t\t Score decresed by 5! \n " << "\033[0m" << endl;
            lives--;
            cout << "\033[91m" << "\n \t\t\t\t Lives decresed by 1!    " << "\033[94m " << "     Remaining lives: " << "\033[0m " << lives << endl << endl;
            if (lives == 0) {
                cout << "\033[91m" << "\t\t\t\t\t          YOU LOST! " << "\033[0m" << endl;
                cout << "\033[92m" << "\t\t\t\t\t   GOODLUCK FOR NEXT TIME!" << "\033[92m" << endl << endl;
            }
        }
        if (lives != 0)
            cout << " \t\t\t\t\t\t      Try Again:\n\n " << endl;
    }
}

//````````````````````````````````````````` Function to checkout if the move IS VALID OR NOT ````````````````````````````````````````````
bool is_valid_move(char** maze, int mazeSize, int row, int col) {
    if (row < 0 || col < 0 || row >= mazeSize || col >= mazeSize) {
        return false;
    }
    if (maze[row][col] == '0' || maze[row][col] == 'M') {
        return false;
    }
    return true;
}

//````````````````````````````````````````` Function to Update Score user score on each move ``````````````````````````````````````````````
void update_score(char** maze, int row, int col, int& score, int& lives) {
    if (maze[row][col] == 'M') {
        score += -5;
        lives -= 1;
    }
    if (maze[row][col] == '0') {
        score -= 1;
    }
    if (maze[row][col] == '1') {
        score += 5;
    }
}

//````````````````````````````````````````` Function to save user score in file(scores.txt) ````````````````````````````````````````````````
void save_user_score(const char* name, int score) {
    ofstream file(SCORE_FILE, ios::app);
    file << name << ", " << score << endl;
    file.close();
}

//````````````````````````````````````````` Function to save Game State in file(game_save.txt) `````````````````````````````````````````````
void save_game_state(const char name[], const char level[], char** maze, int mazeSize, int position[], int score, int lives) {
    ofstream file(SAVE_FILE);
    file.seekp(0);
    file << name << "," << level << " " << mazeSize << " " << position[0] << " " << position[1] << " " << score << " " << lives << endl;

    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            file << maze[i][j] << " ";
        }
        file << endl;
    }
    cout << "\033[92m" << "\t\t\t\t _____________________________________________________________" << "\033[0m" << endl;
    cout << "\033[92m" << "\t\t\t\t|                                                             |" << "\033[0m" << endl;
    cout << "\033[92m" << "\t\t\t\t|                  Game is saved successfully!                |" << "\033[0m" << endl;
    cout << "\033[92m" << "\t\t\t\t|                       You can leave now!                    |" << "\033[0m" << endl;
    cout << "\033[92m" << "\t\t\t\t|_____________________________________________________________|" << "\033[0m" << endl;
    file.close();
}

//```````````````````````````````````````````````` Function to LOAD SAVED GAME STATE ``````````````````````````````````````````````````````
bool load_game_state(char name[], char level[], char**& maze, int& mazeSize, int position[], int& score, int& lives) {
    ifstream file(SAVE_FILE);
    if (!file.is_open()) {
        return false;
    }
    file.getline(name, 20, ',');
    file >> level >> mazeSize >> position[0] >> position[1] >> score >> lives;
    maze = allocate_maze(mazeSize);

    //```````````````````````````````````````````````````````` Filling Array ``````````````````````````````````````````````````````````````
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            file >> maze[i][j];
        }
    }
    file.close();
    return true;
}

//````````````````````````````````````````````````` Function to show Scores Table `````````````````````````````````````````````````````````
void show_scores() {
    ifstream file(SCORE_FILE);
    if (!file.is_open()) {
        cout << "\t\t\t\t No scores available." << endl;
        return;
    }

    char name[20];
    int score;
    cout << "   Scores:" << endl;
    cout << "___________________________" << endl << endl;
    while (file.getline(name, 20, ',') >> score) {
        cout << name << " --> " << score;
    }
    cout << "\n___________________________" << endl;

    file.close();
}

//``````````````````````````````````````````````` Function to show achievements ```````````````````````````````````````````````````````````
void update_and_show_achievments(int lives, int moves_count, char levelChoice[]) {
    if (lives == MAX_LIVES) {
        cout << "\033[38;5;154m" << " \n\n\t\t\t\t\t    *-*-* SURVIVOR ACHIEVEMENT UNLOCKED! *-*-*" << "\033[0m" << endl;
        cout << "\033[92m" << " \n\n\t\t\t\t\t   -_-_-_- You won a Golden Cheese Trophy! -_-_-_-" << "\033[0m" << endl;

    }
    if ((((levelChoice[0] == 'E') || (levelChoice[0] == 'e') && moves_count == 8) || (levelChoice[0] == 'M') || (levelChoice[0] == 'm') && moves_count == 8) || (levelChoice[0] == 'H') || (levelChoice[0] == 'h') && moves_count == 18) {
        cout << "\033[38;5;154m" << " \n\n\t\t\t\t\t  *-*-* MAZE MASTER ACHIEVEMENT UNLOCKED! *-*-*" << "\033[0m" << endl;
        cout << "\033[92m" << " \n\n\t\t\t\t\t   -_-_-_- You won a Diamond Cheese Trophy! -_-_-_-" << "\033[0m" << endl;

    }

}


//````````````````````````````````````` Function to get Feedback from user and save in the file(feedback.txt) ```````````````````````````````
void getfeedback(char name[]) {
    char feedback[100];
    ofstream file;
    file.open("feedback.txt", ios::app);
    float Rating;
    cout << " \t\t Please Rate this game (out of 10):" << endl;
    cin >> Rating;
    file << " Feedback from the User: (" << name << "): " << endl;
    file << "\n Rating (out of 10): " << Rating << endl;
    cout << "\t\t\t\t\t\n Give Feedback: " << endl;
    cout << "\t\t Write from here :~ ";
    cin.ignore();
    cin.getline(feedback, 100);
    file << feedback;
    file << endl << endl;
    cout << "\033[32m" << " \n\n\t\t\t     |-|-| Thankyou So Much for your Feedback |-|-|" << "\033[0m" << endl;
}

// ```````````````````````````````````````````````````` Function to end Game ``````````````````````````````````````````````````````````````
void end_game() {
    cout << "\033[32m" << "\t\t\t\t|---------------------------------------------------------------------|" << "\033[0m" << endl;
    cout << "\033[94m" << "\n\t\t\t\t\t     Thanks for Visiting Rat in a maze Game \n\n\t\t\t\t\t\t\t   Take Care! " << "\033[0m" << endl;
    cout << "\033[32m" << "\t\t\t\t|---------------------------------------------------------------------|" << "\033[0m" << endl;
}
