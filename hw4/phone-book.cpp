#include "phone-book.h"
#include <algorithm>

bool phone_book_t::create_user(const std::string &number, const std::string &name) {
  for (const auto &user : users) {
    if (user.number == number) {
      return false;
    }
  }

  user_t user;
  user.number = number;
  user.name = name;
  users.push_back(user);
  user_info_t user_info;
  user_info.user = user;
  info.push_back(user_info);
  return true;
}

bool phone_book_t::add_call(const call_t &call) {
  for (int i = 0; i < users.size(); i++) {
    if (users[i].number == call.number) {
      calls.push_back(call);
      info[i].total_call_duration_s += call.duration_s;
      return true;
    }
  }
  return false;
}

std::vector<call_t> phone_book_t::get_calls(size_t start_pos, size_t count) const {
  if ((start_pos > calls.size()) | (count == 0)) {
    std::vector<call_t> list;
    return list;
  }
  if ((start_pos + count) > calls.size()) {
    std::vector<call_t> list(calls.begin()+start_pos,calls.end());
    return list;
  }
  std::vector<call_t> list(calls.begin()+start_pos,calls.begin()+start_pos+count);
  return list;
}

std::vector<user_info_t> phone_book_t::search_users_by_number(const std::string &number_prefix, size_t count) const {
  std::vector<user_info_t> sorted(info.begin(),info.end());
  for (int i = 0; i < sorted.size(); i++) {
    for (int j = i+1; j < sorted.size(); j++) {
      if (sorted[j].total_call_duration_s > sorted[i].total_call_duration_s) {
        auto temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j]= temp;
      }
      if (sorted[j].total_call_duration_s == sorted[i].total_call_duration_s) {
        if (sorted[j].user.name < sorted[i].user.name) {
          auto temp = sorted[i];
          sorted[i] = sorted[j];
          sorted[j]= temp;
        }
        if (sorted[j].user.name == sorted[i].user.name) {
          if (sorted[j].user.number < sorted[i].user.number) {
            auto temp = sorted[i];
            sorted[i] = sorted[j];
            sorted[j]= temp;
          }
        }
      }
    }
  }
  if (number_prefix.empty()) {
    std::vector<user_info_t> result(sorted.begin(), sorted.begin()+std::min<size_t>(count, sorted.size()));
    return result;
  }
  std::vector<user_info_t> result2;
  for (const auto& user : sorted) {
    if (user.user.number.rfind(number_prefix,0) == 0) {
      result2.push_back(user);
    }
  }
  std::vector<user_info_t> result3(result2.begin(), result2.begin()+std::min<size_t>(count, result2.size()));
  return result3;
}

std::vector<user_info_t> phone_book_t::search_users_by_name(const std::string &name_prefix, size_t count) const {
  std::vector<user_info_t> sorted(info.begin(),info.end());
  for (int i = 0; i < sorted.size(); i++) {
    for (int j = i+1; j < sorted.size(); j++) {
      if (sorted[j].user.name < sorted[i].user.name) {
        auto temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j]= temp;
      }
      if (sorted[j].user.name == sorted[i].user.name) {
        if (sorted[j].total_call_duration_s > sorted[i].total_call_duration_s) {
          auto temp = sorted[i];
          sorted[i] = sorted[j];
          sorted[j]= temp;
        }
        if (sorted[j].total_call_duration_s == sorted[i].total_call_duration_s) {
          if (sorted[j].user.number < sorted[i].user.number) {
            auto temp = sorted[i];
            sorted[i] = sorted[j];
            sorted[j]= temp;
          }
        }
      }
    }
  }
  if (name_prefix.empty()) {
    std::vector<user_info_t> result(sorted.begin(), sorted.begin()+std::min<size_t>(count, sorted.size()));
    return result;
  }
  std::vector<user_info_t> result;
  for (const auto& user : sorted) {
    if (user.user.name.rfind(name_prefix,0) == 0) {
      result.push_back(user);
    }
  }
  std::vector<user_info_t> result2(result.begin(), result.begin()+std::min<size_t>(count, result.size()));
  return result2;
}

void phone_book_t::clear() {
  users.clear();
  calls.clear();
  info.clear();
}

size_t phone_book_t::size() const {
  return size_t(users.size());
}

bool phone_book_t::empty() const {
  return (users.empty() & calls.empty() & info.empty()) != 0;
}

