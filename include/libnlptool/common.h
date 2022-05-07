// Copyright 2016 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.!

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#if defined(_WIN32) && !defined(__CYGWIN__)
#define OS_WIN
#else
#define OS_UNIX
#endif

#ifdef OS_WIN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t char32;
typedef uint32_t uint32;
typedef uint64_t uint64;

static constexpr uint8 kuint8max = ((uint8)0xFF);
static constexpr uint16 kuint16max = ((uint16)0xFFFF);
static constexpr uint32 kuint32max = ((uint32)0xFFFFFFFF);
static constexpr uint64 kuint64max = ((uint64)(0xFFFFFFFFFFFFFFFF));
static constexpr int8 kint8min = ((int8)~0x7F);
static constexpr int8 kint8max = ((int8)0x7F);
static constexpr int16 kint16min = ((int16)~0x7FFF);
static constexpr int16 kint16max = ((int16)0x7FFF);
static constexpr int32 kint32min = ((int32)~0x7FFFFFFF);
static constexpr int32 kint32max = ((int32)0x7FFFFFFF);
static constexpr int64 kint64min = ((int64)(~0x7FFFFFFFFFFFFFFF));
static constexpr int64 kint64max = ((int64)(0x7FFFFFFFFFFFFFFF));

static constexpr uint32 kUnicodeError = 0xFFFD;

#if defined(OS_WIN) && defined(UNICODE) && defined(_UNICODE)
#define WPATH(path) (::nlptools::Utf8ToWide(path).c_str())
#else
#define WPATH(path) (path)
#endif

template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];

#ifndef _MSC_VER
template <typename T, size_t N>
char (&ArraySizeHelper(const T (&array)[N]))[N];
#endif  // !_MSC_VER

#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#endif