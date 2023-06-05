#include "eval_factor.h"

evaluation* eval_factor::create_eval(eval_type eval_type) {
  std::cout << "create eval:" << eval_type << std::endl;
  switch (eval_type)
  {
  case SIMPLE_EVAL:
    return new simple_eval();
  case NORMAL_EVAL_A:
    return new normal_eval_a();
  case NORMAL_EVAL_B:
    return new normal_eval_b();
  case NORMAL_EVAL_C:
    return new normal_eval_c();
  default:
    return nullptr;
  }
}