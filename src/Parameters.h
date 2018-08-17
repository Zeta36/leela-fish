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


#ifndef GTP_H_INCLUDED
#define GTP_H_INCLUDED

#include <string>
#include <vector>

#ifdef USE_OPENCL
extern std::vector<int> cfg_gpus;
extern bool cfg_sgemm_exhaustive;
extern bool cfg_tune_only;
#endif
extern float cfg_softmax_temp;
extern float cfg_fpu_reduction;
extern bool cfg_fpu_dynamic_eval;
extern std::string cfg_weightsfile;


class Parameters {
public:
    static void setup_default_parameters();
private:
    static const std::string s_commands[];
};


#endif

