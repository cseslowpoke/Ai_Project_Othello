#include "search_method_factor.h"

search_method* search_factor::create_method(method_type method_type, int eval) {
  switch(method_type) {
    case NEGA_ALPHA:
      return new nega_alpha(eval);
    case NEGA_ALPHA_T:
      return new nega_alpha_t(eval);
    default:
      return nullptr; 
  }
}