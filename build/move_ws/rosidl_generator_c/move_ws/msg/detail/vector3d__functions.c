// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from move_ws:msg/Vector3d.idl
// generated code does not contain a copyright notice
#include "move_ws/msg/detail/vector3d__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
move_ws__msg__Vector3d__init(move_ws__msg__Vector3d * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // z
  return true;
}

void
move_ws__msg__Vector3d__fini(move_ws__msg__Vector3d * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // z
}

bool
move_ws__msg__Vector3d__are_equal(const move_ws__msg__Vector3d * lhs, const move_ws__msg__Vector3d * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  return true;
}

bool
move_ws__msg__Vector3d__copy(
  const move_ws__msg__Vector3d * input,
  move_ws__msg__Vector3d * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  return true;
}

move_ws__msg__Vector3d *
move_ws__msg__Vector3d__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  move_ws__msg__Vector3d * msg = (move_ws__msg__Vector3d *)allocator.allocate(sizeof(move_ws__msg__Vector3d), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(move_ws__msg__Vector3d));
  bool success = move_ws__msg__Vector3d__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
move_ws__msg__Vector3d__destroy(move_ws__msg__Vector3d * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    move_ws__msg__Vector3d__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
move_ws__msg__Vector3d__Sequence__init(move_ws__msg__Vector3d__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  move_ws__msg__Vector3d * data = NULL;

  if (size) {
    data = (move_ws__msg__Vector3d *)allocator.zero_allocate(size, sizeof(move_ws__msg__Vector3d), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = move_ws__msg__Vector3d__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        move_ws__msg__Vector3d__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
move_ws__msg__Vector3d__Sequence__fini(move_ws__msg__Vector3d__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      move_ws__msg__Vector3d__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

move_ws__msg__Vector3d__Sequence *
move_ws__msg__Vector3d__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  move_ws__msg__Vector3d__Sequence * array = (move_ws__msg__Vector3d__Sequence *)allocator.allocate(sizeof(move_ws__msg__Vector3d__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = move_ws__msg__Vector3d__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
move_ws__msg__Vector3d__Sequence__destroy(move_ws__msg__Vector3d__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    move_ws__msg__Vector3d__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
move_ws__msg__Vector3d__Sequence__are_equal(const move_ws__msg__Vector3d__Sequence * lhs, const move_ws__msg__Vector3d__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!move_ws__msg__Vector3d__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
move_ws__msg__Vector3d__Sequence__copy(
  const move_ws__msg__Vector3d__Sequence * input,
  move_ws__msg__Vector3d__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(move_ws__msg__Vector3d);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    move_ws__msg__Vector3d * data =
      (move_ws__msg__Vector3d *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!move_ws__msg__Vector3d__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          move_ws__msg__Vector3d__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!move_ws__msg__Vector3d__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
