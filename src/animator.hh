#pragma once
#include "Arduino.h"

//
// 쉬운 애니메이션 구현을 위한 클래스입니다.
//
//     Animator ani;        // 2초 주기를 갖는 애니메이터 생성 (기본값)
//     Animator ani { 5 };  // 5초 주기를 갖는 애니메이터 생성
//
//     ani.period = 15.0;   // 애니메이션 주기를 '15s'로 설정
//     ani.speed = 2.0;     // 애니메이션 속도를 '2 period/s'로 설정
//
//     void loop() {
//       ani.onLoop();      // Must be called in every loop
//
//       const auto current = ani.get(); // Get current *pos*
//
//       /* Do your jobs here... */
//     }
//
// 모든 Animator 객체는 [0.0, 1.0) 범위 안에서 변하는 숫자, pos를 갖고있습니다.
// pos는 0.0에서 시작하여 시간이 지남에 따라 조금씩 커지고, 1.0이 되는순간
// 0.0으로 돌아옵니다.
//
// Animator 클래스를 쓰기 위해선 매 프레임마다 일정한 간격으로 `onLoop()`
// 메서드를 호출해줘야합니다.
//
// 예제와 같이 `period` 프로퍼티의 값을 조절하여, pos가 증가하는 속도를
// 조절할 수 있습니다. `period`는 pos가 0.0에서 1.0이 되기까지 걸리는
// 시간(주기)이며, 단위는 초(second) 입니다. 기본 주기는 2초입니다.
//
struct Animator {
  using type = double;

private:
  type pos = 0.0;
  type _speed; // Should be initialized with `period` field
  decltype(millis()) prevMillis = millis();

  struct Period {
    type& speed;
    Period(type& ref): speed(ref) { }
    type operator=(type period) { return speed = 1.0/period; }
    operator type() const { return 1.0/speed; }
  };

  struct Speed {
    type& speed;
    Speed(type& ref): speed(ref) { }
    type operator=(type given) { return speed = given; }
    operator type() const { return speed; }
  };

public:
  Period period { _speed };
  Speed speed { _speed };

  explicit Animator(type initial_period = 2.0) {
    period = initial_period;
  }

  void onLoop() {
    const auto currentMillis = millis();
    const auto delta = double(currentMillis - prevMillis) / 1000.0;
    prevMillis = currentMillis;

    pos += _speed * delta;

    if (pos >= 1.0) { pos -= floor(pos); }
  }

  type get() const { return pos; }
};
