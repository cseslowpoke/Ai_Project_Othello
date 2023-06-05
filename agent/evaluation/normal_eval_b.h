#include "evaluation.h"
class normal_eval_b : public evaluation {
public:
  int eval(bitboard b);
  void name();
private:
  const int weight[64] = {
      120, -12, 20, 5,  5,  20, -20, 120,
      -20, -40, -5, -5, -5, -5, -40, -20,
      20,  -5,  15, 3,  3,  15, -5,  20,  
      5,   -5,  3,  3,  3,  3,  -5,  5,
      5,   -5,  3,  3,  3,  3,  -5,  5,   
      20,  -5,  15, 3,  3,  15, -5,  20,
      -20, -40, -5, -5, -5, -5, -40, -20, 
      120, -12, 20, 5,  5,  20, -20, 120};
};