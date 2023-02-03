#include "../src/Image.h"
#include "../src/StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  // Image alma; alma.readFromFile("../tests/alma.png");
  // Image i;    i.readFromFile("../tests/i.png");

  // StickerSheet sheet(alma, 5);
  // sheet.addSticker(i, 20, 200);
  // sheet.changeMaxStickers(7);
  // sheet.render();
  // Image finalSheet = sheet.render();
  // finalSheet.writeToFile("../myImage.png");
  // return 0;

  Image picture;
  Image stickerOne;
  Image stickerTwo;
  Image stickerThree;
  std::cout << "kfkfjdkfjdkjfkd";


  picture.readFromFile("../tests/alma.png");
  stickerOne.readFromFile("../tests/JeffBezosBucketHat.png");
  stickerTwo.readFromFile("../tests/MyMike.png");
  stickerThree.readFromFile("../tests/CryingCorn.png");

  StickerSheet myImage(picture, 5);

  myImage.addSticker(stickerOne, 525, 60);
  myImage.addSticker(stickerTwo, 200, 60);
  myImage.addSticker(stickerThree, 300, 350);
  myImage.changeMaxStickers(7);
  myImage.render();
  Image finalImage = myImage.render();
  finalImage.writeToFile("../myImage.png");
  return 0;
}