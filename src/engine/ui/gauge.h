// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GAUGE_H__
#define __VE_GAUGE_H__

#include "engine/ui/ui_container.h"
#include "engine/ui/label.h"
#include "engine/sprites/sprite.h"

namespace ve {

/**
    Gauge is a simple interface component which is used to show action progress.
    It consists of three main parts:
    <ul>
    <li>Background sprite - it is used to render gauge background.</li>
    <li>Bar sprite - it is used to render progress bar.</li>
    <li>Label object - it used to show progress in a textual form.</li>
    </ul>

    Bar sprite rendering goes on the following way:
    Two pair of vertices is used for texture coordinates linear interpolation.
    For example, if you defines pair (0, 1) and (2, 3) for interpolation and
    progress is 30% following bar texture coordinates will be used:

    (texCoord[0], texCoord[0] + 0.33 * (texCoord[1] - texCoord[0])) and <br>
    (texCoord[2], texCoord[2] + 0.33 * (texCoord[3] - texCoord[2])).

    Default pairs for interpolation: (0, 1) and (3, 2)
*/
class Gauge : public UIContainer {
private:
  AbstractSprite *background;
  Sprite *bar;
  Label *label;
  pair<int, int> firstBasisVector;
  pair<int, int> secondBasisVector;
  int value;
  bool labelEnabled;

protected:
  /**
      Checks inconsistencies in gauge value parameter.
      It is used when progress changes.
  */
  void normalize();

public:
  /**
      Simple Gauge constructor.
      @param parent - UI object that will be the owner of this gauge.
  */
  Gauge(UIContainer *parent);

  /**
    Destructor.
  */
  virtual ~Gauge();

  /**
      Renders this gauge.
      @return OK if rendering succeded.
      @return NULL_POINTER may be returned if Label is used, but font is not set.
      @return non-OK if engine error occurred.
  */
  virtual Outcome render();

  /**
      Sets background sprite for this gauge. Passing NULL
      will disable background sprite rendering.
      @param backgroundSprite - sprite to use as background.
  */
  void setBackgroundSprite(AbstractSprite *backgroundSprite);

  /**
      Returns background sprite.
      @return Sprite which is used for background rendering.
  */
  AbstractSprite *getBackgroundSprite();

  /**
      Sets bar sprite for this gauge. Passing NULL
      will disable bar sprite rendering.
      @param barSprite - sprite to use for bar rendering.
  */
  void setBarSprite(Sprite *barSprite);

  /**
      Returns progress bar sprite.
      @return Sprite which is used for progress bar rendering.
  */
  Sprite *getBarSprite();

  /**
      Returns label which is used to render textual info about progress.
      @return Label component.
  */
  Label *getLabel();

  /**
      Enables/Disables label component depending on flag.
      @param isEnabled - set to 'true' to enable label and
      'false' to disable.
  */
  void setLabel(bool isEnabled);

  /**
      Sets progress value in range [0, 100].
      @param newValue - new progress value.
  */
  void setValue(int newValue);

  /**
      Returns current progress value.
      @return Progress value.
  */
  int getValue();

  /**
      Sets vertices pair which is used for texture coordinates
      linear interpolation.
      @param index - Defines pair to change, must be 0 or 1 for
      the first and the second pair respectively.
      @param texCoordsPair - Pair of sprite vertices numbers. This pair
      must contain values from 0 to 3.
  */
  void setBasisVector(uint index, pair<int, int> texCoordsPair);

  /**
      Returns interpolation vector, defined by index.
      @param index - Number of interpolation pair to return. Must be 0 or 1.
      @return Interpolation pair or EPIC_FAIL macro occurred in case of wrong index.
  */
  pair<int, int> getBasisVector(uint index);
};

}

#endif // __VE_GAUGE_H__
