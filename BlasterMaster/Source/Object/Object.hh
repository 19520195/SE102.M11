#pragma once

#include "Engine/Core/Object.hh"

constexpr size_t OBJECT_ID_BRICK  = 0;
constexpr size_t OBJECT_ID_INTERRUPT = 1;

typedef Object Player;

class Enemy : public Object { };
// typedef Object Enemy;

#include "State.hh"
#include "Brick.hh"
#include "Player/SophiaIII.hh"
#include "Enemy/Interrupt.hh"
