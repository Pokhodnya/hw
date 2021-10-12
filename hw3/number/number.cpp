#include "number.h"

// cast operators

number_t::operator bool() const {
  return val;
}

number_t::operator int64_t() const {
  return val;
}

number_t::operator std::string() const {
  return std::to_string(val);
}

// arithmetical operators

number_t &number_t::operator+=(const number_t &other) {
  val += other.val;
  return *this;
}

number_t &number_t::operator-=(const number_t &other) {
  val -= other.val;
  return *this;
}

number_t &number_t::operator*=(const number_t &other) {
  val *= other.val;
  return *this;
}

number_t &number_t::operator/=(const number_t &other) {
  val /= other.val;
  return *this;
}

number_t &number_t::operator%=(const number_t &other) {
  val %= other.val;
  return *this;
}

number_t &number_t::operator^=(const number_t &other) {
  val ^= other.val;
  return *this;
}

number_t &number_t::operator&=(const number_t &other) {
  val &= other.val;
  return *this;
}

number_t &number_t::operator|=(const number_t &other) {
  val |= other.val;
  return *this;
}

number_t &number_t::operator<<=(const number_t &other) {
  val <<= other.val;
  return *this;
}

number_t &number_t::operator>>=(const number_t &other) {
  val >>= other.val;
  return *this;
}

// increment and decrement operators

number_t &number_t::operator++() {
  ++val;
  return *this;
}

number_t &number_t::operator--() {
  --val;
  return *this;
}

number_t number_t::operator++(int) {
  return number_t(val++);
}

number_t number_t::operator--(int) {
  return number_t(val--);
}

// unary operators

number_t number_t::operator+() const {
  return number_t(val);
}

number_t number_t::operator-() const {
  return number_t(-val);
}

number_t number_t::operator~() const {
  return number_t(~val);
}

bool number_t::operator!() const {
  return !val;
}

// binary operators

number_t operator+(number_t first, const number_t &second) {
  return first += second;
}

number_t operator-(number_t first, const number_t &second) {
  return first -= second;
}

number_t operator*(number_t first, const number_t &second) {
  return first *= second;
}

number_t operator/(number_t first, const number_t &second) {
  return first /= second;
}

number_t operator%(number_t first, const number_t &second) {
  return first %= second;
}

number_t operator^(number_t first, const number_t &second) {
  return first ^= second;
}

number_t operator&(number_t first, const number_t &second) {
  return first &= second;
}

number_t operator|(number_t first, const number_t &second) {
  return first |= second;
}

number_t operator<<(number_t first, const number_t &second) {
  return first <<= second;
}

number_t operator>>(number_t first, const number_t &second) {
  return first >>= second;
}

// logical operators

bool operator<(const number_t &first, const number_t &second) {
  return (int64_t)first < (int64_t)second;
}

bool operator>(const number_t &first, const number_t &second) {
  return second < first;
}

bool operator<=(const number_t &first, const number_t &second) {
  return !(first > second);
}

bool operator>=(const number_t &first, const number_t &second) {
  return !(first < second);
}

bool operator==(const number_t &first, const number_t &second) {
  return (first <= second) && (first >= second);
}

bool operator!=(const number_t &first, const number_t &second) {
  return !(first == second);
}

// stream operators

std::ostream& operator<<(std::ostream &o, const number_t &num) {
  o << num.val;
  return o;
}

std::istream& operator>>(std::istream &i, number_t &num) {
  i >> num.val;
  return i;
}