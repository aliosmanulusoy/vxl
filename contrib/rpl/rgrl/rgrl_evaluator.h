#ifndef rgrl_evaluator_h_
#define rgrl_evaluator_h_
//:
// \file
// \author Lee, Ying-Lin (Bess)

#include <iostream>
#include <vector>
#include <vcl_compiler.h>
#include <rgrl/rgrl_object.h>

class rgrl_evaluator : public rgrl_object
{
 public:
  // Default constructor
  rgrl_evaluator() {}
  // Destructor
  virtual ~rgrl_evaluator() {}

  virtual
  double evaluate( std::vector< double > const& a,
                   std::vector< double > const& b,
                   std::vector< double > const& weight ) const = 0;

  // Defines type-related functions
  rgrl_type_macro( rgrl_evaluator, rgrl_object );
};

#endif
