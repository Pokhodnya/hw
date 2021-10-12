#include <set>
#include <forward_list>
#include <algorithm>
#include "sudoku-solver.h"

std::set<int> get_row(const std::vector<std::vector<int>> &field, std::pair<int,int> pos)
{
  int row = pos.first;
  std::set<int> arr;

  for (int i = 0; i < FIELD_SIZE; ++i) {
    arr.insert(field[row][i]);
  }
  arr.erase(0);
  return arr;
}

std::set<int> get_col(const std::vector<std::vector<int>> &field, std::pair<int,int> pos)
{
  int col = pos.second;
  std::set<int> arr;

  for (int i = 0; i < FIELD_SIZE; ++i) {
    arr.insert(field[i][col]);
  }
  arr.erase(0);

  return arr;
}

std::set<int> get_block(const std::vector<std::vector<int>> &field, std::pair<int,int> pos) {
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

std::set<int> find_possible_values(const std::vector<std::vector<int>> &field, std::pair<int,int> pos)
{
  std::set<int> from_row = get_row(field, pos);
  std::set<int> from_col = get_col(field, pos);
  std::set<int> from_block= get_block(field, pos);

  std::set<int> values = {1,2,3,4,5,6,7,8,9};

  for (int value : from_row) {
    auto res = std::find(values.begin(), values.end(), value);
    if (res != std::end(values)) {
      values.erase(value);
    }
  }
  for (int value : from_col) {
    auto res = std::find(values.begin(), values.end(), value);
    if (res != std::end(values)) {
      values.erase(value);
    }
  }
  for (int value : from_block) {
    auto res = std::find(values.begin(), values.end(), value);
    if (res != std::end(values)) {
      values.erase(value);
    }
  }

  return values;
}

int number_of_solutions(std::vector<std::vector<int>> field,
                        std::vector<std::vector<int>> &solution) {
  int sol_count = 0;
  int lowest_PV = 99;
  std::set<int> low_var_PV;
  int row = 0;
  int col = 0;

  for (int i = 0; i < FIELD_SIZE; ++i) {
    for (int j = 0; j < FIELD_SIZE; ++j) {

      if (field[i][j] == 0) {
        std::set<int> values = find_possible_values(field, std::make_pair(i,j));

        if (values.empty()) {
          return 0;
        }

        if (values.size() < lowest_PV) {
          row = i;
          col = j;
          lowest_PV = values.size();
          low_var_PV = values;
        }
      }
    }
  }

  if (low_var_PV.empty()) {
    solution = field;
    return 1;
  }

  for (int value : low_var_PV) {
    field[row][col] = value;
    sol_count += number_of_solutions(field, solution);
  }

  return sol_count;
}

std::pair<size_t, std::vector<std::vector<int>>> sudoku_solve(const std::vector<std::vector<int>> &field) {
  std::vector<std::vector<int>> solution;
  auto count = number_of_solutions(field, solution);

  return std::make_pair(count, solution);
}
