/*
Peter Butler
October 6 2020
CS 111
*/

#include <iostream>
#include <cassert>
#include "sudokuboard.h"
#include "stack.h"


//CITE: TA Session with Kenny Talarico
//DESC: Kenny worked through every line of this method, which had major holes
//      in logic. He also helped me debug a few errors that came along after.  

// This method finds values with least amount of numerical options for placement
// so that the solve works most efficiently.
void find_fewest_numerals(sudokuboard sboard, size_t &r, size_t &c)
{
  size_t smallest_val = 100;
  //Nest for loops to create a loop to check every value
  for (size_t i = 0; i < 9; i++){
    for (size_t j = 0; j < 9; j++){
      size_t options = 0;
      //if there is a numerical option between 1 and 9, increase counter.
      for (char val = '1'; val <= '9'; val++){
        if (sboard.can_place(i,j,val))
          options++;
      }
      //update the location of the blank with the least options
      if ((options < smallest_val) && (options > 0)){
        smallest_val = options;
        r = i;
        c = j;
      }
    }
  }
}

//CITE: Conversation with Belal Shaheen '23
//DESC: Belal helped me think through every condition of my board_solve, which
// made me realize certain stack actions that I had been writing incorrectly.

// This method contains the main algorithm for solving the sudoku board.
void board_solve(sudokuboard &sboard)
{
  stack boardstack;
  size_t r = 0;
  size_t c = 0;
  //This value keeps track of the last used value, should the program need to
  //backtrack.
  char last_attempt = '1';
  find_fewest_numerals(sboard, r, c);
  //While board is not fully solved, try numbers. if not, remove from stack
  //and increase the counter.
  while(!sboard.solved()){
    if(last_attempt > '9'){
      last_attempt = boardstack.top();
      boardstack.pop();
      c = boardstack.top();
      boardstack.pop();
      r = boardstack.top();
      boardstack.pop();
      sboard.remove(r,c);
      last_attempt++;
    }
    //if move is safe, add to stack. Reset last_attempt for next iteration.
    else if (sboard.can_place(r,c,last_attempt)){
      sboard.place(r,c,last_attempt);
      boardstack.push(r);
      boardstack.push(c);
      boardstack.push(last_attempt);
      find_fewest_numerals(sboard, r, c);
      last_attempt = '1';
    }
    else{
      last_attempt++;
    }
  }
}


int main()
{
  //Initialize and loop input the board (don't overload cin)
  sudokuboard board = sudokuboard();
  for (size_t r = 0; r < 9; r++) {
    std::string input;
    std::cin >> input;
    for (size_t c = 0; c < 9;c++){
      board.place(r,c,input[c]);
    }
  }

  //call to solve function
  board_solve(board);
  //print statement for tests
  board.write(std::cout);
}
