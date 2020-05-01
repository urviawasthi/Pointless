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
  cinder::Surface myPicture(cinder::loadImage("assets/monalisa.jpg"));
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
    //TODO: rename global variables (and local values)
  // we're going to choose to either change the color, size, or location of a random circle
  int what_to_change = cinder::Rand::randInt(2); // rand to decide which factor to change

  int circle_num = cinder::Rand::randInt(num_of_circles); // index of circle we want to change
  Circle alter_circle = circles[circle_num]; // circle we want to change


  // get the original color, location and size of selected circle
  //float original_difference = CalculateColorDifference(alter_circle);
  float original_r = alter_circle.GetColor().r;
  float original_g = alter_circle.GetColor().g;
  float original_b = alter_circle.GetColor().b;

  cinder::vec2 original_loc = alter_circle.GetLocation();

  int original_radius = alter_circle.GetRadius();

  // first get the square that we want to work on
  int x_starting_loc = (original_loc.x - original_radius);
  int x_ending_loc = (original_loc.x + original_radius);
  int y_starting_loc = (original_loc.y - original_radius);
  int y_ending_loc = (original_loc.y + original_radius);

  cinder::Area area( x_starting_loc, y_starting_loc, x_ending_loc, y_ending_loc );

  // initially draw all circles and save as a display
  cinder::gl::clear();
  DrawAllCircles();
  original_display = copyWindowSurface(area);

  if (what_to_change == 0) { // change the color of the circle
    // randomly choose whether to darken or lighten that color (the higher it is the lighter it gets)
    int darken = cinder::Rand::randInt(2);
    // choose which rgb to darken
    int which_val = cinder::Rand::randInt(3);


    if (darken == 1) { // darken the circle
      if (which_val == 0) {
        circles[circle_num].SetColor(original_r - 0.2f, original_g, original_b); // TODO: scale change over time
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
  } else { // change the position of the circle
    cinder::vec2 new_location;
    // choose whether to move up, down, left, or right
    int direction = cinder::Rand::randInt(4);
    if (direction == 0) {
      new_location.x = original_loc.x + 40;
      new_location.y = original_loc.y + 40;
    } else if (direction == 1) {
      new_location.x = original_loc.x + 40;
      new_location.y = original_loc.y - 40;
    } else if (direction == 2) {
      new_location.x = original_loc.x - 40;
      new_location.y = original_loc.y - 40;
    } else {
      new_location.x = original_loc.x - 40;
      new_location.y = original_loc.y + 40;
    }
    // however if new location is off the board, then reset
    if (new_location.x < 0 || new_location.x > kWidth || new_location.y < 0 || new_location.y > kHeight) {
      new_location.x = original_loc.x;
      new_location.y = original_loc.y;
    }
    circles[circle_num].SetLocation(new_location);
  }


  // apply changes
  cinder::gl::clear();
  DrawAllCircles();

  // save the new display as an image
  cinder::Surface new_display = copyWindowSurface(area);

  // if the square that we have altered in the new display is closer in color to the original image then we keep it
  //float original_difference = CalculateColorDifferenceDisplay(original_display);
  //float new_difference = CalculateColorDifferenceDisplay(new_display);

  float original_difference = CalculateColorDifferenceSquare(original_display, original_loc, original_radius);
  float new_difference = CalculateColorDifferenceSquare(new_display, original_loc, original_radius);
  //float new_difference = CalculateColorDifference(circles[circle_num]);
  if (new_difference > original_difference) { // the new display is less similar to the original image
    // need to know what to undo
    if (what_to_change == 0) {
      circles[circle_num].SetColor(original_r, original_g, original_b); // change back the color
    } else {
      circles[circle_num].SetLocation(original_loc);
    }
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
       if (i >= 0 && i < kWidth && j >= 0 && j < kHeight) {
         int iter_x = i / 2;
         int iter_y = j / 2;
         total_difference +=
             abs(array_R[iter_x][iter_y] - (display.getPixel(cinder::vec2(i - x_starting_loc, j - y_starting_loc)).r / 255.0f));
         total_difference +=
             abs(array_B[iter_x][iter_y] - (display.getPixel(cinder::vec2(i - x_starting_loc, j - y_starting_loc)).b / 255.0f));
         total_difference +=
             abs(array_G[iter_x][iter_y] - (display.getPixel(cinder::vec2(i - x_starting_loc, j - y_starting_loc)).g / 255.0f));
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
float MyApp::CalculateColorDifferenceDisplay(cinder::Surface& display) {
  float total_difference = 0;
  // now compare rgb values of the old / new display with the arrays created earlier
  for (int i = 0; i < display.getWidth(); i++) {
    for (int j = 0; j < display.getHeight(); j++) {
      if (i >= 0 && i < 1000 && j >= 0 && j < 1000) {
        int iter_x = i / 2;
        int iter_y = j / 2;
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

}  // namespace myapp
