#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


const float g = 2000.81f;   
const float initialHeight = 500.0f;  
const float ballRadius = 20.0f;  // Radius of the ball 
const float initialVelocity = 200.0f;  


int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Fall");

    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400 - ballRadius, initialHeight);  // Start in the middle

    // Initial conditions
    float velocity = initialVelocity;  // Initial velocity (pixels/s)
    float height = initialHeight;  // Initial height (pixels)
    float time = 0.0f;  // Time in seconds
    float dt = 0.01f;  // Time step for the simulation

    // Clock to control frame rate
    sf::Clock clock;

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
        height += velocity * dt;  // h = h0 + v * t

        // If the ball hits the ground, stop it
        if (height + ballRadius >= window.getSize().y) {
            height = window.getSize().y - ballRadius;  // Prevent ball from going below the ground
            velocity = -500;  // Stop the ball (simulating a bounce on the ground)
        }

        // Set the ball's position based on the height
        ball.setPosition(400 - ballRadius, height);

        // Clear the window
        window.clear();

        // Draw the ball
        window.draw(ball);

        // Display the content of the window
        window.display();
    }

    return 0;
}
