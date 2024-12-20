// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "move_ws/msg/detail/vector3d__rosidl_typesupport_introspection_c.h"
#include "move_ws/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "move_ws/msg/detail/vector3d__functions.h"
#include "move_ws/msg/detail/vector3d__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  move_ws__msg__Vector3d__init(message_memory);
}

void move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_fini_function(void * message_memory)
{
  move_ws__msg__Vector3d__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_member_array[3] = {
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__msg__Vector3d, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__msg__Vector3d, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__msg__Vector3d, z),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_members = {
  "move_ws__msg",  // message namespace
  "Vector3d",  // message name
  3,  // number of fields
  sizeof(move_ws__msg__Vector3d),
  false,  // has_any_key_member_
  move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_member_array,  // message members
  move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_init_function,  // function to initialize message memory (memory has to be allocated)
  move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_type_support_handle = {
  0,
  &move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_members,
  get_message_typesupport_handle_function,
  &move_ws__msg__Vector3d__get_type_hash,
  &move_ws__msg__Vector3d__get_type_description,
  &move_ws__msg__Vector3d__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_move_ws
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, msg, Vector3d)() {
  if (!move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_type_support_handle.typesupport_identifier) {
    move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &move_ws__msg__Vector3d__rosidl_typesupport_introspection_c__Vector3d_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
