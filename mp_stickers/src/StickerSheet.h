/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include<vector>
#define x_ first;
#define y_ second;


class StickerSheet {
    public:
        StickerSheet (const Image &picture, unsigned max);
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        ~StickerSheet ();
        
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image render () const;

        std::vector<Image*> get_images() const { return images; };
        std::vector<std::pair<unsigned, unsigned>> get_poses() const { return poses; };
        unsigned get_max() const { return max_; };
    private:
        unsigned max_;
        Image base;
        std::vector<Image*> images;
        std::vector<std::pair<unsigned, unsigned>> poses;
        
};