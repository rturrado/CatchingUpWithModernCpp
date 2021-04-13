#include "ParseIniFile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

struct Parameters
{
    int num_colors{ 0 };
    int board_size{ 0 };
    int num_snails{ 0 };
};
using SectionName = std::string;
using AttributeName = std::string;
using AttributeValue = int;
using Attribute = std::pair<AttributeName, AttributeValue>;
using Section = std::vector<Attribute>;
using Data = std::map<SectionName, std::vector<Section>>;

std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
{
    os << "[parameters]\n";
    os << "numColors = " << parameters.num_colors << "\n";
    os << "boardSize = " << parameters.board_size << "\n";
    os << "numSnails = " << parameters.num_snails << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Data& data)
{
    for (const auto& sections : data)
    {
        int id = 0;
        for (const auto& section : sections.second)
        {
            os << "[" << sections.first << "]\n";
            std::cout << "id = " << id++ << "\n";
            for (const auto& attribute : section)
            {
                os << attribute.first << " = " << attribute.second << "\n";
            }
        }
    }
    return os;
}

void parse_ini_file_main()
{
    std::ifstream ifs{ "res/file.ini" };

    Parameters parameters{};
    Data data{};
    std::string current_section{};
    std::vector<Attribute> current_attributes;
    int current_id{ 0 };

    std::string line{};
    while (std::getline(ifs, line))
    {
        std::regex pattern_section{ R"(\[(\w+)\])" };
        std::regex pattern_attribute{ R"((\w+) = ([+-]?\d+))" };
        std::smatch matches;
        if (std::regex_search(line, matches, pattern_section))
        {
            if (!current_section.empty() && current_section != "parameters")
            {
                data[current_section][current_id] = std::move(current_attributes);
            }
            current_section = matches[1];
            current_id = 0;
        }
        else if (std::regex_search(line, matches, pattern_attribute))
        {
            std::string attribute = matches[1];
            int value = std::stoi(matches[2]);
            if (current_section == "parameters")
            {
                if (attribute == "numColors") parameters.num_colors = value;
                if (attribute == "boardSize") parameters.board_size = value;
                if (attribute == "numSnails") parameters.num_snails = value;
            }
            else if (attribute == "id")
            {
                current_id = value;
                if (data.contains(current_section))
                {
                    data[current_section].resize(static_cast<size_t>(current_id) + 1);
                }
                else
                {
                    data[current_section] = std::vector<Section>{1};
                }
            }
            else
            {
                current_attributes.push_back(std::make_pair(attribute, value));
            }
        }
    }
    if (current_attributes.size() != 0)
    {
        data[current_section][current_id] = std::move(current_attributes);
    }

    assert(data.contains("color") && parameters.num_colors == data["color"].size());

    std::cout << parameters;
    std::cout << data;
}
