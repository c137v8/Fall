#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include "colisiondetection.hpp"


const float g = 2000.81f;   // Accleration due to gravity
const float initialHeight = 500.0f;  // Initial height of ball
const float ballRadius = 20.0f;  // Radius of the ball 
const float initialVelocity = 200.0f;  // Initial velocity of ball
col::collision c; // Colision detection object

int main() {
    // Render the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fall");

    // Create a rectangle
    sf::RectangleShape rectangle(sf::Vector2f(400, 20));
    rectangle.setPosition(((window.getSize().x)/2)-200, (window.getSize().y)-180);
    rectangle.setFillColor( sf::Color::Red);
    
    // Create a ball
    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400 - ballRadius, initialHeight);  // Start in the middle
   
   // Inisilizing sound file 
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("kick23.wav")) {
        std::cerr << "Error: Could not load sound file!" << std::endl;
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    // Initial conditions
    float velocity = initialVelocity;  // Initial velocity (pixels/s)
    float height = initialHeight;  // Initial height (pixels)

    // Clock to control frame rate
    sf::Clock clock;



    // Main loop to render the window
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();  // Time between frames
        float dt = deltaTime.asSeconds();  // Convert to seconds

        // Check for events (like closing the window)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the velocity and height due to gravity
        velocity += g * dt;  // v = u + g * t
        height += velocity * dt;  // h = h(Initial) + v * t

        if (c.collisionCheck(rectangle, ball, 800, 600, ballRadius))
        {
             
   
            if (velocity > 0)
            {
                velocity = -(velocity);
                 sound.play();    
                
            } 
          
          
        }

        // If the ball hits the ground, stop it
        if (height + ballRadius >= window.getSize().y) {
            height = window.getSize().y - (ballRadius);  // Prevent ball from going below the ground
            velocity = 0;  // Stop the ball (simulating a bounce on the ground)
        }
        
        // Check collision

        // Set the ball's position based on the height
        ball.setPosition(400 - ballRadius, height);

        // Clear the window
        window.clear();

        // Draw the ball
        window.draw(ball);
        window.draw(rectangle);

        // Display the content of the window
        window.display();
    }

    return 0;
}
