#include "my_app.h"

#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include "../src/Circle.h"

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using std::vector;

// class variables
int num_of_circles = 500;

MyApp::MyApp() { }

void MyApp::setup() {
  // setup variables to generate random numbers
  position = std::uniform_int_distribution<int> (0, 800); // random position generator
  rng = std::mt19937 (rd());    // random-number engine used (Mersenne-Twister in this case)

  while (circles.size() < num_of_circles) {
    GenerateCircles();
  }

  // get the image as a surface
  cinder::Surface myPicture(cinder::loadImage("assets/sun.jpg"));
  cinder::Area area( 0, 0, 500, 500 );
  cinder::Surface::Iter iter = myPicture.getIter( area );

  // iterate through the rgb arrays and fill them with the value at that pixel
  while( iter.line() ) {
    while( iter.pixel() ) {
      int x = iter.x();
      int y = iter.y();
      array_R[x][y] = iter.r() / 255; //TODO: make this float and divide by 255
      array_B[x][y] = iter.b() / 255;
      array_G[x][y] = iter.g() / 255;
    }
  }
}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::clear();

  // save the current display as a surface
  cinder::Surface first_window = copyWindowSurface();

  // first check that correct thing is being captured
  //cinder::gl::draw(cinder::gl::Texture2d::create(first_window));

  // we're going to choose to either change the color, size, or position of a random circle //TODO: change size or position
  int circle_num = cinder::Rand::randInt(num_of_circles);

  // randomly choose whether to darken or lighten that color
  Circle alter_circle = circles[circle_num];
  float r = alter_circle.GetColor().r;
  float g = alter_circle.GetColor().g;
  float b = alter_circle.GetColor().b;
  circles[circle_num].SetColor(r + 0.1f, g + 0.1f, b + 0.1f); // TODO: also make option for making circle lighter and make less random
  //circles[circle_num].SetColor(r - 0.1f, g - 0.1f, b - 0.1f);

  // save the new display as an image
  cinder::Surface second_window = copyWindowSurface();

  // if the square that we have altered in the new display is closer in color to the original image then we keep it
  // compare the color change in the square area where the color of the circle changed

  // else we continue with the old display

  // then we're going to draw all circles
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
