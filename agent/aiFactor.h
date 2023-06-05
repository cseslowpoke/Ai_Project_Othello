#include "dai.h"
#include "hua.h"
#include "CBplayer.h"
enum aiType { DAI, HUA, YU };

class aiFactor {
public:
  static ai* createAi(aiType aiType, int way, int method = 0, int eval = 1);
};