/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusPrinter.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:09:05 by htsang            #+#    #+#             */
/*   Updated: 2023/09/19 14:54:36 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AvatorPrinter.hpp"
#include "../ClapTrap.hpp"

#include <iostream>

class StatusPrinter : public AvatorPrinter
{
  public:
    StatusPrinter(ClapTrap &claptrap);
    StatusPrinter(const StatusPrinter& value);
    ~StatusPrinter();
    const StatusPrinter& operator=(const StatusPrinter& value);

    int   next();
    bool  isEnd() const;
  
  private:
    StatusPrinter();

    ClapTrap &claptrap_;
};
