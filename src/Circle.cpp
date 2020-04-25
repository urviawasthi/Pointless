// Copyright (c) 2020 [Urvi Awasthi]. All rights reserved.

#include "Circle.h"

#include <cinder/Rand.h>

Circle::Circle(const cinder::vec2& location){
    this->location = location; // previously set location

    // generate new radius and color here

    // assign an opacity to the circle
    this->opacity = 0.8f;

    // assign a random color
    float red = cinder::Rand::randFloat();
    float blue = cinder::Rand::randFloat();
    float green = cinder::Rand::randFloat();
    this->color = cinder::ColorA(red, green, blue, opacity);

    // assign a random radius
    int rand_size = size(rng);
    this->radius = rand_size;
}
cinder::vec2 Circle::GetLocation(){
    return this->location;
}
cinder::ColorA Circle::GetColor(){
    return this->color;
}
int Circle::GetRadius(){
    return this->radius;
}
Circle::Circle(const Circle& circle2) {
  location = circle2.location;
  radius = circle2.radius;
  color = circle2.color;
  opacity = circle2.opacity;
}
void Circle::Draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::color(this->GetColor());
  cinder::gl::drawSolidCircle(this->GetLocation(), this->GetRadius());
}
void Circle::SetColor(float r, float g, float b) {
  this->color = cinder::ColorA(r, g, b, opacity);
}
