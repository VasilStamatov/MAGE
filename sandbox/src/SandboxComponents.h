#pragma once

#include <ecs/Component.h>

struct SandboxComponent : mage::ecs::Component
{
  SandboxComponent(float _a, float _b, int _c, int _d, int _e, int _f)
      : a(_a)
      , b(_b)
      , c(_c)
      , d(_d)
      , e(_e)
      , f(_f)
  {
  }

  float a;
  float b;
  int c;
  int d;
  int e;
  int f;
};
