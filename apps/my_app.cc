// Copyright (c) 2020 [Urvi Awasthi]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>


namespace myapp {

using cinder::app::KeyEvent;
using std::vector;

MyApp::MyApp() { }

void MyApp::setup() {
  // setup variables to generate random numbers
  uni = std::uniform_int_distribution<int> (0,255); // guaranteed unbiased
  rng = std::mt19937 (rd());    // random-number engine used (Mersenne-Twister in this case)
}

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawCircleRandomly() {
  // create a vector to hold coordinates for center of circle
  vector<int> vect;
/*  red = uni(rng);
  blue = uni(rng);
  green = uni(rng);
  timer.start();


  const float rnow = red / 255;
  const float bnow = blue / 255;
  const float gnow = green / 255;
  cinder::gl::color(Color(rnow, gnow, bnow));*/
  //cinder::gl::drawSolidCircle();
}
}  // namespace myapp
