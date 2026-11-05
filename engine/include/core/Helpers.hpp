// A collection of helper functions that I find myself needing
#pragma once
#include <string_view>
#include <source_location>

template<typename T>
constexpr std::string_view getStructName() {
    // Get struct name 
    auto location = std::source_location::current();
    std::string_view structName = location.function_name();
    
    // Format
    if (size_t prefix = structName.find("T = "); prefix != std::string_view::npos) {
        structName.remove_prefix(prefix + 4); // "T = "
        if (size_t suffix = structName.find_first_of("];"); suffix != std::string_view::npos) {
            structName.remove_suffix(structName.size() - suffix);
        } 
        return structName;
    }
    
    return structName;
};