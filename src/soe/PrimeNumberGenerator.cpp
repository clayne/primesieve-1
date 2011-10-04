//
// Copyright (c) 2011 Kim Walisch, <kim.walisch@gmail.com>.
// All rights reserved.
//
// This file is part of primesieve.
// Visit: http://primesieve.googlecode.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above
//     copyright notice, this list of conditions and the following
//     disclaimer in the documentation and/or other materials provided
//     with the distribution.
//   * Neither the name of the author nor the names of its
//     contributors may be used to endorse or promote products derived
//     from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#include "PrimeNumberGenerator.h"
#include "PrimeNumberFinder.h"
#include "SieveOfEratosthenes.h"
#include "defs.h"
#include "bithacks.h"
#include "imath.h"

#include <cassert>

PrimeNumberGenerator::PrimeNumberGenerator(PrimeNumberFinder& finder) :
  SieveOfEratosthenes(
      finder.getPreSieveLimit() + 1,
      isqrt(finder.getStopNumber()),
      nextHighestPowerOf2(defs::PRIMENUMBERGENERATOR_SIEVESIZE * 1024),
      defs::PRIMENUMBERGENERATOR_PRESIEVE_LIMIT),
      primeNumberFinder_(finder) {
  assert(this->getStopNumber() <= UINT32_MAX);
}

/**
 * Generate the primes within the current segment i.e. 
 * [lowerBound, lowerBound + (sieveSize*30+1)] and use them to sieve
 * with primeNumberFinder_ (is a SieveOfEratosthenes).
 * @see SieveOfEratosthenes::sieve(uint32_t)
 */
void PrimeNumberGenerator::generate(const uint8_t* sieve, uint32_t sieveSize) {
  uint32_t lowerBound = static_cast<uint32_t> (this->getSegmentLow());
  // GENERATE_PRIMES() is defined in defs.h
  GENERATE_PRIMES(primeNumberFinder_.sieve, uint32_t);
}

void PrimeNumberGenerator::analyseSieve(const uint8_t* sieve, uint32_t sieveSize) {
  this->generate(sieve, sieveSize);
}
