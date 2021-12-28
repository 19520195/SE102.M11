#pragma once
#include <cstdint>

class Behavior
{
public:
  enum class Direct : uint8_t { Up, Left, Down, Right };
  // enum class State  : uint8_t { Idle, Walk, Jump, Fall };

public:
  Behavior(const Direct& direct = Direct::Up);
  Direct GetDirect() const;
  void SetDirect(const Direct& direct);

private:
  Direct m_Direct;
};