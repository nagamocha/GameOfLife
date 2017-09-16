/*
    Author: Brandon Nyamwega Mochama
    
    rec01.cpp
 
    Implements Conway's game of life
 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


//************************************************************
//simply prints the board minus the borders
void print_board(const vector<string> &board){
    int number_of_relevant_rows = (int)board.size() - 1;
    int number_of_relevant_columns = (int)board[0].length() - 2;
    for (int row = 1; row < number_of_relevant_rows; row++){
        //we 'slice' the string to exclude the border objects at the end
        cout<< board[row].substr(1,number_of_relevant_columns) << endl;
    }
    cout<<endl;
}

//************************************************************
//replace character in a string with another character
//adopted from user /Kirill V. Lyadvinsky, stackoverflow
void replace_char_in_string(string &row, char char_to_be_replaced, char new_char){
    replace(row.begin(), row.end(), char_to_be_replaced, new_char);
}

//************************************************************
// returns true if board object is alive ie is '*'
bool board_object_state(const char board_object){
    if (board_object == '*'){
        return true;
    }
    else {
        return false;
    }
}

//************************************************************
int number_of_neighbours(const vector<string> &previous_state_board, const int u_row, const int u_column, const bool is_alive){
    int count = 0;
    
    
    for (int row = u_row - 1; row <= u_row + 1; row++){
        for (int column = u_column - 1; column <= u_column + 1; column ++){
            if (previous_state_board[row][column] == '*'){
                count++;
            }
        }
    }
    
    if (is_alive){
        return count - 1;
    }
    else{
        return count;
    }
}

//************************************************************
//this function takes in the parameters 'board' and 'previous board state'
//it uses the previous board state to determine how the board objects should be
//altered in the current generation cycle
void process_board(vector<string> &board, const vector<string> &previous_state_board){
    int number_of_rows = (int)board.size();
    int number_of_columns = (int)board[0].length();
    int no_of_neighbours;
    bool is_alive;
    
    for (int row = 1; row <= number_of_rows-1; row++){
        for (int column = 1; column <= number_of_columns-1; column++){
            
            char board_object = board[row][column];
            
            is_alive = board_object_state(board_object);
            
            no_of_neighbours = number_of_neighbours(previous_state_board, row, column, is_alive);
            
            if (is_alive){
                if (no_of_neighbours < 2 || no_of_neighbours > 3){
                    board[row][column] = ' ';
                }
            }
            
            else{//if board object is not alive
                if (no_of_neighbours == 3){
                    board[row][column] = '*';
                }
            }
        }
    }
}


//************************************************************
int main(){
    
    //******************************************************
    //OPEN FILE
    ifstream initial_state_file("life.txt");
    
    //sanity check if file was opened successfuly
    if (!initial_state_file) {
        cerr << "Could not open the file.\n";
        exit(1); //exit with state 1
    }
    
    //******************************************************
    //READ FILE INTO BOARD
    const int number_of_rows = 10;

    vector<string> board(number_of_rows);
    
    string line;

    //read first line and use it to determine no of  columns
    //we assume that each line of the text file will have the same
    //  number of characters ie each row of the board will have same
    //  number of columns
    //'B' represents the border element
    getline(initial_state_file, line);
    const int number_of_columns = (int)line.length();
    replace_char_in_string(line, '-', ' ');
    board[1] = "B" + line + "B";
    
    //start at 2nd line, since we've already read the first line
    int row = 2;
    while (getline(initial_state_file, line)){
        replace_char_in_string(line, '-', ' ');
        board[row] = "B" + line + "B";
        row++;
    }
    
    //add top and bottom borders
    //int border_length = line.size() + 2;
    string topbottom_border(number_of_columns + 2, 'B');
    board[0] = topbottom_border; //bottome border
    board[9] = topbottom_border; //bottom border
    
    //print initial board
    string footer(number_of_columns, '=');//to beautify printing to screen
    cout << "Initial world" << endl;
    print_board(board);
    cout << footer + "=====" <<endl;
    //******************************************************
    //PROCESS BOARD
    const int total_generations = 10;
    vector<string> previous_state_board = board;
    
    for (int generation = 1; generation <= total_generations; generation++ ){
        process_board(board, previous_state_board);
        previous_state_board = board;
        cout << "Generation: " << generation << endl;
        print_board(board);
        cout << footer << endl;
    }
    
    
    //******************************************************
    //END
    initial_state_file.close();
    return 0;
}



