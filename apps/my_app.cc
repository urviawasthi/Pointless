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
  cinder::Surface myPicture(cinder::loadImage("assets/blue.jpg"));
  cinder::Area area( 0, 0, 500, 500 );
  cinder::Surface::Iter iter = myPicture.getIter( area );

  // iterate through the rgb arrays and fill them with the value at that pixel
  while( iter.line() ) {
    while( iter.pixel() ) {
      int x = iter.x();
      int y = iter.y();
      array_R[x][y] = (float) iter.r() / 255;
      array_B[x][y] = (float) iter.b() / 255;
      array_G[x][y] = (float) iter.g() / 255;
    }
  }

}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::clear();
  // first draw all the circles
  DrawAllCircles();

  // save the current display as a surface
  cinder::Surface original_display = copyWindowSurface();

  // we're going to choose to either change the color, size, or position of a random circle //TODO: change size or position
  int circle_num = cinder::Rand::randInt(num_of_circles);

  // first get the original position, size and color of selected circle
  Circle alter_circle = circles[circle_num];

  //float original_difference = CalculateColorDifference(alter_circle);

  float original_r = alter_circle.GetColor().r;
  float original_g = alter_circle.GetColor().g;
  float original_b = alter_circle.GetColor().b;

  cinder::vec2 original_loc = alter_circle.GetLocation();

  int original_radius = alter_circle.GetRadius();

  // randomly choose whether to darken or lighten that color (the higher it is the lighter it gets)
  int darken = cinder::Rand::randInt(2);
  // choose which rgb to darken
  int which_val = cinder::Rand::randInt(3);

  if (darken == 1) { // darken the circle
    if (which_val == 0) {
      circles[circle_num].SetColor(original_r - 0.2f, original_g, original_b);
    } else if (which_val == 1) {
      circles[circle_num].SetColor(original_r, original_g - 0.2f, original_b);
    } else {
      circles[circle_num].SetColor(original_r, original_g, original_b - 0.2f);
    }
  } else { // lighten the circle
    if (which_val == 0) {
      circles[circle_num].SetColor(original_r + 0.2f, original_g, original_b);
    } else if (which_val == 1) {
      circles[circle_num].SetColor(original_r, original_g + 0.2f, original_b);
    } else {
      circles[circle_num].SetColor(original_r, original_g, original_b + 0.2f);
    }
  }

  // apply changes
  cinder::gl::clear();
  DrawAllCircles();

  //TODO: only capture the part of the surface that we have changed
  // save the new display as an image
  cinder::Surface new_display = copyWindowSurface();

  // if the square that we have altered in the new display is closer in color to the original image then we keep it
  float original_difference = CalculateColorDifferenceSquare(original_display, original_loc, original_radius);
  float new_difference = CalculateColorDifferenceSquare(new_display, original_loc, original_radius);
  //float new_difference = CalculateColorDifference(circles[circle_num]);
  if (new_difference > original_difference) { // the new display is less similar to the original image
    circles[circle_num].SetColor(original_r, original_g, original_b);
  }
}

void MyApp::keyDown(KeyEvent event) {
}

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

float MyApp::CalculateColorDifferenceSquare(cinder::Surface& display, cinder::vec2& original_loc, int original_radius) {
  float total_difference = 0;

  // first get the square that we want to work on
  int x_starting_loc = (original_loc.x - original_radius);
  int x_ending_loc = (original_loc.x + original_radius);
  int y_starting_loc = (original_loc.y - original_radius);
  int y_ending_loc = (original_loc.y + original_radius);

   // now compare rgb values of the old / new display with the arrays created earlier
   for (int i = x_starting_loc; i < x_ending_loc; i++) {
     for (int j = y_starting_loc; j < y_ending_loc; j++) {
       if (i >= 0 && i < 1000 && j >= 0 && j < 1000) {
         int iter_x = i / 2;
         int iter_y = j / 2;
         double pixel = display.getPixel(cinder::vec2(i, j)).r;
         total_difference +=
             abs(array_R[iter_x][iter_y] - (display.getPixel(cinder::vec2(i, j)).r / 255.0f));
         total_difference +=
             abs(array_B[iter_x][iter_y] - (display.getPixel(cinder::vec2(i, j)).b / 255.0f));
         total_difference +=
             abs(array_G[iter_x][iter_y] - (display.getPixel(cinder::vec2(i, j)).g / 255.0f));
       }
     }
   }
  return total_difference;
}
float MyApp::CalculateColorDifference(Circle& altered_circle) {
  float total_difference = 0;
  cinder::vec2 original_loc = altered_circle.GetLocation();

  int x = original_loc.x / 2;
  int y = original_loc.y / 2;

  total_difference +=
      abs(array_R[x][y] - altered_circle.GetColor().r);
  total_difference +=
      abs(array_B[x][y] - altered_circle.GetColor().b);
  total_difference +=
      abs(array_G[x][y] - altered_circle.GetColor().g);

  return total_difference;
}

}  // namespace myapp
