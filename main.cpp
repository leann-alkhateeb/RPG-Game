#include <iostream>

//rpg game


using namespace std;

#include "character.h"

int main()
{
  bool game_over = false;
  string name;
  int choice;
  int p_attack, c_attack;
  Character *cptr, *pptr;
  
  cout << "Enter character name: ";
  cin >> name;

  cout << "Select type of character: " << endl;
  cout << "1. Warrior\tPower: 30\tStamina: 200" << endl;
  cout << "2. Wizard\tPower: 30\tStamina: 170" << endl;
  cout << "3. Rogue\tPower: 30\tStamina: 160" << endl;
  cin >> choice;

  switch(choice)
  {
    case 1: pptr = (Character*)new Warrior(name);  break; 
    case 2: pptr = (Character*)new Wizard(name);  break; 
    case 3: pptr = (Character*)new Rogue(name);  break; 
    default: cout << "Invalid choice!" << endl; return 0;
  }

  // Pick a character for the computer 
  int r = rand() % 3;
  if(r == 1)
    cptr = (Character*)new Warrior("Jake");
  else if(r == 2)
    cptr = (Character*)new Wizard("Harry");
  else
    cptr = (Character*)new Rogue("Donald");

  cout << "You are playing against " << cptr -> get_name();
  cout << "(" << cptr -> get_type() << ")" << endl;
  string player_type = pptr -> get_type(); 
  
  while(!game_over)
  {
    cout << "Your stamina: " << pptr -> get_stamina() << endl;
    cout << cptr -> get_name() << "'s stamina: " << cptr -> get_stamina() << endl;
    if(cptr -> get_stamina() <= 0)
    {
      game_over = true;
      cout << "Yay! You win" << endl;
    }
    else if (pptr -> get_stamina() <= 0)
    {
      game_over = true;
      cout << "Oops! You lost" << endl;
    }

    if(game_over == true)
      continue;
    
    // Player's move
    if(player_type == "wizard")
    {
      cout << "Cast spell or attack ? (1/2): ";
      cin >> choice;
      if(choice == 1)
        ((Wizard*)pptr) -> cast_spell(cptr);
      else 
      {
        p_attack = pptr -> get_power();
        cptr -> get_attacked(p_attack);
      }
    }
    else if(player_type == "warrior")
    {
      cout << "High precision attack or low precision attack ? (1/2): ";
      cin >> choice;

      p_attack = ((Warrior*)pptr) -> get_power((choice == 1));
      cptr -> get_attacked(p_attack);
    }
    else 
    {
      cout << "Heal or attack ? (1/2): ";
      cin >> choice;
      if(choice == 1)
        ((Rogue*)pptr) -> heal();
      else 
      {
        p_attack = pptr -> get_power();
        cptr -> get_attacked(p_attack);
      }
    }
    
    // Computer's move
    int r = rand() % 2;
    if(cptr -> get_type() == "warrior")
    {
      c_attack = ((Warrior*)cptr) -> get_power((r == 1));
      pptr -> get_attacked(c_attack);
    }
    else if(cptr -> get_type() == "wizard")
    {
      if(r == 1)
        ((Wizard*)cptr) -> cast_spell(pptr);
      else 
      {
        c_attack = cptr -> get_power();
        pptr -> get_attacked(c_attack);
      }
    }
    else  // Computer is a rogue
    {
      if(r == 1)
        ((Rogue*)cptr) -> heal();
      else 
      {
        c_attack = cptr -> get_power();
        pptr -> get_attacked(c_attack);
      }
    }
      
  }  // End of while loop 

  cout << "Exiting... Goodbye!" << endl;
  return 0;
}