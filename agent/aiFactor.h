#include "dai.h"
#include "hua.h"
#include "CBplayer.h"
enum aiType { DAI, HUA, YU };

class aiFactor {
public:
  static ai* createAi(aiType aiType, int way, evaluation* eval = nullptr, int scoreboard = 0, int depth = 3);
};