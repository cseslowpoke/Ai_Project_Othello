#pragma once
#include "normal_eval_a.h"
#include "normal_eval_b.h"
#include "simple_eval.h"

enum eval_type {SIMPLE_EVAL, NORMAL_EVAL_A, NORMAL_EVAL_B};

class eval_factor {
public:
  static evaluation* create_eval(eval_type eval_type);
};