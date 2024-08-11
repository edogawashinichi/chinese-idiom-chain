/// common_math.h

#pragma once

#include "common_notation.h"

namespace ChineseIdiomChain {

/// bit operation

void split16bits(const short bits16, char& high8, char& low8);
short composite16bits(const char high8, const char low8);

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

/* randomly choose from 0,1,...,n-1 */
int randomChoose(const int n);
  
/* randomly choose an element from vector vec with the equal probability */
int randomChoose(const VI& vec);

/* randomly choose a subvector from vector vec */
PII randomChooseSub(const VI& vec);

/* randomly choose an element from vector vec[min_index,max_index] with the equal probability */
int randomChoose(const VI& vec, const int min_index, const int max_index);

/* randomly choose an element from vector vec with frequency freq */
int randomChoose(const VI& vec, const VI& freq);

/* randomly choose an element from vector vec[min_index,max_index] with frequency freq[min_index,max_index] */
int randomChoose(const VI& vec, const VI& freq, const int min_index, const int max_index);

/// transform vector

void shuffle(VI& v);
void inverse(VI& v);
void sharpen(VI& v);
void inverseSharpen(VI& v);

/// bet

bool bet(const float probability);
bool sharpenBet(const int x, const int y);

}/// namespace ChineseIdiomChain

