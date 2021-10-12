#include <set>
#include <vector>
#include "field-checker.h"
#include "sudoku-solver.h"

std::set<int> fetch_row(const std::vector<std::vector<int>> &field, std::pair<int,int> pos)
{
  int row = pos.first;
  std::set<int> arr;

  for (int i = 0; i < FIELD_SIZE; ++i) {
    arr.insert(field[row][i]);
  }
  arr.erase(0);
  return arr;
}

std::set<int> fetch_col(const std::vector<std::vector<int>> &field, std::pair<int,int> pos)
{
  int col = pos.second;
  std::set<int> arr;

  for (int i = 0; i < FIELD_SIZE; ++i) {
    arr.insert(field[i][col]);
  }
  arr.erase(0);

  return arr;
}

std::set<int> fetch_block(const std::vector<std::vector<int>> &field, std::pair<int,int> pos) {
  int row = (pos.first / 3) * 3;
  int col = (pos.second / 3) * 3;
  std::set<int> arr;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      arr.insert(field[i + row][j + col]);
    }
  }
  arr.erase(0);
  return arr;
}


bool check_field(const std::vector<std::vector<int>> &init_field, const std::vector<std::vector<int>> &solution) {

  for (int i = 0; i < FIELD_SIZE; ++i) {
    for (int j = 0; j < FIELD_SIZE; ++j) {
      if (init_field[i][j] != 0 && init_field[i][j] != solution[i][j]) {
        return false;
      }
    }
  }

  std::set<int> correct_values = {1,2,3,4,5,6,7,8,9};

  for (int i = 0; i < FIELD_SIZE; ++i) {
    std::set<int> from_row = fetch_row(solution, std::make_pair(i,0));
    if (from_row != correct_values) {
      return false;
    }
  }

  for (int i = 0; i < FIELD_SIZE; ++i) {
    std::set<int> from_col = fetch_col(solution, std::make_pair(0,i));
    if (from_col != correct_values) {
      return false;
    }
  }

  for (int i = 0; i < FIELD_SIZE; i += 3) {
    for (int j = 0; j < FIELD_SIZE; j += 3) {
      std::set<int> from_block = fetch_block(solution, std::make_pair(i,j));
      if (from_block != correct_values) {
        return false;
      }
    }
  }

  return true;
}
