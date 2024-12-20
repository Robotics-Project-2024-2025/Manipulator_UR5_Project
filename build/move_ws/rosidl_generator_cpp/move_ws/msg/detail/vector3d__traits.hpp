// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "move_ws/msg/vector3d.hpp"


#ifndef MOVE_WS__MSG__DETAIL__VECTOR3D__TRAITS_HPP_
#define MOVE_WS__MSG__DETAIL__VECTOR3D__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "move_ws/msg/detail/vector3d__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace move_ws
{

namespace msg
{

inline void to_flow_style_yaml(
  const Vector3d & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Vector3d & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Vector3d & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace move_ws

namespace rosidl_generator_traits
{

[[deprecated("use move_ws::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const move_ws::msg::Vector3d & msg,
  std::ostream & out, size_t indentation = 0)
{
  move_ws::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use move_ws::msg::to_yaml() instead")]]
inline std::string to_yaml(const move_ws::msg::Vector3d & msg)
{
  return move_ws::msg::to_yaml(msg);
}

template<>
inline const char * data_type<move_ws::msg::Vector3d>()
{
  return "move_ws::msg::Vector3d";
}

template<>
inline const char * name<move_ws::msg::Vector3d>()
{
  return "move_ws/msg/Vector3d";
}

template<>
struct has_fixed_size<move_ws::msg::Vector3d>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<move_ws::msg::Vector3d>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<move_ws::msg::Vector3d>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOVE_WS__MSG__DETAIL__VECTOR3D__TRAITS_HPP_
