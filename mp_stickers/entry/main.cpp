#include "Image.h"
#include "StickerSheet.h"

#include<iostream>

// void help(StickerSheet& myimage, Image& x) {
//   int width = myimage.get_images.at(0)->width();

// }

int main() {


  Image cxk;     cxk.readFromFile("../cxk.png");
  Image i;        i.readFromFile("../i.png");

  for (unsigned x = 0; x < i.width(); ++ x ) {
    for (unsigned y = 0; y < i.height(); ++ y ) {
      i.getPixel(x, y).h = 216.0;
    }
  }
  cxk.scale(2);
  StickerSheet sheet(cxk, 5);
  sheet.addSticker(i, 300, 500);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 350, 500);


  Image ans = sheet.render();

  // for (unsigned x = 0; x < i.width(); ++ x ) {
  //   for (unsigned y = 0; y < i.height(); ++ y ) {
  //     i.getPixel(x, y).h = 216.0;
  //   }
  // }

  ans.writeToFile("../myImage.png");

  return 0;
}