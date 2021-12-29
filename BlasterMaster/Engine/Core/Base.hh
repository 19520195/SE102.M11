#pragma once
#include <memory>
#include <unordered_map>
#include "Engine/Debug/Debug.hh"

template<typename T> using Ref = std::shared_ptr<T>;
template<typename T> using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args> constexpr Ref<T> CreateRef(Args&& ... args) {	return std::make_shared<T>(std::forward<Args>(args)...); }
template<typename T, typename ... Args> constexpr Scope<T> CreateScope(Args&& ... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

template<typename T> using List = std::vector<T>;
template<typename K, typename V> using HashTable = std::unordered_map<K, V>;
