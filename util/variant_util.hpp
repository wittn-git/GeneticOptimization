#pragma once
#include <variant>
#include <type_traits>

template <typename T>
constexpr auto shared_cast = [](auto& element) -> T* {
    if constexpr (std::is_convertible_v<decltype(element), T*>) return element;
    else return nullptr;
};

template <typename T,typename V>
T* get_variant(V& variant){
    return std::visit(shared_cast<T>,variant);
}