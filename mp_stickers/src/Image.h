/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "cs225/PNG.h"
#include <iostream>
#include <math.h>

class Image: public cs225::PNG {
    public:
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);

    private:
        //Helper Functions
        void allLighten(double amount);
        void allDarken(double amount);
        void allSaturate(double amount);
        void allDesaturate(double amount);
        int colorDiff(int colorOne, int colorTwo);
};