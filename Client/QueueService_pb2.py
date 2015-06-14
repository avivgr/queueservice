# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: QueueService.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='QueueService.proto',
  package='',
  serialized_pb=_b('\n\x12QueueService.proto\"\"\n\x12\x43reateQueueRequest\x12\x0c\n\x04name\x18\x01 \x02(\t\"&\n\x13\x43reateQueueResponse\x12\x0f\n\x07queueid\x18\x01 \x02(\t\"\x1f\n\x0fGetQueueRequest\x12\x0c\n\x04name\x18\x01 \x02(\t\"#\n\x10GetQueueResponse\x12\x0f\n\x07queueid\x18\x01 \x02(\t\"\"\n\x0f\x44\x65lQueueRequest\x12\x0f\n\x07queueid\x18\x01 \x02(\t\"+\n\x10\x44\x65lQueueResponse\x12\x17\n\x06status\x18\x01 \x02(\x0e\x32\x07.Status\"/\n\x0e\x45nqueueRequest\x12\x0f\n\x07queueid\x18\x01 \x02(\t\x12\x0c\n\x04\x64\x61ta\x18\x02 \x02(\x0c\"*\n\x0f\x45nqueueResponse\x12\x17\n\x06status\x18\x01 \x02(\x0e\x32\x07.Status\"/\n\x0bReadRequest\x12\x0f\n\x07queueid\x18\x01 \x02(\t\x12\x0f\n\x07timeout\x18\x02 \x02(\x05\"E\n\x0cReadResponse\x12\x0f\n\x07queueid\x18\x01 \x02(\t\x12\x16\n\x0equeueentitiyid\x18\x02 \x02(\t\x12\x0c\n\x04\x64\x61ta\x18\x03 \x02(\x0c\"9\n\x0e\x44\x65queueRequest\x12\x0f\n\x07queueid\x18\x01 \x02(\t\x12\x16\n\x0equeueentitiyid\x18\x02 \x02(\t\"*\n\x0f\x44\x65queueResponse\x12\x17\n\x06status\x18\x01 \x02(\x0e\x32\x07.Status\"\xda\x02\n\x07Request\x12\x1e\n\x04type\x18\x01 \x02(\x0e\x32\x10.Request.ReqType\x12(\n\x0b\x63reateQueue\x18\x02 \x01(\x0b\x32\x13.CreateQueueRequest\x12\"\n\x08getQueue\x18\x03 \x01(\x0b\x32\x10.GetQueueRequest\x12\"\n\x08\x64\x65lQueue\x18\x04 \x01(\x0b\x32\x10.DelQueueRequest\x12 \n\x07\x65nqueue\x18\x05 \x01(\x0b\x32\x0f.EnqueueRequest\x12\x1a\n\x04read\x18\x06 \x01(\x0b\x32\x0c.ReadRequest\x12 \n\x07\x64\x65queue\x18\x07 \x01(\x0b\x32\x0f.DequeueRequest\"]\n\x07ReqType\x12\x10\n\x0c\x43REATE_QUEUE\x10\x01\x12\r\n\tGET_QUEUE\x10\x02\x12\r\n\tDEL_QUEUE\x10\x03\x12\x0b\n\x07\x45NQUEUE\x10\x04\x12\x08\n\x04READ\x10\x05\x12\x0b\n\x07\x44\x45QUEUE\x10\x06\"\xe4\x02\n\x08Response\x12 \n\x04type\x18\x01 \x02(\x0e\x32\x12.Response.RespType\x12)\n\x0b\x63reateQueue\x18\x02 \x01(\x0b\x32\x14.CreateQueueResponse\x12#\n\x08getQueue\x18\x03 \x01(\x0b\x32\x11.GetQueueResponse\x12#\n\x08\x64\x65lQueue\x18\x04 \x01(\x0b\x32\x11.DelQueueResponse\x12!\n\x07\x65nqueue\x18\x05 \x01(\x0b\x32\x10.EnqueueResponse\x12\x1b\n\x04read\x18\x06 \x01(\x0b\x32\r.ReadResponse\x12!\n\x07\x64\x65queue\x18\x07 \x01(\x0b\x32\x10.DequeueResponse\"^\n\x08RespType\x12\x10\n\x0c\x43REATE_QUEUE\x10\x01\x12\r\n\tGET_QUEUE\x10\x02\x12\r\n\tDEL_QUEUE\x10\x03\x12\x0b\n\x07\x45NQUEUE\x10\x04\x12\x08\n\x04READ\x10\x05\x12\x0b\n\x07\x44\x45QUEUE\x10\x06*+\n\x06Status\x12\x0b\n\x07SUCCESS\x10\x00\x12\n\n\x06NO_MEM\x10\x01\x12\x08\n\x04\x42USY\x10\x02')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_STATUS = _descriptor.EnumDescriptor(
  name='Status',
  full_name='Status',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SUCCESS', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NO_MEM', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BUSY', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1273,
  serialized_end=1316,
)
_sym_db.RegisterEnumDescriptor(_STATUS)

Status = enum_type_wrapper.EnumTypeWrapper(_STATUS)
SUCCESS = 0
NO_MEM = 1
BUSY = 2


_REQUEST_REQTYPE = _descriptor.EnumDescriptor(
  name='ReqType',
  full_name='Request.ReqType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='CREATE_QUEUE', index=0, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GET_QUEUE', index=1, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEL_QUEUE', index=2, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENQUEUE', index=3, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='READ', index=4, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEQUEUE', index=5, number=6,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=819,
  serialized_end=912,
)
_sym_db.RegisterEnumDescriptor(_REQUEST_REQTYPE)

_RESPONSE_RESPTYPE = _descriptor.EnumDescriptor(
  name='RespType',
  full_name='Response.RespType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='CREATE_QUEUE', index=0, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GET_QUEUE', index=1, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEL_QUEUE', index=2, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENQUEUE', index=3, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='READ', index=4, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEQUEUE', index=5, number=6,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1177,
  serialized_end=1271,
)
_sym_db.RegisterEnumDescriptor(_RESPONSE_RESPTYPE)


_CREATEQUEUEREQUEST = _descriptor.Descriptor(
  name='CreateQueueRequest',
  full_name='CreateQueueRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='CreateQueueRequest.name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=22,
  serialized_end=56,
)


_CREATEQUEUERESPONSE = _descriptor.Descriptor(
  name='CreateQueueResponse',
  full_name='CreateQueueResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='queueid', full_name='CreateQueueResponse.queueid', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=58,
  serialized_end=96,
)


_GETQUEUEREQUEST = _descriptor.Descriptor(
  name='GetQueueRequest',
  full_name='GetQueueRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='GetQueueRequest.name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=98,
  serialized_end=129,
)


_GETQUEUERESPONSE = _descriptor.Descriptor(
  name='GetQueueResponse',
  full_name='GetQueueResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='queueid', full_name='GetQueueResponse.queueid', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=131,
  serialized_end=166,
)


_DELQUEUEREQUEST = _descriptor.Descriptor(
  name='DelQueueRequest',
  full_name='DelQueueRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='queueid', full_name='DelQueueRequest.queueid', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=168,
  serialized_end=202,
)


_DELQUEUERESPONSE = _descriptor.Descriptor(
  name='DelQueueResponse',
  full_name='DelQueueResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='DelQueueResponse.status', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=204,
  serialized_end=247,
)


_ENQUEUEREQUEST = _descriptor.Descriptor(
  name='EnqueueRequest',
  full_name='EnqueueRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='queueid', full_name='EnqueueRequest.queueid', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='data', full_name='EnqueueRequest.data', index=1,
      number=2, type=12, cpp_type=9, label=2,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=249,
  serialized_end=296,
)


_ENQUEUERESPONSE = _descriptor.Descriptor(
  name='EnqueueResponse',
  full_name='EnqueueResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='EnqueueResponse.status', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=298,
  serialized_end=340,
)


_READREQUEST = _descriptor.Descriptor(
  name='ReadRequest',
  full_name='ReadRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='queueid', full_name='ReadRequest.queueid', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='timeout', full_name='ReadRequest.timeout', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=342,
  serialized_end=389,
)


_READRESPONSE = _descriptor.Descriptor(
  name='ReadResponse',
  full_name='ReadResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='queueid', full_name='ReadResponse.queueid', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='queueentitiyid', full_name='ReadResponse.queueentitiyid', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='data', full_name='ReadResponse.data', index=2,
      number=3, type=12, cpp_type=9, label=2,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=391,
  serialized_end=460,
)


_DEQUEUEREQUEST = _descriptor.Descriptor(
  name='DequeueRequest',
  full_name='DequeueRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='queueid', full_name='DequeueRequest.queueid', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='queueentitiyid', full_name='DequeueRequest.queueentitiyid', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=462,
  serialized_end=519,
)


_DEQUEUERESPONSE = _descriptor.Descriptor(
  name='DequeueResponse',
  full_name='DequeueResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='DequeueResponse.status', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=521,
  serialized_end=563,
)


_REQUEST = _descriptor.Descriptor(
  name='Request',
  full_name='Request',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Request.type', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='createQueue', full_name='Request.createQueue', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='getQueue', full_name='Request.getQueue', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='delQueue', full_name='Request.delQueue', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='enqueue', full_name='Request.enqueue', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='read', full_name='Request.read', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dequeue', full_name='Request.dequeue', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _REQUEST_REQTYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=566,
  serialized_end=912,
)


_RESPONSE = _descriptor.Descriptor(
  name='Response',
  full_name='Response',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Response.type', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='createQueue', full_name='Response.createQueue', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='getQueue', full_name='Response.getQueue', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='delQueue', full_name='Response.delQueue', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='enqueue', full_name='Response.enqueue', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='read', full_name='Response.read', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dequeue', full_name='Response.dequeue', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _RESPONSE_RESPTYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=915,
  serialized_end=1271,
)

_DELQUEUERESPONSE.fields_by_name['status'].enum_type = _STATUS
_ENQUEUERESPONSE.fields_by_name['status'].enum_type = _STATUS
_DEQUEUERESPONSE.fields_by_name['status'].enum_type = _STATUS
_REQUEST.fields_by_name['type'].enum_type = _REQUEST_REQTYPE
_REQUEST.fields_by_name['createQueue'].message_type = _CREATEQUEUEREQUEST
_REQUEST.fields_by_name['getQueue'].message_type = _GETQUEUEREQUEST
_REQUEST.fields_by_name['delQueue'].message_type = _DELQUEUEREQUEST
_REQUEST.fields_by_name['enqueue'].message_type = _ENQUEUEREQUEST
_REQUEST.fields_by_name['read'].message_type = _READREQUEST
_REQUEST.fields_by_name['dequeue'].message_type = _DEQUEUEREQUEST
_REQUEST_REQTYPE.containing_type = _REQUEST
_RESPONSE.fields_by_name['type'].enum_type = _RESPONSE_RESPTYPE
_RESPONSE.fields_by_name['createQueue'].message_type = _CREATEQUEUERESPONSE
_RESPONSE.fields_by_name['getQueue'].message_type = _GETQUEUERESPONSE
_RESPONSE.fields_by_name['delQueue'].message_type = _DELQUEUERESPONSE
_RESPONSE.fields_by_name['enqueue'].message_type = _ENQUEUERESPONSE
_RESPONSE.fields_by_name['read'].message_type = _READRESPONSE
_RESPONSE.fields_by_name['dequeue'].message_type = _DEQUEUERESPONSE
_RESPONSE_RESPTYPE.containing_type = _RESPONSE
DESCRIPTOR.message_types_by_name['CreateQueueRequest'] = _CREATEQUEUEREQUEST
DESCRIPTOR.message_types_by_name['CreateQueueResponse'] = _CREATEQUEUERESPONSE
DESCRIPTOR.message_types_by_name['GetQueueRequest'] = _GETQUEUEREQUEST
DESCRIPTOR.message_types_by_name['GetQueueResponse'] = _GETQUEUERESPONSE
DESCRIPTOR.message_types_by_name['DelQueueRequest'] = _DELQUEUEREQUEST
DESCRIPTOR.message_types_by_name['DelQueueResponse'] = _DELQUEUERESPONSE
DESCRIPTOR.message_types_by_name['EnqueueRequest'] = _ENQUEUEREQUEST
DESCRIPTOR.message_types_by_name['EnqueueResponse'] = _ENQUEUERESPONSE
DESCRIPTOR.message_types_by_name['ReadRequest'] = _READREQUEST
DESCRIPTOR.message_types_by_name['ReadResponse'] = _READRESPONSE
DESCRIPTOR.message_types_by_name['DequeueRequest'] = _DEQUEUEREQUEST
DESCRIPTOR.message_types_by_name['DequeueResponse'] = _DEQUEUERESPONSE
DESCRIPTOR.message_types_by_name['Request'] = _REQUEST
DESCRIPTOR.message_types_by_name['Response'] = _RESPONSE
DESCRIPTOR.enum_types_by_name['Status'] = _STATUS

CreateQueueRequest = _reflection.GeneratedProtocolMessageType('CreateQueueRequest', (_message.Message,), dict(
  DESCRIPTOR = _CREATEQUEUEREQUEST,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:CreateQueueRequest)
  ))
_sym_db.RegisterMessage(CreateQueueRequest)

CreateQueueResponse = _reflection.GeneratedProtocolMessageType('CreateQueueResponse', (_message.Message,), dict(
  DESCRIPTOR = _CREATEQUEUERESPONSE,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:CreateQueueResponse)
  ))
_sym_db.RegisterMessage(CreateQueueResponse)

GetQueueRequest = _reflection.GeneratedProtocolMessageType('GetQueueRequest', (_message.Message,), dict(
  DESCRIPTOR = _GETQUEUEREQUEST,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:GetQueueRequest)
  ))
_sym_db.RegisterMessage(GetQueueRequest)

GetQueueResponse = _reflection.GeneratedProtocolMessageType('GetQueueResponse', (_message.Message,), dict(
  DESCRIPTOR = _GETQUEUERESPONSE,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:GetQueueResponse)
  ))
_sym_db.RegisterMessage(GetQueueResponse)

DelQueueRequest = _reflection.GeneratedProtocolMessageType('DelQueueRequest', (_message.Message,), dict(
  DESCRIPTOR = _DELQUEUEREQUEST,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:DelQueueRequest)
  ))
_sym_db.RegisterMessage(DelQueueRequest)

DelQueueResponse = _reflection.GeneratedProtocolMessageType('DelQueueResponse', (_message.Message,), dict(
  DESCRIPTOR = _DELQUEUERESPONSE,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:DelQueueResponse)
  ))
_sym_db.RegisterMessage(DelQueueResponse)

EnqueueRequest = _reflection.GeneratedProtocolMessageType('EnqueueRequest', (_message.Message,), dict(
  DESCRIPTOR = _ENQUEUEREQUEST,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:EnqueueRequest)
  ))
_sym_db.RegisterMessage(EnqueueRequest)

EnqueueResponse = _reflection.GeneratedProtocolMessageType('EnqueueResponse', (_message.Message,), dict(
  DESCRIPTOR = _ENQUEUERESPONSE,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:EnqueueResponse)
  ))
_sym_db.RegisterMessage(EnqueueResponse)

ReadRequest = _reflection.GeneratedProtocolMessageType('ReadRequest', (_message.Message,), dict(
  DESCRIPTOR = _READREQUEST,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:ReadRequest)
  ))
_sym_db.RegisterMessage(ReadRequest)

ReadResponse = _reflection.GeneratedProtocolMessageType('ReadResponse', (_message.Message,), dict(
  DESCRIPTOR = _READRESPONSE,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:ReadResponse)
  ))
_sym_db.RegisterMessage(ReadResponse)

DequeueRequest = _reflection.GeneratedProtocolMessageType('DequeueRequest', (_message.Message,), dict(
  DESCRIPTOR = _DEQUEUEREQUEST,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:DequeueRequest)
  ))
_sym_db.RegisterMessage(DequeueRequest)

DequeueResponse = _reflection.GeneratedProtocolMessageType('DequeueResponse', (_message.Message,), dict(
  DESCRIPTOR = _DEQUEUERESPONSE,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:DequeueResponse)
  ))
_sym_db.RegisterMessage(DequeueResponse)

Request = _reflection.GeneratedProtocolMessageType('Request', (_message.Message,), dict(
  DESCRIPTOR = _REQUEST,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:Request)
  ))
_sym_db.RegisterMessage(Request)

Response = _reflection.GeneratedProtocolMessageType('Response', (_message.Message,), dict(
  DESCRIPTOR = _RESPONSE,
  __module__ = 'QueueService_pb2'
  # @@protoc_insertion_point(class_scope:Response)
  ))
_sym_db.RegisterMessage(Response)


# @@protoc_insertion_point(module_scope)
