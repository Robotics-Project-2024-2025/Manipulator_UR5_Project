// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from move_ws:srv/Moving.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "move_ws/srv/moving.hpp"


#ifndef MOVE_WS__SRV__DETAIL__MOVING__STRUCT_HPP_
#define MOVE_WS__SRV__DETAIL__MOVING__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'xe1'
// Member 'phie1'
#include "move_ws/msg/detail/vector3d__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__move_ws__srv__Moving_Request __attribute__((deprecated))
#else
# define DEPRECATED__move_ws__srv__Moving_Request __declspec(deprecated)
#endif

namespace move_ws
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Moving_Request_
{
  using Type = Moving_Request_<ContainerAllocator>;

  explicit Moving_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : xe1(_init),
    phie1(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->argc = 0l;
    }
  }

  explicit Moving_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : xe1(_alloc, _init),
    phie1(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->argc = 0l;
    }
  }

  // field types and members
  using _xe1_type =
    move_ws::msg::Vector3d_<ContainerAllocator>;
  _xe1_type xe1;
  using _phie1_type =
    move_ws::msg::Vector3d_<ContainerAllocator>;
  _phie1_type phie1;
  using _argc_type =
    int32_t;
  _argc_type argc;
  using _argv_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _argv_type argv;

  // setters for named parameter idiom
  Type & set__xe1(
    const move_ws::msg::Vector3d_<ContainerAllocator> & _arg)
  {
    this->xe1 = _arg;
    return *this;
  }
  Type & set__phie1(
    const move_ws::msg::Vector3d_<ContainerAllocator> & _arg)
  {
    this->phie1 = _arg;
    return *this;
  }
  Type & set__argc(
    const int32_t & _arg)
  {
    this->argc = _arg;
    return *this;
  }
  Type & set__argv(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->argv = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    move_ws::srv::Moving_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const move_ws::srv::Moving_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<move_ws::srv::Moving_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<move_ws::srv::Moving_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      move_ws::srv::Moving_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<move_ws::srv::Moving_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      move_ws::srv::Moving_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<move_ws::srv::Moving_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<move_ws::srv::Moving_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<move_ws::srv::Moving_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__move_ws__srv__Moving_Request
    std::shared_ptr<move_ws::srv::Moving_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__move_ws__srv__Moving_Request
    std::shared_ptr<move_ws::srv::Moving_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Moving_Request_ & other) const
  {
    if (this->xe1 != other.xe1) {
      return false;
    }
    if (this->phie1 != other.phie1) {
      return false;
    }
    if (this->argc != other.argc) {
      return false;
    }
    if (this->argv != other.argv) {
      return false;
    }
    return true;
  }
  bool operator!=(const Moving_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Moving_Request_

// alias to use template instance with default allocator
using Moving_Request =
  move_ws::srv::Moving_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace move_ws


#ifndef _WIN32
# define DEPRECATED__move_ws__srv__Moving_Response __attribute__((deprecated))
#else
# define DEPRECATED__move_ws__srv__Moving_Response __declspec(deprecated)
#endif

namespace move_ws
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Moving_Response_
{
  using Type = Moving_Response_<ContainerAllocator>;

  explicit Moving_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = false;
    }
  }

  explicit Moving_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = false;
    }
  }

  // field types and members
  using _result_type =
    bool;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const bool & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    move_ws::srv::Moving_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const move_ws::srv::Moving_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<move_ws::srv::Moving_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<move_ws::srv::Moving_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      move_ws::srv::Moving_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<move_ws::srv::Moving_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      move_ws::srv::Moving_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<move_ws::srv::Moving_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<move_ws::srv::Moving_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<move_ws::srv::Moving_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__move_ws__srv__Moving_Response
    std::shared_ptr<move_ws::srv::Moving_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__move_ws__srv__Moving_Response
    std::shared_ptr<move_ws::srv::Moving_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Moving_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const Moving_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Moving_Response_

// alias to use template instance with default allocator
using Moving_Response =
  move_ws::srv::Moving_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace move_ws


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__move_ws__srv__Moving_Event __attribute__((deprecated))
#else
# define DEPRECATED__move_ws__srv__Moving_Event __declspec(deprecated)
#endif

namespace move_ws
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Moving_Event_
{
  using Type = Moving_Event_<ContainerAllocator>;

  explicit Moving_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit Moving_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<move_ws::srv::Moving_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<move_ws::srv::Moving_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<move_ws::srv::Moving_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<move_ws::srv::Moving_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<move_ws::srv::Moving_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<move_ws::srv::Moving_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<move_ws::srv::Moving_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<move_ws::srv::Moving_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    move_ws::srv::Moving_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const move_ws::srv::Moving_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<move_ws::srv::Moving_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<move_ws::srv::Moving_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      move_ws::srv::Moving_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<move_ws::srv::Moving_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      move_ws::srv::Moving_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<move_ws::srv::Moving_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<move_ws::srv::Moving_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<move_ws::srv::Moving_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__move_ws__srv__Moving_Event
    std::shared_ptr<move_ws::srv::Moving_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__move_ws__srv__Moving_Event
    std::shared_ptr<move_ws::srv::Moving_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Moving_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const Moving_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Moving_Event_

// alias to use template instance with default allocator
using Moving_Event =
  move_ws::srv::Moving_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace move_ws

namespace move_ws
{

namespace srv
{

struct Moving
{
  using Request = move_ws::srv::Moving_Request;
  using Response = move_ws::srv::Moving_Response;
  using Event = move_ws::srv::Moving_Event;
};

}  // namespace srv

}  // namespace move_ws

#endif  // MOVE_WS__SRV__DETAIL__MOVING__STRUCT_HPP_
