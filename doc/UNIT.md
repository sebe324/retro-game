# Unit class

This class is the core of all other game classes.

- header file: [Here](#)
- cpp file: [Here](#)

This class inherits from sf::Drawable.

## Public members:

  ### variables
 
  #### float speed
  The speed at which the object moves.
  
  #### bool left
  This contains information about what side the object is facing.
  
  true - left
  
  false - right 
  
  #### std::string name
  Name of the object.
  
  #### sf::Vector2f velocity
  
  Current velocity of the object in x and y.
  
  #### sf::Rect<float> hitbox
  
  Hitbox of the object.
  
  #### sf::VertexArray bodyParts
  
  Game objects in this game are not sprites. They are composed of few rectangles.
  Thanks to this they can have cool animations like those after defeating enemies.
  ( + I'm not good at pixel art)
  
  #### int bodyPartsNumber
  
  Amount of current body parts of the object.
  
  ### functions
  
  #### Unit(std::string n, sf::Vector2f p, sf::Vector2f s, float spd);
  
  Constructor of the class. It takes name, position, size and speed as input.
  
  #### Unit();
  
  Empty constructor.
  
  #### sf::Vector2f getCenter() const;
  
  This function returns the center of the hitbox.
  
  #### void update(sf::Time elapsed);
  
  Some useless function. It should be deleted.
  
  ####  void moveUp(sf::Time elapsed, float multiplier=1);
  ####  void moveDown(sf::Time elapsed, float multiplier=1);
  ####  void moveLeft(sf::Time elapsed, float multiplier=1);
  ####  void moveRight(sf::Time elapsed, float multiplier=1);
  
  All of these functions add / subtract (depending on the direction)
  speed*elapsed.asSeconds()*multiplier to velocity.
  
  #### void move();
  
  Multiplies the velocity by 0.9 to slow the object down.
  Then adds the velocity to the position
  
  #### float getDistance(Unit& unit) const;
  
  Returns the distance between two objects based on the pythagorean theorem.
  
  #### float getDistanceX(Unit& unit) const;
  
  Returns the X axis distance between two objects.
  
  #### float getDistanceY(Unit& unit) const;
  
  Returns the Y axis distance between two objects.
  
  #### void rotate(float angle);
  
  As the name suggests, this function rotates the object.
  
## Protected members
  
  #### void createBodyPart(sf::Vector2f s, sf::Vector2f offset, sf::Color color);
  
  This function adds a new body part to the unit. 
  
  s - Size of the rectangle.
  offset - Distance from the top left corner of the hitbox.
  color - Color of the object.
  
## Private members
  
  #### virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  Draws the object on the screen.
  
  
