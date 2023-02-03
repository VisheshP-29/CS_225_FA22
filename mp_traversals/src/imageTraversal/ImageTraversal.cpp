#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  currTraversal_ = NULL;
  currPoint_ = Point(0, 0);
  // isDone_ = true;
}

ImageTraversal::Iterator::Iterator(Point& startPoint, PNG& image, double& tolerance, ImageTraversal* traversal) {
  /** @todo [Part 1] */
  startPoint_ = startPoint;
  image_ = image;
  tolerance_ = tolerance;
  currTraversal_ = traversal;
  currPoint_ = startPoint;
  visitedPoints_.resize((image.width() * image.height()), false);
  // visitedPoints_[currPoint_.x + (currPoint_.y * image_.width())] = true;

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!currTraversal_->empty()) {
    currPoint_ = currTraversal_->pop();
    if(checkVisitValid(currPoint_) && !checkVisited(currPoint_)) {
      visitedPoints_[currPoint_.x + (currPoint_.y * image_.width())] = true;

      Point rightPoint = Point(currPoint_.x + 1, currPoint_.y);
      Point bottomPoint = Point(currPoint_.x, currPoint_.y + 1);
      Point leftPoint = Point(currPoint_.x - 1, currPoint_.y);
      Point topPoint = Point(currPoint_.x, currPoint_.y - 1);

      if(checkVisitValid(rightPoint) && !checkVisited(rightPoint)) {
        currTraversal_->add(rightPoint);
      }
      if(checkVisitValid(bottomPoint) && !checkVisited(bottomPoint)) {
        currTraversal_->add(bottomPoint);
      }
      if(checkVisitValid(leftPoint) && !checkVisited(leftPoint)) {
        currTraversal_->add(leftPoint);
      }
      if(checkVisitValid(topPoint) && !checkVisited(topPoint)) {
        currTraversal_->add(topPoint);
      }
    }
  }
  while(!currTraversal_->empty() && checkVisited(currTraversal_->peek())) {
    currTraversal_->pop();
  }
  if(currTraversal_->empty()) {
    return *this;
  }
  currPoint_ = currTraversal_->peek();
  return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currPoint_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool currCheck = true;
  bool otherCheck = true;
  if(currTraversal_ == NULL || currTraversal_->empty()) {
    currCheck = false;
  }
  if(other.currTraversal_ == NULL || other.currTraversal_->empty()) {
    otherCheck = false;
  }
  return !(currCheck == otherCheck);
}

bool ImageTraversal::Iterator::checkVisitValid(const Point& currPoint) {
  if(currPoint.x >= image_.width() || currPoint.y >= image_.height()) {
    return false;
  }
  if(calculateDelta((image_.getPixel(currPoint.x, currPoint.y)), (image_.getPixel(startPoint_.x, startPoint_.y))) >= tolerance_) {
    return false;
  }
  return true;
}

bool ImageTraversal::Iterator::checkVisited(const Point& currPoint) const{
  return visitedPoints_[currPoint.x + (currPoint.y * image_.width())];
}