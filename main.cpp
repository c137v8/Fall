#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include "colisiondetection.hpp"



class ball : public  sf::CircleShape
{
    public:
    ball(float radius, float x , float y )
    {
        setFillColor(sf::Color::Red);
        setRadius(radius);
        setPosition(x,y);
    }
};


class rfloor : public sf::RectangleShape
{
    public:
   rfloor(float width, float height , float x, float y)
   { 
   // sf::RectangleShape rectangle(sf::Vector2f(width, height));
    setSize(sf::Vector2f(height,width));
    setPosition(x, y);
    setFillColor( sf::Color::Red);
   }
};

const float g = 2000.81f;   // Accleration due to gravity
const float initialHeight = 500.0f;  // Initial height of ball
const float ballRadius = 20.0f;  // Radius of the ball 
const float initialVelocity = 200.0f;  // Initial velocity of ball
col::collision c; // Colision detection object



int main() {
    // Render the window

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fall");
    // Create a rectangle
    //sf::RectangleShape rectangle(sf::Vector2f(400, 20));
    //rectangle.setPosition(((window.getSize().x)/2)-200, (window.getSize().y)-180);
    //rectangle.setFillColor( sf::Color::Red);

    rfloor f1(40,200,200,700);
    

    ball b2(20,500,500);

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

        if (c.collisionCheck(f1, b2, 800, 600, ballRadius))
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
        b2.setPosition(400 - ballRadius, height);

        // Clear the window
        window.clear();

        // Draw the ball
        window.draw(f1);
        window.draw(b2);
        window.draw(f1);

        // Display the content of the window
        window.display();
    }

    return 0;
}
