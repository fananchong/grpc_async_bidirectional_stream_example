// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#include "test.pb.h"

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

PROTOBUF_PRAGMA_INIT_SEG
namespace test {
constexpr Frame::Frame(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : _oneof_case_{}{}
struct FrameDefaultTypeInternal {
  constexpr FrameDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~FrameDefaultTypeInternal() {}
  union {
    Frame _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT FrameDefaultTypeInternal _Frame_default_instance_;
constexpr MsgEcho::MsgEcho(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct MsgEchoDefaultTypeInternal {
  constexpr MsgEchoDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MsgEchoDefaultTypeInternal() {}
  union {
    MsgEcho _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MsgEchoDefaultTypeInternal _MsgEcho_default_instance_;
constexpr MsgPing::MsgPing(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized){}
struct MsgPingDefaultTypeInternal {
  constexpr MsgPingDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MsgPingDefaultTypeInternal() {}
  union {
    MsgPing _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MsgPingDefaultTypeInternal _MsgPing_default_instance_;
}  // namespace test
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_test_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_test_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_test_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_test_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::test::Frame, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::test::Frame, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  PROTOBUF_FIELD_OFFSET(::test::Frame, Msg_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::test::MsgEcho, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::test::MsgEcho, data_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::test::MsgPing, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::test::Frame)},
  { 8, -1, sizeof(::test::MsgEcho)},
  { 14, -1, sizeof(::test::MsgPing)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::test::_Frame_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::test::_MsgEcho_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::test::_MsgPing_default_instance_),
};

const char descriptor_table_protodef_test_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\ntest.proto\022\004test\"L\n\005Frame\022\035\n\004Echo\030\001 \001("
  "\0132\r.test.MsgEchoH\000\022\035\n\004ping\030\002 \001(\0132\r.test."
  "MsgPingH\000B\005\n\003Msg\"\027\n\007MsgEcho\022\014\n\004Data\030\001 \001("
  "\t\"\t\n\007MsgPing2\204\001\n\013TestService\022&\n\006Stream\022\013"
  ".test.Frame\032\013.test.Frame(\0010\001\022\'\n\007Stream2\022"
  "\013.test.Frame\032\013.test.Frame(\0010\001\022$\n\004Echo\022\r."
  "test.MsgEcho\032\r.test.MsgEchoB\010Z\006./testb\006p"
  "roto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_test_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_test_2eproto = {
  false, false, 285, descriptor_table_protodef_test_2eproto, "test.proto", 
  &descriptor_table_test_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_test_2eproto::offsets,
  file_level_metadata_test_2eproto, file_level_enum_descriptors_test_2eproto, file_level_service_descriptors_test_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_test_2eproto_getter() {
  return &descriptor_table_test_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_test_2eproto(&descriptor_table_test_2eproto);
namespace test {

// ===================================================================

class Frame::_Internal {
 public:
  static const ::test::MsgEcho& echo(const Frame* msg);
  static const ::test::MsgPing& ping(const Frame* msg);
};

const ::test::MsgEcho&
Frame::_Internal::echo(const Frame* msg) {
  return *msg->Msg_.echo_;
}
const ::test::MsgPing&
Frame::_Internal::ping(const Frame* msg) {
  return *msg->Msg_.ping_;
}
void Frame::set_allocated_echo(::test::MsgEcho* echo) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  clear_Msg();
  if (echo) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::test::MsgEcho>::GetOwningArena(echo);
    if (message_arena != submessage_arena) {
      echo = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, echo, submessage_arena);
    }
    set_has_echo();
    Msg_.echo_ = echo;
  }
  // @@protoc_insertion_point(field_set_allocated:test.Frame.Echo)
}
void Frame::set_allocated_ping(::test::MsgPing* ping) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  clear_Msg();
  if (ping) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::test::MsgPing>::GetOwningArena(ping);
    if (message_arena != submessage_arena) {
      ping = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, ping, submessage_arena);
    }
    set_has_ping();
    Msg_.ping_ = ping;
  }
  // @@protoc_insertion_point(field_set_allocated:test.Frame.ping)
}
Frame::Frame(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:test.Frame)
}
Frame::Frame(const Frame& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  clear_has_Msg();
  switch (from.Msg_case()) {
    case kEcho: {
      _internal_mutable_echo()->::test::MsgEcho::MergeFrom(from._internal_echo());
      break;
    }
    case kPing: {
      _internal_mutable_ping()->::test::MsgPing::MergeFrom(from._internal_ping());
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:test.Frame)
}

inline void Frame::SharedCtor() {
clear_has_Msg();
}

Frame::~Frame() {
  // @@protoc_insertion_point(destructor:test.Frame)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Frame::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (has_Msg()) {
    clear_Msg();
  }
}

void Frame::ArenaDtor(void* object) {
  Frame* _this = reinterpret_cast< Frame* >(object);
  (void)_this;
}
void Frame::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Frame::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Frame::clear_Msg() {
// @@protoc_insertion_point(one_of_clear_start:test.Frame)
  switch (Msg_case()) {
    case kEcho: {
      if (GetArenaForAllocation() == nullptr) {
        delete Msg_.echo_;
      }
      break;
    }
    case kPing: {
      if (GetArenaForAllocation() == nullptr) {
        delete Msg_.ping_;
      }
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = MSG_NOT_SET;
}


void Frame::Clear() {
// @@protoc_insertion_point(message_clear_start:test.Frame)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clear_Msg();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Frame::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .test.MsgEcho Echo = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_echo(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .test.MsgPing ping = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_ping(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
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

::PROTOBUF_NAMESPACE_ID::uint8* Frame::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:test.Frame)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .test.MsgEcho Echo = 1;
  if (_internal_has_echo()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::echo(this), target, stream);
  }

  // .test.MsgPing ping = 2;
  if (_internal_has_ping()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::ping(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.Frame)
  return target;
}

size_t Frame::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:test.Frame)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  switch (Msg_case()) {
    // .test.MsgEcho Echo = 1;
    case kEcho: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *Msg_.echo_);
      break;
    }
    // .test.MsgPing ping = 2;
    case kPing: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *Msg_.ping_);
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Frame::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Frame::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Frame::GetClassData() const { return &_class_data_; }

void Frame::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<Frame *>(to)->MergeFrom(
      static_cast<const Frame &>(from));
}


void Frame::MergeFrom(const Frame& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:test.Frame)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.Msg_case()) {
    case kEcho: {
      _internal_mutable_echo()->::test::MsgEcho::MergeFrom(from._internal_echo());
      break;
    }
    case kPing: {
      _internal_mutable_ping()->::test::MsgPing::MergeFrom(from._internal_ping());
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Frame::CopyFrom(const Frame& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:test.Frame)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Frame::IsInitialized() const {
  return true;
}

void Frame::InternalSwap(Frame* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(Msg_, other->Msg_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata Frame::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_test_2eproto_getter, &descriptor_table_test_2eproto_once,
      file_level_metadata_test_2eproto[0]);
}

// ===================================================================

class MsgEcho::_Internal {
 public:
};

MsgEcho::MsgEcho(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:test.MsgEcho)
}
MsgEcho::MsgEcho(const MsgEcho& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_data().empty()) {
    data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_data(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:test.MsgEcho)
}

inline void MsgEcho::SharedCtor() {
data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

MsgEcho::~MsgEcho() {
  // @@protoc_insertion_point(destructor:test.MsgEcho)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void MsgEcho::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  data_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void MsgEcho::ArenaDtor(void* object) {
  MsgEcho* _this = reinterpret_cast< MsgEcho* >(object);
  (void)_this;
}
void MsgEcho::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MsgEcho::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void MsgEcho::Clear() {
// @@protoc_insertion_point(message_clear_start:test.MsgEcho)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MsgEcho::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string Data = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_data();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "test.MsgEcho.Data"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
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

::PROTOBUF_NAMESPACE_ID::uint8* MsgEcho::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:test.MsgEcho)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string Data = 1;
  if (!this->_internal_data().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data().data(), static_cast<int>(this->_internal_data().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "test.MsgEcho.Data");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_data(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.MsgEcho)
  return target;
}

size_t MsgEcho::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:test.MsgEcho)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string Data = 1;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MsgEcho::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    MsgEcho::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MsgEcho::GetClassData() const { return &_class_data_; }

void MsgEcho::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<MsgEcho *>(to)->MergeFrom(
      static_cast<const MsgEcho &>(from));
}


void MsgEcho::MergeFrom(const MsgEcho& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:test.MsgEcho)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_data().empty()) {
    _internal_set_data(from._internal_data());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MsgEcho::CopyFrom(const MsgEcho& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:test.MsgEcho)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MsgEcho::IsInitialized() const {
  return true;
}

void MsgEcho::InternalSwap(MsgEcho* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &data_, GetArenaForAllocation(),
      &other->data_, other->GetArenaForAllocation()
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata MsgEcho::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_test_2eproto_getter, &descriptor_table_test_2eproto_once,
      file_level_metadata_test_2eproto[1]);
}

// ===================================================================

class MsgPing::_Internal {
 public:
};

MsgPing::MsgPing(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:test.MsgPing)
}
MsgPing::MsgPing(const MsgPing& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:test.MsgPing)
}

inline void MsgPing::SharedCtor() {
}

MsgPing::~MsgPing() {
  // @@protoc_insertion_point(destructor:test.MsgPing)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void MsgPing::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void MsgPing::ArenaDtor(void* object) {
  MsgPing* _this = reinterpret_cast< MsgPing* >(object);
  (void)_this;
}
void MsgPing::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MsgPing::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void MsgPing::Clear() {
// @@protoc_insertion_point(message_clear_start:test.MsgPing)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MsgPing::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* MsgPing::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:test.MsgPing)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.MsgPing)
  return target;
}

size_t MsgPing::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:test.MsgPing)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MsgPing::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    MsgPing::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MsgPing::GetClassData() const { return &_class_data_; }

void MsgPing::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<MsgPing *>(to)->MergeFrom(
      static_cast<const MsgPing &>(from));
}


void MsgPing::MergeFrom(const MsgPing& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:test.MsgPing)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MsgPing::CopyFrom(const MsgPing& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:test.MsgPing)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MsgPing::IsInitialized() const {
  return true;
}

void MsgPing::InternalSwap(MsgPing* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
}

::PROTOBUF_NAMESPACE_ID::Metadata MsgPing::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_test_2eproto_getter, &descriptor_table_test_2eproto_once,
      file_level_metadata_test_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace test
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::test::Frame* Arena::CreateMaybeMessage< ::test::Frame >(Arena* arena) {
  return Arena::CreateMessageInternal< ::test::Frame >(arena);
}
template<> PROTOBUF_NOINLINE ::test::MsgEcho* Arena::CreateMaybeMessage< ::test::MsgEcho >(Arena* arena) {
  return Arena::CreateMessageInternal< ::test::MsgEcho >(arena);
}
template<> PROTOBUF_NOINLINE ::test::MsgPing* Arena::CreateMaybeMessage< ::test::MsgPing >(Arena* arena) {
  return Arena::CreateMessageInternal< ::test::MsgPing >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
