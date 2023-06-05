#include "search_method_factor.h"

search_method* search_factor::create_method(method_type method_type) {
  switch(method_type) {
    case NEGA_ALPHA:
      return new nega_alpha();
    case NEGA_ALPHA_T:
      return new nega_alpha_t();
    default:
      return nullptr; 
  }
}