#include <chrono>
#include <format>
#include <iostream>
#include <sstream>  // istringstream
#include <string>

void adding_two_days_to_a_date_main() {
    using namespace std::chrono;

    auto dt{ "10/30-09:50" };
    auto fixed_dt{ std::string{"00/"} + dt };
    std::istringstream iss{ fixed_dt };
    sys_time<minutes> tp1{};
    from_stream(iss, "%y/%m/%d-%H:%M", tp1);
    auto tp2{ tp1 + days{2} };
    auto dp2{ floor<days>(tp2) };
    year_month_day ymd{ sys_days{ dp2 } };
    hh_mm_ss hms{ floor<minutes>(tp2 - dp2) };
    std::cout << std::format("{}/{}-{}:{}\n", ymd.month(), ymd.day(), hms.hours(), hms.minutes());
}
