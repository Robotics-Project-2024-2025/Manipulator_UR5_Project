// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "move_ws/msg/detail/vector3d__functions.h"
#include "move_ws/msg/detail/vector3d__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace move_ws
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Vector3d_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) move_ws::msg::Vector3d(_init);
}

void Vector3d_fini_function(void * message_memory)
{
  auto typed_message = static_cast<move_ws::msg::Vector3d *>(message_memory);
  typed_message->~Vector3d();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Vector3d_message_member_array[3] = {
  {
    "x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws::msg::Vector3d, x),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws::msg::Vector3d, y),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "z",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws::msg::Vector3d, z),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Vector3d_message_members = {
  "move_ws::msg",  // message namespace
  "Vector3d",  // message name
  3,  // number of fields
  sizeof(move_ws::msg::Vector3d),
  false,  // has_any_key_member_
  Vector3d_message_member_array,  // message members
  Vector3d_init_function,  // function to initialize message memory (memory has to be allocated)
  Vector3d_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Vector3d_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Vector3d_message_members,
  get_message_typesupport_handle_function,
  &move_ws__msg__Vector3d__get_type_hash,
  &move_ws__msg__Vector3d__get_type_description,
  &move_ws__msg__Vector3d__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace move_ws


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<move_ws::msg::Vector3d>()
{
  return &::move_ws::msg::rosidl_typesupport_introspection_cpp::Vector3d_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, move_ws, msg, Vector3d)() {
  return &::move_ws::msg::rosidl_typesupport_introspection_cpp::Vector3d_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
