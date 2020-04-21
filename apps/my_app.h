// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "../src/Circle.h"

#include <random>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void DrawCircleRandomly();
  void DrawAllCircles();

 private:
  std::random_device rd;     // only used once to initialise (seed) engine
  std::uniform_int_distribution<int> position; // guaranteed unbiased
  std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)

  std::vector<Circle> circles;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
