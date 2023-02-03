#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  traversalList_.push_back(&traversal);
  colorPickerList_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  PNG tempImage = png_;
  for(unsigned i = 0; i < traversalList_.size(); i++) {
    ImageTraversal* currTraversal = traversalList_[i];
    ColorPicker* currColorPicker = colorPickerList_[i];
    unsigned countFrame = 0;

    for(ImageTraversal::Iterator iter = currTraversal->begin(); iter != currTraversal->end(); ++iter) {
      if(countFrame % frameInterval == 0) {
        animation.addFrame(tempImage);
      }
      HSLAPixel& currPixel = tempImage.getPixel((*iter).x, (*iter).y);
      currPixel = currColorPicker->getColor((*iter).x, (*iter).y);
      countFrame++;
    }
    animation.addFrame(tempImage);
  }
  return animation;
}


// Animation FloodFilledImage::animate(unsigned frameInterval) const {
//   Animation animation;
//   /** @todo [Part 2] */

//   PNG pic = image_;
  
//   for (unsigned i = 0; i < traversal_.size(); ++i) {

//     unsigned int frameNum = 0;
//     ColorPicker* c = colorPicker_[i];
//     ImageTraversal* t = traversal_[i];

//     for (ImageTraversal::Iterator iter = t->begin(); iter != t->end(); ++iter) {

//       if (frameNum % frameInterval == 0) {
//         // frameNum = 0;
//         animation.addFrame(pic);
//       }

//       HSLAPixel& pix = pic.getPixel((*iter).x, (*iter).y);
      
//       pix = c->getColor((*iter).x, (*iter).y);

//       frameNum++;
//     }
//     animation.addFrame(pic);
//   }

//   return animation;
// }