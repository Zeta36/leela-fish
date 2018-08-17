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


#include <algorithm>
#include <cassert>
#include <cstring>   // For std::memset
#include <iomanip>
#include <sstream>
#include <iostream>

#include "evaluate.h"
#include "thread.h"
#include "Network.h"
#include "NNPosition.h"

namespace Trace {
  enum Tracing { NO_TRACE, TRACE };
}

using namespace Trace;

namespace {

  // Evaluation class computes and stores attacks tables and other working data
  template<Tracing T>
  class Evaluation {

  public:
    Evaluation() = delete;
    explicit Evaluation(const Position& p, const BoardHistory& state) : pos(p), state(state) {}
    Evaluation& operator=(const Evaluation&) = delete;
    Value value();

  private:
    const Position& pos;
	const BoardHistory& state;
  };

  // Evaluation::value() is the main function of the class. It computes the various
  // parts of the evaluation and returns the value of the position from the point
  // of view of the side to move.

  template<Tracing T>
  Value Evaluation<T>::value() {

    assert(!pos.checkers());
	
	// Network support
	auto raw_netlist = Network::get_scored_moves(state);

	// DCNN returns winrate as side to move
	Value net_eval = Value(int(raw_netlist.second * 1000));
		
	Value v = (pos.side_to_move() == WHITE ? Value(int(net_eval)) : Value(1000 - int(net_eval)));

    return  (pos.side_to_move() == WHITE ? v : -v) // Side to move point of view
           + Eval::Tempo;
  }

} // namespace


/// evaluate() is the evaluator for the outer world. It returns a static
/// evaluation of the position from the point of view of the side to move.

Value Eval::evaluate(const Position& pos, const BoardHistory& state) {
  return Evaluation<NO_TRACE>(pos, state).value();
}
