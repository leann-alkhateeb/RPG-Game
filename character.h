#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>

using namespace std;

class Character
{
  protected:
  int stamina;      // Player's stamina. Player dies if stamina <= 0
  string name;      // Player's name. Initialized by the constructor 
  int power;        // Attacking power of the player
  string type;      // "warrior", "wizard", or "rogue"

  public:  
  Character(string _name, int _power, int _stamina)
  {
    name = _name;
    power = _power;
    stamina = _stamina;
  }  

  // Accessors
  string get_name() { return name; }
  int get_stamina() { return stamina; }
  int get_power() { return power; }
  string get_type() { return type; }

  // Other methods of the class
  void reduce_power(int value)
  {
    power -= value;
    cout << name << "'s power reduced to " << power << endl;
  }

  void get_attacked(int attack)
  {
    stamina -= attack;
    if(stamina < 0)
      stamina = 0;
    cout << name << "'s stamina reduced to " << stamina << endl;
  }
  
};  // End of Character class definition. 

class Warrior: protected Character
{
  private:

  public:
  // Constructor arguments - Name, attacking power, stamina
  Warrior(string _name): Character(_name, 30, 200)
  {
    type = "warrior";
  }

  // Overriding the function of the base class
  int get_power(bool highPrecision)
  {
    int random = rand() % 10;
    if(highPrecision)  // Weak attack with high hit ratio
      return (random < 7) ? (power - 10) : 0;
    else  // Strong attack with low hit ratio
      return (random < 7) ? 0 : (power + 10);
  }
};

class Wizard: protected Character
{
  public:
  // Constructor arguments - Name, attacking power, stamina
  Wizard(string _name): Character(_name, 30, 170)
  {
    type = "wizard";
  }
  void cast_spell(Character* c)
  {
    c -> reduce_power(3);
  }
};

class Rogue: protected Character
{
  public:
  // Constructor arguments - Name, attacking power, stamina
  Rogue(string _name): Character(_name, 30, 160)
  {
    type = "rogue";
  }

  void heal()
  {
    stamina += 20; 
    cout << name << "'s stamina improved to " << stamina << endl;
  }
};

#endif