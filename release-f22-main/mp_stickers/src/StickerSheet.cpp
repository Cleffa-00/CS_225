#include "StickerSheet.h"
#include "Image.h"
#include "../lib/cs225/HSLAPixel.h"


#include<vector>
#define x_ first;
#define y_ second;

using namespace cs225;

StickerSheet::StickerSheet (const Image &picture, unsigned max) 
    : max_(max + 1) {
        images.push_back(new Image(picture));
        poses.push_back({0, 0});
}

StickerSheet::StickerSheet (const StickerSheet &other) 
    : max_(other.get_max()), images(), poses(other.get_poses()) {
        for (auto i : other.get_images()) { images.push_back(std::move(new Image(*i))); };
    }

const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    max_ = other.get_max();
    for (auto& i : images) {
        delete i;
    }
    images.clear();
    poses = other.get_poses();
    for (auto i : other.get_images()) { images.push_back(std::move(new Image(*i))); };
    return *this;
}

StickerSheet::~StickerSheet () {
    for (auto& image : images) {
        delete image;
    }
}

void StickerSheet::changeMaxStickers (unsigned max) {
    if (images.size() > max + 1) {
        for (unsigned i = images.size() - 1; i >= max + 1; -- i ) {
            delete images.at(i);
            images.pop_back();
            poses.pop_back();
        }
    }
    max_ = max + 1;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
    if (images.size() == max_) return -1;
    images.push_back(std::move(new Image(sticker)));
    poses.push_back({x, y});
    return 0;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index >= images.size()) {
        return false;
    }
    poses[index + 1] = {x, y}; 
    return true;
}

void StickerSheet::removeSticker (unsigned index) {
    
    if (index < 0 || index >= images.size()) return;

    delete images.at(index + 1);
    images.erase(begin(images) + index + 1);
    poses.erase(begin(poses) + index + 1);
}

Image * StickerSheet::getSticker (unsigned index) {
    index ++ ;
    if (index < 0 || index >= images.size()) return NULL;
    return images.at(index);
}

Image StickerSheet::render () const {


    unsigned w = images.at(0)->width();
    unsigned h = images.at(0)->height();

    Image to_return(*images.at(0));

    for (unsigned i = 1; i < images.size(); ++ i ) {
        unsigned nw = images.at(i)->width() + poses.at(i).x_;
        unsigned nh = images.at(i)->height() + poses.at(i).y_;

        if (nw > w) w = nw;
        if (nh > h) h = nh;
    }

    to_return.resize(w, h);

    for (unsigned i = 1; i < images.size(); ++ i) {
        unsigned sx = poses.at(i).x_;
        unsigned sy = poses.at(i).y_;

        for (unsigned x = 0; x < images.at(i)->width(); ++ x ) {
            for (unsigned y = 0; y < images.at(i)->height(); ++ y ) {

                HSLAPixel* a = &images.at(i)->getPixel(x, y);

                if (a->a == 0.0) continue;

                HSLAPixel* b = &to_return.getPixel(sx + x, sy + y);

                b->h = a->h;
                b->l = a->l;
                b->a = a->a;
                b->s = a->s;
            }
        }
    }
    
    return to_return;
}