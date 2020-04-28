# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Urvi Awasthi - [`urvia2@illinois.edu`](mailto:urvia2@illinois.edu)

My project will focus on using iterative randomized optimization to recreate full images using only circles. The program will start off by generating a full canvas of randomly sized and colored circles. In each iteration, my program will choose a random circle, and either change the color, size, or location of that circle. It will then compare the original image to the altered image, and if the altered image is closer in appearance to the original image, the next iteration will use the altered image as its new foundation. Else, the program will stick to the original image, and change it in a different way in the next iteration. This same process will be repeated for thousands of iterations.

I want to do this project because I believe that it will be fun to see a computer generate an image from scratch through complete randomness, using nothing but different colors and sizes of circles. I heard about this project from an upperclassman, and I was immediately intrigued. I am excited to see the final output, and compare its similarity to the initial image after thousands of iterations.

This project will be using Cinder's graphic library to generate its circles, and it will be using an additional external library, cimg, or http://cimg.eu/, to help with image processing. I expect the image rendering to take the most time, so a rough timeline would be as follows: by the end of week one, I want to have the main class structure / logic done for the entire program. During weeks two and three, I will put all my focus onto rendering the image. If I have more time, I would like to experiment with different shapes as well.
