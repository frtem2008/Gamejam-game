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

#include <functional>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

inline std::mt19937 random_data(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
    T randomValue(sf::Vector2<T> interval) {
        return std::uniform_real_distribution<T>(interval.x, interval.y)(random_data);
    }

template<>
    int randomValue<int>(sf::Vector2i interval);
