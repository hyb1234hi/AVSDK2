// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: uploadlog.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "uploadlog.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

namespace YouMeProtocol {

void protobuf_ShutdownFile_uploadlog_2eproto() {
  delete UploadLog::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_uploadlog_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_uploadlog_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::YouMeProtocol::protobuf_AddDesc_common_2eproto();
  UploadLog::default_instance_ = new UploadLog();
  UploadLog::default_instance_->InitAsDefaultInstance();
  ::youmecommon::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_uploadlog_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_uploadlog_2eproto_once_);
void protobuf_AddDesc_uploadlog_2eproto() {
  ::youmecommon::protobuf::GoogleOnceInit(&protobuf_AddDesc_uploadlog_2eproto_once_,
                 &protobuf_AddDesc_uploadlog_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_uploadlog_2eproto {
  StaticDescriptorInitializer_uploadlog_2eproto() {
    protobuf_AddDesc_uploadlog_2eproto();
  }
} static_descriptor_initializer_uploadlog_2eproto_;
#endif
bool UploadType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
      return true;
    default:
      return false;
  }
}


namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int UploadLog::kHeadFieldNumber;
const int UploadLog::kFilelenFieldNumber;
const int UploadLog::kMd5FieldNumber;
const int UploadLog::kUpTypeFieldNumber;
const int UploadLog::kErrorcodeFieldNumber;
const int UploadLog::kUseridFieldNumber;
#endif  // !_MSC_VER

UploadLog::UploadLog()
  : ::youmecommon::protobuf::MessageLite(), _arena_ptr_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:YouMeProtocol.UploadLog)
}

void UploadLog::InitAsDefaultInstance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  head_ = const_cast< ::YouMeProtocol::PacketHead*>(
      ::YouMeProtocol::PacketHead::internal_default_instance());
#else
  head_ = const_cast< ::YouMeProtocol::PacketHead*>(&::YouMeProtocol::PacketHead::default_instance());
#endif
}

UploadLog::UploadLog(const UploadLog& from)
  : ::youmecommon::protobuf::MessageLite(),
    _arena_ptr_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:YouMeProtocol.UploadLog)
}

void UploadLog::SharedCtor() {
  ::youmecommon::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  _unknown_fields_.UnsafeSetDefault(
      &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  head_ = NULL;
  filelen_ = 0;
  md5_.UnsafeSetDefault(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  uptype_ = 1;
  errorcode_ = 0;
  userid_.UnsafeSetDefault(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

UploadLog::~UploadLog() {
  // @@protoc_insertion_point(destructor:YouMeProtocol.UploadLog)
  SharedDtor();
}

void UploadLog::SharedDtor() {
  _unknown_fields_.DestroyNoArena(
      &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  md5_.DestroyNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  userid_.DestroyNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
    delete head_;
  }
}

void UploadLog::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const UploadLog& UploadLog::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_uploadlog_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_uploadlog_2eproto();
#endif
  return *default_instance_;
}

UploadLog* UploadLog::default_instance_ = NULL;

UploadLog* UploadLog::New(::youmecommon::protobuf::Arena* arena) const {
  UploadLog* n = new UploadLog;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void UploadLog::Clear() {
  if (_has_bits_[0 / 32] & 63u) {
    if (has_head()) {
      if (head_ != NULL) head_->::YouMeProtocol::PacketHead::Clear();
    }
    filelen_ = 0;
    if (has_md5()) {
      md5_.ClearToEmptyNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    uptype_ = 1;
    errorcode_ = 0;
    if (has_userid()) {
      userid_.ClearToEmptyNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  _unknown_fields_.ClearToEmptyNoArena(
      &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool UploadLog::MergePartialFromCodedStream(
    ::youmecommon::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::youmecommon::protobuf::uint32 tag;
  ::youmecommon::protobuf::io::StringOutputStream unknown_fields_string(
      mutable_unknown_fields());
  ::youmecommon::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string);
  // @@protoc_insertion_point(parse_start:YouMeProtocol.UploadLog)
  for (;;) {
    ::std::pair< ::youmecommon::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::youmecommon::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .YouMeProtocol.PacketHead head = 1;
      case 1: {
        if (tag == 10) {
          DO_(::youmecommon::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_head()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_filelen;
        break;
      }

      // required int32 filelen = 2;
      case 2: {
        if (tag == 16) {
         parse_filelen:
          DO_((::youmecommon::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::youmecommon::protobuf::int32, ::youmecommon::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &filelen_)));
          set_has_filelen();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_md5;
        break;
      }

      // optional string md5 = 3;
      case 3: {
        if (tag == 26) {
         parse_md5:
          DO_(::youmecommon::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_md5()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_upType;
        break;
      }

      // optional .YouMeProtocol.UploadType upType = 4;
      case 4: {
        if (tag == 32) {
         parse_upType:
          int value;
          DO_((::youmecommon::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::youmecommon::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::YouMeProtocol::UploadType_IsValid(value)) {
            set_uptype(static_cast< ::YouMeProtocol::UploadType >(value));
          } else {
            unknown_fields_stream.WriteVarint32(tag);
            unknown_fields_stream.WriteVarint32(value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_errorcode;
        break;
      }

      // optional int32 errorcode = 5;
      case 5: {
        if (tag == 40) {
         parse_errorcode:
          DO_((::youmecommon::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::youmecommon::protobuf::int32, ::youmecommon::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &errorcode_)));
          set_has_errorcode();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(50)) goto parse_userid;
        break;
      }

      // optional string userid = 6;
      case 6: {
        if (tag == 50) {
         parse_userid:
          DO_(::youmecommon::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_userid()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::youmecommon::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::youmecommon::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::youmecommon::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:YouMeProtocol.UploadLog)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:YouMeProtocol.UploadLog)
  return false;
#undef DO_
}

void UploadLog::SerializeWithCachedSizes(
    ::youmecommon::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:YouMeProtocol.UploadLog)
  // required .YouMeProtocol.PacketHead head = 1;
  if (has_head()) {
    ::youmecommon::protobuf::internal::WireFormatLite::WriteMessage(
      1, *this->head_, output);
  }

  // required int32 filelen = 2;
  if (has_filelen()) {
    ::youmecommon::protobuf::internal::WireFormatLite::WriteInt32(2, this->filelen(), output);
  }

  // optional string md5 = 3;
  if (has_md5()) {
    ::youmecommon::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->md5(), output);
  }

  // optional .YouMeProtocol.UploadType upType = 4;
  if (has_uptype()) {
    ::youmecommon::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->uptype(), output);
  }

  // optional int32 errorcode = 5;
  if (has_errorcode()) {
    ::youmecommon::protobuf::internal::WireFormatLite::WriteInt32(5, this->errorcode(), output);
  }

  // optional string userid = 6;
  if (has_userid()) {
    ::youmecommon::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      6, this->userid(), output);
  }

  output->WriteRaw(unknown_fields().data(),
                   unknown_fields().size());
  // @@protoc_insertion_point(serialize_end:YouMeProtocol.UploadLog)
}

int UploadLog::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_head()) {
    // required .YouMeProtocol.PacketHead head = 1;
    total_size += 1 +
      ::youmecommon::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->head_);
  }

  if (has_filelen()) {
    // required int32 filelen = 2;
    total_size += 1 +
      ::youmecommon::protobuf::internal::WireFormatLite::Int32Size(
        this->filelen());
  }

  return total_size;
}
int UploadLog::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .YouMeProtocol.PacketHead head = 1;
    total_size += 1 +
      ::youmecommon::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->head_);

    // required int32 filelen = 2;
    total_size += 1 +
      ::youmecommon::protobuf::internal::WireFormatLite::Int32Size(
        this->filelen());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_has_bits_[2 / 32] & 60u) {
    // optional string md5 = 3;
    if (has_md5()) {
      total_size += 1 +
        ::youmecommon::protobuf::internal::WireFormatLite::StringSize(
          this->md5());
    }

    // optional .YouMeProtocol.UploadType upType = 4;
    if (has_uptype()) {
      total_size += 1 +
        ::youmecommon::protobuf::internal::WireFormatLite::EnumSize(this->uptype());
    }

    // optional int32 errorcode = 5;
    if (has_errorcode()) {
      total_size += 1 +
        ::youmecommon::protobuf::internal::WireFormatLite::Int32Size(
          this->errorcode());
    }

    // optional string userid = 6;
    if (has_userid()) {
      total_size += 1 +
        ::youmecommon::protobuf::internal::WireFormatLite::StringSize(
          this->userid());
    }

  }
  total_size += unknown_fields().size();

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void UploadLog::CheckTypeAndMergeFrom(
    const ::youmecommon::protobuf::MessageLite& from) {
  MergeFrom(*::youmecommon::protobuf::down_cast<const UploadLog*>(&from));
}

void UploadLog::MergeFrom(const UploadLog& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_head()) {
      mutable_head()->::YouMeProtocol::PacketHead::MergeFrom(from.head());
    }
    if (from.has_filelen()) {
      set_filelen(from.filelen());
    }
    if (from.has_md5()) {
      set_has_md5();
      md5_.AssignWithDefault(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), from.md5_);
    }
    if (from.has_uptype()) {
      set_uptype(from.uptype());
    }
    if (from.has_errorcode()) {
      set_errorcode(from.errorcode());
    }
    if (from.has_userid()) {
      set_has_userid();
      userid_.AssignWithDefault(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), from.userid_);
    }
  }
  mutable_unknown_fields()->append(from.unknown_fields());
}

void UploadLog::CopyFrom(const UploadLog& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UploadLog::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (has_head()) {
    if (!this->head_->IsInitialized()) return false;
  }
  return true;
}

void UploadLog::Swap(UploadLog* other) {
  if (other == this) return;
  InternalSwap(other);
}
void UploadLog::InternalSwap(UploadLog* other) {
  std::swap(head_, other->head_);
  std::swap(filelen_, other->filelen_);
  md5_.Swap(&other->md5_);
  std::swap(uptype_, other->uptype_);
  std::swap(errorcode_, other->errorcode_);
  userid_.Swap(&other->userid_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _unknown_fields_.Swap(&other->_unknown_fields_);
  std::swap(_cached_size_, other->_cached_size_);
}

::std::string UploadLog::GetTypeName() const {
  return "YouMeProtocol.UploadLog";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// UploadLog

// required .YouMeProtocol.PacketHead head = 1;
bool UploadLog::has_head() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void UploadLog::set_has_head() {
  _has_bits_[0] |= 0x00000001u;
}
void UploadLog::clear_has_head() {
  _has_bits_[0] &= ~0x00000001u;
}
void UploadLog::clear_head() {
  if (head_ != NULL) head_->::YouMeProtocol::PacketHead::Clear();
  clear_has_head();
}
const ::YouMeProtocol::PacketHead& UploadLog::head() const {
  // @@protoc_insertion_point(field_get:YouMeProtocol.UploadLog.head)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  return head_ != NULL ? *head_ : *default_instance().head_;
#else
  return head_ != NULL ? *head_ : *default_instance_->head_;
#endif
}
::YouMeProtocol::PacketHead* UploadLog::mutable_head() {
  set_has_head();
  if (head_ == NULL) {
    head_ = new ::YouMeProtocol::PacketHead;
  }
  // @@protoc_insertion_point(field_mutable:YouMeProtocol.UploadLog.head)
  return head_;
}
::YouMeProtocol::PacketHead* UploadLog::release_head() {
  clear_has_head();
  ::YouMeProtocol::PacketHead* temp = head_;
  head_ = NULL;
  return temp;
}
void UploadLog::set_allocated_head(::YouMeProtocol::PacketHead* head) {
  delete head_;
  head_ = head;
  if (head) {
    set_has_head();
  } else {
    clear_has_head();
  }
  // @@protoc_insertion_point(field_set_allocated:YouMeProtocol.UploadLog.head)
}

// required int32 filelen = 2;
bool UploadLog::has_filelen() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void UploadLog::set_has_filelen() {
  _has_bits_[0] |= 0x00000002u;
}
void UploadLog::clear_has_filelen() {
  _has_bits_[0] &= ~0x00000002u;
}
void UploadLog::clear_filelen() {
  filelen_ = 0;
  clear_has_filelen();
}
 ::youmecommon::protobuf::int32 UploadLog::filelen() const {
  // @@protoc_insertion_point(field_get:YouMeProtocol.UploadLog.filelen)
  return filelen_;
}
 void UploadLog::set_filelen(::youmecommon::protobuf::int32 value) {
  set_has_filelen();
  filelen_ = value;
  // @@protoc_insertion_point(field_set:YouMeProtocol.UploadLog.filelen)
}

// optional string md5 = 3;
bool UploadLog::has_md5() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void UploadLog::set_has_md5() {
  _has_bits_[0] |= 0x00000004u;
}
void UploadLog::clear_has_md5() {
  _has_bits_[0] &= ~0x00000004u;
}
void UploadLog::clear_md5() {
  md5_.ClearToEmptyNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_md5();
}
 const ::std::string& UploadLog::md5() const {
  // @@protoc_insertion_point(field_get:YouMeProtocol.UploadLog.md5)
  return md5_.GetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void UploadLog::set_md5(const ::std::string& value) {
  set_has_md5();
  md5_.SetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:YouMeProtocol.UploadLog.md5)
}
 void UploadLog::set_md5(const char* value) {
  set_has_md5();
  md5_.SetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:YouMeProtocol.UploadLog.md5)
}
 void UploadLog::set_md5(const char* value, size_t size) {
  set_has_md5();
  md5_.SetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:YouMeProtocol.UploadLog.md5)
}
 ::std::string* UploadLog::mutable_md5() {
  set_has_md5();
  // @@protoc_insertion_point(field_mutable:YouMeProtocol.UploadLog.md5)
  return md5_.MutableNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* UploadLog::release_md5() {
  clear_has_md5();
  return md5_.ReleaseNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void UploadLog::set_allocated_md5(::std::string* md5) {
  if (md5 != NULL) {
    set_has_md5();
  } else {
    clear_has_md5();
  }
  md5_.SetAllocatedNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), md5);
  // @@protoc_insertion_point(field_set_allocated:YouMeProtocol.UploadLog.md5)
}

// optional .YouMeProtocol.UploadType upType = 4;
bool UploadLog::has_uptype() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void UploadLog::set_has_uptype() {
  _has_bits_[0] |= 0x00000008u;
}
void UploadLog::clear_has_uptype() {
  _has_bits_[0] &= ~0x00000008u;
}
void UploadLog::clear_uptype() {
  uptype_ = 1;
  clear_has_uptype();
}
 ::YouMeProtocol::UploadType UploadLog::uptype() const {
  // @@protoc_insertion_point(field_get:YouMeProtocol.UploadLog.upType)
  return static_cast< ::YouMeProtocol::UploadType >(uptype_);
}
 void UploadLog::set_uptype(::YouMeProtocol::UploadType value) {
  assert(::YouMeProtocol::UploadType_IsValid(value));
  set_has_uptype();
  uptype_ = value;
  // @@protoc_insertion_point(field_set:YouMeProtocol.UploadLog.upType)
}

// optional int32 errorcode = 5;
bool UploadLog::has_errorcode() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
void UploadLog::set_has_errorcode() {
  _has_bits_[0] |= 0x00000010u;
}
void UploadLog::clear_has_errorcode() {
  _has_bits_[0] &= ~0x00000010u;
}
void UploadLog::clear_errorcode() {
  errorcode_ = 0;
  clear_has_errorcode();
}
 ::youmecommon::protobuf::int32 UploadLog::errorcode() const {
  // @@protoc_insertion_point(field_get:YouMeProtocol.UploadLog.errorcode)
  return errorcode_;
}
 void UploadLog::set_errorcode(::youmecommon::protobuf::int32 value) {
  set_has_errorcode();
  errorcode_ = value;
  // @@protoc_insertion_point(field_set:YouMeProtocol.UploadLog.errorcode)
}

// optional string userid = 6;
bool UploadLog::has_userid() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
void UploadLog::set_has_userid() {
  _has_bits_[0] |= 0x00000020u;
}
void UploadLog::clear_has_userid() {
  _has_bits_[0] &= ~0x00000020u;
}
void UploadLog::clear_userid() {
  userid_.ClearToEmptyNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_userid();
}
 const ::std::string& UploadLog::userid() const {
  // @@protoc_insertion_point(field_get:YouMeProtocol.UploadLog.userid)
  return userid_.GetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void UploadLog::set_userid(const ::std::string& value) {
  set_has_userid();
  userid_.SetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:YouMeProtocol.UploadLog.userid)
}
 void UploadLog::set_userid(const char* value) {
  set_has_userid();
  userid_.SetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:YouMeProtocol.UploadLog.userid)
}
 void UploadLog::set_userid(const char* value, size_t size) {
  set_has_userid();
  userid_.SetNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:YouMeProtocol.UploadLog.userid)
}
 ::std::string* UploadLog::mutable_userid() {
  set_has_userid();
  // @@protoc_insertion_point(field_mutable:YouMeProtocol.UploadLog.userid)
  return userid_.MutableNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* UploadLog::release_userid() {
  clear_has_userid();
  return userid_.ReleaseNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void UploadLog::set_allocated_userid(::std::string* userid) {
  if (userid != NULL) {
    set_has_userid();
  } else {
    clear_has_userid();
  }
  userid_.SetAllocatedNoArena(&::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited(), userid);
  // @@protoc_insertion_point(field_set_allocated:YouMeProtocol.UploadLog.userid)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace YouMeProtocol

// @@protoc_insertion_point(global_scope)
