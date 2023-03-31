#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(int x_) {
  xx = x_;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  
  if (xx == 1) {
    return HSLAPixel(248, 0.53, 0.58);
  }
  return HSLAPixel(141,1,0.5,1);
}
