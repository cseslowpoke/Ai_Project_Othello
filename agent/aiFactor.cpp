#include "aiFactor.h"
ai* aiFactor::createAi(aiType aiType, int way, evaluation *eval, int scoreboard,  int depth)  {
  switch (aiType) {
  case DAI:
    if (eval != NULL) {
      return new dai(way, eval);
    }
    return new dai(way);
  case HUA:
    return new min_max_monte_carlo(way, 4, 40);
  case YU:
    return new CBplayer(way, 3, 9);
  default:
    return new dai(way);
  }
} 