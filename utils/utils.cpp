#pragma once

#ifdef UTILS_INCLUDE_STB_IMPL

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize2.h>
#undef STB_IMAGE_RESIZE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#undef STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#endif

// misc

#include "misc/named_object.cpp"
#include "misc/notifiable.cpp"
#include "misc/printable_object.cpp"

// node

#include "node/node.cpp"
#include "node/tree_node.cpp"
#include "node/node_tree.cpp"

// frame

#include "frame/frame_manager.cpp"
#include "frame/physics_frame_manager.cpp"

// process

#include "process/processable.cpp"
#include "process/process_manager.cpp"

// event

#include "event/event.cpp"
#include "event/event_handler.cpp"

// image

#include "image/pixel.cpp"
#include "image/base_image.cpp"
#include "image/fast_image.cpp"

// reflection

#include "reflection/class_info.cpp"
#include "reflection/class_db.cpp"
