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
    //if (!theTiles.size() || !theSource.getRows() || !theSource.getColumns()) return nullptr;
    MosaicCanvas* currMosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    map<Point<3>, int> sourceTileMap;
    vector<Point<3>> currPoints;
    for(size_t i = 0; i < theTiles.size(); i++) {
      Point<3> holdPoint = convertToXYZ(theTiles[i].getAverageColor());
      currPoints.push_back(holdPoint);
      sourceTileMap[holdPoint] = i;
    }

    KDTree<3>* currTree = new KDTree<3>(currPoints);

    for(int row = 0; row < theSource.getRows(); row++) {
      for(int col = 0; col < theSource.getColumns(); col++) {
        Point<3> holdPoint = convertToXYZ(theSource.getRegionColor(row, col));
        Point<3> nearestPoint = currTree->findNearestNeighbor(holdPoint);
        int nearestIndex = sourceTileMap[nearestPoint];
        currMosaic->setTile(row, col, &theTiles[nearestIndex]);
      }
    }
    return currMosaic;
}