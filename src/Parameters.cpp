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


#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <random>
#include <chrono>

#include "config.h"
#include "Utils.h"
#include "Network.h"
#include "Parameters.h"

using namespace Utils;

#ifdef USE_OPENCL
std::vector<int> cfg_gpus;
bool cfg_sgemm_exhaustive;
bool cfg_tune_only;
#endif
float cfg_softmax_temp;
float cfg_fpu_reduction;
bool cfg_fpu_dynamic_eval;
std::string cfg_weightsfile;

void Parameters::setup_default_parameters() {
#ifdef USE_OPENCL
    cfg_gpus = { };
    cfg_sgemm_exhaustive = false;
    cfg_tune_only = false;
#endif
    cfg_softmax_temp = 1.0f;
    cfg_fpu_reduction = 0.1f;
    cfg_fpu_dynamic_eval = true;
    cfg_weightsfile = "weights.txt";
}

