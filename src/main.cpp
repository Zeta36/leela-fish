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

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <iostream>

#include "config.h"
#include "Parameters.h"
#include "Utils.h"
#include "Network.h"
#include "syzygy/tbprobe.h"

#include "bitboard.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "tt.h"
#include "Uci.h"

namespace PSQT {
	void init();
}

using namespace Utils;

static void license_blurb() {
    myprintf_so(
        "LeelaFish %s Copyright (C) 2018  Samuel Graván and contributors\n"
        "Based on:\n"
        "Leela Chess Copyright (C) 2017 benediamond\n"
        "Leela Zero Copyright (C) 2017-2018  Gian-Carlo Pascutto and contributors\n"
        "Stockfish Copyright (C) 2017  Tord Romstad, Marco Costalba, Joona Kiiski, Gary Linscott\n"
        "This program comes with ABSOLUTELY NO WARRANTY.\n"
        "This is free software, and you are welcome to redistribute it\n"
        "under certain conditions; see the COPYING file for details.\n\n",
        PROGRAM_VERSION
    );
}

static std::string parse_commandline(int argc, char *argv[]) {
    namespace po = boost::program_options;
    // Declare the supported options.
    po::options_description v_desc("Allowed options");
    v_desc.add_options()
        ("help,h", "Show commandline options.")
        ("weights,w", po::value<std::string>(), "File with network weights.")
#ifdef USE_OPENCL
        ("gpu",  po::value<std::vector<int> >(),
                "ID of the OpenCL device(s) to use (disables autodetection).")
        ("full-tuner", "Try harder to find an optimal OpenCL tuning.")
        ("tune-only", "Tune OpenCL only and then exit.")
#endif
        ;

    // Parse both the above, we will check if any of the latter are present.
    po::options_description all("All options");    
    po::positional_options_description p_desc;
    p_desc.add("arguments", -1);
    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv)
                  .options(all).positional(p_desc).run(), vm);
        po::notify(vm);
    }  catch(const boost::program_options::error& e) {
        myprintf("ERROR: %s\n", e.what());
        license_blurb();
        std::cout << v_desc << std::endl;
        exit(EXIT_FAILURE);
    }

    // Handle commandline options
    if (vm.count("help") || vm.count("arguments")) {
        auto ev = EXIT_SUCCESS;
        // The user specified an argument. We don't accept any, so explain
        // our usage.
        if (vm.count("arguments")) {
            for (auto& arg : vm["arguments"].as<std::vector<std::string>>()) {
                std::cout << "Unrecognized argument: " << arg << std::endl;
            }
            ev = EXIT_FAILURE;
        }
        license_blurb();
        std::cout << v_desc << std::endl;
        exit(ev);
    }

    if (vm.count("weights")) {
        cfg_weightsfile = vm["weights"].as<std::string>();
    } 

#ifdef USE_OPENCL
    if (vm.count("gpu")) {
        cfg_gpus = vm["gpu"].as<std::vector<int> >();
    }

    if (vm.count("full-tuner")) {
        cfg_sgemm_exhaustive = true;
    }

    if (vm.count("tune-only")) {
        cfg_tune_only = true;
    }
#endif

    std::string start = "";
    if (vm.count("start")) {
        start = vm["start"].as<std::string>();
    }

    return start;
}

int main(int argc, char* argv[]) {

  Bitboards::init();
  Position::init();
  NNPosition::init();
  Parameters::setup_default_parameters();

  Network::initialize();

  std::cout << engine_info() << std::endl;

  UCI::init(Options);
  PSQT::init();
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Search::init();
  Pawns::init();
  Tablebases::init(Options["SyzygyPath"]); // After Bitboards are set
  Threads.set(Options["Threads"]);
  Search::clear(); // After threads are up

  UCI::loop(argc, argv);

  Threads.set(0);
  
  return 0;
}
