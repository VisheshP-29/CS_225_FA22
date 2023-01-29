/* Your code here! */
#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include "dsets.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;


class SquareMaze {
  private:
    int width_;
    int height_;
    struct Cell {
      public:
        Cell(bool right, bool down) {
          rightWall_ = right;
          downWall_ = down;
        }
        bool rightWall_;
        bool downWall_;
    };
    vector<Cell> cells_;
    DisjointSets mazeSet;

  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
};