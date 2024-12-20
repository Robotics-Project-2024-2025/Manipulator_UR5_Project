// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from move_ws:srv/Moving.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "move_ws/srv/moving.hpp"


#ifndef MOVE_WS__SRV__DETAIL__MOVING__BUILDER_HPP_
#define MOVE_WS__SRV__DETAIL__MOVING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "move_ws/srv/detail/moving__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace move_ws
{

namespace srv
{

namespace builder
{

class Init_Moving_Request_argv
{
public:
  explicit Init_Moving_Request_argv(::move_ws::srv::Moving_Request & msg)
  : msg_(msg)
  {}
  ::move_ws::srv::Moving_Request argv(::move_ws::srv::Moving_Request::_argv_type arg)
  {
    msg_.argv = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_ws::srv::Moving_Request msg_;
};

class Init_Moving_Request_argc
{
public:
  explicit Init_Moving_Request_argc(::move_ws::srv::Moving_Request & msg)
  : msg_(msg)
  {}
  Init_Moving_Request_argv argc(::move_ws::srv::Moving_Request::_argc_type arg)
  {
    msg_.argc = std::move(arg);
    return Init_Moving_Request_argv(msg_);
  }

private:
  ::move_ws::srv::Moving_Request msg_;
};

class Init_Moving_Request_phie1
{
public:
  explicit Init_Moving_Request_phie1(::move_ws::srv::Moving_Request & msg)
  : msg_(msg)
  {}
  Init_Moving_Request_argc phie1(::move_ws::srv::Moving_Request::_phie1_type arg)
  {
    msg_.phie1 = std::move(arg);
    return Init_Moving_Request_argc(msg_);
  }

private:
  ::move_ws::srv::Moving_Request msg_;
};

class Init_Moving_Request_xe1
{
public:
  Init_Moving_Request_xe1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Moving_Request_phie1 xe1(::move_ws::srv::Moving_Request::_xe1_type arg)
  {
    msg_.xe1 = std::move(arg);
    return Init_Moving_Request_phie1(msg_);
  }

private:
  ::move_ws::srv::Moving_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_ws::srv::Moving_Request>()
{
  return move_ws::srv::builder::Init_Moving_Request_xe1();
}

}  // namespace move_ws


namespace move_ws
{

namespace srv
{

namespace builder
{

class Init_Moving_Response_result
{
public:
  Init_Moving_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::move_ws::srv::Moving_Response result(::move_ws::srv::Moving_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_ws::srv::Moving_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_ws::srv::Moving_Response>()
{
  return move_ws::srv::builder::Init_Moving_Response_result();
}

}  // namespace move_ws


namespace move_ws
{

namespace srv
{

namespace builder
{

class Init_Moving_Event_response
{
public:
  explicit Init_Moving_Event_response(::move_ws::srv::Moving_Event & msg)
  : msg_(msg)
  {}
  ::move_ws::srv::Moving_Event response(::move_ws::srv::Moving_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::move_ws::srv::Moving_Event msg_;
};

class Init_Moving_Event_request
{
public:
  explicit Init_Moving_Event_request(::move_ws::srv::Moving_Event & msg)
  : msg_(msg)
  {}
  Init_Moving_Event_response request(::move_ws::srv::Moving_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Moving_Event_response(msg_);
  }

private:
  ::move_ws::srv::Moving_Event msg_;
};

class Init_Moving_Event_info
{
public:
  Init_Moving_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Moving_Event_request info(::move_ws::srv::Moving_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Moving_Event_request(msg_);
  }

private:
  ::move_ws::srv::Moving_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::move_ws::srv::Moving_Event>()
{
  return move_ws::srv::builder::Init_Moving_Event_info();
}

}  // namespace move_ws

#endif  // MOVE_WS__SRV__DETAIL__MOVING__BUILDER_HPP_
