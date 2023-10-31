#pragma once

#define WTS_NONCOPYABLE(Class)             \
  Class(const Class&)            = delete; \
  Class& operator=(const Class&) = delete
