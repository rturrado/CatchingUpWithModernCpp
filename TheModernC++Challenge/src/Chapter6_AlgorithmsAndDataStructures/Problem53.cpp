#include "Chapter6_AlgorithmsAndDataStructures.h"

#include <algorithm>  // sort
#include <iomanip>  // setprecision
#include <ios>  // fixed
#include <iostream>  // cout
#include <map>
#include <numeric>  // accumulate
#include <vector>

using ratings = std::vector<int>;
using movie_ratings = std::map<std::string, ratings>;

double average_rating(ratings rs)
{
    if (rs.empty()) { return double{ 0.0 }; };

    std::sort(begin(rs), end(rs));

    size_t ratings_to_remove{ static_cast<size_t>(rs.size() * 0.1 + 0.5) };  // removing a 10% instead of a 5%
    rs.erase(begin(rs), begin(rs) + ratings_to_remove);
    rs.erase(end(rs) - ratings_to_remove, end(rs));

    return std::accumulate(begin(rs), end(rs), 0.0) / rs.size();
}

// Average rating of movies
//
// Write a program that calculates and prints the average rating of a list of movies.
// Each movie has a list of ratings from 1 to 10 (where 1 is the lowest and 10 is the highest rating).
// In order to compute the rating, you must remove 5% of the highest and lowest ratings before computing their average.
// The result must be displayed with a single decimal point.
void problem_53_main()
{
    movie_ratings mr = {
        { "The Godfather", { 10, 8, 7, 9, 9, 9, 3, 10, 6 } },
        { "The Godfather II", { 10, 9, 9, 8, 8, 10, 2, 4, 6 } },
        { "The Godfather III", { 9, 7, 7, 8, 8, 9, 8, 4, 5 } }
    };

    std::cout << "Average rating of movies:\n";
    for (const auto& m : mr)
    {
        std::cout << "\t" << m.first << ": " << std::fixed << std::setprecision(1) << average_rating(m.second) << "\n";
    }
    std::cout << "\n";
}
