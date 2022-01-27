#pragma once

typedef struct MethodInfo;
typedef void *Il2CppAssembly;

typedef struct Il2CppDomain {
  void *domain;
  void *setup;
  void *default_context;
  const char *friendly_name;
};

typedef struct Il2CppImage {
  const char *name;
};

typedef struct Il2CppClass {
  const Il2CppImage *image;
  void *gc_desc;
  const char *name;
  const char *namespaze;
  const void **byval_arg;
  const void **this_arg;
  Il2CppClass *element_class;
  Il2CppClass *castClass;
  Il2CppClass *declaringType;
  Il2CppClass *parent;
  void **generic_class;
  const void **typeDefinition;
  const void **interopData;
  void **fields;
  const void **events;
  const void **properties;
  const MethodInfo **methods;
  Il2CppClass **nestedTypes;
  Il2CppClass **implementedInterfaces;
  void **interfaceOffsets;
  void *static_fields;
  const void **rgctx_data;
  struct Il2CppClass **typeHierarchy;
  uint32_t cctor_started;
  uint32_t cctor_finished;
  __attribute__((aligned(8))) uint64_t cctor_thread;
  void *genericContainerIndex;
  void *customAttributeIndex;
  uint32_t instance_size;
  uint32_t actualSize;
  uint32_t element_size;
  int32_t native_size;
  uint32_t static_fields_size;
  uint32_t thread_static_fields_size;
  int32_t thread_static_fields_offset;
  uint32_t flags;
  uint32_t token;
  uint16_t method_count;
  uint16_t property_count;
  uint16_t field_count;
  uint16_t event_count;
  uint16_t nested_type_count;
  uint16_t vtable_count;
  uint16_t interfaces_count;
  uint16_t interface_offsets_count;
  uint8_t typeHierarchyDepth;
  uint8_t genericRecursionDepth;
  uint8_t rank;
  uint8_t minimumAlignment;
  uint8_t packingSize;
  uint8_t valuetype : 1;
  uint8_t initialized : 1;
  uint8_t enumtype : 1;
  uint8_t is_generic : 1;
  uint8_t has_references : 1;
  uint8_t init_pending : 1;
  uint8_t size_inited : 1;
  uint8_t has_finalize : 1;
  uint8_t has_cctor : 1;
  uint8_t is_blittable : 1;
  uint8_t is_import_or_windows_runtime : 1;
  uint8_t is_vtable_initialized : 1;
};

typedef struct MethodInfo {
  void *methodPointer;
  void *invoker_method;
  const char *name;
  Il2CppClass *klass;
  const void **return_type;
  const void **parameters;
};