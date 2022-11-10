#include "Image.h"
#include<algorithm>

using cs225::HSLAPixel;
using cs225::PNG;

void Image::lighten() { lighten(0.1); }
void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); x ++ ) {
        for (unsigned int y = 0; y < height(); y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);
            if (pixel->l > 1.0 - amount) {
                pixel->l = 1.0;
            } else {
                pixel->l += amount;
            }
        }
    }
}

void Image::darken() { darken(0.1); }
void Image::darken(double amount) {
    for (unsigned int x = 0; x < width(); x ++ ) {
        for (unsigned int y = 0; y < height(); y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);
            if (pixel->l < amount) {
                pixel->l = 0.0;
            } else {
                pixel->l -= amount;
            }
        }
    }
}

void Image::saturate() { saturate(0.1); }
void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); x ++ ) {
        for (unsigned int y = 0; y < height(); y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);
            if (pixel->s > 1.0 - amount) {
                pixel->s = 1.0;
            } else {
                pixel->s += amount;
            }
        }
    }
}

void Image::desaturate() { desaturate(0.1); }
void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); x ++ ) {
        for (unsigned int y = 0; y < height(); y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);
            if (pixel->s < amount) {
                pixel->s = 0.0;
            } else {
                pixel->s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x ++ ) {
        for (unsigned int y = 0; y < height(); y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);
            pixel->s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); x ++ ) {
        for (unsigned int y = 0; y < height(); y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);

            if (pixel->h > 360.0 - degrees) {
                pixel->h -= 360.0;
            } else if (pixel->h < degrees) {
                pixel->h += 360.0;
            }

            pixel->h += degrees;
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < width(); x ++ ) {
        for (unsigned int y = 0; y < height(); y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);
            if (std::abs(pixel->h - 11) >= std::abs(pixel->h - 216)) {
                pixel->h = 216;
            } else {
                pixel->h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int nw = width() * factor;
    unsigned int nh = height() * factor;

    HSLAPixel* newimage = new HSLAPixel[nw * nh];

    for (unsigned int x = 0; x < nw; x ++ ) {
        for (unsigned int y = 0; y < nh; y ++ ) {
            HSLAPixel *pixel = &getPixel(x / factor, y / factor);

            newimage[y * nw + x].l = pixel->l;
            newimage[y * nw + x].h = pixel->h;
            newimage[y * nw + x].s = pixel->s;
            newimage[y * nw + x].a = pixel->a;
        }
    }

    resize(nw, nh);

    for (unsigned int x = 0; x < nw; x ++ ) {
        for (unsigned int y = 0; y < nh; y ++ ) {
            HSLAPixel *pixel = &getPixel(x, y);

            pixel->l = newimage[y * nw + x].l;
            pixel->h = newimage[y * nw + x].h;
            pixel->s = newimage[y * nw + x].s;
            pixel->a = newimage[y * nw + x].a;
        }
    }

    delete[] newimage;
}

void Image::scale(unsigned w, unsigned h) {
    double factor = std::min(static_cast<double>(w) / static_cast<double>(width()), static_cast<double>(h) / static_cast<double>(height()));
    scale(factor);
}