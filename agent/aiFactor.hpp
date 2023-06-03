#include "dai.hpp"
#include "hua.hpp"
enum aiType{
  DAI,
  HUA,
  YU
};

class aiFactor {
  public:
    static ai* createAi(aiType aiType, int way) {
      switch (aiType) {
        case DAI:
          return new dai(way);
        case HUA:
          return new min_max_monte_carlo(way, 4, 40);
      }
    }
};