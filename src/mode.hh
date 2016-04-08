#pragma once
#include <stdint.h>

template<uint32_t N>
class Mode {
public:
  using type = decltype(N);

private:
  type state;

public:
  explicit Mode(type initial_state = 0) : state(initial_state) { }

  type operator++() { return inc(); }
  type inc() {
    if (state == N - 1) { state = 0; }
    else { state += 1; }
    return state;
  }

  type operator--() { return dec(); }
  type dec() {
    if (state == 0) { state = N - 1; }
    else { state -= 1; }
    return state;
  }

  operator type() const { return get(); }
  type get() const { return state; }
};
