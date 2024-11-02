#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include "smrt_ptr_tests.hpp"
#include "graphic.hpp"


// Функция для горизонтального отображения легенды в верхней части окна
void draw_legend(sf::RenderWindow& window, sf::Font& font) {
    std::vector<std::pair<std::string, sf::Color>> legends = {
        {"smrt_ptr", sf::Color::Blue},
        {"shrd_ptr", sf::Color::Green},
        {"unique_ptr", sf::Color::Red}
    };

    float legend_x = 50.f;
    float legend_y = 10.f;

    for (const auto& legend : legends) {
        sf::Text legend_text;
        legend_text.setFont(font);
        legend_text.setString(legend.first);
        legend_text.setCharacterSize(14);
        legend_text.setFillColor(legend.second);
        legend_text.setPosition(legend_x, legend_y);
        window.draw(legend_text);
        legend_x += legend_text.getLocalBounds().width + 20.f;
    }
}

// Функция для рисования подписей осей
void draw_axis_labels(sf::RenderWindow& window, sf::Font& font, float padding) {
    // Подпись для оси x - "Количество объектов"
    sf::Text x_label;
    x_label.setFont(font);
    x_label.setString("Counts");
    x_label.setCharacterSize(16);
    x_label.setFillColor(sf::Color::Black);
    x_label.setPosition(window.getSize().x / 2 - 70, window.getSize().y - padding + 30); // Центрируем по x
    window.draw(x_label);

    // Подпись для оси y - "Время (ms)"
    sf::Text y_label;
    y_label.setFont(font);
    y_label.setString("Time (ms)");
    y_label.setCharacterSize(16);
    y_label.setFillColor(sf::Color::Black);
    y_label.setPosition(padding - 50, window.getSize().y / 2 - 100); // Размещаем ближе к оси y
    y_label.setRotation(-90); // Поворачиваем текст на 90 градусов для вертикальной ориентации
    window.draw(y_label);
}

void create_graphic(int start_size, int end_size, int step_size) {
    std::vector<std::pair<long, long>> coordinates_1 = load_smrt_ptr_tests(start_size, end_size, step_size);
    std::vector<std::pair<long, long>> coordinates_2 = load_shrd_ptr_tests(start_size, end_size, step_size);
    std::vector<std::pair<long, long>> coordinates_3 = load_unique_ptr_tests(start_size, end_size, step_size);

    const int window_width = 800;
    const int window_height = 600;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "XY Graphs");

    float min_x = coordinates_1[0].first, max_x = coordinates_1[0].first;
    float min_y = coordinates_1[0].second, max_y = coordinates_1[0].second;
    for (const auto& coords : {coordinates_1, coordinates_2, coordinates_3}) {
        for (const auto& coord : coords) {
            if (coord.first < min_x) min_x = coord.first;
            if (coord.first > max_x) max_x = coord.first;
            if (coord.second < min_y) min_y = coord.second;
            if (coord.second > max_y) max_y = coord.second;
        }
    }

    const float padding = 50.f;
    float scale_x = (window.getSize().x - 2 * padding) / (max_x - min_x);
    float scale_y = (window.getSize().y - 2 * padding) / (max_y - min_y);

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Vladislav\\CLionProjects\\lab1-mephi\\cmake-build-debug\\regular.ttf")) {
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
    }

    sf::Vector2f offset(0.f, 0.f);
    bool is_dragging = false;
    sf::Vector2i previous_mouse_position;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                is_dragging = true;
                previous_mouse_position = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                is_dragging = false;
            }
            if (event.type == sf::Event::MouseMoved && is_dragging) {
                sf::Vector2i current_mouse_position = sf::Mouse::getPosition(window);
                offset.x += (current_mouse_position.x - previous_mouse_position.x);
                offset.y += (current_mouse_position.y - previous_mouse_position.y);
                previous_mouse_position = current_mouse_position;
            }
        }

        window.clear(sf::Color::White);

        sf::VertexArray x_axis(sf::Lines, 2);
        x_axis[0].position = sf::Vector2f(padding + offset.x, window.getSize().y - padding + offset.y);
        x_axis[1].position = sf::Vector2f(window.getSize().x - padding + offset.x, window.getSize().y - padding + offset.y);
        x_axis[0].color = x_axis[1].color = sf::Color::Black;

        sf::VertexArray y_axis(sf::Lines, 2);
        y_axis[0].position = sf::Vector2f(padding + offset.x, padding + offset.y);
        y_axis[1].position = sf::Vector2f(padding + offset.x, window.getSize().y - padding + offset.y);
        y_axis[0].color = y_axis[1].color = sf::Color::Black;

        window.draw(x_axis);
        window.draw(y_axis);

        for (int i = 0; i <= 10; ++i) {
            float x_value = min_x + (max_x - min_x) * i / 10;
            float x_pos = padding + (x_value - min_x) * scale_x + offset.x;

            sf::Text x_label;
            x_label.setFont(font);
            x_label.setString(std::to_string(static_cast<int>(x_value)));
            x_label.setCharacterSize(12);
            x_label.setFillColor(sf::Color::Black);
            x_label.setPosition(x_pos, window.getSize().y - padding + 5 + offset.y);
            window.draw(x_label);

            float y_value = min_y + (max_y - min_y) * i / 10;
            float y_pos = window.getSize().y - padding - (y_value - min_y) * scale_y + offset.y;

            sf::Text y_label;
            y_label.setFont(font);
            y_label.setString(std::to_string(static_cast<int>(y_value)));
            y_label.setCharacterSize(12);
            y_label.setFillColor(sf::Color::Black);
            y_label.setPosition(padding - 30 + offset.x, y_pos - 10);
            window.draw(y_label);
        }

        auto draw_graph = [&](const std::vector<std::pair<long, long>>& coordinates, sf::Color color) {
            sf::VertexArray lines(sf::LinesStrip, coordinates.size());
            for (size_t i = 0; i < coordinates.size(); ++i) {
                float x = padding + (coordinates[i].first - min_x) * scale_x + offset.x;
                float y = window.getSize().y - padding - (coordinates[i].second - min_y) * scale_y + offset.y;
                lines[i].position = sf::Vector2f(x, y);
                lines[i].color = color;

                sf::CircleShape point(3);
                point.setFillColor(color);
                point.setPosition(x - point.getRadius(), y - point.getRadius());
                window.draw(point);
            }
            window.draw(lines);
        };

        draw_graph(coordinates_1, sf::Color::Blue);
        draw_graph(coordinates_2, sf::Color::Green);
        draw_graph(coordinates_3, sf::Color::Red);

        draw_legend(window, font);
        draw_axis_labels(window, font, padding); // Вызов функции для отображения подписей осей

        window.display();
    }

}