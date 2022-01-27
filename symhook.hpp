#pragma once

#include <dlfcn.h>
#include <string>
#include <unistd.h>

#include "il2cpp.hpp"
#include "utils.h"

class Symhook {
  void *handle;
  long baseAddr = 0;

  template <typename R, typename... Types>
  static constexpr size_t getArgumentCount(R (*f)(Types...)) {
    return sizeof...(Types);
  }

public:
  Il2Cpp *il2cpp;

  Symhook(const char *moduleName);

  static void Wait(const char *moduleName);
  static unsigned long GetBaseAddr(const char *moduleName);

  template <typename A, typename B>
  void hook(void *ptr, A replace, B original);

  template <typename A, typename B>
  void hook(unsigned long offset, A replace, B original);

  template <typename A, typename B>
  void hook(const char *symbol, A replace, B original);

  template <typename A, typename B>
  void hook(const char *className, const char *fn, A replace, B original);

  template <typename A, typename B>
  void hook(const char *namespaze, const char *className, const char *fn, A replace, B original);

  template <typename A, typename B>
  void hook(const char *assemblyName, const char *namespaze, const char *className, const char *fn, A replace, B original);
};

Symhook::Symhook(const char *moduleName) {
  Wait(moduleName);
  while (handle == NULL) {
    handle = dlopen(moduleName, RTLD_LAZY);
  }

  if (strstr(moduleName, "libil2cpp.so")) {
    il2cpp = new Il2Cpp(handle);
  }
}

void Symhook::Wait(const char *moduleName) {
  while (GetBaseAddr(moduleName) == 0) {
  }
}

unsigned long Symhook::GetBaseAddr(const char *moduleName) {
  FILE *file;
  unsigned long addr = 0;

  char filePath[256], lineBuffer[1024];
  snprintf(filePath, sizeof(filePath), "/proc/self/maps");

  file = fopen(filePath, "r");
  if (file) {
    while (fgets(lineBuffer, sizeof(lineBuffer), file)) {
      if (strstr(lineBuffer, moduleName)) {
        addr = strtoul(lineBuffer, NULL, 16);
        if (addr == 0x8000) {
          addr = 0;
        }
        break;
      }
    }
    fclose(file);
  }
  return addr;
}

template <typename A, typename B>
void Symhook::hook(void *ptr, A replace, B original) {
  if (ptr != NULL) {
    while (*(void **)original == NULL) {
      HookFunction(ptr, (void *)replace, original ? (void **)original : NULL);
    }
  }
}

template <typename A, typename B>
void Symhook::hook(unsigned long offset, A replace, B original) {
  if (offset) {
    hook((void *)(baseAddr + offset), replace, original);
  }
}

template <typename A, typename B>
void Symhook::hook(const char *symbol, A replace, B original) {
  if (symbol) {
    hook(dlsym(handle, symbol), replace, original);
  }
}

template <typename A, typename B>
void Symhook::hook(const char *className, const char *fn, A replace, B original) {
  hook("", className, fn, replace, original);
}

template <typename A, typename B>
void Symhook::hook(const char *namespaze, const char *className, const char *fn, A replace, B original) {
  hook(NULL, namespaze, className, fn, replace, original);
}

template <typename A, typename B>
void Symhook::hook(const char *assemblyName, const char *namespaze, const char *className, const char *fn, A replace, B original) {
  if (assemblyName == NULL) {
    assemblyName = "Assembly-CSharp.dll";
  }
  auto klass = il2cpp->GetClass(assemblyName, namespaze, className);
  if (klass != NULL) {
    auto method = il2cpp->GetMethod(klass, fn, getArgumentCount(replace) - 1);
    if (method != NULL) {
      hook((void *)method->methodPointer, replace, original);
    }
  }
}
