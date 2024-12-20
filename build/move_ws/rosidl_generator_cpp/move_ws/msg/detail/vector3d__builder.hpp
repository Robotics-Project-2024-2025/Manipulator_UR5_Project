// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "move_ws/msg/vector3d.hpp"


#ifndef MOVE_WS__MSG__DETAIL__VECTOR3D__BUILDER_HPP_
#define MOVE_WS__MSG__DETAIL__VECTOR3D__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "move_ws/msg/detail/vector3d__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace move_ws
{

namespace msg
{

namespace builder
{

class Init_Vector3d_z
{
public:
  explicit Init_Vector3d_z(::move_ws::msg::Vector3d & msg)
  : msg_(msg)
  {}
  ::move_ws::msg::Vector3d z(::move_ws::msg::Vector3d::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_ws::msg::Vector3d msg_;
};

class Init_Vector3d_y
{
public:
  explicit Init_Vector3d_y(::move_ws::msg::Vector3d & msg)
  : msg_(msg)
  {}
  Init_Vector3d_z y(::move_ws::msg::Vector3d::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Vector3d_z(msg_);
  }

private:
  ::move_ws::msg::Vector3d msg_;
};

class Init_Vector3d_x
{
public:
  Init_Vector3d_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Vector3d_y x(::move_ws::msg::Vector3d::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Vector3d_y(msg_);
  }

private:
  ::move_ws::msg::Vector3d msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_ws::msg::Vector3d>()
{
  return move_ws::msg::builder::Init_Vector3d_x();
}

}  // namespace move_ws

#endif  // MOVE_WS__MSG__DETAIL__VECTOR3D__BUILDER_HPP_
