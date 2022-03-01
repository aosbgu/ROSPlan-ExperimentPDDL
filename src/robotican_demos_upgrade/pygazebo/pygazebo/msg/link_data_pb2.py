# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: link_data.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from . import vector3d_pb2
from . import time_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='link_data.proto',
  package='gazebo.msgs',
  serialized_pb=_b('\n\x0flink_data.proto\x12\x0bgazebo.msgs\x1a\x0evector3d.proto\x1a\ntime.proto\"\x9a\x01\n\x08LinkData\x12\x1f\n\x04time\x18\x01 \x02(\x0b\x32\x11.gazebo.msgs.Time\x12\x0c\n\x04name\x18\x02 \x02(\t\x12.\n\x0flinear_velocity\x18\x03 \x01(\x0b\x32\x15.gazebo.msgs.Vector3d\x12/\n\x10\x61ngular_velocity\x18\x04 \x01(\x0b\x32\x15.gazebo.msgs.Vector3d')
  ,
  dependencies=[vector3d_pb2.DESCRIPTOR,time_pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_LINKDATA = _descriptor.Descriptor(
  name='LinkData',
  full_name='gazebo.msgs.LinkData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='time', full_name='gazebo.msgs.LinkData.time', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='gazebo.msgs.LinkData.name', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='linear_velocity', full_name='gazebo.msgs.LinkData.linear_velocity', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='angular_velocity', full_name='gazebo.msgs.LinkData.angular_velocity', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
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
  serialized_start=61,
  serialized_end=215,
)

_LINKDATA.fields_by_name['time'].message_type = time_pb2._TIME
_LINKDATA.fields_by_name['linear_velocity'].message_type = vector3d_pb2._VECTOR3D
_LINKDATA.fields_by_name['angular_velocity'].message_type = vector3d_pb2._VECTOR3D
DESCRIPTOR.message_types_by_name['LinkData'] = _LINKDATA

LinkData = _reflection.GeneratedProtocolMessageType('LinkData', (_message.Message,), dict(
  DESCRIPTOR = _LINKDATA,
  __module__ = 'link_data_pb2'
  # @@protoc_insertion_point(class_scope:gazebo.msgs.LinkData)
  ))
_sym_db.RegisterMessage(LinkData)


# @@protoc_insertion_point(module_scope)