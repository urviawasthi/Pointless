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


MyApp::MyApp() { }

void MyApp::setup() {
  // generate all circles and place into a vector
  while (circles.size() < num_of_circles) {
    GenerateCircles();
  }

  // get the image as a surface
  cinder::Surface myPicture(cinder::loadImage("assets/sun.jpg"));
  cinder::Area area( 0, 0, kWidth, kHeight );
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
  cinder::Surface original_display = copyWindowSurface();

  // first hope that correct thing is being captured
  //cinder::gl::draw(cinder::gl::Texture2d::create(original_display));

  // we're going to choose to either change the color, size, or position of a random circle //TODO: change size or position
  int circle_num = cinder::Rand::randInt(num_of_circles);

  // first get the original position, size and color of selected circle
  Circle alter_circle = circles[circle_num];

  float original_r = alter_circle.GetColor().r;
  float original_g = alter_circle.GetColor().g;
  float original_b = alter_circle.GetColor().b;

  cinder::vec2 original_loc = alter_circle.GetLocation();

  int original_radius = alter_circle.GetRadius();

  // randomly choose whether to darken or lighten that color
  circles[circle_num].SetColor(original_r + 0.1f, original_g + 0.1f, original_b + 0.1f); // TODO: also make option for making circle lighter and make less random
  //circles[circle_num].SetColor(r - 0.1f, g - 0.1f, b - 0.1f);

  // save the new display as an image
  cinder::Surface new_display = copyWindowSurface();

  // if the square that we have altered in the new display is closer in color to the original image then we keep it
  // TODO: save stats for old display so that you don't have to recalculate every time!
  int original_difference = CalculateColorDifference(original_display, original_loc, original_radius);
  int new_difference = CalculateColorDifference(new_display, original_loc, original_radius);

  if (new_difference > original_difference) { // the new display is less similar to the original image
    // we undo changes
    circles[circle_num].SetColor(original_r - 0.1f, original_g - 0.1f, original_b - 0.1f); // TODO: also make option for making circle lighter and make less random
  }

  // then we're going to draw all circles
  DrawAllCircles();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::GenerateCircles() {
  // create a vector to hold coordinates for center of circle
  cinder::vec2 location;
  location.x = cinder::Rand::randInt(kWidth);
  location.y = cinder::Rand::randInt(kHeight);

  // now create a circle with above location and add to vector of circles
  Circle circle(location);
  circles.push_back(circle);
}

void MyApp::DrawAllCircles() {
  for (Circle circle : circles) {
    circle.Draw();
  }
}

float MyApp::CalculateColorDifference(cinder::Surface& display, cinder::vec2& original_loc, int original_radius) {
  float total_difference = 0;

  // first get the square that we want to work on
  int x_starting_loc = original_loc.x - original_radius;
  int x_ending_loc = original_loc.x + original_radius;
  int y_starting_loc = original_loc.y - original_radius;
  int y_ending_loc = original_loc.y + original_radius;

  // now compare rgb values of the old / new display with the arrays created earlier
  for (int i = x_starting_loc; i < x_ending_loc; i++) {
    for (int j = y_starting_loc; j < y_ending_loc; j++) {
      total_difference += abs(array_R[i][j] - display.getPixel(cinder::vec2(i, j)).r);
      total_difference += abs(array_B[i][j] - display.getPixel(cinder::vec2(i, j)).b);
      total_difference += abs(array_G[i][j] - display.getPixel(cinder::vec2(i, j)).g);

    }
  }
  return total_difference;
}

}  // namespace myapp
