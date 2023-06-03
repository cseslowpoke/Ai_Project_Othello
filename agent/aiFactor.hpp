#include "dai.hpp"
#include "hua.hpp"
enum aiType{
  DAI,
  HUA,
  YU
};

class aiFactor {
  public:
    static ai* createAi(aiType aiType, int way, evaluation* eval = NULL) {
      switch (aiType) {
        case DAI:
          if (eval != NULL) {
            return new dai(way, eval);
          }
          return new dai(way);
        case HUA:
          return new min_max_monte_carlo(way, 4, 40);
      }
    }
};