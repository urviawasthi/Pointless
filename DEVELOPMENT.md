# Development

---
4/22 Focused on making the circles opaque and made them imitate the image that is passed in. 

4/23 Implemented two different methods of making the circles imitate the original image- first one targets each circle separately and compares the color of the circle to the pixel at that position in the original image, and the second one compares the entire area of the circle to the area of the square inside the image. 

4/24 Fixed many basic errors, started modularizing by adding smaller helper functions. 

4/26 Added options to make the circles get larger in size, as well as change position in small increments to imitate the original image. 

4/28 Decreased the size of the surface passed in in order to make program runtime smaller.

4/29 Removed option for decreasing size of circles, instead am looking for a way to rescale calculating differences when the circles are of different sizes, hopefully to make the circle not get continually smaller as time goes on. 

4/30 Added a cinder block, ImGui, in order to set the title of the picture within the window frame. 
