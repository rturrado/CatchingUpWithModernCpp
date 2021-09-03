#include <string>  // string
#include <chrono>  // sys_seconds, local_seconds, parse, duration
#include <iostream>  // cout

// Daylight Saving Time (DST) started in Europe/Madrid time zone on 2021-03-28 at 02:00:00
// Examples below compute the time difference (in s) between 01:59:00 and 03:01:00 on that day
//
// - Case 1 uses system times with no time zone info, so the output is 3720 (1 hour and 2 minutes)
// - Case 2 uses local times paired to a time zone, and the output is 120 (2 minutes)
//   Again, if we just compute the difference using the local times with no time zone info,
//   the output is 3720 (1 hour and 2 minutes)
// - Case 3 uses system times with offsets, to obtain an output of 120 (2 minutes)
void playing_with_time_zones_and_dst_main()
{
    // Case 1
    //
    // Outputs:
    //     (2021-03-28 01:59:00, 2021-03-28 03:01:00) (UTC, no tz info) = 3720
    {
        std::cout << "Case 1: parsed type is system time -> time point is UTC\n";

        // Input string
        const std::string line{ "(2021-03-28 01:59:00, 2021-03-28 03:01:00)" };
        
        // Parsed type is system time
        std::chrono::sys_seconds start_tp{};
        std::chrono::sys_seconds stop_tp{};

        // Parse system time (%F %T)
        std::istringstream iss{ line };
        if (iss >> std::chrono::parse(std::string{ "(%F %T" }, start_tp) and
            iss >> std::chrono::parse(std::string{ ", %F %T)" }, stop_tp))
        {
            // Calculate elapse time in s between the start and stop time points
            double elapsed_time_s = std::chrono::duration<double>(stop_tp - start_tp).count();

            std::cout << "\t" << line << " (UTC, no tz info) = " << elapsed_time_s << "\n\n";
        }
    }

    // Case 2
    //
    // Outputs:
    //     (2021-03-28 01:59:00 Europe/Madrid, 2021-03-28 03:01:00 Europe/Madrid) (UTC, w/ tz info) = 120
    //     (2021-03-28 01:59:00 Europe/Madrid, 2021-03-28 03:01:00 Europe/Madrid) (local time, no tz info) = 3720
    {
        std::cout << "Case 2: parsed type is local time paired to a time zone -> time point is local time paired to a time zone\n";

        // Input string contains time zone names
        const std::string line{ "(2021-03-28 01:59:00 Europe/Madrid, 2021-03-28 03:01:00 Europe/Madrid)" };

        // Parsed type is local time paired to a time zone
        std::chrono::local_seconds start_ltp{};
        std::chrono::local_seconds stop_ltp{};
        std::string start_zn{};
        std::string stop_zn{};

        // Parse local time (%F %T) and time zone name (%Z)
        std::istringstream iss{ line };
        if (iss >> std::chrono::parse(std::string{ "(%F %T %Z" }, start_ltp, start_zn) and
            iss >> std::chrono::parse(std::string{ ", %F %T %Z)" }, stop_ltp, stop_zn))
        {
            // Build a time zone object pairing the local time and the time zone
            std::chrono::zoned_seconds start_z_s( std::chrono::locate_zone(start_zn), start_ltp );
            std::chrono::zoned_seconds stop_z_s( std::chrono::locate_zone(stop_zn), stop_ltp );

            // Get system time (UTC) from the time zone object
            std::chrono::sys_seconds start_stp{ start_z_s.get_sys_time() };
            std::chrono::sys_seconds stop_stp{ stop_z_s.get_sys_time() };

            // Calculate elapse time in s between the start and stop system time points
            double elapsed_time_s_utc = std::chrono::duration<double>(stop_stp - start_stp).count();
            std::cout << "\t" << line << " (UTC, w/ tz info) = " << elapsed_time_s_utc << "\n";

            // Calculate elapse time in s between the start and stop local time points
            double elapsed_time_s_lt = std::chrono::duration<double>(stop_ltp - start_ltp).count();
            std::cout << "\t" << line << " (local time, no tz info) = " << elapsed_time_s_lt << "\n\n";
        }
    }

    // Case 3
    //
    // Outputs:
    //     (2021-03-28 01:59:00 +0100, 2021-03-28 03:01:00 +0200) (UTC) = 120
    {
        std::cout << "Case 3: format string and input parse an offset and parsed type is system time -> time point is UTC\n";

        // Input string contains offsets
        const std::string line{ "(2021-03-28 01:59:00 +0100, 2021-03-28 03:01:00 +0200)" };

        // Parsed type is system time
        std::chrono::sys_seconds start_tp{};
        std::chrono::sys_seconds stop_tp{};

        // Parse system time (%F %T) and offset (%z)
        std::istringstream iss{ line };
        if (iss >> std::chrono::parse(std::string{ "(%F %T %z" }, start_tp) and
            iss >> std::chrono::parse(std::string{ ", %F %T %z)" }, stop_tp))
        {
            // Calculate elapse time in s between the start and stop time points
            double elapsed_time_s = std::chrono::duration<double>(stop_tp - start_tp).count();

            std::cout << "\t" << line << " (UTC) = " << elapsed_time_s << "\n";
        }
    }
}
