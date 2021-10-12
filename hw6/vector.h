#pragma once

template<typename T>

class vector_t {
public:
  vector_t() : vec_capacity(0), pos(0), arr(nullptr) {};

  vector_t(size_t size, const T &fill = T()) {
    if (size) {
      if (size == 1) { vec_capacity = 2; }
      else {
        size_t i = 1;
        for (; i < size; i *= 2) {}
        vec_capacity = i;
      }
      arr = new T[vec_capacity];
      for (size_t j = 0; j < size; ++j) {
        arr[j] = fill;
      }
      pos = size;
    }
    else {
      vec_capacity = 0;
      pos = 0;
      arr = nullptr;
    }
  }

  vector_t(const vector_t &other) {
    if (other.pos) {
      pos = other.pos;
      size_t i = 1;
      for (; i <= pos; i *= 2) {}
      vec_capacity = i;
      arr = new T[vec_capacity];
      for (size_t j = 0; j < pos; ++j) {
        arr[j] = other[j];
      }
    }
    else {
      vec_capacity = 0;
      pos = 0;
      arr = nullptr;
    }
  }

  vector_t &operator=(const vector_t &other) {
    vector_t temp(other);
    swap(temp);
    return *this;
  }

  ~vector_t() {
    delete[] arr;
    arr = nullptr;
    pos = 0;
    vec_capacity = 0;
  }

  const T &operator[](size_t i) const {
    return arr[i];
  }

  T &operator[](size_t i) {
    return arr[i];
  }

  T &front() const {
    return arr[0];
  }

  T &front() {
    return arr[0];
  }

  T &back() const {
    return arr[pos-1];
  }

  T &back() {
    return arr[pos-1];
  }

  const T *data() const {
    return arr;
  }

  T *data() {
    return arr;
  }

  bool empty() const {
    return (pos == 0);
  }

  size_t size() const {
    return pos;
  }

  void reserve(size_t new_cap) {
    if (vec_capacity < new_cap) {
      vector_t temp = vector_t(new_cap);
      temp.pos = pos;
      for (size_t j = 0; j < pos; ++j) {
        temp.arr[j] = arr[j];
      }
      delete[] arr;
      vec_capacity = temp.vec_capacity;
      arr = new T[vec_capacity];
      for (size_t j = 0; j < pos; ++j) {
        arr[j] = temp.arr[j];
      }
    }
  }

  size_t capacity() const {
    return vec_capacity;
  }

  void shrink_to_fit() {
    if (empty()) {
      vec_capacity = 0;
      delete[] arr;
      arr = nullptr;
    }
    else{
      size_t i = 0;
      for (; i < pos; i *= 2) {}
      reserve(i);
    }
  }

  void clear() {
    vec_capacity = 0;
    pos = 0;
    arr = nullptr;
  }

  void insert(size_t where, const T &value) {
    insert(where, 1, value);
  }

  void insert(size_t where, size_t count, const T &value) {
    reserve(pos+count);
    if (where != pos) {
      for (size_t i = 0; i > pos-where+1; ++i) {
        arr[pos+count-i] = arr[pos-i];
      }
    }
    for (size_t j = 0; j < count; ++j) {
      arr[where+j] = value;
    }
    pos += count;
  }

  void erase(size_t where) {
    for (size_t j = where; j < size()-1; ++j) {
      arr[j] = arr[j+1];
    }
    pos -= 1;
  }

  void erase(size_t first, size_t last) {
    if (first != last) {
      if ((last - first) == 1) {
        erase(first);
      }
      else {
        for (size_t j = last; j < pos; ++j) {
          arr[j-(last-first)] = arr[j];
        }
        pos -= (last - first);
      }
    }
  }

  void push_back(const T &value) {
    size_t cap = pos + 1;
    reserve(cap);
    ++pos;
    arr[size()-1] = value;
  }

  void pop_back() {
    --pos;
  }

  void resize(size_t new_size, const T &val = T()) {
    if (size() >= new_size) {
      pos -= (size() - new_size);
    }
    else {
      for (int i = pos; i < new_size; ++i) {
       this->push_back(val);
      }
    }
  }

  void swap(vector_t &vec) {
    size_t temp_pos = vec.pos;
    size_t temp_cap = vec.vec_capacity;
    T *temp_arr = vec.arr;

    vec.pos = pos;
    vec.vec_capacity = vec_capacity;
    vec.arr = arr;

    pos = temp_pos;
    vec_capacity = temp_cap;
    arr = temp_arr;
  }

  friend bool operator<(const vector_t<T> &vec1, const vector_t<T> &vec2) {
    if (vec2.size() > vec1.size()) {
      return true;
    }
    if (vec2.size() == vec1.size()) {
      size_t counter = 0;
      for (int i = 0; i < vec1.size(); ++i) {
        if (vec1[i] > vec2[i]) {
          return false;
        }
        if (vec1[i] == vec2[i]) {
          counter++;
        }
      }
      if (vec1.size() == counter) {
        return false;
      }
    }
    return true;
  }

  friend bool operator>(const vector_t &vec1, const vector_t &vec2) {
    if (vec2.size() < vec1.size()) {
      return true;
    }
    if (vec2.size() == vec1.size()) {
      size_t counter = 0;
      for (int i = 0; i < vec1.size(); ++i) {
        if (vec1[i] < vec2[i]) {
          return false;
        }
        if (vec1[i] == vec2[i]) {
          counter++;
        }
      }
      if (vec1.size() == counter) {
        return false;
      }
    }
    return true;
  }

  friend bool operator<=(const vector_t &vec1, const vector_t &vec2){
    return (!operator>(vec1,vec2));
    }

  friend bool operator>=(const vector_t &vec1, const vector_t &vec2) {
    return (!operator<(vec1,vec2));
  }

  friend bool operator==(const vector_t &vec1, const vector_t &vec2) {
    if (vec1.size() == vec2.size()) {
      for (int i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) {
          return false;
        }
      }
      return true;
    }
    else {
      return false;
    }
  }

  friend bool operator!=(const vector_t &vec1, const vector_t &vec2) {
    return (!operator==(vec1,vec2));
  }

private:
  size_t vec_capacity{};
  size_t pos{};
  T *arr;
};





/*
 * if (vec.size() == size()) {
      for (int i = 0; i < size(); ++i) {
        if (*(this[i]) != vec[i]) {
          return true;
        }
      }
      return false;
    }
    else {
      return true;
    }

    if (vec.size() > size()) {
        return true;
      }
      if (vec.size() == size()) {
        for (int i = 0; i < size(); ++i) {
          if (*(this[i]) > vec[i]) {
            return false;
          }
        }
      }
      return true;

    if (vec.size() < size()) {
      return true;
    }
    if (vec.size() == size()) {
      for (int i = 0; i < size(); ++i) {
        if (*(this[i]) < vec[i]) {
          return false;
        }
      }
    }
    return true;
 */

/*
 *
  void insert(size_t where, const T &value) {
    std::cout << "vec_cap " << vec_capacity << std::endl;
    std::cout << "where " << where << std::endl;
    reserve(pos+1);
    std::cout << "vec_cap " << vec_capacity << std::endl;
    if (where != pos) { // pos may be incremented in constructor
      for (size_t i = pos; i > where; --i ) {
        arr[i] = arr[i-1];
      }
    }
    arr[where] = value;
    pos += 1;
  }

  void insert(size_t where, size_t amount, const T &value) {
    if (amount == 1) {
      insert(where, value);
    }
    else{
      std::cout << "vec_cap " << vec_capacity << std::endl;
      std::cout << "where " << where << std::endl;
      size_t cap = pos + amount;
      reserve(cap);
      std::cout << "vec_cap " << vec_capacity << std::endl;
      if (where != pos) {
        for (size_t i = cap - 1; i > where + amount - 1; --i ) {
          arr[i] = arr[i-amount];
        }
      }
      for (size_t j = where; j > where + amount - 1; --j) {
        arr[j] = value;
      }
      pos = cap;
    }
  }

 */