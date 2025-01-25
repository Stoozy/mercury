#include <catch2/catch_test_macros.hpp>
#include <ctime>
#include <util.h>

TEST_CASE("DateTime Conversion", "[util]"){
    int DAY = 9;
    int MONTH = 1;
    int YEAR = 2014;

    // std::tm tm = { /* .tm_sec  = */ 0,
    //            /* .tm_min  = */ 0,
    //            /* .tm_hour = */ 0,
    //            /* .tm_mday = */ (DAY),
    //            /* .tm_mon  = */ (MONTH) - 1,
    //            /* .tm_year = */ (YEAR) - 1900,
    // };

    std::tm tm;
    tm.tm_sec = 0;
    tm.tm_min = 0;
    tm.tm_hour = 0;
    tm.tm_mday = (DAY);
    tm.tm_mon = (MONTH) - 1;
    tm.tm_year = (YEAR) - 1900;

    auto time = util::parse_date("2014-01-09");
    REQUIRE(time == std::chrono::system_clock::from_time_t(std::mktime(&tm)));
}

TEST_CASE("char*->string Conversion", "[util]"){
    const char * tmp = "Testing 123";


    std::string str = util::char_ptr_to_string(tmp);

    REQUIRE(str == "Testing 123");
}


TEST_CASE("Average", "[util]"){

    float r1 = rand() % 100 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = rand() % 100 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r3 = rand() % 100 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    std::vector<float> v =  {r1, r2, r3};
        
    float avg = (r1+r2+r3)/3.0f;

    REQUIRE(avg == util::get_fp_avg_vec(v));
}
