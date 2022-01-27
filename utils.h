#pragma once

#if defined(__aarch64__)
#include "And64InlineHook/And64InlineHook.hpp
#define HookFunction A64HookFunction
#else
#include "Substrate/CydiaSubstrate.h
#define HookFunction MSHookFunction
#endif