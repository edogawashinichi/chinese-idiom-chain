/// common_math.h

#pragma once

#include "common_notation.h"

namespace ChineseIdiomChain {

/// judge vector

bool isEqual(const VI& u, const VI& v);

/// generate vector

/* vec[i] = k * i + b for i = 0,1,...,n-1 */
VI linearVec(const int n, const int k, const int b);

/* vec[i] = i + start_val for i = 0,1,...,n-1 */
VI idVec(const int n, const int start_val);

/* vec[i] = i for i = 0,1,...,n-1 */
VI idVec(const int n);

/// choose from vector

/* randomly choose an element from vector vec with the equal probability */
int randomChoose(const VI& vec);

/* randomly choose an element from vector vec with frequency freq */
int randomChoose(const VI& vec, const VI& freq);

/// shuffle vector

void shuffle(VI& v);

/// bet

bool bet(const float prob);

}/// namespace ChineseIdiomChain

