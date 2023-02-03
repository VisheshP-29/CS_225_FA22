#include "Image.h"

#include <iostream>

int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.lighten(0.2);
  alma.writeToFile("../lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.saturate(0.2);
  alma.writeToFile("../saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(2);
  alma.writeToFile("../scale2x.png");

  std::cout << "Using Image::rotateColor to create `rotateColor.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.rotateColor(-3000);
  alma.writeToFile("../rotateColor.png");

  std::cout << "Using Image::illinify to create `illinify.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.illinify();
  alma.writeToFile("../illinify.png");

  std::cout << "Using Image::darken to create `darken.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.darken(0.2);
  alma.writeToFile("../darken.png");
}