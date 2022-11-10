
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG myFloodFill; myFloodFill.readFromFile("../myFloodFill.png");
  FloodFilledImage image(myFloodFill);
  BFS bfs(myFloodFill, Point(273, 54), 0.5);
  MyColorPicker x(1), y(2);
  // image.addFloodFill(bfs, x);
  BFS bfs1(myFloodFill, Point(100, 150), 0.5);
  BFS bfs2(myFloodFill, Point(100, 240), 0.5);
  BFS bfs3(myFloodFill, Point(400, 150), 0.5);
  BFS bfs4(myFloodFill, Point(410, 236), 0.5);
  BFS bfs5(myFloodFill, Point(70, 320), 0.5);
  image.addFloodFill(bfs1, x);
  image.addFloodFill(bfs3, x);
  image.addFloodFill(bfs2, x);
  image.addFloodFill(bfs4, x);
  image.addFloodFill(bfs5, y);
  Animation animation = image.animate(50);
  animation.write("../output.gif");
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("../result.png");
  return 0;
}
