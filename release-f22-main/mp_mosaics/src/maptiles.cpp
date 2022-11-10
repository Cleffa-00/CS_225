/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int rows = theSource.getRows(), cols = theSource.getColumns();
    MosaicCanvas* ret = new MosaicCanvas(rows, cols);
    vector<Point<3>> points;

    map<Point<3>, TileImage*> mp;
    for (auto i = theTiles.begin(); i != theTiles.end(); ++ i) {
        Point<3> temp = convertToXYZ(i -> getAverageColor());
        mp[temp] = &*i;
        points.push_back(temp);
    }
    KDTree<3> tree(points);
    for (int i = 0; i < rows; ++ i)
        for (int j = 0; j < cols; ++ j)
            ret -> setTile(i, j, mp[tree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)))]);
            
    return ret;
}

