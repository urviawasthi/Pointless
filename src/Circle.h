// Copyright (c) 2020 [Urvi Awasthi]. All rights reserved.


#ifndef FINALPROJECT_CIRCLE_H
#define FINALPROJECT_CIRCLE_H

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <random>

using cinder::Color;


class Circle {
 public:
  Circle(const cinder::vec2& location);
  void Draw();
  cinder::vec2 GetLocation();
  cinder::ColorA GetColor();
  void SetColor(float r, float g, float b);
  int GetRadius();
  // Copy constructor
  Circle(const Circle &circle);

 private:
  cinder::vec2 location;
  cinder::ColorA color;
  int radius;
  float opacity;

  // variables for random
  std::random_device rd;     // only used once to initialise (seed) engine
  std::uniform_int_distribution<int> size = std::uniform_int_distribution<int> (90, 100); // random size generator
  std::mt19937 rng = std::mt19937 (rd());    // random-number engine used (Mersenne-Twister in this case)
};

#endif  // FINALPROJECT_CIRCLE_H
