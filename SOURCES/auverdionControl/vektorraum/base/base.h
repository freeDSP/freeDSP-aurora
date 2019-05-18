/*
  ==============================================================================

    base.h
    Created: 7 May 2018 11:28:03am
    Author:  Raphael Knoop

  ==============================================================================
*/

#pragma once

#include "./base/typedefs.h"
#include "./base/tvector.h"
#include "./base/tmatrix.h"

namespace Vektorraum
{

tvector<double> linspace( double base, double limit, uint64_t N );

}
