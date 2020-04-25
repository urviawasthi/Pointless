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
  float CalculateColorDifference(cinder::Surface& display, cinder::vec2& original_loc, int original_radius);

 private:
  std::vector<Circle> circles; // vector with all circles
  int num_of_circles = 500;   // number of circles we want to produce
  const int kWidth = 1000;   // width of display
  const int kHeight = 1000;  // height of display
  float array_B[1000][1000]; // array holding all blue values for pixel of image
  float array_G[1000][1000]; // array holding all green values for pixel of image
  float array_R[1000][1000]; // array holding all blue values for pixel of image

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
