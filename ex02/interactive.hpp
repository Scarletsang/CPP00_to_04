/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:39:24 by htsang            #+#    #+#             */
/*   Updated: 2023/10/10 16:36:21 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <string>
#include <iostream>

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Vector.hpp"

namespace interactive
{

  namespace printer
  {
    typedef void (&Printer)();

    void  InteractivePrompt();

    void  CharacterNamePrompt();

    void  CharacterGradePrompt();

    void  FormTargetPrompt();

    void  FormTypePrompt();

    void  ChooseFormPrompt();

    void  NoFormError();

    void  ShowForms(Vector<AForm*>& forms);

    void  InteractiveInvalidPrompt();
  } // namespace printer

  struct s_index
  {
    int number;
    int upper_bound;
  };

  namespace parser
  {
    int Parse(std::string& input, std::string& string);

    int Parse(std::string& input, int& number);

    int Parse(std::string& input, struct s_index& index);
    
    int Parse(std::string& input, Bureaucrat*& bureaucrat);

    template <typename T>
    int ParseWithPrompt(std::string& input, T& target, printer::Printer prompt);

    template <typename T>
    int Parse(std::string& input, AForm*& form)
    {
      std::string target;

      try
      {
        if (ParseWithPrompt(input, target, printer::FormTargetPrompt))
          return EXIT_FAILURE;
        form = new T(target);
        return EXIT_SUCCESS;
      }
      catch (std::exception& e)
      {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
      }
    }

    template <typename T>
    int ParseWithPrompt(std::string& input, T& target, printer::Printer prompt)
    {
      prompt();
      std::getline(std::cin, input);
      while (std::cin.good())
      {
        if (!Parse(input, target))
          return EXIT_SUCCESS;
        else
        {
          printer::InteractiveInvalidPrompt();
          std::getline(std::cin, input);
        }
      }
      return EXIT_FAILURE;
    }

    template <typename T>
    int ParseUntilCorrect(std::string& input, T& target)
    {
      while (std::cin.good())
      {
        if (!Parse(input, target))
          return EXIT_SUCCESS;
      }
      return EXIT_FAILURE;
    }
  } // namespace parser

} // namespace interactive

