// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GUI_BUILDER_H__
#define __VE_GUI_BUILDER_H__

#include "engine/sprites/sprite.h"
#include "engine/ui/ui.h"

namespace ve {

class Engine;

/**
    Class that simplifies GUI elements creation process.
*/
class GUIBuilder {
public:
  /**
      Loads texture from the file and then creates sprite from it. Width
      and height of the newly-created sprite will be the same as texture has.
      @param engine - Engine that will be used to create sprite and texture.
      @param fileName - Path to the file that should be used for sprite creation.
      @return Sprite object if operation succeeded.
      @return NULL if image format is not supported or file does not exist.
  */
  static Sprite* createSpriteFromFile(Engine *engine, std::string fileName);

  /**
    Creates a button from three sprites. Sprites are created from three images and
    their paths are specified in the parameters list. Width and height for the
    newly-created button is computed as a maximum value for the corresponding dimension
    among the given images.
    @param engine - Engine to create sprites and textures.
    @param gui - UI to create the button.
    @param parent - UI container that will be the owner of the button.
    @param baseImage - Path to the image that will be used as a base image for the
    button.
    @param coveredImage - Path to the image that will be shown when mouse is
    above the button.
    @param pressedimage - Path to the image for pressed state of the button.
    @return Button object if operation succeeded.
    @return NULL if image format is not supported or some file does not exist.
  */
  static Button *createButtonFromFiles(Engine *engine, UI *gui, UIContainer *parent,
    std::string baseImage, std::string coveredImage, std::string pressedImage);
};

}

#endif // __VE_GUI_BUILDER_H__
