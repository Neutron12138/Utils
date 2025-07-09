#pragma once

#include <base/version.hpp>

// node

#include "node/node.hpp"
#include "node/tree_node.hpp"
#include "node/node_tree.hpp"

#include "node/node.cpp"
#include "node/tree_node.cpp"
#include "node/node_tree.cpp"

// time

#include "time/time_manager.hpp"

// frame

#include "frame/frame_manager.hpp"
#include "frame/physics_frame_manager.hpp"

#include "frame/frame_manager.cpp"
#include "frame/physics_frame_manager.cpp"

// process

#include "process/processable.hpp"
#include "process/process_manager.hpp"

// event

#include "event/event.hpp"
#include "event/event_handler.hpp"

// image

#include "image/pixel.hpp"
#include "image/base_image.hpp"
#include "image/fast_image.hpp"

// meta

#include "meta/meta_base.hpp"
#include "meta/field_base.hpp"
#include "meta/method_base.hpp"
#include "meta/global_field.hpp"
#include "meta/global_method.hpp"
#include "meta/member_field.hpp"
#include "meta/member_field_offset.hpp"
#include "meta/member_method.hpp"

// reflection

#include "reflection/class_info.hpp"
#include "reflection/class_info_base_register.hpp"
#include "reflection/class_info_register.hpp"
#include "reflection/dynamic_class_info_register.hpp"
#include "reflection/class_db.hpp"

#include "reflection/class_info.cpp"
