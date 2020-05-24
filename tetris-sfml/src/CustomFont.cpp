#include "CustomFont.h"

CustomFont::CustomFont() {
}

CustomFont::CustomFont(string _message, int _sizeText, int _xPosition, int _yPosition, sf::Color _color) {
    displayText = font.loadFromFile("fonts/OpenSans.ttf");
    message = _message;
    sizeText = _sizeText;
    xPosition = _xPosition;
    yPosition = _yPosition;
    color = _color;

    if(displayText) {
        text.setFont(font);
        text.setString(message);
        text.setCharacterSize(sizeText);
        text.setFillColor(color);
        text.setStyle(sf::Text::Bold);
        text.setPosition(xPosition, yPosition);
    }
}

 bool CustomFont::displayMessage() {
    return displayText;
 }

 sf::Text CustomFont::getText(){
    return text;
 }

void CustomFont::setMessage(string newMessage) {
    message = newMessage;
    text.setString(message);
}
