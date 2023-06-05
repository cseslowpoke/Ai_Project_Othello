#include "aiFactor.h"
ai* aiFactor::createAi(aiType aiType, int way)  {
  switch (aiType) {
  case DAI:
    return new dai(way);
  case HUA:
    return new min_max_monte_carlo(way, 5, 40);
  case YU:
    return new CBplayer(way, 3, 9);
  default:
    return new dai(way);
  }
} 