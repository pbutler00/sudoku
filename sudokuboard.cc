#include "sudokuboard.h"
#include <cassert>
#include <iostream>
#include <cmath>

#define DIM 9


sudokuboard::sudokuboard()
{
  // Make an empty board.  (This constructor provided by Prof. Campbell)
  for (int i=0;i<DIM;i++) {
    rows[i] = "";
    for (int j=0;j<DIM;j++)
      rows[i] = rows[i] + "_";
  }
}
//CITE: TA Session with Kenny Talarico
//DESC: Kenny had me split my original can_place into multiple functions to
//      make my logic more clear. This helped me fix many errors during testing.

//This method returns true if (1) row doesnt have number (2) col doesnt have
//number (3) 9x9 square does not have number
bool sudokuboard::can_place(size_t r,size_t c, char n) const
{

  return ( (rows[r][c] == '_')
    and row_check(r,n)
    and col_check(c,n)
    and mini_puzzle(r, c, n));
}
// This method checks condition 1 of can_place (if row doesnt have number)
bool sudokuboard::row_check(size_t r, char n) const
{
  for(size_t i = 0; i < DIM; i++){
    if (rows[r][i] == n){
      return false;
    }
  }
  return true;
}

// This method checks condition 2 of can_place (if col doesnt have number)
bool sudokuboard::col_check(size_t c, char n) const
{
  for(size_t i = 0; i < DIM; i++){
    if (rows[i][c] == n){
      return false;
    }
  }
  return true;
}

// This method checks condition 3 (if 9x9 square does not have number).
bool sudokuboard::mini_puzzle(size_t r, size_t c, char n) const
{
  //CITE: TA Kenny Talarico
  //DESC: Kenny drew out how I needed to add value to my loops to check each
  //      mini puzzle. He also helped me with the math (int. division) to find
  //      how much to add to each loop. 
  size_t mini_square_r = (r/3) * 3;
  size_t mini_square_c = (c/3) * 3;
  for (size_t i = 0; i < 3 ; i++){
    for (size_t j = 0; j < 3 ; j++){
      if (rows[mini_square_r + i][mini_square_c + j] == n){
        return false;
      }
    }
  }
  return true;
}

bool sudokuboard::solved() const
{
  // This method provided by Professor Campbell
  for (int i=0;i<DIM;i++){
    if (rows[i].find('_')<(size_t)DIM){
      return false;
    }
  }
  return true;
}

void sudokuboard::write(std::ostream & ostr) const
{
  // This method provided by Professor Campbell
  for (int i=0;i<DIM;i++){
    ostr << rows[i] << std::endl;
  }
}
//Places the value on the board by setting the value at (r,c) to n.
void sudokuboard::place(size_t r,size_t c,char n)
{
  rows[r][c]= n;
}
//Returns the value given the location (r,c).
char sudokuboard::get(size_t r,size_t c) const
{
    return rows[r][c];
}
//"Removes" the value from the board by replacing with an empty character.
void sudokuboard::remove(size_t r,size_t c)
{
  rows[r][c] = '_';
}
