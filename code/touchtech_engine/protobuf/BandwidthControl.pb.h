// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BandwidthControl.proto

#ifndef PROTOBUF_BandwidthControl_2eproto__INCLUDED
#define PROTOBUF_BandwidthControl_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_util.h>
// @@protoc_insertion_point(includes)

namespace YmBwCtrlProto {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_BandwidthControl_2eproto();
void protobuf_AssignDesc_BandwidthControl_2eproto();
void protobuf_ShutdownFile_BandwidthControl_2eproto();

class CtrlMsgClient;
class CtrlMsgMain;
class CtrlMsgServer;

enum CtrlMsgType {
  CtrlMsgServerCommand = 0,
  CtrlMsgClientReport = 1
};
bool CtrlMsgType_IsValid(int value);
const CtrlMsgType CtrlMsgType_MIN = CtrlMsgServerCommand;
const CtrlMsgType CtrlMsgType_MAX = CtrlMsgClientReport;
const int CtrlMsgType_ARRAYSIZE = CtrlMsgType_MAX + 1;

enum FecType {
  FecNone = 0,
  FecOpus = 1,
  FecRed = 2,
  FecUlp = 3,
  FecUxp = 4
};
bool FecType_IsValid(int value);
const FecType FecType_MIN = FecNone;
const FecType FecType_MAX = FecUxp;
const int FecType_ARRAYSIZE = FecType_MAX + 1;

// ===================================================================

class CtrlMsgServer : public ::youmecommon::protobuf::MessageLite {
 public:
  CtrlMsgServer();
  virtual ~CtrlMsgServer();

  CtrlMsgServer(const CtrlMsgServer& from);

  inline CtrlMsgServer& operator=(const CtrlMsgServer& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_.GetNoArena(
        &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  inline ::std::string* mutable_unknown_fields() {
    return _unknown_fields_.MutableNoArena(
        &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  static const CtrlMsgServer& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const CtrlMsgServer* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(CtrlMsgServer* other);

  // implements Message ----------------------------------------------

  inline CtrlMsgServer* New() const { return New(NULL); }

  CtrlMsgServer* New(::youmecommon::protobuf::Arena* arena) const;
  void CheckTypeAndMergeFrom(const ::youmecommon::protobuf::MessageLite& from);
  void CopyFrom(const CtrlMsgServer& from);
  void MergeFrom(const CtrlMsgServer& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::youmecommon::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::youmecommon::protobuf::io::CodedOutputStream* output) const;
  void DiscardUnknownFields();
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(CtrlMsgServer* other);
  private:
  inline ::youmecommon::protobuf::Arena* GetArenaNoVirtual() const {
    return _arena_ptr_;
  }
  inline ::youmecommon::protobuf::Arena* MaybeArenaPtr() const {
    return _arena_ptr_;
  }
  public:

  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .YmBwCtrlProto.FecType fecToUse = 1;
  bool has_fectouse() const;
  void clear_fectouse();
  static const int kFecToUseFieldNumber = 1;
  ::YmBwCtrlProto::FecType fectouse() const;
  void set_fectouse(::YmBwCtrlProto::FecType value);

  // optional int32 redunantPercent = 2;
  bool has_redunantpercent() const;
  void clear_redunantpercent();
  static const int kRedunantPercentFieldNumber = 2;
  ::youmecommon::protobuf::int32 redunantpercent() const;
  void set_redunantpercent(::youmecommon::protobuf::int32 value);

  // optional int32 redunantGroupSize = 3;
  bool has_redunantgroupsize() const;
  void clear_redunantgroupsize();
  static const int kRedunantGroupSizeFieldNumber = 3;
  ::youmecommon::protobuf::int32 redunantgroupsize() const;
  void set_redunantgroupsize(::youmecommon::protobuf::int32 value);

  // optional int32 targetBitrateBps = 4;
  bool has_targetbitratebps() const;
  void clear_targetbitratebps();
  static const int kTargetBitrateBpsFieldNumber = 4;
  ::youmecommon::protobuf::int32 targetbitratebps() const;
  void set_targetbitratebps(::youmecommon::protobuf::int32 value);

  // optional int32 originalTimestamp = 5;
  bool has_originaltimestamp() const;
  void clear_originaltimestamp();
  static const int kOriginalTimestampFieldNumber = 5;
  ::youmecommon::protobuf::int32 originaltimestamp() const;
  void set_originaltimestamp(::youmecommon::protobuf::int32 value);

  // optional int32 loopbackTimestamp = 6;
  bool has_loopbacktimestamp() const;
  void clear_loopbacktimestamp();
  static const int kLoopbackTimestampFieldNumber = 6;
  ::youmecommon::protobuf::int32 loopbacktimestamp() const;
  void set_loopbacktimestamp(::youmecommon::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:YmBwCtrlProto.CtrlMsgServer)
 private:
  inline void set_has_fectouse();
  inline void clear_has_fectouse();
  inline void set_has_redunantpercent();
  inline void clear_has_redunantpercent();
  inline void set_has_redunantgroupsize();
  inline void clear_has_redunantgroupsize();
  inline void set_has_targetbitratebps();
  inline void clear_has_targetbitratebps();
  inline void set_has_originaltimestamp();
  inline void clear_has_originaltimestamp();
  inline void set_has_loopbacktimestamp();
  inline void clear_has_loopbacktimestamp();

  ::youmecommon::protobuf::internal::ArenaStringPtr _unknown_fields_;
  ::youmecommon::protobuf::Arena* _arena_ptr_;

  ::youmecommon::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  int fectouse_;
  ::youmecommon::protobuf::int32 redunantpercent_;
  ::youmecommon::protobuf::int32 redunantgroupsize_;
  ::youmecommon::protobuf::int32 targetbitratebps_;
  ::youmecommon::protobuf::int32 originaltimestamp_;
  ::youmecommon::protobuf::int32 loopbacktimestamp_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_BandwidthControl_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_BandwidthControl_2eproto();
  #endif
  friend void protobuf_AssignDesc_BandwidthControl_2eproto();
  friend void protobuf_ShutdownFile_BandwidthControl_2eproto();

  void InitAsDefaultInstance();
  static CtrlMsgServer* default_instance_;
};
// -------------------------------------------------------------------

class CtrlMsgClient : public ::youmecommon::protobuf::MessageLite {
 public:
  CtrlMsgClient();
  virtual ~CtrlMsgClient();

  CtrlMsgClient(const CtrlMsgClient& from);

  inline CtrlMsgClient& operator=(const CtrlMsgClient& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_.GetNoArena(
        &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  inline ::std::string* mutable_unknown_fields() {
    return _unknown_fields_.MutableNoArena(
        &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  static const CtrlMsgClient& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const CtrlMsgClient* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(CtrlMsgClient* other);

  // implements Message ----------------------------------------------

  inline CtrlMsgClient* New() const { return New(NULL); }

  CtrlMsgClient* New(::youmecommon::protobuf::Arena* arena) const;
  void CheckTypeAndMergeFrom(const ::youmecommon::protobuf::MessageLite& from);
  void CopyFrom(const CtrlMsgClient& from);
  void MergeFrom(const CtrlMsgClient& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::youmecommon::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::youmecommon::protobuf::io::CodedOutputStream* output) const;
  void DiscardUnknownFields();
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(CtrlMsgClient* other);
  private:
  inline ::youmecommon::protobuf::Arena* GetArenaNoVirtual() const {
    return _arena_ptr_;
  }
  inline ::youmecommon::protobuf::Arena* MaybeArenaPtr() const {
    return _arena_ptr_;
  }
  public:

  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 forSessionId = 1;
  bool has_forsessionid() const;
  void clear_forsessionid();
  static const int kForSessionIdFieldNumber = 1;
  ::youmecommon::protobuf::int32 forsessionid() const;
  void set_forsessionid(::youmecommon::protobuf::int32 value);

  // optional int32 packetLossRateQ8 = 2;
  bool has_packetlossrateq8() const;
  void clear_packetlossrateq8();
  static const int kPacketLossRateQ8FieldNumber = 2;
  ::youmecommon::protobuf::int32 packetlossrateq8() const;
  void set_packetlossrateq8(::youmecommon::protobuf::int32 value);

  // optional int32 packetLossRateAfterFecQ8 = 3;
  bool has_packetlossrateafterfecq8() const;
  void clear_packetlossrateafterfecq8();
  static const int kPacketLossRateAfterFecQ8FieldNumber = 3;
  ::youmecommon::protobuf::int32 packetlossrateafterfecq8() const;
  void set_packetlossrateafterfecq8(::youmecommon::protobuf::int32 value);

  // optional int32 maxConsecutiveLostPackets = 4;
  bool has_maxconsecutivelostpackets() const;
  void clear_maxconsecutivelostpackets();
  static const int kMaxConsecutiveLostPacketsFieldNumber = 4;
  ::youmecommon::protobuf::int32 maxconsecutivelostpackets() const;
  void set_maxconsecutivelostpackets(::youmecommon::protobuf::int32 value);

  // optional int32 loopbackTimestamp = 5;
  bool has_loopbacktimestamp() const;
  void clear_loopbacktimestamp();
  static const int kLoopbackTimestampFieldNumber = 5;
  ::youmecommon::protobuf::int32 loopbacktimestamp() const;
  void set_loopbacktimestamp(::youmecommon::protobuf::int32 value);

  // optional .YmBwCtrlProto.FecType highestFecSupported = 6;
  bool has_highestfecsupported() const;
  void clear_highestfecsupported();
  static const int kHighestFecSupportedFieldNumber = 6;
  ::YmBwCtrlProto::FecType highestfecsupported() const;
  void set_highestfecsupported(::YmBwCtrlProto::FecType value);

  // optional int32 originalTimestamp = 7;
  bool has_originaltimestamp() const;
  void clear_originaltimestamp();
  static const int kOriginalTimestampFieldNumber = 7;
  ::youmecommon::protobuf::int32 originaltimestamp() const;
  void set_originaltimestamp(::youmecommon::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:YmBwCtrlProto.CtrlMsgClient)
 private:
  inline void set_has_forsessionid();
  inline void clear_has_forsessionid();
  inline void set_has_packetlossrateq8();
  inline void clear_has_packetlossrateq8();
  inline void set_has_packetlossrateafterfecq8();
  inline void clear_has_packetlossrateafterfecq8();
  inline void set_has_maxconsecutivelostpackets();
  inline void clear_has_maxconsecutivelostpackets();
  inline void set_has_loopbacktimestamp();
  inline void clear_has_loopbacktimestamp();
  inline void set_has_highestfecsupported();
  inline void clear_has_highestfecsupported();
  inline void set_has_originaltimestamp();
  inline void clear_has_originaltimestamp();

  ::youmecommon::protobuf::internal::ArenaStringPtr _unknown_fields_;
  ::youmecommon::protobuf::Arena* _arena_ptr_;

  ::youmecommon::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::youmecommon::protobuf::int32 forsessionid_;
  ::youmecommon::protobuf::int32 packetlossrateq8_;
  ::youmecommon::protobuf::int32 packetlossrateafterfecq8_;
  ::youmecommon::protobuf::int32 maxconsecutivelostpackets_;
  ::youmecommon::protobuf::int32 loopbacktimestamp_;
  int highestfecsupported_;
  ::youmecommon::protobuf::int32 originaltimestamp_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_BandwidthControl_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_BandwidthControl_2eproto();
  #endif
  friend void protobuf_AssignDesc_BandwidthControl_2eproto();
  friend void protobuf_ShutdownFile_BandwidthControl_2eproto();

  void InitAsDefaultInstance();
  static CtrlMsgClient* default_instance_;
};
// -------------------------------------------------------------------

class CtrlMsgMain : public ::youmecommon::protobuf::MessageLite {
 public:
  CtrlMsgMain();
  virtual ~CtrlMsgMain();

  CtrlMsgMain(const CtrlMsgMain& from);

  inline CtrlMsgMain& operator=(const CtrlMsgMain& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_.GetNoArena(
        &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  inline ::std::string* mutable_unknown_fields() {
    return _unknown_fields_.MutableNoArena(
        &::youmecommon::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  static const CtrlMsgMain& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const CtrlMsgMain* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(CtrlMsgMain* other);

  // implements Message ----------------------------------------------

  inline CtrlMsgMain* New() const { return New(NULL); }

  CtrlMsgMain* New(::youmecommon::protobuf::Arena* arena) const;
  void CheckTypeAndMergeFrom(const ::youmecommon::protobuf::MessageLite& from);
  void CopyFrom(const CtrlMsgMain& from);
  void MergeFrom(const CtrlMsgMain& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::youmecommon::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::youmecommon::protobuf::io::CodedOutputStream* output) const;
  void DiscardUnknownFields();
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(CtrlMsgMain* other);
  private:
  inline ::youmecommon::protobuf::Arena* GetArenaNoVirtual() const {
    return _arena_ptr_;
  }
  inline ::youmecommon::protobuf::Arena* MaybeArenaPtr() const {
    return _arena_ptr_;
  }
  public:

  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .YmBwCtrlProto.CtrlMsgType msgType = 1;
  bool has_msgtype() const;
  void clear_msgtype();
  static const int kMsgTypeFieldNumber = 1;
  ::YmBwCtrlProto::CtrlMsgType msgtype() const;
  void set_msgtype(::YmBwCtrlProto::CtrlMsgType value);

  // required uint32 msgVersion = 2;
  bool has_msgversion() const;
  void clear_msgversion();
  static const int kMsgVersionFieldNumber = 2;
  ::youmecommon::protobuf::uint32 msgversion() const;
  void set_msgversion(::youmecommon::protobuf::uint32 value);

  // optional .YmBwCtrlProto.CtrlMsgServer msgServer = 3;
  bool has_msgserver() const;
  void clear_msgserver();
  static const int kMsgServerFieldNumber = 3;
  const ::YmBwCtrlProto::CtrlMsgServer& msgserver() const;
  ::YmBwCtrlProto::CtrlMsgServer* mutable_msgserver();
  ::YmBwCtrlProto::CtrlMsgServer* release_msgserver();
  void set_allocated_msgserver(::YmBwCtrlProto::CtrlMsgServer* msgserver);

  // optional .YmBwCtrlProto.CtrlMsgClient msgClient = 4;
  bool has_msgclient() const;
  void clear_msgclient();
  static const int kMsgClientFieldNumber = 4;
  const ::YmBwCtrlProto::CtrlMsgClient& msgclient() const;
  ::YmBwCtrlProto::CtrlMsgClient* mutable_msgclient();
  ::YmBwCtrlProto::CtrlMsgClient* release_msgclient();
  void set_allocated_msgclient(::YmBwCtrlProto::CtrlMsgClient* msgclient);

  // @@protoc_insertion_point(class_scope:YmBwCtrlProto.CtrlMsgMain)
 private:
  inline void set_has_msgtype();
  inline void clear_has_msgtype();
  inline void set_has_msgversion();
  inline void clear_has_msgversion();
  inline void set_has_msgserver();
  inline void clear_has_msgserver();
  inline void set_has_msgclient();
  inline void clear_has_msgclient();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::youmecommon::protobuf::internal::ArenaStringPtr _unknown_fields_;
  ::youmecommon::protobuf::Arena* _arena_ptr_;

  ::youmecommon::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  int msgtype_;
  ::youmecommon::protobuf::uint32 msgversion_;
  ::YmBwCtrlProto::CtrlMsgServer* msgserver_;
  ::YmBwCtrlProto::CtrlMsgClient* msgclient_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_BandwidthControl_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_BandwidthControl_2eproto();
  #endif
  friend void protobuf_AssignDesc_BandwidthControl_2eproto();
  friend void protobuf_ShutdownFile_BandwidthControl_2eproto();

  void InitAsDefaultInstance();
  static CtrlMsgMain* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// CtrlMsgServer

// optional .YmBwCtrlProto.FecType fecToUse = 1;
inline bool CtrlMsgServer::has_fectouse() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CtrlMsgServer::set_has_fectouse() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CtrlMsgServer::clear_has_fectouse() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CtrlMsgServer::clear_fectouse() {
  fectouse_ = 0;
  clear_has_fectouse();
}
inline ::YmBwCtrlProto::FecType CtrlMsgServer::fectouse() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgServer.fecToUse)
  return static_cast< ::YmBwCtrlProto::FecType >(fectouse_);
}
inline void CtrlMsgServer::set_fectouse(::YmBwCtrlProto::FecType value) {
  assert(::YmBwCtrlProto::FecType_IsValid(value));
  set_has_fectouse();
  fectouse_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgServer.fecToUse)
}

// optional int32 redunantPercent = 2;
inline bool CtrlMsgServer::has_redunantpercent() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CtrlMsgServer::set_has_redunantpercent() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CtrlMsgServer::clear_has_redunantpercent() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CtrlMsgServer::clear_redunantpercent() {
  redunantpercent_ = 0;
  clear_has_redunantpercent();
}
inline ::youmecommon::protobuf::int32 CtrlMsgServer::redunantpercent() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgServer.redunantPercent)
  return redunantpercent_;
}
inline void CtrlMsgServer::set_redunantpercent(::youmecommon::protobuf::int32 value) {
  set_has_redunantpercent();
  redunantpercent_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgServer.redunantPercent)
}

// optional int32 redunantGroupSize = 3;
inline bool CtrlMsgServer::has_redunantgroupsize() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CtrlMsgServer::set_has_redunantgroupsize() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CtrlMsgServer::clear_has_redunantgroupsize() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CtrlMsgServer::clear_redunantgroupsize() {
  redunantgroupsize_ = 0;
  clear_has_redunantgroupsize();
}
inline ::youmecommon::protobuf::int32 CtrlMsgServer::redunantgroupsize() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgServer.redunantGroupSize)
  return redunantgroupsize_;
}
inline void CtrlMsgServer::set_redunantgroupsize(::youmecommon::protobuf::int32 value) {
  set_has_redunantgroupsize();
  redunantgroupsize_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgServer.redunantGroupSize)
}

// optional int32 targetBitrateBps = 4;
inline bool CtrlMsgServer::has_targetbitratebps() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CtrlMsgServer::set_has_targetbitratebps() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CtrlMsgServer::clear_has_targetbitratebps() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CtrlMsgServer::clear_targetbitratebps() {
  targetbitratebps_ = 0;
  clear_has_targetbitratebps();
}
inline ::youmecommon::protobuf::int32 CtrlMsgServer::targetbitratebps() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgServer.targetBitrateBps)
  return targetbitratebps_;
}
inline void CtrlMsgServer::set_targetbitratebps(::youmecommon::protobuf::int32 value) {
  set_has_targetbitratebps();
  targetbitratebps_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgServer.targetBitrateBps)
}

// optional int32 originalTimestamp = 5;
inline bool CtrlMsgServer::has_originaltimestamp() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void CtrlMsgServer::set_has_originaltimestamp() {
  _has_bits_[0] |= 0x00000010u;
}
inline void CtrlMsgServer::clear_has_originaltimestamp() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void CtrlMsgServer::clear_originaltimestamp() {
  originaltimestamp_ = 0;
  clear_has_originaltimestamp();
}
inline ::youmecommon::protobuf::int32 CtrlMsgServer::originaltimestamp() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgServer.originalTimestamp)
  return originaltimestamp_;
}
inline void CtrlMsgServer::set_originaltimestamp(::youmecommon::protobuf::int32 value) {
  set_has_originaltimestamp();
  originaltimestamp_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgServer.originalTimestamp)
}

// optional int32 loopbackTimestamp = 6;
inline bool CtrlMsgServer::has_loopbacktimestamp() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void CtrlMsgServer::set_has_loopbacktimestamp() {
  _has_bits_[0] |= 0x00000020u;
}
inline void CtrlMsgServer::clear_has_loopbacktimestamp() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void CtrlMsgServer::clear_loopbacktimestamp() {
  loopbacktimestamp_ = 0;
  clear_has_loopbacktimestamp();
}
inline ::youmecommon::protobuf::int32 CtrlMsgServer::loopbacktimestamp() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgServer.loopbackTimestamp)
  return loopbacktimestamp_;
}
inline void CtrlMsgServer::set_loopbacktimestamp(::youmecommon::protobuf::int32 value) {
  set_has_loopbacktimestamp();
  loopbacktimestamp_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgServer.loopbackTimestamp)
}

// -------------------------------------------------------------------

// CtrlMsgClient

// optional int32 forSessionId = 1;
inline bool CtrlMsgClient::has_forsessionid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CtrlMsgClient::set_has_forsessionid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CtrlMsgClient::clear_has_forsessionid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CtrlMsgClient::clear_forsessionid() {
  forsessionid_ = 0;
  clear_has_forsessionid();
}
inline ::youmecommon::protobuf::int32 CtrlMsgClient::forsessionid() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgClient.forSessionId)
  return forsessionid_;
}
inline void CtrlMsgClient::set_forsessionid(::youmecommon::protobuf::int32 value) {
  set_has_forsessionid();
  forsessionid_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgClient.forSessionId)
}

// optional int32 packetLossRateQ8 = 2;
inline bool CtrlMsgClient::has_packetlossrateq8() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CtrlMsgClient::set_has_packetlossrateq8() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CtrlMsgClient::clear_has_packetlossrateq8() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CtrlMsgClient::clear_packetlossrateq8() {
  packetlossrateq8_ = 0;
  clear_has_packetlossrateq8();
}
inline ::youmecommon::protobuf::int32 CtrlMsgClient::packetlossrateq8() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgClient.packetLossRateQ8)
  return packetlossrateq8_;
}
inline void CtrlMsgClient::set_packetlossrateq8(::youmecommon::protobuf::int32 value) {
  set_has_packetlossrateq8();
  packetlossrateq8_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgClient.packetLossRateQ8)
}

// optional int32 packetLossRateAfterFecQ8 = 3;
inline bool CtrlMsgClient::has_packetlossrateafterfecq8() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CtrlMsgClient::set_has_packetlossrateafterfecq8() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CtrlMsgClient::clear_has_packetlossrateafterfecq8() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CtrlMsgClient::clear_packetlossrateafterfecq8() {
  packetlossrateafterfecq8_ = 0;
  clear_has_packetlossrateafterfecq8();
}
inline ::youmecommon::protobuf::int32 CtrlMsgClient::packetlossrateafterfecq8() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgClient.packetLossRateAfterFecQ8)
  return packetlossrateafterfecq8_;
}
inline void CtrlMsgClient::set_packetlossrateafterfecq8(::youmecommon::protobuf::int32 value) {
  set_has_packetlossrateafterfecq8();
  packetlossrateafterfecq8_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgClient.packetLossRateAfterFecQ8)
}

// optional int32 maxConsecutiveLostPackets = 4;
inline bool CtrlMsgClient::has_maxconsecutivelostpackets() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CtrlMsgClient::set_has_maxconsecutivelostpackets() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CtrlMsgClient::clear_has_maxconsecutivelostpackets() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CtrlMsgClient::clear_maxconsecutivelostpackets() {
  maxconsecutivelostpackets_ = 0;
  clear_has_maxconsecutivelostpackets();
}
inline ::youmecommon::protobuf::int32 CtrlMsgClient::maxconsecutivelostpackets() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgClient.maxConsecutiveLostPackets)
  return maxconsecutivelostpackets_;
}
inline void CtrlMsgClient::set_maxconsecutivelostpackets(::youmecommon::protobuf::int32 value) {
  set_has_maxconsecutivelostpackets();
  maxconsecutivelostpackets_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgClient.maxConsecutiveLostPackets)
}

// optional int32 loopbackTimestamp = 5;
inline bool CtrlMsgClient::has_loopbacktimestamp() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void CtrlMsgClient::set_has_loopbacktimestamp() {
  _has_bits_[0] |= 0x00000010u;
}
inline void CtrlMsgClient::clear_has_loopbacktimestamp() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void CtrlMsgClient::clear_loopbacktimestamp() {
  loopbacktimestamp_ = 0;
  clear_has_loopbacktimestamp();
}
inline ::youmecommon::protobuf::int32 CtrlMsgClient::loopbacktimestamp() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgClient.loopbackTimestamp)
  return loopbacktimestamp_;
}
inline void CtrlMsgClient::set_loopbacktimestamp(::youmecommon::protobuf::int32 value) {
  set_has_loopbacktimestamp();
  loopbacktimestamp_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgClient.loopbackTimestamp)
}

// optional .YmBwCtrlProto.FecType highestFecSupported = 6;
inline bool CtrlMsgClient::has_highestfecsupported() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void CtrlMsgClient::set_has_highestfecsupported() {
  _has_bits_[0] |= 0x00000020u;
}
inline void CtrlMsgClient::clear_has_highestfecsupported() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void CtrlMsgClient::clear_highestfecsupported() {
  highestfecsupported_ = 0;
  clear_has_highestfecsupported();
}
inline ::YmBwCtrlProto::FecType CtrlMsgClient::highestfecsupported() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgClient.highestFecSupported)
  return static_cast< ::YmBwCtrlProto::FecType >(highestfecsupported_);
}
inline void CtrlMsgClient::set_highestfecsupported(::YmBwCtrlProto::FecType value) {
  assert(::YmBwCtrlProto::FecType_IsValid(value));
  set_has_highestfecsupported();
  highestfecsupported_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgClient.highestFecSupported)
}

// optional int32 originalTimestamp = 7;
inline bool CtrlMsgClient::has_originaltimestamp() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void CtrlMsgClient::set_has_originaltimestamp() {
  _has_bits_[0] |= 0x00000040u;
}
inline void CtrlMsgClient::clear_has_originaltimestamp() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void CtrlMsgClient::clear_originaltimestamp() {
  originaltimestamp_ = 0;
  clear_has_originaltimestamp();
}
inline ::youmecommon::protobuf::int32 CtrlMsgClient::originaltimestamp() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgClient.originalTimestamp)
  return originaltimestamp_;
}
inline void CtrlMsgClient::set_originaltimestamp(::youmecommon::protobuf::int32 value) {
  set_has_originaltimestamp();
  originaltimestamp_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgClient.originalTimestamp)
}

// -------------------------------------------------------------------

// CtrlMsgMain

// required .YmBwCtrlProto.CtrlMsgType msgType = 1;
inline bool CtrlMsgMain::has_msgtype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CtrlMsgMain::set_has_msgtype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CtrlMsgMain::clear_has_msgtype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CtrlMsgMain::clear_msgtype() {
  msgtype_ = 0;
  clear_has_msgtype();
}
inline ::YmBwCtrlProto::CtrlMsgType CtrlMsgMain::msgtype() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgMain.msgType)
  return static_cast< ::YmBwCtrlProto::CtrlMsgType >(msgtype_);
}
inline void CtrlMsgMain::set_msgtype(::YmBwCtrlProto::CtrlMsgType value) {
  assert(::YmBwCtrlProto::CtrlMsgType_IsValid(value));
  set_has_msgtype();
  msgtype_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgMain.msgType)
}

// required uint32 msgVersion = 2;
inline bool CtrlMsgMain::has_msgversion() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CtrlMsgMain::set_has_msgversion() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CtrlMsgMain::clear_has_msgversion() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CtrlMsgMain::clear_msgversion() {
  msgversion_ = 0u;
  clear_has_msgversion();
}
inline ::youmecommon::protobuf::uint32 CtrlMsgMain::msgversion() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgMain.msgVersion)
  return msgversion_;
}
inline void CtrlMsgMain::set_msgversion(::youmecommon::protobuf::uint32 value) {
  set_has_msgversion();
  msgversion_ = value;
  // @@protoc_insertion_point(field_set:YmBwCtrlProto.CtrlMsgMain.msgVersion)
}

// optional .YmBwCtrlProto.CtrlMsgServer msgServer = 3;
inline bool CtrlMsgMain::has_msgserver() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CtrlMsgMain::set_has_msgserver() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CtrlMsgMain::clear_has_msgserver() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CtrlMsgMain::clear_msgserver() {
  if (msgserver_ != NULL) msgserver_->::YmBwCtrlProto::CtrlMsgServer::Clear();
  clear_has_msgserver();
}
inline const ::YmBwCtrlProto::CtrlMsgServer& CtrlMsgMain::msgserver() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgMain.msgServer)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  return msgserver_ != NULL ? *msgserver_ : *default_instance().msgserver_;
#else
  return msgserver_ != NULL ? *msgserver_ : *default_instance_->msgserver_;
#endif
}
inline ::YmBwCtrlProto::CtrlMsgServer* CtrlMsgMain::mutable_msgserver() {
  set_has_msgserver();
  if (msgserver_ == NULL) {
    msgserver_ = new ::YmBwCtrlProto::CtrlMsgServer;
  }
  // @@protoc_insertion_point(field_mutable:YmBwCtrlProto.CtrlMsgMain.msgServer)
  return msgserver_;
}
inline ::YmBwCtrlProto::CtrlMsgServer* CtrlMsgMain::release_msgserver() {
  clear_has_msgserver();
  ::YmBwCtrlProto::CtrlMsgServer* temp = msgserver_;
  msgserver_ = NULL;
  return temp;
}
inline void CtrlMsgMain::set_allocated_msgserver(::YmBwCtrlProto::CtrlMsgServer* msgserver) {
  delete msgserver_;
  msgserver_ = msgserver;
  if (msgserver) {
    set_has_msgserver();
  } else {
    clear_has_msgserver();
  }
  // @@protoc_insertion_point(field_set_allocated:YmBwCtrlProto.CtrlMsgMain.msgServer)
}

// optional .YmBwCtrlProto.CtrlMsgClient msgClient = 4;
inline bool CtrlMsgMain::has_msgclient() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CtrlMsgMain::set_has_msgclient() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CtrlMsgMain::clear_has_msgclient() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CtrlMsgMain::clear_msgclient() {
  if (msgclient_ != NULL) msgclient_->::YmBwCtrlProto::CtrlMsgClient::Clear();
  clear_has_msgclient();
}
inline const ::YmBwCtrlProto::CtrlMsgClient& CtrlMsgMain::msgclient() const {
  // @@protoc_insertion_point(field_get:YmBwCtrlProto.CtrlMsgMain.msgClient)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  return msgclient_ != NULL ? *msgclient_ : *default_instance().msgclient_;
#else
  return msgclient_ != NULL ? *msgclient_ : *default_instance_->msgclient_;
#endif
}
inline ::YmBwCtrlProto::CtrlMsgClient* CtrlMsgMain::mutable_msgclient() {
  set_has_msgclient();
  if (msgclient_ == NULL) {
    msgclient_ = new ::YmBwCtrlProto::CtrlMsgClient;
  }
  // @@protoc_insertion_point(field_mutable:YmBwCtrlProto.CtrlMsgMain.msgClient)
  return msgclient_;
}
inline ::YmBwCtrlProto::CtrlMsgClient* CtrlMsgMain::release_msgclient() {
  clear_has_msgclient();
  ::YmBwCtrlProto::CtrlMsgClient* temp = msgclient_;
  msgclient_ = NULL;
  return temp;
}
inline void CtrlMsgMain::set_allocated_msgclient(::YmBwCtrlProto::CtrlMsgClient* msgclient) {
  delete msgclient_;
  msgclient_ = msgclient;
  if (msgclient) {
    set_has_msgclient();
  } else {
    clear_has_msgclient();
  }
  // @@protoc_insertion_point(field_set_allocated:YmBwCtrlProto.CtrlMsgMain.msgClient)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace YmBwCtrlProto

#ifndef SWIG
namespace youmecommon {
namespace protobuf {

template <> struct is_proto_enum< ::YmBwCtrlProto::CtrlMsgType> : ::youmecommon::protobuf::internal::true_type {};
template <> struct is_proto_enum< ::YmBwCtrlProto::FecType> : ::youmecommon::protobuf::internal::true_type {};

}  // namespace protobuf
}  // namespace youmecommon
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_BandwidthControl_2eproto__INCLUDED
