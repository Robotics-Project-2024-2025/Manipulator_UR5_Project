// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "move_ws/msg/vector3d.h"


#ifndef MOVE_WS__MSG__DETAIL__VECTOR3D__STRUCT_H_
#define MOVE_WS__MSG__DETAIL__VECTOR3D__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Vector3d in the package move_ws.
typedef struct move_ws__msg__Vector3d
{
  float x;
  float y;
  float z;
} move_ws__msg__Vector3d;

// Struct for a sequence of move_ws__msg__Vector3d.
typedef struct move_ws__msg__Vector3d__Sequence
{
  move_ws__msg__Vector3d * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_ws__msg__Vector3d__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOVE_WS__MSG__DETAIL__VECTOR3D__STRUCT_H_
