// Copyright (c) 2020 [Urvi Awasthi]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <iostream>
#include "my_app.h"


using cinder::app::App;
using cinder::app::RendererGl;

using namespace std;

namespace myapp {

const int kSamples = 8;
const int kWidth = 1000;
const int kHeight = 1000;

void SetUp(App::Settings* settings) {
  //TODO: make starting window size of original image
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
