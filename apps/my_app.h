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
  void GenerateCircles();
  void DrawAllCircles();

 private:
  std::random_device rd;     // only used once to initialise (seed) engine
  std::uniform_int_distribution<int> position; // guaranteed unbiased
  std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)

  std::vector<Circle> circles; // vector with all circles
  int array_B[1000][1000]; // array holding all blue values for pixel of image
  int array_G[1000][1000]; // array holding all green values for pixel of image
  int array_R[1000][1000]; // array holding all blue values for pixel of image

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
