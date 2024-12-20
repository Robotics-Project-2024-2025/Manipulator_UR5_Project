// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from move_ws:srv/Moving.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "move_ws/srv/moving.h"


#ifndef MOVE_WS__SRV__DETAIL__MOVING__STRUCT_H_
#define MOVE_WS__SRV__DETAIL__MOVING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'xe1'
// Member 'phie1'
#include "move_ws/msg/detail/vector3d__struct.h"
// Member 'argv'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Moving in the package move_ws.
typedef struct move_ws__srv__Moving_Request
{
  move_ws__msg__Vector3d xe1;
  move_ws__msg__Vector3d phie1;
  int32_t argc;
  rosidl_runtime_c__String__Sequence argv;
} move_ws__srv__Moving_Request;

// Struct for a sequence of move_ws__srv__Moving_Request.
typedef struct move_ws__srv__Moving_Request__Sequence
{
  move_ws__srv__Moving_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_ws__srv__Moving_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/Moving in the package move_ws.
typedef struct move_ws__srv__Moving_Response
{
  bool result;
} move_ws__srv__Moving_Response;

// Struct for a sequence of move_ws__srv__Moving_Response.
typedef struct move_ws__srv__Moving_Response__Sequence
{
  move_ws__srv__Moving_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_ws__srv__Moving_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  move_ws__srv__Moving_Event__request__MAX_SIZE = 1
};
// response
enum
{
  move_ws__srv__Moving_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/Moving in the package move_ws.
typedef struct move_ws__srv__Moving_Event
{
  service_msgs__msg__ServiceEventInfo info;
  move_ws__srv__Moving_Request__Sequence request;
  move_ws__srv__Moving_Response__Sequence response;
} move_ws__srv__Moving_Event;

// Struct for a sequence of move_ws__srv__Moving_Event.
typedef struct move_ws__srv__Moving_Event__Sequence
{
  move_ws__srv__Moving_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} move_ws__srv__Moving_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOVE_WS__SRV__DETAIL__MOVING__STRUCT_H_
