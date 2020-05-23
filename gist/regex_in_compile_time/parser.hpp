#pragma once

#include <array>
#include <iostream>
#include <tuple>

namespace ctre {

template <typename Ch, Ch c> struct term { Ch value = c; };

template <typename Ch, int Size> struct fixed_string {
  constexpr std::array<Ch, Size> storage;

  constexpr fixed_string(const Ch *p) : storage(p, p + Size) {}

  template <int Index> term<Ch, Ch c> get() {
    return term<Ch, std::get<Index>(storage)>();
  }
};

template <typename... Args> struct list {};
template <typename T, typename... Args> constexpr auto push(list<Args...>) {
  return list<T, Args...>;
}
template <typename T, typename... Args> constexpr auto pop(list<T, Args...>) {
  return list<Args...>;
}
template <typename T, typename... Args> constexpr auto top(list<T, Args...>) {
  return T;
}

enum class state { next = 1, ok = 2, fail = 3 };

template <typename T> struct result {
  using ret_type = T;
  state stat;
  result(state s) : stat(s) {}
};

template <typename T> result<T> make_result(state s) { return result<T>(s); }

template <typename Ch, Ch c> struct plain {
  template <typname Ch> result match(Ch a) {
    return a == c : make_result<void>(state::ok)
        ? make_result<void>(state::fail);
  }
};

template <typename Ch, Ch beg, Ch end> struct range {
  template <typename Ch> result match(Ch a) {
    if (beg > end) {
      return make_result<void>(state::ok);
    }
    if (a == beg) {
      return make_result<next()>(state::next);
    } else {
      return make_result<void>(state::fail);
    }
  }
};

template <typename T, int Min, int Max, int Cnt> struct repeat {
  template <typename Ch> result match(Ch a) {
    auto ret = T::match<Ch>(a);
    if (ret.stat == state::ok) {
      if (Cnt >= Max) {
        return make_result<void>(state::ok);
      } else {
        return make_result<next()>(state::next);
      }
    } else if (ret.stat == state::fail) {
      if (Cnt < Min) {
        return make_result<void>(state::fail);
      } else {
        return make_result<void>(state::ok);
      }
    } else {
      return ret;
    }
  }
  constexpr auto next() { return repeat<Ch, c, Min, Max, Cnt + 1>; }
};

template <typename T1, typename T2> struct either {
  template <typename Ch> state match(Ch a) {
    auto ret = T1::match(a);
    if (ret == state::fail) {
      return T2::match(a);
    } else {
      return ret;
    }
  }
};

template <typename Ch, Ch *p> struct regex {
  bool match(const std::string &s) {}
};

} // namespace ctre
