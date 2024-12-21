#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

class collision
{

public:
    int rec_x  ; 
    int cir_x ;

    // Calculateing the distance between the ball's center and the closest point on rectriangle
    
    int rec_y ;
    int cir_y  ;

    int closest_x ;
    int closest_y ;

// Function to check if two objects are colliding.
int collisionCheck(sf::RectangleShape o1, sf::CircleShape o2, float w , float h, float r)
{
    
    // Finding closest point of rectriangle to circles center
     rec_x = o1.getPosition().x; 
     cir_x = o2.getPosition().x;

    // Calculateing the distance between the ball's center and the closest point on rectriangle
    
     rec_y = o1.getPosition().y;
     cir_y = o2.getPosition().y;

     closest_x = fmax(rec_x, fmin(cir_x, rec_x + w));
     closest_y = fmax(rec_y, fmin(cir_x, rec_y + h));

    float distance_x = cir_x- closest_x;
    float distance_y = cir_y- closest_y;
    float distance = sqrt((pow(distance_x,2 )  + pow(distance_y,2 ) ));

    // Check if the distance is less than or equal to the ball's radius
    return distance <= r;
}
};
const float g = 2000.81f;   // accleration due to gravity
const float initialHeight = 500.0f;  // height of ball
const float ballRadius = 20.0f;  // Radius of the ball 
const float initialVelocity = 200.0f;  //initial velocity of ball
collision c;

int main() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fall");

      sf::RectangleShape rectangle(sf::Vector2f(400, 20));
    rectangle.setPosition(((window.getSize().x)/2)-200, (window.getSize().y)-180);
    rectangle.setFillColor( sf::Color::Red);

    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400 - ballRadius, initialHeight);  // Start in the middle
   
  


    // Initial conditions
    float velocity = initialVelocity;  // Initial velocity (pixels/s)
    float height = initialHeight;  // Initial height (pixels)

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
        height += velocity * dt;  // h = h(Initial) + v * t

        if (c.collisionCheck(rectangle, ball, 800, 600, ballRadius))
        {
             
   
            velocity = 0 ;
            height = c.closest_y - 40;
          
        }

        // If the ball hits the ground, stop it
        if (height + ballRadius >= window.getSize().y) {
            //height = window.getSize().y - (ballRadius);  // Prevent ball from going below the ground
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
