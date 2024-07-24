#include <boost/program_options.hpp>
#include <dlfcn.h>
#include <iostream>

#include "bitboards/moves/all.hh"
#include "bitboards/moves/moves.hh"
#include "bitboards/pgn.hh"
#include "listener.hh"

using namespace boost::program_options;
using namespace board;

const std::vector<unsigned long long> Knight_moves;
const std::vector<unsigned long long> White_pawn_moves;
const std::vector<unsigned long long> Black_pawn_moves;
const std::vector<unsigned long long> King_moves;

int main(int argc, char **argv)
{
    board::Move board;
    try
    {
        options_description desc{ "Allowed options" };
        desc.add_options()("help,h", "show usage")("pgn", value<std::string>(),
                                                   "path to the PGN game file")(
            "listeners,l", value<std::vector<std::string>>(),
            "list of paths to listener plugins")("perft", value<std::string>(),
                                                 "path to a perft file");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
        if (vm.count("help"))
            std::cout << desc << '\n';
        else if (vm.count("pgn"))
        {
            std::string path = vm["pgn"].as<std::string>();
            if (vm.count("listeners"))
            {
                std::vector<std::string> list =
                    vm["listeners"].as<std::vector<std::string>>();
                for (auto lib : list)
                {
                    auto handle = dlopen(lib.c_str(), RTLD_LAZY);
                    if (handle)
                    {
                        void *x = dlsym(handle, "listener_create");
                        listener::Listener *listener =
                            reinterpret_cast<listener::Listener *(*)()>(x)();
                        listeners(path, listener);
                        dlclose(handle);
                    }
                }
            }
        }
        else if (vm.count("perft"))
        {
            std::string path = vm["perft"].as<std::string>();
            unsigned long long nb = board.get_number_of_moves(path);
            std::cout << nb << '\n';
        }
    }
    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 0;
}
