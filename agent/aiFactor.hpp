#include "dai.h"
#include "hua.h"
#include "CBplayer.h"
enum aiType { DAI, HUA, YU };

class aiFactor {
public:
  static ai *createAi(aiType aiType, int way, evaluation *eval = NULL, int scoreboard = 0, int depth=3) {
    switch (aiType) {
    case DAI:
      if (eval != NULL) {
        return new dai(way, eval);
      }
      return new dai(way);
    case HUA:
      return new min_max_monte_carlo(way, 4, 100);
    case YU:
      return new CBplayer(way, 3, 9);
    default:
      return new dai(way);
    }
  }
};