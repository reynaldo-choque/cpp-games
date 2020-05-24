#ifndef FIGURE_H
#define FIGURE_H

class Figure {
    private:
        int currentFigure;
        struct Point {
            int x, y;
        } current[4], previous[4];
    public:
        Figure();
        void createFigure();
        void rotateFigure(bool, int (&)[31][16]);
        void moveFigure(int, int (&)[31][16]);
        void restorePreviousPosition();
        void increaseAllYPositions();
        void fillFieldWithVisitedPositions(int (&)[31][16], int colorNum);
        bool check(int (&)[31][16]);
        bool isGameOver(int (&)[31][16]);
        int getXPosition(int tile);
        int getYPosition(int tile);
};

#endif // FIGURE_H
