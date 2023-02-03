#include "Image.h"
#include <math.h>

void Image::lighten() {
    allLighten(0.1);
}

void Image::lighten(double amount) {
    allLighten(amount);
}

void Image::darken() {
    allDarken(0.1);
}

void Image::darken(double amount) {
    allDarken(amount);
}

void Image::saturate() {
    allSaturate(0.1);
}

void Image::saturate(double amount) {
    allSaturate(amount);
}

void Image::desaturate() {
    allDesaturate(0.1);
}

void Image::desaturate(double amount) {
    allDesaturate(amount);
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            getPixel(x, y).s = 0.0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            getPixel(x, y).h += degrees;
            while(getPixel(x, y).h > 360) {
                getPixel(x, y).h -= 360;
            }
            while(getPixel(x, y).h < 0) {
                getPixel(x, y).h += 360;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            int hold = getPixel(x, y).h;
            int orange = 11;
            int blue = 216;
            int diffOrange = std::min(colorDiff(hold, orange), colorDiff(orange, hold));
            int diffBlue = std::min(colorDiff(hold, blue), colorDiff(blue, hold));
            if(diffOrange < diffBlue) {
                getPixel(x, y).h = orange;
            } else {
                getPixel(x, y).h = blue;
            }
        }
    }
}

void Image::scale(double factor) {
    PNG* before = new PNG(*this);
    this->resize(width()*factor, height()*factor);
    if(factor > 0 && factor < 1) {
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                cs225::HSLAPixel beforePixel = before->getPixel(std::ceil(x/factor), std::ceil(y/factor));
                getPixel(x, y).h = beforePixel.h;
                getPixel(x, y).s = beforePixel.s;
                getPixel(x, y).l = beforePixel.l;
                getPixel(x, y).a = beforePixel.a;
            }
        }
    }
    if(factor > 1) {
        for (unsigned x = 0; x < width()/factor; x++) {
            for (unsigned y = 0; y < height()/factor; y++) {
                cs225::HSLAPixel beforePixel = before->getPixel(x, y);
                for (unsigned i = 0; i < std::ceil(factor); i++) {
                    for (unsigned j = 0; j < std::ceil(factor); j++) {
                        getPixel(x*factor+i, y*factor+j).h = beforePixel.h;
                        getPixel(x*factor+i, y*factor+j).s = beforePixel.s;
                        getPixel(x*factor+i, y*factor+j).l = beforePixel.l;
                        getPixel(x*factor+i, y*factor+j).a = beforePixel.a;
                    }
                }
            }
        }
    }
    delete before;
    before = NULL;
}

void Image::scale(unsigned w, unsigned h) {
    double factor = std::min((w*1.0)/(width()*1.0), (h*1.0)/(height()*1.0));
    scale(factor);
}

//Helper functions
void Image::allLighten(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if(amount > 1.0) {
                getPixel(x, y).l = 1.0;
            }
            if(getPixel(x, y).l > (1.0 - amount)) {
                getPixel(x, y).l = 1.0;
            } else {
                getPixel(x, y).l += amount;
            }
        }
    }
}

void Image::allDarken(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if(amount > 1.0) {
                getPixel(x, y).l = 0.0;
            }
            if(getPixel(x, y).l < (0.0 + amount)) {
                getPixel(x, y).l = 0.0;
            } else {
                getPixel(x, y).l -= amount;
            }
        }
    }
}

void Image::allSaturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if(amount > 1.0) {
                getPixel(x, y).s = 1.0;
            }
            if(getPixel(x, y).s > (1.0 - amount)) {
                getPixel(x, y).s = 1.0;
            } else {
                getPixel(x, y).s += amount;
            }
        }
    }
}

void Image::allDesaturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if(amount > 1.0) {
                getPixel(x, y).s = 0.0;
            }
            if(getPixel(x, y).s > (0.0 + amount)) {
                getPixel(x, y).s = 1.0;
            } else {
                getPixel(x, y).s -= amount;
            }
        }
    }
}

int Image::colorDiff(int colorOne, int colorTwo){
    int diff = colorOne - colorTwo;
    if(diff > 360) {
        diff -= 360;
    } else if(diff < 0) {
        diff += 360;
    }
    return diff;
}