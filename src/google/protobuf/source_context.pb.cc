// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/source_context.proto

#include <google/protobuf/source_context.pb.h>

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
PROTOBUF_NAMESPACE_OPEN
class SourceContextDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<SourceContext> _instance;
} _SourceContext_default_instance_;
PROTOBUF_NAMESPACE_CLOSE
static void InitDefaultsscc_info_SourceContext_google_2fprotobuf_2fsource_5fcontext_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &PROTOBUF_NAMESPACE_ID::_SourceContext_default_instance_;
    new (ptr) PROTOBUF_NAMESPACE_ID::SourceContext();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  PROTOBUF_NAMESPACE_ID::SourceContext::InitAsDefaultInstance();
}

PROTOBUF_EXPORT ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_SourceContext_google_2fprotobuf_2fsource_5fcontext_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_SourceContext_google_2fprotobuf_2fsource_5fcontext_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_google_2fprotobuf_2fsource_5fcontext_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_google_2fprotobuf_2fsource_5fcontext_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_google_2fprotobuf_2fsource_5fcontext_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_google_2fprotobuf_2fsource_5fcontext_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(PROTOBUF_NAMESPACE_ID::SourceContext, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(PROTOBUF_NAMESPACE_ID::SourceContext, file_name_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(PROTOBUF_NAMESPACE_ID::SourceContext)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&PROTOBUF_NAMESPACE_ID::_SourceContext_default_instance_),
};

const char descriptor_table_protodef_google_2fprotobuf_2fsource_5fcontext_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n$google/protobuf/source_context.proto\022\017"
  "google.protobuf\"\"\n\rSourceContext\022\021\n\tfile"
  "_name\030\001 \001(\tB\225\001\n\023com.google.protobufB\022Sou"
  "rceContextProtoP\001ZAgoogle.golang.org/gen"
  "proto/protobuf/source_context;source_con"
  "text\242\002\003GPB\252\002\036Google.Protobuf.WellKnownTy"
  "pesb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_sccs[1] = {
  &scc_info_SourceContext_google_2fprotobuf_2fsource_5fcontext_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_once;
static bool descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto = {
  &descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_initialized, descriptor_table_protodef_google_2fprotobuf_2fsource_5fcontext_2eproto, "google/protobuf/source_context.proto", 251,
  &descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_once, descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_sccs, descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_google_2fprotobuf_2fsource_5fcontext_2eproto::offsets,
  file_level_metadata_google_2fprotobuf_2fsource_5fcontext_2eproto, 1, file_level_enum_descriptors_google_2fprotobuf_2fsource_5fcontext_2eproto, file_level_service_descriptors_google_2fprotobuf_2fsource_5fcontext_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_google_2fprotobuf_2fsource_5fcontext_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_google_2fprotobuf_2fsource_5fcontext_2eproto)), true);
PROTOBUF_NAMESPACE_OPEN

// ===================================================================

void SourceContext::InitAsDefaultInstance() {
}
class SourceContext::_Internal {
 public:
};

SourceContext::SourceContext()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:google.protobuf.SourceContext)
}
SourceContext::SourceContext(const SourceContext& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  file_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_file_name().empty()) {
    file_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.file_name_);
  }
  // @@protoc_insertion_point(copy_constructor:google.protobuf.SourceContext)
}

void SourceContext::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_SourceContext_google_2fprotobuf_2fsource_5fcontext_2eproto.base);
  file_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

SourceContext::~SourceContext() {
  // @@protoc_insertion_point(destructor:google.protobuf.SourceContext)
  SharedDtor();
}

void SourceContext::SharedDtor() {
  file_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void SourceContext::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const SourceContext& SourceContext::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_SourceContext_google_2fprotobuf_2fsource_5fcontext_2eproto.base);
  return *internal_default_instance();
}


void SourceContext::Clear() {
// @@protoc_insertion_point(message_clear_start:google.protobuf.SourceContext)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  file_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

const char* SourceContext::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string file_name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_file_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "google.protobuf.SourceContext.file_name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* SourceContext::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:google.protobuf.SourceContext)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string file_name = 1;
  if (this->file_name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_file_name().data(), static_cast<int>(this->_internal_file_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "google.protobuf.SourceContext.file_name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_file_name(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:google.protobuf.SourceContext)
  return target;
}

size_t SourceContext::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:google.protobuf.SourceContext)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string file_name = 1;
  if (this->file_name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_file_name());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SourceContext::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:google.protobuf.SourceContext)
  GOOGLE_DCHECK_NE(&from, this);
  const SourceContext* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<SourceContext>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:google.protobuf.SourceContext)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:google.protobuf.SourceContext)
    MergeFrom(*source);
  }
}

void SourceContext::MergeFrom(const SourceContext& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:google.protobuf.SourceContext)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.file_name().size() > 0) {

    file_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.file_name_);
  }
}

void SourceContext::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:google.protobuf.SourceContext)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SourceContext::CopyFrom(const SourceContext& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:google.protobuf.SourceContext)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SourceContext::IsInitialized() const {
  return true;
}

void SourceContext::InternalSwap(SourceContext* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  file_name_.Swap(&other->file_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata SourceContext::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_CLOSE
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE PROTOBUF_NAMESPACE_ID::SourceContext* Arena::CreateMaybeMessage< PROTOBUF_NAMESPACE_ID::SourceContext >(Arena* arena) {
  return Arena::CreateInternal< PROTOBUF_NAMESPACE_ID::SourceContext >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
