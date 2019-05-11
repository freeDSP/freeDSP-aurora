/*
  ==============================================================================

    matlib.h
    Created: 19 Apr 2018 10:44:42am
    Author:  Raphael Knoop

  ==============================================================================
*/

#pragma once

#include <cmath>

#include "./base/base.h"
#include "./core/core.h"
#include "./fft/fft.h"
#include "./signal/signal.h"
#include "./statistics/statistics.h"

namespace Vektorraum
{

static const double pi = static_cast<double>(M_PI);
static const tcomplex j( 0.f, 1.f );

}
