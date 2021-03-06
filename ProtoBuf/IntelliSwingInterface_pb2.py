# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: IntelliSwingInterface.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
import type_pb2 as type__pb2
import IntelliSwingService_pb2 as IntelliSwingService__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1bIntelliSwingInterface.proto\x12\x0cIntelliSwing\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a\ntype.proto\x1a\x19IntelliSwingService.proto\"z\n\rInitializeMsg\x12\x32\n\x06\x63lient\x18\x04 \x01(\x0e\x32\".IntelliSwing.InitializeMsg.Client\"5\n\x06\x43lient\x12\x07\n\x03GDR\x10\x00\x12\x0b\n\x07NextGDR\x10\x01\x12\n\n\x06Vision\x10\x02\x12\t\n\x05Ohter\x10\x03\"\x18\n\nReleaseMsg\x12\n\n\x02id\x18\x01 \x01(\x05\"\xdc\x03\n\x08StartMsg\x12?\n\x0f\x63lubInformation\x18\x01 \x01(\x0e\x32&.IntelliSwing.StartMsg.ClubInformation\x12\x32\n\x10goundAttribution\x18\x02 \x01(\x0e\x32\x18.IntelliSwing.GroundAttr\"\xda\x02\n\x0f\x43lubInformation\x12\x0e\n\nNonPutting\x10\x00\x12\x0b\n\x07Putting\x10\x01\x12\x08\n\x04Wood\x10\x64\x12\x06\n\x02W1\x10\x65\x12\x06\n\x02W2\x10\x66\x12\x06\n\x02W3\x10g\x12\x06\n\x02W4\x10h\x12\x06\n\x02W5\x10i\x12\x06\n\x02W6\x10j\x12\x06\n\x02W7\x10k\x12\x06\n\x02W8\x10l\x12\x06\n\x02W9\x10m\x12\t\n\x04Iron\x10\xc8\x01\x12\x07\n\x02I2\x10\xca\x01\x12\x07\n\x02I3\x10\xcb\x01\x12\x07\n\x02I4\x10\xcc\x01\x12\x07\n\x02I5\x10\xcd\x01\x12\x07\n\x02I6\x10\xce\x01\x12\x07\n\x02I7\x10\xcf\x01\x12\x07\n\x02I8\x10\xd0\x01\x12\x07\n\x02I9\x10\xd1\x01\x12\n\n\x05Wedge\x10\xac\x02\x12\x07\n\x02PW\x10\xb6\x02\x12\x07\n\x02SW\x10\xc0\x02\x12\x07\n\x02LW\x10\xca\x02\x12\x0b\n\x06Hybrid\x10\x90\x03\x12\t\n\x04UTIL\x10\xa4\x03\x12\n\n\x05UTIL2\x10\xa6\x03\x12\n\n\x05UTIL3\x10\xa7\x03\x12\n\n\x05UTIL4\x10\xa8\x03\x12\n\n\x05UTIL5\x10\xa9\x03\x12\n\n\x05UTIL6\x10\xaa\x03\x12\n\n\x05UTIL7\x10\xab\x03\"\xb4\t\n\x10SensorRunningMsg\x12-\n\ttimeStamp\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x35\n\x05ready\x18\x02 \x01(\x0b\x32$.IntelliSwing.SensorRunningMsg.ReadyH\x00\x12;\n\x08notReady\x18\x03 \x01(\x0b\x32\'.IntelliSwing.SensorRunningMsg.NotReadyH\x00\x12\x46\n\rshotTriggered\x18\x04 \x01(\x0b\x32-.IntelliSwing.SensorRunningMsg.ShortTriggeredH\x00\x12\x41\n\x08\x62\x61llInfo\x18\x05 \x01(\x0b\x32-.IntelliSwing.SensorRunningMsg.BallFlightInfoH\x00\x12?\n\x08\x63lubInfo\x18\x06 \x01(\x0b\x32+.IntelliSwing.SensorRunningMsg.ClubPathInfoH\x00\x1as\n\x05Ready\x12\'\n\x08position\x18\x01 \x01(\x0b\x32\x15.IntelliSwing.Point3f\x12\r\n\x05isTee\x18\x02 \x01(\x08\x12\x32\n\x10goundAttribution\x18\x03 \x01(\x0e\x32\x18.IntelliSwing.GroundAttr\x1a\xa8\x01\n\x08NotReady\x12L\n\rnotReadyCause\x18\x01 \x01(\x0e\x32\x35.IntelliSwing.SensorRunningMsg.NotReady.NotReadyCause\"N\n\rNotReadyCause\x12\x0e\n\nNotDefined\x10\x00\x12\x0c\n\x08OutBound\x10\x01\x12\x10\n\x0c\x42\x61llNotFound\x10\x02\x12\r\n\tMultiBall\x10\x03\x1a\x33\n\x0eShortTriggered\x12\x0e\n\x06shotId\x18\x01 \x01(\x05\x12\x11\n\ttimestamp\x18\x02 \x01(\x04\x1a}\n\x0e\x42\x61llFlightInfo\x12\x0e\n\x06shotId\x18\x01 \x01(\x05\x12\x11\n\tballSpeed\x18\x02 \x01(\x02\x12\x11\n\tIncidence\x18\x03 \x01(\x02\x12\x11\n\tdirection\x18\x04 \x01(\x02\x12\x10\n\x08\x62\x61\x63kSpin\x18\x05 \x01(\x02\x12\x10\n\x08sideSpin\x18\x06 \x01(\x02\x1a\xd0\x02\n\x0c\x43lubPathInfo\x12\x0e\n\x06shotId\x18\x01 \x01(\x05\x12\x11\n\theadSpeed\x18\x02 \x01(\x02\x12>\n\x04path\x18\x03 \x01(\x0b\x32\x30.IntelliSwing.SensorRunningMsg.ClubPathInfo.Path\x12\x11\n\tfaceAngle\x18\x04 \x01(\x02\x12\x13\n\x0b\x61ttackAngle\x18\x05 \x01(\x02\x12L\n\x0bimpactPoint\x18\x06 \x01(\x0b\x32\x37.IntelliSwing.SensorRunningMsg.ClubPathInfo.ImpactPoint\x1a\x1a\n\x04Path\x12\x12\n\nGAClubPath\x18\x01 \x01(\x02\x1aK\n\x0bImpactPoint\x12\x1d\n\x15GAClubImpactPoint_Hor\x18\x01 \x01(\x02\x12\x1d\n\x15GAClubImpactPoint_Ver\x18\x02 \x01(\x02\x42\n\n\x08runState\"\"\n\x10ShotImageRequest\x12\x0e\n\x06shotId\x18\x01 \x01(\x05\"\xcc\x02\n\tImageData\x12\r\n\x05width\x18\x01 \x01(\x05\x12\x0e\n\x06height\x18\x02 \x01(\x05\x12\x0f\n\x07\x63hannel\x18\x03 \x01(\x05\x12\x11\n\tdata_type\x18\x04 \x01(\x05\x12\x12\n\nimage_type\x18\x05 \x01(\x05\x12\x0b\n\x03\x66ps\x18\x06 \x01(\x02\x12,\n\x05\x64\x61tas\x18\x07 \x03(\x0b\x32\x1d.IntelliSwing.ImageData.Image\x1a\xac\x01\n\x05Image\x12\x0c\n\x04\x64\x61ta\x18\x02 \x01(\x0c\x12\x11\n\ttimeStamp\x18\x03 \x01(\x04\x12\x0b\n\x03tag\x18\x07 \x01(\t\x12\x35\n\x07markers\x18\x08 \x03(\x0b\x32$.IntelliSwing.ImageData.Image.Marker\x1a>\n\x06Marker\x12\'\n\x08position\x18\x01 \x01(\x0b\x32\x15.IntelliSwing.Point2i\x12\x0b\n\x03tag\x18\x02 \x01(\t*N\n\nGroundAttr\x12\x0b\n\x07\x46\x41IRWAY\x10\x00\x12\t\n\x05ROUGH\x10\x01\x12\n\n\x06\x42UNKER\x10\x02\x12\x07\n\x03TEE\x10\x03\x12\t\n\x05GREEN\x10\x04\x12\x08\n\x04NONE\x10\x05\x32\x9a\x08\n\x14IntelliSwingProtocol\x12\x44\n\nInitialize\x12\x1b.IntelliSwing.InitializeMsg\x1a\x17.IntelliSwing.ReturnMsg\"\x00\x12>\n\x07Release\x12\x18.IntelliSwing.ReleaseMsg\x1a\x17.IntelliSwing.ReturnMsg\"\x00\x12;\n\x06Reboot\x12\x16.google.protobuf.Empty\x1a\x17.IntelliSwing.ReturnMsg\"\x00\x12\x43\n\x05Start\x12\x16.IntelliSwing.StartMsg\x1a\x1e.IntelliSwing.SensorRunningMsg\"\x00\x30\x01\x12\x39\n\x04Stop\x12\x16.google.protobuf.Empty\x1a\x17.IntelliSwing.ReturnMsg\"\x00\x12I\n\x0cGetClubImage\x12\x1e.IntelliSwing.ShotImageRequest\x1a\x17.IntelliSwing.ImageData\"\x00\x12I\n\x0cGetBallImage\x12\x1e.IntelliSwing.ShotImageRequest\x1a\x17.IntelliSwing.ImageData\"\x00\x12\x43\n\rGetDeviceInfo\x12\x16.google.protobuf.Empty\x1a\x18.IntelliSwing.DeviceInfo\"\x00\x12G\n\x0fGetDeviceStatus\x12\x16.google.protobuf.Empty\x1a\x1a.IntelliSwing.DeviceStatus\"\x00\x12>\n\x06GetLog\x12\x18.IntelliSwing.LogRequest\x1a\x18.IntelliSwing.LogMessage\"\x00\x12R\n\rGetStatistics\x12\x1f.IntelliSwing.StatisticsRequest\x1a\x1e.IntelliSwing.SensorStatistics\"\x00\x12\x61\n\x12RunSiteCalibration\x12$.IntelliSwing.SiteCalibrationRequest\x1a#.IntelliSwing.SiteCalibrationResult\"\x00\x12[\n\x0eUpdateFirmware\x12#.IntelliSwing.UpdateFirmwareRequest\x1a\".IntelliSwing.UpdateFirmwareResult\"\x00\x12G\n\x08GetImage\x12 .IntelliSwing.CameraImageRequest\x1a\x17.IntelliSwing.ImageData\"\x00\x62\x06proto3')

_GROUNDATTR = DESCRIPTOR.enum_types_by_name['GroundAttr']
GroundAttr = enum_type_wrapper.EnumTypeWrapper(_GROUNDATTR)
FAIRWAY = 0
ROUGH = 1
BUNKER = 2
TEE = 3
GREEN = 4
NONE = 5


_INITIALIZEMSG = DESCRIPTOR.message_types_by_name['InitializeMsg']
_RELEASEMSG = DESCRIPTOR.message_types_by_name['ReleaseMsg']
_STARTMSG = DESCRIPTOR.message_types_by_name['StartMsg']
_SENSORRUNNINGMSG = DESCRIPTOR.message_types_by_name['SensorRunningMsg']
_SENSORRUNNINGMSG_READY = _SENSORRUNNINGMSG.nested_types_by_name['Ready']
_SENSORRUNNINGMSG_NOTREADY = _SENSORRUNNINGMSG.nested_types_by_name['NotReady']
_SENSORRUNNINGMSG_SHORTTRIGGERED = _SENSORRUNNINGMSG.nested_types_by_name['ShortTriggered']
_SENSORRUNNINGMSG_BALLFLIGHTINFO = _SENSORRUNNINGMSG.nested_types_by_name['BallFlightInfo']
_SENSORRUNNINGMSG_CLUBPATHINFO = _SENSORRUNNINGMSG.nested_types_by_name['ClubPathInfo']
_SENSORRUNNINGMSG_CLUBPATHINFO_PATH = _SENSORRUNNINGMSG_CLUBPATHINFO.nested_types_by_name['Path']
_SENSORRUNNINGMSG_CLUBPATHINFO_IMPACTPOINT = _SENSORRUNNINGMSG_CLUBPATHINFO.nested_types_by_name['ImpactPoint']
_SHOTIMAGEREQUEST = DESCRIPTOR.message_types_by_name['ShotImageRequest']
_IMAGEDATA = DESCRIPTOR.message_types_by_name['ImageData']
_IMAGEDATA_IMAGE = _IMAGEDATA.nested_types_by_name['Image']
_IMAGEDATA_IMAGE_MARKER = _IMAGEDATA_IMAGE.nested_types_by_name['Marker']
_INITIALIZEMSG_CLIENT = _INITIALIZEMSG.enum_types_by_name['Client']
_STARTMSG_CLUBINFORMATION = _STARTMSG.enum_types_by_name['ClubInformation']
_SENSORRUNNINGMSG_NOTREADY_NOTREADYCAUSE = _SENSORRUNNINGMSG_NOTREADY.enum_types_by_name['NotReadyCause']
InitializeMsg = _reflection.GeneratedProtocolMessageType('InitializeMsg', (_message.Message,), {
  'DESCRIPTOR' : _INITIALIZEMSG,
  '__module__' : 'IntelliSwingInterface_pb2'
  # @@protoc_insertion_point(class_scope:IntelliSwing.InitializeMsg)
  })
_sym_db.RegisterMessage(InitializeMsg)

ReleaseMsg = _reflection.GeneratedProtocolMessageType('ReleaseMsg', (_message.Message,), {
  'DESCRIPTOR' : _RELEASEMSG,
  '__module__' : 'IntelliSwingInterface_pb2'
  # @@protoc_insertion_point(class_scope:IntelliSwing.ReleaseMsg)
  })
_sym_db.RegisterMessage(ReleaseMsg)

StartMsg = _reflection.GeneratedProtocolMessageType('StartMsg', (_message.Message,), {
  'DESCRIPTOR' : _STARTMSG,
  '__module__' : 'IntelliSwingInterface_pb2'
  # @@protoc_insertion_point(class_scope:IntelliSwing.StartMsg)
  })
_sym_db.RegisterMessage(StartMsg)

SensorRunningMsg = _reflection.GeneratedProtocolMessageType('SensorRunningMsg', (_message.Message,), {

  'Ready' : _reflection.GeneratedProtocolMessageType('Ready', (_message.Message,), {
    'DESCRIPTOR' : _SENSORRUNNINGMSG_READY,
    '__module__' : 'IntelliSwingInterface_pb2'
    # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg.Ready)
    })
  ,

  'NotReady' : _reflection.GeneratedProtocolMessageType('NotReady', (_message.Message,), {
    'DESCRIPTOR' : _SENSORRUNNINGMSG_NOTREADY,
    '__module__' : 'IntelliSwingInterface_pb2'
    # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg.NotReady)
    })
  ,

  'ShortTriggered' : _reflection.GeneratedProtocolMessageType('ShortTriggered', (_message.Message,), {
    'DESCRIPTOR' : _SENSORRUNNINGMSG_SHORTTRIGGERED,
    '__module__' : 'IntelliSwingInterface_pb2'
    # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg.ShortTriggered)
    })
  ,

  'BallFlightInfo' : _reflection.GeneratedProtocolMessageType('BallFlightInfo', (_message.Message,), {
    'DESCRIPTOR' : _SENSORRUNNINGMSG_BALLFLIGHTINFO,
    '__module__' : 'IntelliSwingInterface_pb2'
    # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg.BallFlightInfo)
    })
  ,

  'ClubPathInfo' : _reflection.GeneratedProtocolMessageType('ClubPathInfo', (_message.Message,), {

    'Path' : _reflection.GeneratedProtocolMessageType('Path', (_message.Message,), {
      'DESCRIPTOR' : _SENSORRUNNINGMSG_CLUBPATHINFO_PATH,
      '__module__' : 'IntelliSwingInterface_pb2'
      # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg.ClubPathInfo.Path)
      })
    ,

    'ImpactPoint' : _reflection.GeneratedProtocolMessageType('ImpactPoint', (_message.Message,), {
      'DESCRIPTOR' : _SENSORRUNNINGMSG_CLUBPATHINFO_IMPACTPOINT,
      '__module__' : 'IntelliSwingInterface_pb2'
      # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg.ClubPathInfo.ImpactPoint)
      })
    ,
    'DESCRIPTOR' : _SENSORRUNNINGMSG_CLUBPATHINFO,
    '__module__' : 'IntelliSwingInterface_pb2'
    # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg.ClubPathInfo)
    })
  ,
  'DESCRIPTOR' : _SENSORRUNNINGMSG,
  '__module__' : 'IntelliSwingInterface_pb2'
  # @@protoc_insertion_point(class_scope:IntelliSwing.SensorRunningMsg)
  })
_sym_db.RegisterMessage(SensorRunningMsg)
_sym_db.RegisterMessage(SensorRunningMsg.Ready)
_sym_db.RegisterMessage(SensorRunningMsg.NotReady)
_sym_db.RegisterMessage(SensorRunningMsg.ShortTriggered)
_sym_db.RegisterMessage(SensorRunningMsg.BallFlightInfo)
_sym_db.RegisterMessage(SensorRunningMsg.ClubPathInfo)
_sym_db.RegisterMessage(SensorRunningMsg.ClubPathInfo.Path)
_sym_db.RegisterMessage(SensorRunningMsg.ClubPathInfo.ImpactPoint)

ShotImageRequest = _reflection.GeneratedProtocolMessageType('ShotImageRequest', (_message.Message,), {
  'DESCRIPTOR' : _SHOTIMAGEREQUEST,
  '__module__' : 'IntelliSwingInterface_pb2'
  # @@protoc_insertion_point(class_scope:IntelliSwing.ShotImageRequest)
  })
_sym_db.RegisterMessage(ShotImageRequest)

ImageData = _reflection.GeneratedProtocolMessageType('ImageData', (_message.Message,), {

  'Image' : _reflection.GeneratedProtocolMessageType('Image', (_message.Message,), {

    'Marker' : _reflection.GeneratedProtocolMessageType('Marker', (_message.Message,), {
      'DESCRIPTOR' : _IMAGEDATA_IMAGE_MARKER,
      '__module__' : 'IntelliSwingInterface_pb2'
      # @@protoc_insertion_point(class_scope:IntelliSwing.ImageData.Image.Marker)
      })
    ,
    'DESCRIPTOR' : _IMAGEDATA_IMAGE,
    '__module__' : 'IntelliSwingInterface_pb2'
    # @@protoc_insertion_point(class_scope:IntelliSwing.ImageData.Image)
    })
  ,
  'DESCRIPTOR' : _IMAGEDATA,
  '__module__' : 'IntelliSwingInterface_pb2'
  # @@protoc_insertion_point(class_scope:IntelliSwing.ImageData)
  })
_sym_db.RegisterMessage(ImageData)
_sym_db.RegisterMessage(ImageData.Image)
_sym_db.RegisterMessage(ImageData.Image.Marker)

_INTELLISWINGPROTOCOL = DESCRIPTOR.services_by_name['IntelliSwingProtocol']
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _GROUNDATTR._serialized_start=2353
  _GROUNDATTR._serialized_end=2431
  _INITIALIZEMSG._serialized_start=146
  _INITIALIZEMSG._serialized_end=268
  _INITIALIZEMSG_CLIENT._serialized_start=215
  _INITIALIZEMSG_CLIENT._serialized_end=268
  _RELEASEMSG._serialized_start=270
  _RELEASEMSG._serialized_end=294
  _STARTMSG._serialized_start=297
  _STARTMSG._serialized_end=773
  _STARTMSG_CLUBINFORMATION._serialized_start=427
  _STARTMSG_CLUBINFORMATION._serialized_end=773
  _SENSORRUNNINGMSG._serialized_start=776
  _SENSORRUNNINGMSG._serialized_end=1980
  _SENSORRUNNINGMSG_READY._serialized_start=1163
  _SENSORRUNNINGMSG_READY._serialized_end=1278
  _SENSORRUNNINGMSG_NOTREADY._serialized_start=1281
  _SENSORRUNNINGMSG_NOTREADY._serialized_end=1449
  _SENSORRUNNINGMSG_NOTREADY_NOTREADYCAUSE._serialized_start=1371
  _SENSORRUNNINGMSG_NOTREADY_NOTREADYCAUSE._serialized_end=1449
  _SENSORRUNNINGMSG_SHORTTRIGGERED._serialized_start=1451
  _SENSORRUNNINGMSG_SHORTTRIGGERED._serialized_end=1502
  _SENSORRUNNINGMSG_BALLFLIGHTINFO._serialized_start=1504
  _SENSORRUNNINGMSG_BALLFLIGHTINFO._serialized_end=1629
  _SENSORRUNNINGMSG_CLUBPATHINFO._serialized_start=1632
  _SENSORRUNNINGMSG_CLUBPATHINFO._serialized_end=1968
  _SENSORRUNNINGMSG_CLUBPATHINFO_PATH._serialized_start=1865
  _SENSORRUNNINGMSG_CLUBPATHINFO_PATH._serialized_end=1891
  _SENSORRUNNINGMSG_CLUBPATHINFO_IMPACTPOINT._serialized_start=1893
  _SENSORRUNNINGMSG_CLUBPATHINFO_IMPACTPOINT._serialized_end=1968
  _SHOTIMAGEREQUEST._serialized_start=1982
  _SHOTIMAGEREQUEST._serialized_end=2016
  _IMAGEDATA._serialized_start=2019
  _IMAGEDATA._serialized_end=2351
  _IMAGEDATA_IMAGE._serialized_start=2179
  _IMAGEDATA_IMAGE._serialized_end=2351
  _IMAGEDATA_IMAGE_MARKER._serialized_start=2289
  _IMAGEDATA_IMAGE_MARKER._serialized_end=2351
  _INTELLISWINGPROTOCOL._serialized_start=2434
  _INTELLISWINGPROTOCOL._serialized_end=3484
# @@protoc_insertion_point(module_scope)
