/*
LeelaFish, a UCI chess playing engine derived from Stockfish and LeelaChess Zero
Copyright (C) 2018 Samuel Graván

LeelaFish is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

LeelaFish is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EVALUATE_H_INCLUDED
#define EVALUATE_H_INCLUDED

#include <string>

#include "types.h"
#include "NNPosition.h"

class Position;

namespace Eval {

constexpr Value Tempo = Value(20); // Must be visible to search

Value evaluate(const Position& pos, const BoardHistory& state);
}

#endif // #ifndef EVALUATE_H_INCLUDED
