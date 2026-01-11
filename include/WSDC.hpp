#pragma once

#include "WSDC/Definitions.hpp"


#if defined(WSDC_IMPLEMENT) ^ defined(WSDC_IMP_CORE)

// core
#include "WSDC/Core/Color.hpp"
#include "WSDC/Core/Geometry.hpp"
#include "WSDC/Core/Math.hpp"
#include "WSDC/Core/Position.hpp"
#include "WSDC/Core/Size.hpp"
#include "WSDC/Core/Utils.hpp"

#endif
#if defined(WSDC_IMPLEMENT) ^ defined(WSDC_IMP_DRAW)

// drawing
#include "WSDC/Draw/Image.hpp"
#include "WSDC/Draw/SpriteSheet.hpp"
#include "WSDC/Draw/Wrappers.hpp"

#endif
#if defined(WSDC_IMPLEMENT) ^ defined(WSDC_IMP_ENGINE)

// engine
#include "WSDC/Engine/Button.hpp"
#include "WSDC/Engine/Object.hpp"

#endif
#if defined(WSDC_IMPLEMENT) ^ defined(WSDC_IMP_MANAGER)

// scene manager
#include "WSDC/SceneManager/Scene.hpp"

#endif
#if defined(WSDC_IMPLEMENT) ^ defined(WSDC_IMP_TEXT)

// text
#include "WSDC/Text/Font/FontStyle.hpp"
#include "WSDC/Text/Font.hpp"
#include "WSDC/Text/Format.hpp"
#include "WSDC/Text/Log.hpp"

#endif
#if defined(WSDC_IMPLEMENT) ^ defined(WSDC_IMP_WINDOW)

// window
#include "WSDC/Window/Sub.hpp"


#endif
#if defined(WSDC_IMPLEMENT) ^ defined(WSDC_IMP_TOP)

// top-level
#include "WSDC/Engine.hpp"
#include "WSDC/Events.hpp"
#include "WSDC/SceneManager.hpp"
#include "WSDC/TextRenderer.hpp"
#include "WSDC/Window.hpp"

#endif
