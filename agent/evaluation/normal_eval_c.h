#include "evaluation.h"
class normal_eval_c : public evaluation {
public:
  int eval(bitboard b);
  void name();
private:
  const int weight[64]={120,-20, 20,  5,  5, 20,-20,120,
		      -20,-40, 15, -5, -5, 15,-40,-20,
		       15, 15, 15,  3,  3, 15, 15, 15,
		        5, -5,  3, 20, 20,  3, -5,  5,
		        5, -5,  3, 20, 20,  3, -5,  5,
		       15, 15, 15,  3,  3, 15, 15, 15,
		      -20,-40, 15, -5, -5, 15,-40,-20,
		      120,-20, 20,  5,  5, 20,-20,120};
};


