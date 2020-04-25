#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include "../src/Circle.h"

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using std::vector;


MyApp::MyApp() { }

void MyApp::setup() {
  // setup variables to generate random numbers
  position = std::uniform_int_distribution<int> (0, 800); // random position generator
  rng = std::mt19937 (rd());    // random-number engine used (Mersenne-Twister in this case)

  while (circles.size() < 1000) {
    GenerateCircles();
  }
}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::clear();
  DrawAllCircles();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::GenerateCircles() {
  // create a vector to hold coordinates for center of circle
  cinder::vec2 location;
  location.x = position(rng);
  location.y = position(rng);

  // now create a circle with above location and add to vector of circles
  Circle circle(location);
  circles.push_back(circle);
}

void MyApp::DrawAllCircles() {
  for (Circle circle : circles) {
    circle.Draw();
  }
}

}  // namespace myapp
