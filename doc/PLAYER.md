# Player class

This class inherits from the Character class.


- header file: [Here](#)
- cpp file: [Here](#)

## Public members

### variables

#### sf::Keyboard::Key keyUp=sf::Keyboard::W;

After pressing this key the player goes up.

#### sf::Keyboard::Key keyDown=sf::Keyboard::S;

After pressing this key the player goes down.

#### sf::Keyboard::Key keyLeft=sf::Keyboard::A;

After pressing this key the player goes left.

#### sf::Keyboard::Key keyRight=sf::Keyboard::D;

After pressing this key the player goes right.

#### sf::Time ability1Cooldown=sf::Time::Zero;
#### sf::Time ability2Cooldown=sf::Time::Zero;
#### sf::Time ability3Cooldown=sf::Time::Zero;

Time left to use an ability.

#### sf::Time ability1Time=sf::seconds(1);
#### sf::Time ability2Time=sf::seconds(1);
#### sf::Time ability3Time=sf::seconds(1);

Time to which ability cooldown resets.

#### float ability1Cost;
#### float ability2Cost;
#### float ability3Cost;

Ability cost in mana.

### Functions

#### Player(std::string n, float d, float as, float spd, int l, sf::Vector2f p, sf::Vector2f s);

Constructor for the player class.
Arguments: Name, damage, attack speed, movement speed, level, position and hitbox size.
This constructor sets the BodyType enum to living.
It also sets the experience to 0 and calculates exp required to go to next level.

#### Player(std::string n, sf::Vector2f p, sf::Vector2f s);

It is similar to the previous constructor, but it sets some default values for damage, attack speed, speed and level.

#### Player();

Empty constructor.

#### void addExp(int n);

Increases experience by n.
  
#### int getExp();

Getter for the experience variable.

#### int getExpRequired();

Getter for the experience required to level up.

#### bool checkLevelUp();

Checks if there is enough experience to level up.

#### void movementWSAD(bool b);

If true sets the movement keys to WSAD.
Is false sets the movement keys to arrows.

#### virtual void update(sf::Time elapsed, std::vector<std::unique_ptr<Monster>>& monsters);
  
  It reduces the abilities' cooldowns and attack delay by elapsed time.
  Also it moves the object by the velocity and regenerates health.
  
#### virtual void ability1(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos);
#### virtual void ability2(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos);
#### virtual void ability3(std::vector<std::unique_ptr<Monster>>& monsters, std::vector<ParticleSystem> &particleSystem, std::vector<std::unique_ptr<Projectile>> &projectiles, sf::Vector2f mousePos);
  
Abilities of the player. They are different for every class.

## Private members
  ### variables
  
  #### int experience=0;
  
  Current experience of the player.
  
  #### int expRequired;
  
  Experience required to level up.
  
  #### void setExpRequired();
  
  Sets the expRequired variable based on level.
  
