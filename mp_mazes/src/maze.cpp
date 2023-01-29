/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
}

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    int mazeSize = width_ * height_;
    cells_.clear();
    mazeSet.addelements(mazeSize);
    for(int i = 0; i < mazeSize; i++) {
        Cell newCell(true, true);
        cells_.push_back(newCell);
    }

    int numSets = mazeSize;
    while(numSets > 1) {
        int row = rand() % height;
        int col = rand() % width_;
        int wall = rand() % 2;
        if(wall == 0) {
            if(col < (width_ - 1)) {
                int currCellIndex = (row * width_) + col;
                int nextCellIndex = (row * width_) + (col + 1);
                if(mazeSet.find(currCellIndex) != mazeSet.find(nextCellIndex)) {
                    mazeSet.setunion(currCellIndex, nextCellIndex);
                    cells_[currCellIndex].rightWall_ = false;
                    numSets--;
                }
            }
        } else if (wall == 1){
            if(row < (height_ - 1)) {
                int currCellIndex = (row * width_) + col;
                int nextCellIndex = ((row + 1) * width_) + col;
                if(mazeSet.find(currCellIndex) != mazeSet.find(nextCellIndex)) {
                    mazeSet.setunion(currCellIndex, nextCellIndex);
                    cells_[currCellIndex].downWall_ = false;
                    numSets--;
                }
            }
        }
    }
    return;
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if((width_ == 0) || height_ == 0) {
        return false;
    }
    if((dir == 0) && (x < width_)) {
        return !(cells_[(y * width_) + x].rightWall_);
    } else if((dir == 1) && (y < height_)) {
        return !(cells_[(y * width_) + x].downWall_);
    } else if((dir == 2) && (x > 0)) {
        return !(cells_[(y * width_) + (x - 1)].rightWall_);
    } else if((dir == 3) && (y > 0)) {
        return !(cells_[((y - 1) * width_) + x].downWall_);
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if((dir == 0) && (x >= width_ -1)) {
        return;
    }
    if((dir == 1) && (y >= height_ -1)) {
        return;
    }
    if(dir == 0) {
        cells_[(y * width_) + x].rightWall_ = exists;
        return;
    }
    if(dir == 1) {
        cells_[(y * width_) + x].downWall_ = exists;
        return;
    }
    return;
}

vector<int> SquareMaze::solveMaze() {
    vector<int> path;
    unordered_map<int, vector<int>> visitedPaths;
    queue<int> search;
    int smallestX = -1;

    search.push(0);
    visitedPaths[0] = path;

    while(!search.empty()) {
        int currIndex = search.front();
        search.pop();
        int x = currIndex % width_;
        int y = currIndex / width_;
        
        if((y == height_ - 1) && (path.size() < visitedPaths[currIndex].size())) {
            path = visitedPaths[currIndex];
            smallestX = x;
        }
        if((y == height_ - 1) && (path.size() == visitedPaths[currIndex].size()) && (x < smallestX)) {
            path = visitedPaths[currIndex];
            smallestX = x;
        }
    
        if(canTravel(x, y, 0) && (visitedPaths.find(currIndex + 1) == visitedPaths.end())) {
            visitedPaths[currIndex + 1] = visitedPaths[currIndex];
            visitedPaths[currIndex + 1].push_back(0);
            search.push(currIndex + 1);
        }
        if(canTravel(x, y, 1) && (visitedPaths.find(currIndex + width_) == visitedPaths.end())) {
            visitedPaths[currIndex + width_] = visitedPaths[currIndex];
            visitedPaths[currIndex + width_].push_back(1);
            search.push(currIndex + width_);
        }
        if(canTravel(x, y, 2) && (visitedPaths.find(currIndex - 1) == visitedPaths.end())) {
            visitedPaths[currIndex - 1] = visitedPaths[currIndex];
            visitedPaths[currIndex - 1].push_back(2);
            search.push(currIndex - 1);
        }
        if(canTravel(x, y, 3) && (visitedPaths.find(currIndex - width_) == visitedPaths.end())) {
            visitedPaths[currIndex - width_] = visitedPaths[currIndex];
            visitedPaths[currIndex - width_].push_back(3);
            search.push(currIndex - width_);
        }
    }

    return path;
}

PNG* SquareMaze::drawMaze() const {
    PNG* drawnMaze = new PNG((width_ * 10) + 1, (height_ * 10) + 1);
    HSLAPixel tempBlack = HSLAPixel(0, 0, 0);
    for(unsigned toBlack = 0; toBlack < drawnMaze->width(); toBlack++) {
        if((toBlack < 1) || (toBlack > 9)) {
            drawnMaze->getPixel(toBlack, 0) = tempBlack;
        }
    }
    for(unsigned toBlack = 0; toBlack < drawnMaze->height(); toBlack++) {
        drawnMaze->getPixel(0, toBlack) = tempBlack;
    }

    for(int col = 0; col < width_; col++) {
        for(int row = 0; row < height_; row++) {
            if(cells_[(row * width_) + col].rightWall_) {
                for(int k = 0; k <= 10; k++) {
                    drawnMaze->getPixel((col + 1) * 10, (row * 10) + k) = tempBlack;
                }
            }
            if(cells_[(row * width_) + col].downWall_) {
                for(int k = 0; k <= 10; k++) {
                    drawnMaze->getPixel((col * 10) + k, (row + 1) * 10) = tempBlack;
                }
            }
        }
    }
    return drawnMaze;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* drawnMazeWSol = drawMaze();
    vector<int> solution = solveMaze();
    int currDrawX = 5; 
    int currDrawY = 5;
    int solX = 0;
    int solY = 0;
    HSLAPixel tempRed = HSLAPixel(0, 1, 0.5, 1);
    HSLAPixel tempWhite = HSLAPixel(0, 0, 1);

    for(unsigned drawSol = 0; drawSol < solution.size(); drawSol++) {
        int stepDirection = solution[drawSol];
        if(stepDirection == 0) {
            for(int k = 0; k <=10; k++) {
                drawnMazeWSol->getPixel(currDrawX + k, currDrawY) = tempRed;
            }
            currDrawX += 10;
            solX++;
        }
        if (stepDirection == 1) {
            for(int k = 0; k <=10; k++) {
                drawnMazeWSol->getPixel(currDrawX, currDrawY + k) = tempRed;
            }
            currDrawY += 10;
            solY++;
        }
        if (stepDirection == 2) {
            for(int k = 0; k <=10; k++) {
                drawnMazeWSol->getPixel(currDrawX - k, currDrawY) = tempRed;
            }
            currDrawX -= 10;
            solX--;
        }
        if (stepDirection == 3) {
            for(int k = 0; k <=10; k++) {
                drawnMazeWSol->getPixel(currDrawX, currDrawY - k) = tempRed;
            }
            currDrawY -= 10;
            solY--;
        }
    }
    for(int k = 1; k <= 9; k++) {
        drawnMazeWSol->getPixel((solX * 10) + k, (solY + 1) * 10) = tempWhite;
    }
    return drawnMazeWSol;
}