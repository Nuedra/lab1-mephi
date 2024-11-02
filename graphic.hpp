
#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>

void draw_legend(sf::RenderWindow& window, sf::Font& font);
void draw_axis_labels(sf::RenderWindow& window, sf::Font& font, float padding);
void create_graphic();

#endif //GRAPHIC_HPP
