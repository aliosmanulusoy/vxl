// vil_nitf2: Written by Rob Radtke (rob@) and Harry Voorhees (hlv@) of
// Stellar Science Ltd. Co. (stellarscience.com) for 
// Air Force Research Laboratory, 2005.

#ifndef VIL_NITF2_CLASSIFICATION_H
#define VIL_NITF2_CLASSIFICATION_H

#include "vil_nitf2.h"

#include <vcl_string.h>
#include <vcl_map.h>
#include <vcl_utility.h> // vcl_pair

class vil_nitf2_field_definitions;

// A purely static class that generates classification field definitions.
// Use \sa get_field_definitions() to get a field definition that will 
// parse either a nitf 2.1 or nitf 2.0 stream.  Note that the two are 
// very different, so be sure to ask for the right one.  They don't even 
// have the same field width. In NITF 2.1, the classification string is 
// fixed at 205 characters.  In NITF 2.0, it can either be 167 or 207 
// characters depending on whether the conditional field SDEVT is present 
// or not. The field names also vary according to the type of header
// that contains them.
//
class vil_nitf2_classification
{
public:
  
  // NITF file version
  enum file_version 
  { 
    V_UNKNOWN, V_NITF_10, V_NITF_20, V_NITF_21,
    // If you weren't confused enough already, now we're telling you
    // that NSIF 1.0 is the same as NITF 2.1. It's true though.
    V_NSIF_10 = V_NITF_21 
  };

  // Classification fields are used in a number of places with slightly
  // different tag names and pretty names. In the file header the first
  // classification field is "FSCLAS" ("File Security Classification");
  // in the image subheader, the corresponding field is "ISCLAS" 
  // ("Image Security Classification"). Fortunately, these differences
  // are consistent, so all tag names in one context can be generated by 
  // prepending the same string to the base tag name; similarly for 
  // the fields' pretty names. The tag_prefix and pretty_name_prefix 
  // argument below allow the caller to generate the field definitions
  // appropriate to the context, e.g., "F" and "File", respectively, 
  // in the case of a file header.
  static const vil_nitf2_field_definitions* get_field_definitions( 
    const file_version& version,
    vcl_string tag_prefix, vcl_string pretty_name_prefix );

  // Like get_field_defintions(), but appends fields to defs instead
  // of returning them.
  static void add_field_defs( 
    vil_nitf2_field_definitions* defs, const file_version& version, 
    vcl_string prefix, vcl_string pretty_name_prefix);

private:
  // Purely static class; don't instantiate.
  vil_nitf2_classification();

  // A cache of field definitions, indexed by version, tag_prefix and 
  // pretty_name_prefix.
  typedef vcl_pair< file_version, vcl_pair< vcl_string, vcl_string> > 
    type_field_defs_key;
  typedef vcl_map< type_field_defs_key, vil_nitf2_field_definitions*>
    type_field_defs_map;
  static type_field_defs_map s_field_definitions;
};

#endif //VIL_NITF2_CLASSIFICATION_H
