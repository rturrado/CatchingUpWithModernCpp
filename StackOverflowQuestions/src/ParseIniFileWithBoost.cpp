#include "ParseIniFileWithBoost.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <iostream>

void parse_ini_file_with_boost_main()
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("res/file.ini", pt);
    std::cout << pt.get<std::string>("parameters.numColors") << std::endl;
    std::cout << pt.get<std::string>("parameters.boardSize") << std::endl;
}
