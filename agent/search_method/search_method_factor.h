#include "naga_alpha_t.h"
#include "nega_alpha.h"
#include "../evaluation/eval_factor.h"
#include <iostream>
enum method_type {NEGA_ALPHA, NEGA_ALPHA_T};

class search_factor {
public:
  static search_method* create_method(method_type method_type, int eval = 1);
};