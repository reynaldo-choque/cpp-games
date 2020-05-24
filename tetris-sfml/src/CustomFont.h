#ifndef CUSTOMFONT_H
#define CUSTOMFONT_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class CustomFont {
    private:
        sf::Font font;
        sf::Text text;
        sf::Color color;
        string message;
        int sizeText, xPosition, yPosition;
        bool displayText;
    public:
        CustomFont();
        CustomFont(string, int, int, int, sf::Color );
        void setMessage(string);
        bool displayMessage();
        sf::Text getText();
};

#endif // CUSTOMFONT_H
