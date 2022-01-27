#pragma once

#include <map>
#include <string>

#include "types.h"
#include "utils.h"

class Il2Cpp {
  static Il2CppDomain *(*getDomain)(void);
  static Il2CppAssembly *(*openAssembly)(Il2CppDomain *domain, const char *name);
  static const Il2CppImage *(*assemblyGetImage)(Il2CppAssembly *assembly);
  static Il2CppClass *(*getClass)(const Il2CppImage *image, const char *namespaze, const char *name);
  static const MethodInfo *(*getMethod)(Il2CppClass *klass, const char *fn, int argsCount);

public:
  Il2Cpp(void *handle);

  Il2CppClass *GetClass(const char *namespaze, const char *name);
  Il2CppClass *GetClass(const char *assemblyName, const char *namespaze, const char *name);

  const MethodInfo *GetMethod(Il2CppClass *klass, const char *name, int argsCount);
};

Il2CppDomain *(*Il2Cpp::getDomain)(void);
Il2CppAssembly *(*Il2Cpp::openAssembly)(Il2CppDomain *domain, const char *name);
const Il2CppImage *(*Il2Cpp::assemblyGetImage)(Il2CppAssembly *assembly);
Il2CppClass *(*Il2Cpp::getClass)(const Il2CppImage *image, const char *namespaze, const char *name);
const MethodInfo *(*Il2Cpp::getMethod)(Il2CppClass *, const char *, int);

Il2Cpp::Il2Cpp(void *handle) {
#define RESOLVE_IMPORT(f, s)                              \
  while (f == NULL) {                                     \
    f = reinterpret_cast<decltype(f)>(dlsym(handle, #s)); \
  }
  RESOLVE_IMPORT(getDomain, il2cpp_domain_get);
  RESOLVE_IMPORT(openAssembly, il2cpp_domain_assembly_open);
  RESOLVE_IMPORT(assemblyGetImage, il2cpp_assembly_get_image);
  RESOLVE_IMPORT(getClass, il2cpp_class_from_name);
  RESOLVE_IMPORT(getMethod, il2cpp_class_get_method_from_name);
}

Il2CppClass *Il2Cpp::GetClass(const char *namespaze, const char *name) {
  return GetClass("Assembly-CSharp.dll", namespaze, name);
}

Il2CppClass *Il2Cpp::GetClass(const char *assemblyName, const char *namespaze, const char *name) {
  auto assembly = openAssembly(getDomain(), assemblyName);
  if (assembly == NULL) {
    return NULL;
  }
  auto image = assemblyGetImage(assembly);
  if (image == NULL) {
    return NULL;
  }
  return getClass(image, namespaze, name);
}

const MethodInfo *Il2Cpp::GetMethod(Il2CppClass *klass, const char *name, int argsCount) {
  return getMethod(klass, name, argsCount);
}
