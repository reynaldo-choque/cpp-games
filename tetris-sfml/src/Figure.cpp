#include "Figure.h"
#include <iostream>
using namespace std;

Figure::Figure() {
    createFigure();
}

void Figure::createFigure() {
    int n = rand() % 7;
    int figuresTemplate[7][4] = {
        1, 3, 5, 7,
        2, 4, 5, 7,
        3, 5, 4, 6,
        3, 5, 4, 7,
        2, 3, 5, 7,
        3, 5, 7, 6,
        2, 3, 4, 5
    };
    currentFigure = n;
    for(int i = 0; i < 4; i++) {
        current[i].x = figuresTemplate[n][i] % 2;
        current[i].y = figuresTemplate[n][i] / 2;
    }
}

void Figure::rotateFigure(bool rotate, int (&field)[31][16]) {
    if(rotate && currentFigure != 6) {
        Point pivot = current[1];
        for(int i = 0; i < 4; i++){
            int x = current[i].y - pivot.y;
            int y = current[i].x - pivot.x;
            current[i].x = pivot.x - x;
            current[i].y = pivot.y + y;
        }
        if(!check(field))
            restorePreviousPosition();
    }
}

void Figure::fillFieldWithVisitedPositions(int (&field)[31][16], int colorNum) {
    for(int i = 0; i < 4; i++)
        field[previous[i].y][previous[i].x] = colorNum;
}

void Figure::moveFigure(int dx, int (&field)[31][16]) {
    for(int i = 0; i < 4; i++)
        previous[i] = current[i], current[i].x += dx;
    if(!check(field))
        restorePreviousPosition();
}

void Figure::restorePreviousPosition() {
    for(int i = 0; i < 4; i++)
        current[i] = previous[i];
}

void Figure::increaseAllYPositions() {
    for(int i = 0; i < 4; i++)
        previous[i] = current[i], current[i].y += 1;
}

bool Figure::check(int (&field)[31][16]) {
    for(int i = 0; i < 4; i++){
        if(current[i].x < 0 || current[i].x >= 15 || current[i].y >= 30)
            return false;
        else if( field[current[i].y][current[i].x] )
            return false;
    }
    return true;
}

bool Figure::isGameOver(int (&field)[31][16]) {
    int minimumVisited = 10000000;
    bool hasVisited = false;
    for(int i =0; i < 4; i++){
        minimumVisited = min(minimumVisited,  current[i].y);
        if( field[current[i].y][current[i].x] )
            hasVisited = true;
    }
    if(hasVisited)
        return minimumVisited <= 2;
    return false;
}

int Figure::getXPosition(int tile) {
    return current[tile].x;
}
int Figure::getYPosition(int tile) {
    return current[tile].y;
}

