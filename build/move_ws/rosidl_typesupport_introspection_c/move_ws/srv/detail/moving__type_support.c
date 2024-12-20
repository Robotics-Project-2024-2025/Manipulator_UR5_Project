// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from move_ws:srv/Moving.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "move_ws/srv/detail/moving__rosidl_typesupport_introspection_c.h"
#include "move_ws/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "move_ws/srv/detail/moving__functions.h"
#include "move_ws/srv/detail/moving__struct.h"


// Include directives for member types
// Member `xe1`
// Member `phie1`
#include "move_ws/msg/vector3d.h"
// Member `xe1`
// Member `phie1`
#include "move_ws/msg/detail/vector3d__rosidl_typesupport_introspection_c.h"
// Member `argv`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  move_ws__srv__Moving_Request__init(message_memory);
}

void move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_fini_function(void * message_memory)
{
  move_ws__srv__Moving_Request__fini(message_memory);
}

size_t move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__size_function__Moving_Request__argv(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__get_const_function__Moving_Request__argv(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__get_function__Moving_Request__argv(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__fetch_function__Moving_Request__argv(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__get_const_function__Moving_Request__argv(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__assign_function__Moving_Request__argv(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__get_function__Moving_Request__argv(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__resize_function__Moving_Request__argv(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_member_array[4] = {
  {
    "xe1",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__srv__Moving_Request, xe1),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "phie1",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__srv__Moving_Request, phie1),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "argc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__srv__Moving_Request, argc),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "argv",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__srv__Moving_Request, argv),  // bytes offset in struct
    NULL,  // default value
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__size_function__Moving_Request__argv,  // size() function pointer
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__get_const_function__Moving_Request__argv,  // get_const(index) function pointer
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__get_function__Moving_Request__argv,  // get(index) function pointer
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__fetch_function__Moving_Request__argv,  // fetch(index, &value) function pointer
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__assign_function__Moving_Request__argv,  // assign(index, value) function pointer
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__resize_function__Moving_Request__argv  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_members = {
  "move_ws__srv",  // message namespace
  "Moving_Request",  // message name
  4,  // number of fields
  sizeof(move_ws__srv__Moving_Request),
  false,  // has_any_key_member_
  move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_member_array,  // message members
  move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_type_support_handle = {
  0,
  &move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_members,
  get_message_typesupport_handle_function,
  &move_ws__srv__Moving_Request__get_type_hash,
  &move_ws__srv__Moving_Request__get_type_description,
  &move_ws__srv__Moving_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_move_ws
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Request)() {
  move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, msg, Vector3d)();
  move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, msg, Vector3d)();
  if (!move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_type_support_handle.typesupport_identifier) {
    move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "move_ws/srv/detail/moving__rosidl_typesupport_introspection_c.h"
// already included above
// #include "move_ws/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "move_ws/srv/detail/moving__functions.h"
// already included above
// #include "move_ws/srv/detail/moving__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  move_ws__srv__Moving_Response__init(message_memory);
}

void move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_fini_function(void * message_memory)
{
  move_ws__srv__Moving_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_member_array[1] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__srv__Moving_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_members = {
  "move_ws__srv",  // message namespace
  "Moving_Response",  // message name
  1,  // number of fields
  sizeof(move_ws__srv__Moving_Response),
  false,  // has_any_key_member_
  move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_member_array,  // message members
  move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_type_support_handle = {
  0,
  &move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_members,
  get_message_typesupport_handle_function,
  &move_ws__srv__Moving_Response__get_type_hash,
  &move_ws__srv__Moving_Response__get_type_description,
  &move_ws__srv__Moving_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_move_ws
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Response)() {
  if (!move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_type_support_handle.typesupport_identifier) {
    move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "move_ws/srv/detail/moving__rosidl_typesupport_introspection_c.h"
// already included above
// #include "move_ws/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "move_ws/srv/detail/moving__functions.h"
// already included above
// #include "move_ws/srv/detail/moving__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "move_ws/srv/moving.h"
// Member `request`
// Member `response`
// already included above
// #include "move_ws/srv/detail/moving__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  move_ws__srv__Moving_Event__init(message_memory);
}

void move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_fini_function(void * message_memory)
{
  move_ws__srv__Moving_Event__fini(message_memory);
}

size_t move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__size_function__Moving_Event__request(
  const void * untyped_member)
{
  const move_ws__srv__Moving_Request__Sequence * member =
    (const move_ws__srv__Moving_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_const_function__Moving_Event__request(
  const void * untyped_member, size_t index)
{
  const move_ws__srv__Moving_Request__Sequence * member =
    (const move_ws__srv__Moving_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_function__Moving_Event__request(
  void * untyped_member, size_t index)
{
  move_ws__srv__Moving_Request__Sequence * member =
    (move_ws__srv__Moving_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__fetch_function__Moving_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const move_ws__srv__Moving_Request * item =
    ((const move_ws__srv__Moving_Request *)
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_const_function__Moving_Event__request(untyped_member, index));
  move_ws__srv__Moving_Request * value =
    (move_ws__srv__Moving_Request *)(untyped_value);
  *value = *item;
}

void move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__assign_function__Moving_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  move_ws__srv__Moving_Request * item =
    ((move_ws__srv__Moving_Request *)
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_function__Moving_Event__request(untyped_member, index));
  const move_ws__srv__Moving_Request * value =
    (const move_ws__srv__Moving_Request *)(untyped_value);
  *item = *value;
}

bool move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__resize_function__Moving_Event__request(
  void * untyped_member, size_t size)
{
  move_ws__srv__Moving_Request__Sequence * member =
    (move_ws__srv__Moving_Request__Sequence *)(untyped_member);
  move_ws__srv__Moving_Request__Sequence__fini(member);
  return move_ws__srv__Moving_Request__Sequence__init(member, size);
}

size_t move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__size_function__Moving_Event__response(
  const void * untyped_member)
{
  const move_ws__srv__Moving_Response__Sequence * member =
    (const move_ws__srv__Moving_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_const_function__Moving_Event__response(
  const void * untyped_member, size_t index)
{
  const move_ws__srv__Moving_Response__Sequence * member =
    (const move_ws__srv__Moving_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_function__Moving_Event__response(
  void * untyped_member, size_t index)
{
  move_ws__srv__Moving_Response__Sequence * member =
    (move_ws__srv__Moving_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__fetch_function__Moving_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const move_ws__srv__Moving_Response * item =
    ((const move_ws__srv__Moving_Response *)
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_const_function__Moving_Event__response(untyped_member, index));
  move_ws__srv__Moving_Response * value =
    (move_ws__srv__Moving_Response *)(untyped_value);
  *value = *item;
}

void move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__assign_function__Moving_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  move_ws__srv__Moving_Response * item =
    ((move_ws__srv__Moving_Response *)
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_function__Moving_Event__response(untyped_member, index));
  const move_ws__srv__Moving_Response * value =
    (const move_ws__srv__Moving_Response *)(untyped_value);
  *item = *value;
}

bool move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__resize_function__Moving_Event__response(
  void * untyped_member, size_t size)
{
  move_ws__srv__Moving_Response__Sequence * member =
    (move_ws__srv__Moving_Response__Sequence *)(untyped_member);
  move_ws__srv__Moving_Response__Sequence__fini(member);
  return move_ws__srv__Moving_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(move_ws__srv__Moving_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(move_ws__srv__Moving_Event, request),  // bytes offset in struct
    NULL,  // default value
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__size_function__Moving_Event__request,  // size() function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_const_function__Moving_Event__request,  // get_const(index) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_function__Moving_Event__request,  // get(index) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__fetch_function__Moving_Event__request,  // fetch(index, &value) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__assign_function__Moving_Event__request,  // assign(index, value) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__resize_function__Moving_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(move_ws__srv__Moving_Event, response),  // bytes offset in struct
    NULL,  // default value
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__size_function__Moving_Event__response,  // size() function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_const_function__Moving_Event__response,  // get_const(index) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__get_function__Moving_Event__response,  // get(index) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__fetch_function__Moving_Event__response,  // fetch(index, &value) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__assign_function__Moving_Event__response,  // assign(index, value) function pointer
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__resize_function__Moving_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_members = {
  "move_ws__srv",  // message namespace
  "Moving_Event",  // message name
  3,  // number of fields
  sizeof(move_ws__srv__Moving_Event),
  false,  // has_any_key_member_
  move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_member_array,  // message members
  move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_type_support_handle = {
  0,
  &move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_members,
  get_message_typesupport_handle_function,
  &move_ws__srv__Moving_Event__get_type_hash,
  &move_ws__srv__Moving_Event__get_type_description,
  &move_ws__srv__Moving_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_move_ws
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Event)() {
  move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Request)();
  move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Response)();
  if (!move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_type_support_handle.typesupport_identifier) {
    move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "move_ws/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "move_ws/srv/detail/moving__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_service_members = {
  "move_ws__srv",  // service namespace
  "Moving",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_Request_message_type_support_handle,
  NULL,  // response message
  // move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_Response_message_type_support_handle
  NULL  // event_message
  // move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_Response_message_type_support_handle
};


static rosidl_service_type_support_t move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_service_type_support_handle = {
  0,
  &move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_service_members,
  get_service_typesupport_handle_function,
  &move_ws__srv__Moving_Request__rosidl_typesupport_introspection_c__Moving_Request_message_type_support_handle,
  &move_ws__srv__Moving_Response__rosidl_typesupport_introspection_c__Moving_Response_message_type_support_handle,
  &move_ws__srv__Moving_Event__rosidl_typesupport_introspection_c__Moving_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    move_ws,
    srv,
    Moving
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    move_ws,
    srv,
    Moving
  ),
  &move_ws__srv__Moving__get_type_hash,
  &move_ws__srv__Moving__get_type_description,
  &move_ws__srv__Moving__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_move_ws
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving)(void) {
  if (!move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_service_type_support_handle.typesupport_identifier) {
    move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, move_ws, srv, Moving_Event)()->data;
  }

  return &move_ws__srv__detail__moving__rosidl_typesupport_introspection_c__Moving_service_type_support_handle;
}
