#pragma once

#include <cstdint>
#include <iostream>

class number_t {
public:
  // constructors
  number_t() = default;
  number_t(const number_t &other) = default;
  number_t(int64_t num) : val(num) {}
  ~number_t() = default;
  number_t &operator=(const number_t &other) = default;

  // cast operators
  explicit operator bool() const;
  explicit operator int64_t() const;
  explicit operator std::string() const;

  // arithmetical operators
  number_t &operator+=(const number_t &other);
  number_t &operator-=(const number_t &other);
  number_t &operator*=(const number_t &other);
  number_t &operator/=(const number_t &other);
  number_t &operator%=(const number_t &other);
  number_t &operator^=(const number_t &other);
  number_t &operator&=(const number_t &other);
  number_t &operator|=(const number_t &other);
  number_t &operator<<=(const number_t &other);
  number_t &operator>>=(const number_t &other);

  // increment and decrement operators
  number_t &operator++();
  number_t &operator--();
  number_t operator++(int);
  number_t operator--(int);

  // unary operators
  number_t operator+() const;
  number_t operator-() const;
  number_t operator~() const;
  bool operator!() const;

  // stream operators
  friend std::ostream& operator<<(std::ostream &o, const number_t &num);
  friend std::istream& operator>>(std::istream &i, number_t &num);
private:
  // internally stored value
  int64_t val{0};
};

// binary operators
number_t operator+(number_t first, const number_t &second);
number_t operator-(number_t first, const number_t &second);
number_t operator*(number_t first, const number_t &second);
number_t operator/(number_t first, const number_t &second);
number_t operator%(number_t first, const number_t &second);
number_t operator^(number_t first, const number_t &second);
number_t operator&(number_t first, const number_t &second);
number_t operator|(number_t first, const number_t &second);
number_t operator<<(number_t first, const number_t &second);
number_t operator>>(number_t first, const number_t &second);

// logical operators
bool operator<(const number_t &first, const number_t &second);
bool operator>(const number_t &first, const number_t &second);
bool operator<=(const number_t &first, const number_t &second);
bool operator>=(const number_t &first, const number_t &second);
bool operator==(const number_t &first, const number_t &second);
bool operator!=(const number_t &first, const number_t &second);