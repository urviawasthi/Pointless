// Copyright (c) 2020 [Urvi Awasthi]. All rights reserved.

#include "Circle.h"

#include <cinder/Rand.h>

Circle::Circle(const cinder::vec2& location){
    this->location = location; // previously set location

    // generate new radius and color here

    // assign a random color
    float red = cinder::Rand::randFloat();
    float blue = cinder::Rand::randFloat();
    float green = cinder::Rand::randFloat();
    this->color = Color(red, green, blue);

    // 2. assign a random radius
    float rand_size = size(rng);
    this->radius = rand_size;

    // 3. assign a certain opacity to the circle
    //TODO: change opacity
}
cinder::vec2 Circle::GetLocation(){
    return this->location;
}
cinder::Color Circle::GetColor(){
    return this->color;
}
float Circle::GetRadius(){
    return this->radius;
}
Circle::Circle(const Circle& circle2) {
  location = circle2.location;
  radius = circle2.radius;
  color = circle2.color;
}
void Circle::Draw() {
  cinder::gl::color(this->GetColor());
  cinder::gl::drawSolidCircle(this->GetLocation(), this->GetRadius());
}
void Circle::SetColor(float r, float g, float b) {
  this->color = Color(r, g, b);
}
