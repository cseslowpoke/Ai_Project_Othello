#pragma once
#include "normal_eval_a.h"
#include "normal_eval_b.h"
#include "normal_eval_c.h"
#include "simple_eval.h"


enum eval_type {SIMPLE_EVAL, NORMAL_EVAL_A, NORMAL_EVAL_B, NORMAL_EVAL_C};

class eval_factor {
public:
  static evaluation* create_eval(eval_type eval_type);
};