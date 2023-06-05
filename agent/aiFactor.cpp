#include "aiFactor.h"
ai* aiFactor::createAi(aiType aiType, int way, int method)  {
  switch (aiType) {
  case DAI:
    return new dai(way, method);
  case HUA:
    return new min_max_monte_carlo(way, 5, 40);
  case YU:
    return new CBplayer(way);
  default:
    return new dai(way);
  }
} 