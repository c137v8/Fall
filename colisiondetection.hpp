
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
namespace col{

class collision
{

public:

float closest_x;
float closest_y;
// Function to check if two objects are colliding.
int collisionCheck(const sf::RectangleShape& o1, const sf::CircleShape& o2)
{
    float w = o1.getSize().x;
    float h = o1.getSize().y;

    // Finding closest point of rectriangle to circles center
     float rec_x = o1.getPosition().x; 
     float cir_x = o2.getPosition().x;
    float r = o2.getRadius();

    // Calculateing the distance between the ball's center and the closest point on rectriangle
    
     float rec_y = o1.getPosition().y;
     float cir_y = o2.getPosition().y;
    
     closest_x = fmax(rec_x, fmin(cir_x, rec_x + w));
     closest_y = fmax(rec_y, fmin(cir_y, rec_y + h));

    float distance_x = cir_x- closest_x;
    float distance_y = cir_y- closest_y;
    float distance = sqrt(pow(distance_x,2 )  + pow(distance_y,2 ) );

    // Check if the distance is less than or equal to the ball's radius
    return distance <= r;
}
};
}