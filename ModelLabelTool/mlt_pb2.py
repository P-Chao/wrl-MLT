# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: mlt.proto

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
  name='mlt.proto',
  package='mlt',
  serialized_pb=_b('\n\tmlt.proto\x12\x03mlt\"v\n\x05Label\x12\x0f\n\x07version\x18\x01 \x01(\t\x12\x13\n\x0bwrlFileName\x18\x02 \x01(\t\x12\x13\n\x0bimgFileName\x18\x03 \x01(\t\x12\x17\n\x04info\x18\x04 \x01(\x0b\x32\t.mlt.Info\x12\x19\n\x05point\x18\x05 \x03(\x0b\x32\n.mlt.Point\"\xab\x01\n\x04Info\x12\x13\n\x0bviewpoint_x\x18\x01 \x01(\x01\x12\x13\n\x0bviewpoint_y\x18\x02 \x01(\x01\x12\x13\n\x0bviewpoint_z\x18\x03 \x01(\x01\x12\x11\n\tlookori_x\x18\x04 \x01(\x01\x12\x11\n\tlookori_y\x18\x05 \x01(\x01\x12\x11\n\tlookori_z\x18\x06 \x01(\x01\x12\r\n\x05rot_x\x18\x07 \x01(\x01\x12\r\n\x05rot_y\x18\x08 \x01(\x01\x12\r\n\x05rot_z\x18\t \x01(\x01\"M\n\x05Point\x12\n\n\x02id\x18\x01 \x01(\x05\x12\t\n\x01x\x18\x02 \x01(\x05\x12\t\n\x01y\x18\x03 \x01(\x05\x12\n\n\x02xl\x18\x04 \x01(\x01\x12\n\n\x02yl\x18\x05 \x01(\x01\x12\n\n\x02zl\x18\x06 \x01(\x01')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_LABEL = _descriptor.Descriptor(
  name='Label',
  full_name='mlt.Label',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='version', full_name='mlt.Label.version', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='wrlFileName', full_name='mlt.Label.wrlFileName', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='imgFileName', full_name='mlt.Label.imgFileName', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='info', full_name='mlt.Label.info', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='point', full_name='mlt.Label.point', index=4,
      number=5, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=18,
  serialized_end=136,
)


_INFO = _descriptor.Descriptor(
  name='Info',
  full_name='mlt.Info',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='viewpoint_x', full_name='mlt.Info.viewpoint_x', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='viewpoint_y', full_name='mlt.Info.viewpoint_y', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='viewpoint_z', full_name='mlt.Info.viewpoint_z', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='lookori_x', full_name='mlt.Info.lookori_x', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='lookori_y', full_name='mlt.Info.lookori_y', index=4,
      number=5, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='lookori_z', full_name='mlt.Info.lookori_z', index=5,
      number=6, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rot_x', full_name='mlt.Info.rot_x', index=6,
      number=7, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rot_y', full_name='mlt.Info.rot_y', index=7,
      number=8, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rot_z', full_name='mlt.Info.rot_z', index=8,
      number=9, type=1, cpp_type=5, label=1,
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
  serialized_start=139,
  serialized_end=310,
)


_POINT = _descriptor.Descriptor(
  name='Point',
  full_name='mlt.Point',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='mlt.Point.id', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='x', full_name='mlt.Point.x', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='mlt.Point.y', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='xl', full_name='mlt.Point.xl', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='yl', full_name='mlt.Point.yl', index=4,
      number=5, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='zl', full_name='mlt.Point.zl', index=5,
      number=6, type=1, cpp_type=5, label=1,
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
  serialized_start=312,
  serialized_end=389,
)

_LABEL.fields_by_name['info'].message_type = _INFO
_LABEL.fields_by_name['point'].message_type = _POINT
DESCRIPTOR.message_types_by_name['Label'] = _LABEL
DESCRIPTOR.message_types_by_name['Info'] = _INFO
DESCRIPTOR.message_types_by_name['Point'] = _POINT

Label = _reflection.GeneratedProtocolMessageType('Label', (_message.Message,), dict(
  DESCRIPTOR = _LABEL,
  __module__ = 'mlt_pb2'
  # @@protoc_insertion_point(class_scope:mlt.Label)
  ))
_sym_db.RegisterMessage(Label)

Info = _reflection.GeneratedProtocolMessageType('Info', (_message.Message,), dict(
  DESCRIPTOR = _INFO,
  __module__ = 'mlt_pb2'
  # @@protoc_insertion_point(class_scope:mlt.Info)
  ))
_sym_db.RegisterMessage(Info)

Point = _reflection.GeneratedProtocolMessageType('Point', (_message.Message,), dict(
  DESCRIPTOR = _POINT,
  __module__ = 'mlt_pb2'
  # @@protoc_insertion_point(class_scope:mlt.Point)
  ))
_sym_db.RegisterMessage(Point)


# @@protoc_insertion_point(module_scope)
