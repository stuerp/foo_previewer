
/** $VER: Support.cpp (2022.12.06) P. Stuer **/

#pragma once

#include <iostream>
#include <iomanip>
#include <istream>
#include <sstream>
#include <string>

/// <summary>
/// Returns true if the specfied string contains a number.
/// </summary>
/// <typeparam name="Numeric"></typeparam>
/// <param name="s"></param>
/// <returns></returns>
template<typename Numeric>
bool IsNumber(const char * s)
{
    Numeric n = Numeric();

    return((std::istringstream(s) >> n >> std::ws).eof());
}
