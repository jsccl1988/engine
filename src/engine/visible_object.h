// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VISIBLE_OBJECT_H__
#define __VE_VISIBLE_OBJECT_H__

#include "common.h"

namespace ve {

/**
    Should be based class for all renderable objects. It has only one field which defines
    if this object is visible or not.
*/
class VisibleObject :public Object {
private:
  /** Visibility flag. */
  bool visible;

public:
  /**
      Default constructor.
      Set visibility flag to 'true'.
  */
  VisibleObject();

  /**
      Sets visibility flag.
      If this flag is set to 'true' then object
      is visible and rendering goes in a usual way.
      In case of 'false' render() function must return OK
      and do no rendering.
  */
  void setVisible(bool value);

  /**
      Checks if this object is visible.
      @return 'true' if it is visible and 'false' if not.
  */
  bool isVisible();
};

}

#endif // __VE_VISIBLE_OBJECT_H__
