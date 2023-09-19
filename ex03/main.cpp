/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:44:18 by htsang            #+#    #+#             */
/*   Updated: 2023/09/19 19:14:13 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include "battle/Battle.hpp"

#include <unistd.h>

#include <cstdlib>
#include <iostream>

namespace interactive
{
  int  PromptName(std::string& name)
  {
    std::cout << "Enter your name (max 10 characters): ";
    std::getline(std::cin, name);
    while (std::cin.good())
    {
      if (name.length() > 10)
        std::cout << "Name too long, try again: ";
      else
        return EXIT_SUCCESS;
      std::getline(std::cin, name);
    }
    return EXIT_FAILURE;
  }

  int  PromptAction(Battle &battle)
  {
    std::string action;
  
    std::cout << "Enter your action (A/R): ";
    std::getline(std::cin, action);
    while (std::cin.good())
    {
      if (action != "A" && action != "R")
        std::cout << "Invalid action, try again: ";
      else
      {
        battle.printTurn();
        if (action == "A")
          battle.attack();
        else
          battle.repair();
        return EXIT_SUCCESS;
      }
      std::getline(std::cin, action);
    }
    return EXIT_FAILURE;
  }

  int PromptCharacter()
  {
    
  }

  int Run()
  {
    std::string player_name;

    if (PromptName(player_name))
      return EXIT_FAILURE;
    FragTrap player1(player_name);
    FragTrap player2("Frag dude");

    Battle  battle(player1, player2, 60, 3, 23, 35);
    while (!battle.isEnd() && std::cin.good())
    {
      if (PromptAction(battle))
        return EXIT_FAILURE;
      battle.print();
      std::cout << "Opponent deciding moves..." << std::endl << std::endl;
      sleep(1);
      battle.printTurn();
      battle.randomAction();
      battle.print();
    }
    battle.printWinner();
    return EXIT_SUCCESS;
  }
} // namespace battle

namespace noninteractive
{
  int Run()
  {
    DiamondTrap diamondTrap("diamondTrap");

    diamondTrap.attack("target");
    diamondTrap.takeDamage(10);
    diamondTrap.beRepaired(10);
    diamondTrap.whoAmI();
    diamondTrap.guardGate();
    diamondTrap.highFivesGuys();
    diamondTrap.whoAmI();
    return EXIT_SUCCESS;
  }
} // namespace noninteractive

int main(int argc, const char** argv)
{
  if (argc == 1)
    return noninteractive::Run();
  else if (argc == 2 && std::string(argv[1]) == "-i")
    return interactive::Run();
  else
  {
    std::cerr << "Usage: " << argv[0] << " [-i]" << std::endl;
    return EXIT_FAILURE;
  }
}
