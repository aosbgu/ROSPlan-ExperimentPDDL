# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: propagation_particle.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='propagation_particle.proto',
  package='gazebo.msgs',
  serialized_pb=_b('\n\x1apropagation_particle.proto\x12\x0bgazebo.msgs\"A\n\x13PropagationParticle\x12\t\n\x01x\x18\x01 \x02(\x01\x12\t\n\x01y\x18\x02 \x02(\x01\x12\x14\n\x0csignal_level\x18\x03 \x02(\x01')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_PROPAGATIONPARTICLE = _descriptor.Descriptor(
  name='PropagationParticle',
  full_name='gazebo.msgs.PropagationParticle',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='gazebo.msgs.PropagationParticle.x', index=0,
      number=1, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='gazebo.msgs.PropagationParticle.y', index=1,
      number=2, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='signal_level', full_name='gazebo.msgs.PropagationParticle.signal_level', index=2,
      number=3, type=1, cpp_type=5, label=2,
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
  serialized_start=43,
  serialized_end=108,
)

DESCRIPTOR.message_types_by_name['PropagationParticle'] = _PROPAGATIONPARTICLE

PropagationParticle = _reflection.GeneratedProtocolMessageType('PropagationParticle', (_message.Message,), dict(
  DESCRIPTOR = _PROPAGATIONPARTICLE,
  __module__ = 'propagation_particle_pb2'
  # @@protoc_insertion_point(class_scope:gazebo.msgs.PropagationParticle)
  ))
_sym_db.RegisterMessage(PropagationParticle)


# @@protoc_insertion_point(module_scope)
