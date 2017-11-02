// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_COMMON_H__
#define __VE_COMMON_H__

#include <ctime>
#include <cmath>
#include <memory.h>

#include "types.h"
#include "consts.h"

#include "debug.h"
#include "object.h"
#include "keys.h"

/* Include common GL headers */
#ifdef VE_WINDOWS
#include <Ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "third_party/gl/glext.h"
#include "third_party/gl/wglext.h"

/* Fuck the native windows definitions of ERROR, max and min, etc. */
#undef ERROR
#undef max
#undef min
#undef FLOAT

#endif // VE_WINDOWS

#ifdef VE_LINUX
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#endif // VE_LINUX

#include "logs/log.h"
#include "tools/memory_manager.h"

/**
  @mainpage

  <b>VR Engine</b> is an Open Source library that allows you get an access
  to all OpenGL features through high-level objects. It saves
  your time, speeds up game development process and let you focus on game development
  instead of diving into numerous OpenGL/Xlib functions.

  Main classes of <b>VR Engine</b> library which will be used in almost every application:
  <ul>
  <li>
  \link ve::WindowSystem WindowSystem \endlink - abstract class that provides communication with window system.
  It includes following basic operations: window creation, setting position & caption,
  handling window system events (mouse, keyboard events).
  </li>
  <li>
  \link ve::Window Window \endlink - class that is usually created by WindowSystem class and is used to manage window properties.
  </li>
  <li>
  \link ve::Engine Engine \endlink - abstract class that represents rendering system (RS). It contains a lot of functions for
  resources creation. This class is used not so often inspite of fact that it is the only one which
  communicates with rendering system. More often, communication with RS is implicit and it is done via
  resource classes like \link ve::Texture Texture \endlink , \link ve::FrameBuffer FrameBuffer \endlink ,
  \link ve::VideoBuffer VideoBuffer \endlink . When, for example, functions of VideoBuffer class is called
  then they will manually call engine functions. So, there is almost no need in low-level access through Engine class.
  Use high-level functions of the objects and they will do low-level stuff and all the interaction with the OpenGL engine for you.
  </li>
  <li>
  \link ve::GPUStateManager GPUStateManager \endlink - abstract class that is used to track state of GPU pipeline. By using instance
  of this class (it can be easily accessed via getStateManager() fucntion of the Engine class) you may get / set different states of
  the pipeline. But if you do not need low level access to the states you may use build-in classes (like \link ve::Sprite Sprite \endlink)
  and they will set neccessary states for you.
  </li>
  <li>
  \link ve::UI UI \endlink - class that manages all interface items on the screen, provides messaging in the GUI
  system, so that every object in this system handles mouse/key messages. Implementing your own
  interface system is often boring task, because you need to implement a lot of different and
  sometimes complex components. With interface system classes (like \link ve::Form Form \endlink ,
  \link ve::Label Label \endlink , \link ve::Button Button \endlink , etc.) you
  will obtain speed up to GUI development process. You just need to set sprites, describe object
  properties (fonts, position, for example) and get GUI done along with good messaging handling across it.
  </li>
  <li>
  \link ve::GUIBuilder GUIBuilder \endlink - class that simplifies GUI elements creation process. Use it to create buttons
  ans sprites by giving paths to the textures that should be loaded for them.
  </li>
  <li>
  \link ve::Font Font \endlink - this class provides functions that helps to use fonts registered in a system, draw any number
  of Unicode symbols on the screen in a quite well performance way, which is supported even on GMA945 chipsets.
  </li>
  <li>
  \link ve::Texture Texture \endlink - the name of this class is self-explainable. It is an entity which provides you high-level
  functions to load them, bind to pipeline, apply samplers, etc.
  </li>
  <li>
  \link ve::Sprite Sprite \endlink - one more self-explainable name. No routine work is needed with this class. You can create sprite
  objects, set textures, key colors to make them transparaent and apply any transformation: translation,
  rotaion, scaling, even shaders. There are several useful sprite classes in this library: \link ve::AnimatedSprite AnimatedSprite \endlink -
  sprite that contains all the function to create animation in your games and the second is
  \link ve::MovableSprite MovableSprite \endlink - the class that will help you to add units & characters into your game.
  Check out "sprite_animation" and "movable_sprite" samples from the source code archive to check how they work.
  Additional information may be found in the <a href = "http://eengine.org/en/sprite-animation/"> Sprite Animation </a> lesson.
  </li>
  </ul>
*/

#endif // __VE_COMMON_H__
