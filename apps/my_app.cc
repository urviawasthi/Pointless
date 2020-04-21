// Copyright (c) 2020 [Urvi Awasthi]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using std::vector;


MyApp::MyApp() { }

void MyApp::setup() {
  // setup variables to generate random numbers
  position = std::uniform_int_distribution<int> (0, 800); // random position generator
  rgb = std::uniform_int_distribution<int> (0, 255); // random rgb generator
  size = std::uniform_int_distribution<int> (20, 40); // random rgb generator

  rng = std::mt19937 (rd());    // random-number engine used (Mersenne-Twister in this case)
}

void MyApp::update() { }

void MyApp::draw() {
  DrawAllCircles();
  DrawCircleRandomly();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawCircleRandomly() {
  cinder::gl::clear();

  // assign a random color
  float red = (float) rgb(rng) / 255;
  float blue = (float) rgb(rng) / 255;
  float green = (float) rgb(rng) / 255;
  cinder::gl::color(Color(red, green, blue));

  // create a vector to hold coordinates for center of circle
  cinder::vec2 location;
  location.x = position(rng);
  location.y = position(rng);

  // assign a random radius for our circle
  float radius = size(rng);
  cinder::gl::drawSolidCircle(location, radius);
}
}  // namespace myapp
