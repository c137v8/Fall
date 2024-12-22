
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <cmath>
namespace col{

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
}