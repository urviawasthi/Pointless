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
  cinder::vec2 GetLocation();
  cinder::Color GetColor();
  float GetRadius();
  // Copy constructor
  Circle(const Circle &circle);

 private:
  cinder::vec2 location;
  cinder::Color color;
  float radius;

  // variables for random
  std::random_device rd;     // only used once to initialise (seed) engine
  std::uniform_int_distribution<int> rgb = std::uniform_int_distribution<int> (0, 255); // random rgb generator
  std::uniform_int_distribution<int> size = std::uniform_int_distribution<int> (20, 40); // random rgb generator
  std::mt19937 rng = std::mt19937 (rd());    // random-number engine used (Mersenne-Twister in this case)
};

#endif  // FINALPROJECT_CIRCLE_H