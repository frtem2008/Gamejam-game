//
// Created by livefish on 8/3/24.
//

#pragma once

#include <vector>
#include <list>
#include <map>
#include <stack>

#include <random>

#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>

#include <memory>

#include <chrono>

#include <optional>
#include <variant>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

inline std::mt19937 random_data(std::chrono::steady_clock::now().time_since_epoch().count());
