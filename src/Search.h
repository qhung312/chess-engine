#pragma once
#include "Moves.h"
#include "Eval.h"

using namespace std;
using Move = pair<string, int>;

Move search(const Board&, int, int, int);
Move search(const Board&);