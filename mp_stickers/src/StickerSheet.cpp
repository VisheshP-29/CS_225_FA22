#include "StickerSheet.h"

//Constructors
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    this->maxStickers = max;
    this->basePicture = new Image(picture);
    this->stickerArr = new Image*[max];
    this->xCoord = new unsigned[max];
    this->yCoord = new unsigned[max];
    for (unsigned i = 0; i < max; i++) {
        this->stickerArr[i] = nullptr;
        xCoord[i] = 0;
        yCoord[i] = 0;
    }
}

StickerSheet::~StickerSheet() {
    delete[] this->xCoord;
    xCoord = nullptr;
    delete[] this->yCoord;
    yCoord = nullptr;
    delete[] this->stickerArr;
    this->stickerArr = nullptr;
    delete basePicture;
    basePicture = nullptr;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    this->maxStickers = other.maxStickers;
    this->basePicture = new Image(*other.basePicture);
    this->stickerArr = new Image*[other.maxStickers];
    this->xCoord = new unsigned[other.maxStickers];
    this->yCoord = new unsigned[other.maxStickers];
    for(unsigned i = 0; i < other.maxStickers; i++) {
        this->stickerArr[i] = other.stickerArr[i];
        this->xCoord[i] = other.xCoord[i];
        this->yCoord[i] = other.yCoord[i];
    }
}

//Public functions
const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    if (this == &other) {
        return *this;
    }
    this->maxStickers = other.maxStickers;
    delete basePicture;
    this->basePicture = new Image(*other.basePicture);
    delete[] stickerArr;
    this->stickerArr = new Image*[other.maxStickers];
    delete[] xCoord;
    this->xCoord = new unsigned[other.maxStickers];
    delete[] yCoord;
    this->yCoord = new unsigned[other.maxStickers];
    for (unsigned i = 0; i < other.maxStickers; i++) {
        this->stickerArr[i] = other.stickerArr[i];
        this->xCoord[i] = other.xCoord[i];
        this->yCoord[i] = other.yCoord[i];
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if(maxStickers == max) {
        return;
    }
    Image ** changedstickerVect = new Image*[max];
    unsigned* changedxCoord = new unsigned[max];
    unsigned* changedyCoord = new unsigned[max];

    if(maxStickers < max) {
        for (unsigned i = 0; i < max; i++) {
            if(i < maxStickers && stickerArr[i] != nullptr) {
                changedstickerVect[i] = stickerArr[i];
                changedxCoord[i] = xCoord[i];
                changedyCoord[i] = yCoord[i];
            }
            else {
                changedstickerVect[i] = nullptr;
                changedxCoord[i] = 0;
                changedyCoord[i] = 0;
            }
        }
    }
    if(maxStickers > max) {
        for (unsigned i = 0; i < max; i++) {
            changedstickerVect[i] = stickerArr[i];
            changedxCoord[i] = xCoord[i];
            changedyCoord[i] = yCoord[i];
        }
    }

    this->maxStickers = max;
    delete[] stickerArr;
    stickerArr = changedstickerVect;
    delete[] xCoord;
    this->xCoord = changedxCoord;
    delete[] yCoord;
    this->yCoord = changedyCoord;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    for (unsigned i = 0; i < maxStickers; i++) {
        if(stickerArr[i] == nullptr) {
            delete[] stickerArr[i];
            stickerArr[i] = &sticker;
            xCoord[i] = x;
            yCoord[i] = y;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {  
    if(index >= maxStickers || stickerArr[index] == nullptr || index < 0) {
        return false;
    } 
    xCoord[index] = x;
    yCoord[index] = y;
    return true;

}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= maxStickers || index < 0) {
        return;
    }
    stickerArr[index] = nullptr;
    xCoord[index] = 0;
    yCoord[index] = 0;
}

Image* StickerSheet::getSticker(unsigned index) {
    if(index >= maxStickers || stickerArr[index] == nullptr || index < 0) {
        return nullptr;
    }
    return stickerArr[index];
}

Image StickerSheet::render() const {
    Image renderedImage(*basePicture);
    unsigned renderWidth = basePicture->width();
    unsigned renderHeight = basePicture->height();

    for (unsigned i = 0; i < maxStickers; i++) {
        if (stickerArr[i] != nullptr) {
            if((xCoord[i]+stickerArr[i]->width()) > renderWidth) {
                renderWidth = xCoord[i]+stickerArr[i]->width();
            }
            if((yCoord[i]+stickerArr[i]->height()) > renderHeight) {
                renderHeight = yCoord[i]+stickerArr[i]->height();
            }
        }
    }
    renderedImage.resize(renderWidth, renderHeight);

    if(renderWidth == 0 || renderHeight == 0) {
        return *basePicture;
    }
    
    for (unsigned i = 0; i < maxStickers; i++) {
        if (stickerArr[i] != nullptr) {
            for (unsigned x = 0; x < stickerArr[i]->width(); x++) {
                for (unsigned y = 0; y < stickerArr[i]->height(); y++) {
                    cs225::HSLAPixel & currPixel = stickerArr[i]->getPixel(x, y);
                    if(currPixel.a == 0.0) {
                        continue;
                    }
                    else {
                        cs225::HSLAPixel & newPixel = renderedImage.getPixel(xCoord[i] + x, yCoord[i] + y);
                        newPixel.h = currPixel.h;
                        newPixel.s = currPixel.s;
                        newPixel.l = currPixel.l;
                        newPixel.a = currPixel.a;
                    }
                }
            }
        }
    }
    return renderedImage;
}