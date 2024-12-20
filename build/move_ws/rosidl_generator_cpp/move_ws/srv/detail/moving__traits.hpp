// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from move_ws:srv/Moving.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "move_ws/srv/moving.hpp"


#ifndef MOVE_WS__SRV__DETAIL__MOVING__TRAITS_HPP_
#define MOVE_WS__SRV__DETAIL__MOVING__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "move_ws/srv/detail/moving__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'xe1'
// Member 'phie1'
#include "move_ws/msg/detail/vector3d__traits.hpp"

namespace move_ws
{

namespace srv
{

inline void to_flow_style_yaml(
  const Moving_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: xe1
  {
    out << "xe1: ";
    to_flow_style_yaml(msg.xe1, out);
    out << ", ";
  }

  // member: phie1
  {
    out << "phie1: ";
    to_flow_style_yaml(msg.phie1, out);
    out << ", ";
  }

  // member: argc
  {
    out << "argc: ";
    rosidl_generator_traits::value_to_yaml(msg.argc, out);
    out << ", ";
  }

  // member: argv
  {
    if (msg.argv.size() == 0) {
      out << "argv: []";
    } else {
      out << "argv: [";
      size_t pending_items = msg.argv.size();
      for (auto item : msg.argv) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Moving_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: xe1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "xe1:\n";
    to_block_style_yaml(msg.xe1, out, indentation + 2);
  }

  // member: phie1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "phie1:\n";
    to_block_style_yaml(msg.phie1, out, indentation + 2);
  }

  // member: argc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "argc: ";
    rosidl_generator_traits::value_to_yaml(msg.argc, out);
    out << "\n";
  }

  // member: argv
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.argv.size() == 0) {
      out << "argv: []\n";
    } else {
      out << "argv:\n";
      for (auto item : msg.argv) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Moving_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace move_ws

namespace rosidl_generator_traits
{

[[deprecated("use move_ws::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const move_ws::srv::Moving_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  move_ws::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use move_ws::srv::to_yaml() instead")]]
inline std::string to_yaml(const move_ws::srv::Moving_Request & msg)
{
  return move_ws::srv::to_yaml(msg);
}

template<>
inline const char * data_type<move_ws::srv::Moving_Request>()
{
  return "move_ws::srv::Moving_Request";
}

template<>
inline const char * name<move_ws::srv::Moving_Request>()
{
  return "move_ws/srv/Moving_Request";
}

template<>
struct has_fixed_size<move_ws::srv::Moving_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<move_ws::srv::Moving_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<move_ws::srv::Moving_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace move_ws
{

namespace srv
{

inline void to_flow_style_yaml(
  const Moving_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: result
  {
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Moving_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Moving_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace move_ws

namespace rosidl_generator_traits
{

[[deprecated("use move_ws::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const move_ws::srv::Moving_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  move_ws::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use move_ws::srv::to_yaml() instead")]]
inline std::string to_yaml(const move_ws::srv::Moving_Response & msg)
{
  return move_ws::srv::to_yaml(msg);
}

template<>
inline const char * data_type<move_ws::srv::Moving_Response>()
{
  return "move_ws::srv::Moving_Response";
}

template<>
inline const char * name<move_ws::srv::Moving_Response>()
{
  return "move_ws/srv/Moving_Response";
}

template<>
struct has_fixed_size<move_ws::srv::Moving_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<move_ws::srv::Moving_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<move_ws::srv::Moving_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace move_ws
{

namespace srv
{

inline void to_flow_style_yaml(
  const Moving_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Moving_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Moving_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace move_ws

namespace rosidl_generator_traits
{

[[deprecated("use move_ws::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const move_ws::srv::Moving_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  move_ws::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use move_ws::srv::to_yaml() instead")]]
inline std::string to_yaml(const move_ws::srv::Moving_Event & msg)
{
  return move_ws::srv::to_yaml(msg);
}

template<>
inline const char * data_type<move_ws::srv::Moving_Event>()
{
  return "move_ws::srv::Moving_Event";
}

template<>
inline const char * name<move_ws::srv::Moving_Event>()
{
  return "move_ws/srv/Moving_Event";
}

template<>
struct has_fixed_size<move_ws::srv::Moving_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<move_ws::srv::Moving_Event>
  : std::integral_constant<bool, has_bounded_size<move_ws::srv::Moving_Request>::value && has_bounded_size<move_ws::srv::Moving_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<move_ws::srv::Moving_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<move_ws::srv::Moving>()
{
  return "move_ws::srv::Moving";
}

template<>
inline const char * name<move_ws::srv::Moving>()
{
  return "move_ws/srv/Moving";
}

template<>
struct has_fixed_size<move_ws::srv::Moving>
  : std::integral_constant<
    bool,
    has_fixed_size<move_ws::srv::Moving_Request>::value &&
    has_fixed_size<move_ws::srv::Moving_Response>::value
  >
{
};

template<>
struct has_bounded_size<move_ws::srv::Moving>
  : std::integral_constant<
    bool,
    has_bounded_size<move_ws::srv::Moving_Request>::value &&
    has_bounded_size<move_ws::srv::Moving_Response>::value
  >
{
};

template<>
struct is_service<move_ws::srv::Moving>
  : std::true_type
{
};

template<>
struct is_service_request<move_ws::srv::Moving_Request>
  : std::true_type
{
};

template<>
struct is_service_response<move_ws::srv::Moving_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MOVE_WS__SRV__DETAIL__MOVING__TRAITS_HPP_
