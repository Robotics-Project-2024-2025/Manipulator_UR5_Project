// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice

#include "move_ws/msg/detail/vector3d__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_move_ws
const rosidl_type_hash_t *
move_ws__msg__Vector3d__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xd0, 0xc0, 0x29, 0xca, 0x95, 0x26, 0x31, 0x6e,
      0xfa, 0x3f, 0xc1, 0x79, 0xa1, 0x18, 0x48, 0xad,
      0x0e, 0x76, 0x97, 0x9c, 0xf3, 0x0e, 0xdd, 0x22,
      0x4b, 0xde, 0x7a, 0x02, 0x1f, 0x24, 0x05, 0xa9,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char move_ws__msg__Vector3d__TYPE_NAME[] = "move_ws/msg/Vector3d";

// Define type names, field names, and default values
static char move_ws__msg__Vector3d__FIELD_NAME__x[] = "x";
static char move_ws__msg__Vector3d__FIELD_NAME__y[] = "y";
static char move_ws__msg__Vector3d__FIELD_NAME__z[] = "z";

static rosidl_runtime_c__type_description__Field move_ws__msg__Vector3d__FIELDS[] = {
  {
    {move_ws__msg__Vector3d__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__msg__Vector3d__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__msg__Vector3d__FIELD_NAME__z, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
move_ws__msg__Vector3d__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {move_ws__msg__Vector3d__TYPE_NAME, 20, 20},
      {move_ws__msg__Vector3d__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 x\n"
  "float32 y\n"
  "float32 z";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
move_ws__msg__Vector3d__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {move_ws__msg__Vector3d__TYPE_NAME, 20, 20},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 30, 30},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
move_ws__msg__Vector3d__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *move_ws__msg__Vector3d__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
