#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/CustomFont.h"
#include "src/Figure.h"
#include <ctime>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
using namespace sf;

const int M = 30;
const int N = 15;

int field[M + 1][N + 1] = {0};

int checkLines() {
    int k = M - 1, totalLines = 0;
    for(int i = M - 1; i > 0; i--) {
        int cnt = 0;
        for(int j = 0; j < N; j++) {
            if(field[i][j])
                cnt++;
            field[k][j] = field[i][j];
        }
        if(cnt < N )
            k--;
        else
            totalLines++;
    }
    return totalLines;
}

int main(){
    srand(time(0));
    RenderWindow window(VideoMode(420, 542), "Tetris Grame");
    Texture t, t2;
    t.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/background.png");
    Sprite s(t), background(t2);
    s.setTextureRect(IntRect( rand() % 8 * 18, 0, 18, 18));
    int dx = 0, colorNum = 1 + rand() % 7, score = 0;
    bool rotate = false, isOver = false, playSong = false, displayText = true;
    float timer = 0, delay = 0.3;
    Clock clock;

    Music troika;
    if (troika.openFromFile("audio/Troika.ogg"))
        playSong = true;

    if(playSong) {
        troika.setLoop(true);
        troika.play();
    }

    RectangleShape grid[N][M];
    Vector2f cellSize(18, 18);

    Vertex line1[] = {
        Vertex(Vector2f(N * 18, 18)),
        Vertex(Vector2f(N * 18, M * 18))
    };

    Vertex line2[] = {
        Vertex(Vector2f(0, 18)),
        Vertex(Vector2f(18 * N, 18))
    };

    CustomFont gameOver("Game Over !!!", 24, 120, 180, Color::White);
    CustomFont scoreTitle("Score", 35, 300, 50, Color::White);
    CustomFont scoreCount("0", 25, 300, 90, Color::White);

    Figure tetrisFigure;
    while(window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while(window.pollEvent(e)) {
            if(e.type == Event::Closed)
                window.close();
            if(!isOver && e.type == Event::KeyPressed) {
                if(e.key.code == Keyboard::Up) rotate = true;
                else if(e.key.code == Keyboard::Left) dx = -1;
                else if(e.key.code == Keyboard::Right) dx = 1;
            }
        }
        if(isOver) {
            if(troika.getStatus() == 2)
                troika.stop();
            if(displayText){
                if(gameOver.displayMessage())
                    window.draw(gameOver.getText());
                displayText = false;
                window.display();
            }
            continue;
        }
        if(Keyboard::isKeyPressed(Keyboard::Down))
            delay = 0.04;

        tetrisFigure.moveFigure(dx, field);
        tetrisFigure.rotateFigure(rotate, field);

        //advance according time
        if(timer > delay) {
            tetrisFigure.increaseAllYPositions();
            if(tetrisFigure.isGameOver(field))
                isOver = true;
            if(!tetrisFigure.check(field)) {
                tetrisFigure.fillFieldWithVisitedPositions(field, colorNum);
                tetrisFigure.createFigure();
                colorNum = 1 + rand() % 7;
                tetrisFigure.createFigure();
            }
            timer = 0;
        }
        score += checkLines();
        scoreCount.setMessage(to_string(score) );

        dx = 0; rotate = false, delay = 0.3;
        window.clear(Color::White);
        window.draw(background);

        if(scoreTitle.displayMessage())
            window.draw(scoreTitle.getText());
        if(scoreCount.displayMessage())
            window.draw(scoreCount.getText());
        //Grid
        for(int i=0;i<N;i++){
            for(int j=1;j<M;j++){
                grid[i][j].setSize(cellSize);
                grid[i][j].setOutlineColor(Color(255, 255, 255));
                grid[i][j].setFillColor(Color::Transparent);
                grid[i][j].setOutlineThickness(.5f);
                grid[i][j].setPosition(i * cellSize.x, j * cellSize.y);
                window.draw(grid[i][j]);
            }
        }
        window.draw(line1, 2, Lines);
        window.draw(line2, 2, Lines);

        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                if(field[i][j] == 0)
                    continue;
                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18, i * 18);
                window.draw(s);
            }
        }
        for(int i = 0; i < 4; i++) {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s.setPosition(tetrisFigure.getXPosition(i) * 18, tetrisFigure.getYPosition(i) * 18);
            window.draw(s);
        }
        window.display();
    }
    return 0;
}
