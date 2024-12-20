// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice

#ifndef MOVE_WS__MSG__DETAIL__VECTOR3D__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define MOVE_WS__MSG__DETAIL__VECTOR3D__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "move_ws/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "move_ws/msg/detail/vector3d__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace move_ws
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
cdr_serialize(
  const move_ws::msg::Vector3d & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  move_ws::msg::Vector3d & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
get_serialized_size(
  const move_ws::msg::Vector3d & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
max_serialized_size_Vector3d(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
cdr_serialize_key(
  const move_ws::msg::Vector3d & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
get_serialized_size_key(
  const move_ws::msg::Vector3d & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
max_serialized_size_key_Vector3d(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace move_ws

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_move_ws
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, move_ws, msg, Vector3d)();

#ifdef __cplusplus
}
#endif

#endif  // MOVE_WS__MSG__DETAIL__VECTOR3D__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
