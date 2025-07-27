#pragma once

#include <base/version.hpp>

// io

#include "io/print_container.hpp"
#include "io/read_binary.hpp"
#include "io/write_binary.hpp"
#include "io/read_bytes.hpp"
#include "io/read_string.hpp"

// misc

#include "misc/named_object.hpp"
#include "misc/notifiable.hpp"
#include "misc/printable_object.hpp"

// node

#include "node/node.hpp"
#include "node/tree_node.hpp"
#include "node/node_tree.hpp"

// time

#include "time/time_manager.hpp"

// frame

#include "frame/frame_manager.hpp"
#include "frame/physics_frame_manager.hpp"

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
