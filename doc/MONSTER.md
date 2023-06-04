# Monster class

This class inherits from the Character class.

- header file: [Here](#)
- cpp file: [Here](#)

## Public members

### Variables

   #### float detectionRange;
   
   The distance from which the monster detects the player.
   
   #### bool asleep=false;
   
   This bool determines if the monster moves or not.
   
   #### bool dangerDetected=false;
   
   If true, then the monster will run away.
   
   ####  bool preyDetected=false;
   
   If true, then the monster will move towards the player.
   #### bool fightUntilDeath=false;
   
   If the hp falls under a certain treshold, the monster will run away.
   
   #### int direction=0;
   
   Direction in which the monster moves.
   
   #### Attitude attitude;
   
   Current monster attitude.
   
   #### Attitude defaultAttitude;
   
   Default monster attitude.
   
   #### sf::Time moveDelay=sf::seconds(0);
   
   Timer to make a random move.
   
### Functions
 #### Monster(std::string name, int level, float dr, sf::Vector2f p={0.f,0.f}, sf::Vector2f s={50.f,80.f});
 
 Constructor for the class.
 Arguments: name, level, detecion range, position, hitbox size.
 
 #### Monster();
 
 Empty constructor. 
 
 #### void randomMove(sf::Time elapsed);
 #### void pathFindTo(sf::Time elapsed, Character& character);
 #### void runFrom(sf::Time elapsed, Character& character);
 #### void makeDecision(sf::Time elapsed, Character& character, std::vector<std::unique_ptr<Projectile>> &projectiles);
 #### void attack(std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos, sf::Time elapsed);
 #### virtual void wakeUp();
 #### virtual void goSleep();
  
   
