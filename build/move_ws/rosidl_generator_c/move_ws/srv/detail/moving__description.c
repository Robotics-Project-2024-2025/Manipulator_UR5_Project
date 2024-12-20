// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from move_ws:srv/Moving.idl
// generated code does not contain a copyright notice

#include "move_ws/srv/detail/moving__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_move_ws
const rosidl_type_hash_t *
move_ws__srv__Moving__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x9b, 0x78, 0x12, 0x5f, 0x11, 0x21, 0xde, 0xfe,
      0xe6, 0x6a, 0x6d, 0x66, 0x38, 0xf3, 0xe1, 0x2f,
      0x7a, 0x16, 0xb7, 0x9b, 0x06, 0x66, 0xeb, 0x29,
      0x56, 0xb2, 0xca, 0xaf, 0xf4, 0x55, 0x76, 0xa1,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_move_ws
const rosidl_type_hash_t *
move_ws__srv__Moving_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x7c, 0xdf, 0x3e, 0xa3, 0xca, 0xfb, 0x1b, 0x95,
      0xab, 0x0d, 0x68, 0x19, 0x39, 0xde, 0xd9, 0x29,
      0x50, 0xe3, 0x2a, 0x50, 0x1b, 0x45, 0xfe, 0x46,
      0x3a, 0x22, 0x08, 0x1b, 0x4b, 0xba, 0xf9, 0x92,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_move_ws
const rosidl_type_hash_t *
move_ws__srv__Moving_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2e, 0x75, 0xec, 0x89, 0x18, 0x3b, 0x80, 0x56,
      0xbd, 0x47, 0xcb, 0x1e, 0xc8, 0x56, 0x9c, 0xd5,
      0x62, 0x48, 0x6a, 0x02, 0x27, 0xb2, 0x40, 0x3d,
      0x7d, 0xce, 0xe9, 0xf3, 0x74, 0xab, 0x22, 0xd1,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_move_ws
const rosidl_type_hash_t *
move_ws__srv__Moving_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x81, 0x77, 0xa7, 0x1a, 0x2d, 0xc9, 0x7c, 0xd1,
      0xca, 0xed, 0x96, 0x29, 0x1b, 0xa3, 0x60, 0xc3,
      0xe3, 0x39, 0x27, 0x2c, 0x8f, 0xe1, 0x5f, 0x09,
      0x1f, 0x95, 0xe4, 0x96, 0x78, 0xff, 0x56, 0x7e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "move_ws/msg/detail/vector3d__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t move_ws__msg__Vector3d__EXPECTED_HASH = {1, {
    0xd0, 0xc0, 0x29, 0xca, 0x95, 0x26, 0x31, 0x6e,
    0xfa, 0x3f, 0xc1, 0x79, 0xa1, 0x18, 0x48, 0xad,
    0x0e, 0x76, 0x97, 0x9c, 0xf3, 0x0e, 0xdd, 0x22,
    0x4b, 0xde, 0x7a, 0x02, 0x1f, 0x24, 0x05, 0xa9,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char move_ws__srv__Moving__TYPE_NAME[] = "move_ws/srv/Moving";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char move_ws__msg__Vector3d__TYPE_NAME[] = "move_ws/msg/Vector3d";
static char move_ws__srv__Moving_Event__TYPE_NAME[] = "move_ws/srv/Moving_Event";
static char move_ws__srv__Moving_Request__TYPE_NAME[] = "move_ws/srv/Moving_Request";
static char move_ws__srv__Moving_Response__TYPE_NAME[] = "move_ws/srv/Moving_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char move_ws__srv__Moving__FIELD_NAME__request_message[] = "request_message";
static char move_ws__srv__Moving__FIELD_NAME__response_message[] = "response_message";
static char move_ws__srv__Moving__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field move_ws__srv__Moving__FIELDS[] = {
  {
    {move_ws__srv__Moving__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {move_ws__srv__Moving_Request__TYPE_NAME, 26, 26},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {move_ws__srv__Moving_Response__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {move_ws__srv__Moving_Event__TYPE_NAME, 24, 24},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription move_ws__srv__Moving__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {move_ws__msg__Vector3d__TYPE_NAME, 20, 20},
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Event__TYPE_NAME, 24, 24},
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Request__TYPE_NAME, 26, 26},
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Response__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
move_ws__srv__Moving__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {move_ws__srv__Moving__TYPE_NAME, 18, 18},
      {move_ws__srv__Moving__FIELDS, 3, 3},
    },
    {move_ws__srv__Moving__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&move_ws__msg__Vector3d__EXPECTED_HASH, move_ws__msg__Vector3d__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = move_ws__msg__Vector3d__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = move_ws__srv__Moving_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = move_ws__srv__Moving_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = move_ws__srv__Moving_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char move_ws__srv__Moving_Request__FIELD_NAME__xe1[] = "xe1";
static char move_ws__srv__Moving_Request__FIELD_NAME__phie1[] = "phie1";
static char move_ws__srv__Moving_Request__FIELD_NAME__argc[] = "argc";
static char move_ws__srv__Moving_Request__FIELD_NAME__argv[] = "argv";

static rosidl_runtime_c__type_description__Field move_ws__srv__Moving_Request__FIELDS[] = {
  {
    {move_ws__srv__Moving_Request__FIELD_NAME__xe1, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {move_ws__msg__Vector3d__TYPE_NAME, 20, 20},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Request__FIELD_NAME__phie1, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {move_ws__msg__Vector3d__TYPE_NAME, 20, 20},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Request__FIELD_NAME__argc, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Request__FIELD_NAME__argv, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription move_ws__srv__Moving_Request__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {move_ws__msg__Vector3d__TYPE_NAME, 20, 20},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
move_ws__srv__Moving_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {move_ws__srv__Moving_Request__TYPE_NAME, 26, 26},
      {move_ws__srv__Moving_Request__FIELDS, 4, 4},
    },
    {move_ws__srv__Moving_Request__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&move_ws__msg__Vector3d__EXPECTED_HASH, move_ws__msg__Vector3d__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = move_ws__msg__Vector3d__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char move_ws__srv__Moving_Response__FIELD_NAME__result[] = "result";

static rosidl_runtime_c__type_description__Field move_ws__srv__Moving_Response__FIELDS[] = {
  {
    {move_ws__srv__Moving_Response__FIELD_NAME__result, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
move_ws__srv__Moving_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {move_ws__srv__Moving_Response__TYPE_NAME, 27, 27},
      {move_ws__srv__Moving_Response__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char move_ws__srv__Moving_Event__FIELD_NAME__info[] = "info";
static char move_ws__srv__Moving_Event__FIELD_NAME__request[] = "request";
static char move_ws__srv__Moving_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field move_ws__srv__Moving_Event__FIELDS[] = {
  {
    {move_ws__srv__Moving_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {move_ws__srv__Moving_Request__TYPE_NAME, 26, 26},
    },
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {move_ws__srv__Moving_Response__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription move_ws__srv__Moving_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {move_ws__msg__Vector3d__TYPE_NAME, 20, 20},
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Request__TYPE_NAME, 26, 26},
    {NULL, 0, 0},
  },
  {
    {move_ws__srv__Moving_Response__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
move_ws__srv__Moving_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {move_ws__srv__Moving_Event__TYPE_NAME, 24, 24},
      {move_ws__srv__Moving_Event__FIELDS, 3, 3},
    },
    {move_ws__srv__Moving_Event__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&move_ws__msg__Vector3d__EXPECTED_HASH, move_ws__msg__Vector3d__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = move_ws__msg__Vector3d__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = move_ws__srv__Moving_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = move_ws__srv__Moving_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "move_ws/Vector3d xe1\n"
  "move_ws/Vector3d phie1\n"
  "int32 argc\n"
  "string[] argv\n"
  "---\n"
  "bool result";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
move_ws__srv__Moving__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {move_ws__srv__Moving__TYPE_NAME, 18, 18},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 85, 85},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
move_ws__srv__Moving_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {move_ws__srv__Moving_Request__TYPE_NAME, 26, 26},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
move_ws__srv__Moving_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {move_ws__srv__Moving_Response__TYPE_NAME, 27, 27},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
move_ws__srv__Moving_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {move_ws__srv__Moving_Event__TYPE_NAME, 24, 24},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
move_ws__srv__Moving__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *move_ws__srv__Moving__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *move_ws__msg__Vector3d__get_individual_type_description_source(NULL);
    sources[3] = *move_ws__srv__Moving_Event__get_individual_type_description_source(NULL);
    sources[4] = *move_ws__srv__Moving_Request__get_individual_type_description_source(NULL);
    sources[5] = *move_ws__srv__Moving_Response__get_individual_type_description_source(NULL);
    sources[6] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
move_ws__srv__Moving_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *move_ws__srv__Moving_Request__get_individual_type_description_source(NULL),
    sources[1] = *move_ws__msg__Vector3d__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
move_ws__srv__Moving_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *move_ws__srv__Moving_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
move_ws__srv__Moving_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *move_ws__srv__Moving_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *move_ws__msg__Vector3d__get_individual_type_description_source(NULL);
    sources[3] = *move_ws__srv__Moving_Request__get_individual_type_description_source(NULL);
    sources[4] = *move_ws__srv__Moving_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
