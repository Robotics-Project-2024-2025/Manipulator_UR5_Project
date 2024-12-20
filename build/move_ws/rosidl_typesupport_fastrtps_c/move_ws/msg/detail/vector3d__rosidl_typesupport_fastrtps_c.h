// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice
#ifndef MOVE_WS__MSG__DETAIL__VECTOR3D__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define MOVE_WS__MSG__DETAIL__VECTOR3D__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "move_ws/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "move_ws/msg/detail/vector3d__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
bool cdr_serialize_move_ws__msg__Vector3d(
  const move_ws__msg__Vector3d * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
bool cdr_deserialize_move_ws__msg__Vector3d(
  eprosima::fastcdr::Cdr &,
  move_ws__msg__Vector3d * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
size_t get_serialized_size_move_ws__msg__Vector3d(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
size_t max_serialized_size_move_ws__msg__Vector3d(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
bool cdr_serialize_key_move_ws__msg__Vector3d(
  const move_ws__msg__Vector3d * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
size_t get_serialized_size_key_move_ws__msg__Vector3d(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
size_t max_serialized_size_key_move_ws__msg__Vector3d(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_move_ws
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, move_ws, msg, Vector3d)();

#ifdef __cplusplus
}
#endif

#endif  // MOVE_WS__MSG__DETAIL__VECTOR3D__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
