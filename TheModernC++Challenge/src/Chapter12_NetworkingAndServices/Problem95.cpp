#include "Chapter12_NetworkingAndServices.h"

#include <format>
#include <iostream>  // cout
#include <string>
#include <string_view>
#include <utility>  // pair
#include <vector>

#include <boost/asio.hpp>


auto get_host_ipv4_addresses(std::string_view host, std::string_view service)
{
    using namespace boost::asio;

    std::vector<std::string> ret{};

    io_context my_io_context;
    ip::tcp::resolver resolver(my_io_context);
    auto iter{ resolver.resolve(ip::tcp::v4(), host, service)};
    ip::tcp::resolver::iterator end{};
    while (iter != end)
    {
        ip::tcp::endpoint endpoint = *iter++;
        ret.emplace_back(endpoint.address().to_string().c_str());
    }
    return ret;
}


// Finding the IP address of a host
//
// Write a program that can retrieve and print the IPv4 address of a host.
// If multiple addresses are found, then all of them should be printed.
// The program should work on all platforms
void problem_95_main()
{
    for (auto&& [host, service] : std::vector<std::pair<std::string_view, std::string_view>>{
        { "localhost", "8080" },
        { "www.boost.org", "http" },
        { "www.google.com", "https" } })
    {
        std::cout << std::format("Getting IPv4 addresses for host = '{}' and service = '{}'\n", host, service);
        for (auto&& address : get_host_ipv4_addresses(host, service))
        {
            std::cout << std::format("\t{}\n", address);
        }
    }

    std::cout << "\n";
}
