// Auto-generated. Do not edit!

// (in-package localization.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class gps {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.FPD_Header = null;
      this.FPD_GPSWeek = null;
      this.FPD_GPSTime = null;
      this.Heading = null;
      this.Pitch = null;
      this.Roll = null;
      this.Lattitude = null;
      this.Longitude = null;
      this.Altitude = null;
      this.Ve = null;
      this.Vn = null;
      this.Vu = null;
      this.Baseline = null;
      this.NSV1 = null;
      this.NSV2 = null;
      this.Status = null;
      this.FPD_Cs = null;
      this.IMU_Header = null;
      this.IMU_GPSWeek = null;
      this.IMU_GPSTime = null;
      this.GyroX = null;
      this.GyroY = null;
      this.GyroZ = null;
      this.AccX = null;
      this.AccY = null;
      this.AccZ = null;
      this.Tpr = null;
      this.IMU_Cs = null;
      this.x = null;
      this.y = null;
    }
    else {
      if (initObj.hasOwnProperty('FPD_Header')) {
        this.FPD_Header = initObj.FPD_Header
      }
      else {
        this.FPD_Header = '';
      }
      if (initObj.hasOwnProperty('FPD_GPSWeek')) {
        this.FPD_GPSWeek = initObj.FPD_GPSWeek
      }
      else {
        this.FPD_GPSWeek = '';
      }
      if (initObj.hasOwnProperty('FPD_GPSTime')) {
        this.FPD_GPSTime = initObj.FPD_GPSTime
      }
      else {
        this.FPD_GPSTime = '';
      }
      if (initObj.hasOwnProperty('Heading')) {
        this.Heading = initObj.Heading
      }
      else {
        this.Heading = '';
      }
      if (initObj.hasOwnProperty('Pitch')) {
        this.Pitch = initObj.Pitch
      }
      else {
        this.Pitch = '';
      }
      if (initObj.hasOwnProperty('Roll')) {
        this.Roll = initObj.Roll
      }
      else {
        this.Roll = '';
      }
      if (initObj.hasOwnProperty('Lattitude')) {
        this.Lattitude = initObj.Lattitude
      }
      else {
        this.Lattitude = '';
      }
      if (initObj.hasOwnProperty('Longitude')) {
        this.Longitude = initObj.Longitude
      }
      else {
        this.Longitude = '';
      }
      if (initObj.hasOwnProperty('Altitude')) {
        this.Altitude = initObj.Altitude
      }
      else {
        this.Altitude = '';
      }
      if (initObj.hasOwnProperty('Ve')) {
        this.Ve = initObj.Ve
      }
      else {
        this.Ve = '';
      }
      if (initObj.hasOwnProperty('Vn')) {
        this.Vn = initObj.Vn
      }
      else {
        this.Vn = '';
      }
      if (initObj.hasOwnProperty('Vu')) {
        this.Vu = initObj.Vu
      }
      else {
        this.Vu = '';
      }
      if (initObj.hasOwnProperty('Baseline')) {
        this.Baseline = initObj.Baseline
      }
      else {
        this.Baseline = '';
      }
      if (initObj.hasOwnProperty('NSV1')) {
        this.NSV1 = initObj.NSV1
      }
      else {
        this.NSV1 = '';
      }
      if (initObj.hasOwnProperty('NSV2')) {
        this.NSV2 = initObj.NSV2
      }
      else {
        this.NSV2 = '';
      }
      if (initObj.hasOwnProperty('Status')) {
        this.Status = initObj.Status
      }
      else {
        this.Status = '';
      }
      if (initObj.hasOwnProperty('FPD_Cs')) {
        this.FPD_Cs = initObj.FPD_Cs
      }
      else {
        this.FPD_Cs = '';
      }
      if (initObj.hasOwnProperty('IMU_Header')) {
        this.IMU_Header = initObj.IMU_Header
      }
      else {
        this.IMU_Header = '';
      }
      if (initObj.hasOwnProperty('IMU_GPSWeek')) {
        this.IMU_GPSWeek = initObj.IMU_GPSWeek
      }
      else {
        this.IMU_GPSWeek = '';
      }
      if (initObj.hasOwnProperty('IMU_GPSTime')) {
        this.IMU_GPSTime = initObj.IMU_GPSTime
      }
      else {
        this.IMU_GPSTime = '';
      }
      if (initObj.hasOwnProperty('GyroX')) {
        this.GyroX = initObj.GyroX
      }
      else {
        this.GyroX = '';
      }
      if (initObj.hasOwnProperty('GyroY')) {
        this.GyroY = initObj.GyroY
      }
      else {
        this.GyroY = '';
      }
      if (initObj.hasOwnProperty('GyroZ')) {
        this.GyroZ = initObj.GyroZ
      }
      else {
        this.GyroZ = '';
      }
      if (initObj.hasOwnProperty('AccX')) {
        this.AccX = initObj.AccX
      }
      else {
        this.AccX = '';
      }
      if (initObj.hasOwnProperty('AccY')) {
        this.AccY = initObj.AccY
      }
      else {
        this.AccY = '';
      }
      if (initObj.hasOwnProperty('AccZ')) {
        this.AccZ = initObj.AccZ
      }
      else {
        this.AccZ = '';
      }
      if (initObj.hasOwnProperty('Tpr')) {
        this.Tpr = initObj.Tpr
      }
      else {
        this.Tpr = '';
      }
      if (initObj.hasOwnProperty('IMU_Cs')) {
        this.IMU_Cs = initObj.IMU_Cs
      }
      else {
        this.IMU_Cs = '';
      }
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = 0.0;
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type gps
    // Serialize message field [FPD_Header]
    bufferOffset = _serializer.string(obj.FPD_Header, buffer, bufferOffset);
    // Serialize message field [FPD_GPSWeek]
    bufferOffset = _serializer.string(obj.FPD_GPSWeek, buffer, bufferOffset);
    // Serialize message field [FPD_GPSTime]
    bufferOffset = _serializer.string(obj.FPD_GPSTime, buffer, bufferOffset);
    // Serialize message field [Heading]
    bufferOffset = _serializer.string(obj.Heading, buffer, bufferOffset);
    // Serialize message field [Pitch]
    bufferOffset = _serializer.string(obj.Pitch, buffer, bufferOffset);
    // Serialize message field [Roll]
    bufferOffset = _serializer.string(obj.Roll, buffer, bufferOffset);
    // Serialize message field [Lattitude]
    bufferOffset = _serializer.string(obj.Lattitude, buffer, bufferOffset);
    // Serialize message field [Longitude]
    bufferOffset = _serializer.string(obj.Longitude, buffer, bufferOffset);
    // Serialize message field [Altitude]
    bufferOffset = _serializer.string(obj.Altitude, buffer, bufferOffset);
    // Serialize message field [Ve]
    bufferOffset = _serializer.string(obj.Ve, buffer, bufferOffset);
    // Serialize message field [Vn]
    bufferOffset = _serializer.string(obj.Vn, buffer, bufferOffset);
    // Serialize message field [Vu]
    bufferOffset = _serializer.string(obj.Vu, buffer, bufferOffset);
    // Serialize message field [Baseline]
    bufferOffset = _serializer.string(obj.Baseline, buffer, bufferOffset);
    // Serialize message field [NSV1]
    bufferOffset = _serializer.string(obj.NSV1, buffer, bufferOffset);
    // Serialize message field [NSV2]
    bufferOffset = _serializer.string(obj.NSV2, buffer, bufferOffset);
    // Serialize message field [Status]
    bufferOffset = _serializer.string(obj.Status, buffer, bufferOffset);
    // Serialize message field [FPD_Cs]
    bufferOffset = _serializer.string(obj.FPD_Cs, buffer, bufferOffset);
    // Serialize message field [IMU_Header]
    bufferOffset = _serializer.string(obj.IMU_Header, buffer, bufferOffset);
    // Serialize message field [IMU_GPSWeek]
    bufferOffset = _serializer.string(obj.IMU_GPSWeek, buffer, bufferOffset);
    // Serialize message field [IMU_GPSTime]
    bufferOffset = _serializer.string(obj.IMU_GPSTime, buffer, bufferOffset);
    // Serialize message field [GyroX]
    bufferOffset = _serializer.string(obj.GyroX, buffer, bufferOffset);
    // Serialize message field [GyroY]
    bufferOffset = _serializer.string(obj.GyroY, buffer, bufferOffset);
    // Serialize message field [GyroZ]
    bufferOffset = _serializer.string(obj.GyroZ, buffer, bufferOffset);
    // Serialize message field [AccX]
    bufferOffset = _serializer.string(obj.AccX, buffer, bufferOffset);
    // Serialize message field [AccY]
    bufferOffset = _serializer.string(obj.AccY, buffer, bufferOffset);
    // Serialize message field [AccZ]
    bufferOffset = _serializer.string(obj.AccZ, buffer, bufferOffset);
    // Serialize message field [Tpr]
    bufferOffset = _serializer.string(obj.Tpr, buffer, bufferOffset);
    // Serialize message field [IMU_Cs]
    bufferOffset = _serializer.string(obj.IMU_Cs, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _serializer.float64(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float64(obj.y, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type gps
    let len;
    let data = new gps(null);
    // Deserialize message field [FPD_Header]
    data.FPD_Header = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [FPD_GPSWeek]
    data.FPD_GPSWeek = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [FPD_GPSTime]
    data.FPD_GPSTime = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Heading]
    data.Heading = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Pitch]
    data.Pitch = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Roll]
    data.Roll = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Lattitude]
    data.Lattitude = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Longitude]
    data.Longitude = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Altitude]
    data.Altitude = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Ve]
    data.Ve = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Vn]
    data.Vn = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Vu]
    data.Vu = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Baseline]
    data.Baseline = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [NSV1]
    data.NSV1 = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [NSV2]
    data.NSV2 = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Status]
    data.Status = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [FPD_Cs]
    data.FPD_Cs = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [IMU_Header]
    data.IMU_Header = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [IMU_GPSWeek]
    data.IMU_GPSWeek = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [IMU_GPSTime]
    data.IMU_GPSTime = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [GyroX]
    data.GyroX = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [GyroY]
    data.GyroY = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [GyroZ]
    data.GyroZ = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [AccX]
    data.AccX = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [AccY]
    data.AccY = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [AccZ]
    data.AccZ = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Tpr]
    data.Tpr = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [IMU_Cs]
    data.IMU_Cs = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.FPD_Header.length;
    length += object.FPD_GPSWeek.length;
    length += object.FPD_GPSTime.length;
    length += object.Heading.length;
    length += object.Pitch.length;
    length += object.Roll.length;
    length += object.Lattitude.length;
    length += object.Longitude.length;
    length += object.Altitude.length;
    length += object.Ve.length;
    length += object.Vn.length;
    length += object.Vu.length;
    length += object.Baseline.length;
    length += object.NSV1.length;
    length += object.NSV2.length;
    length += object.Status.length;
    length += object.FPD_Cs.length;
    length += object.IMU_Header.length;
    length += object.IMU_GPSWeek.length;
    length += object.IMU_GPSTime.length;
    length += object.GyroX.length;
    length += object.GyroY.length;
    length += object.GyroZ.length;
    length += object.AccX.length;
    length += object.AccY.length;
    length += object.AccZ.length;
    length += object.Tpr.length;
    length += object.IMU_Cs.length;
    return length + 128;
  }

  static datatype() {
    // Returns string type for a message object
    return 'localization/gps';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6cefa42fc634a5edcdb1a380b1794e86';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string FPD_Header
    string FPD_GPSWeek
    string FPD_GPSTime
    string Heading
    string Pitch
    string Roll
    string Lattitude
    string Longitude
    string Altitude
    string Ve
    string Vn
    string Vu
    string Baseline
    string NSV1
    string NSV2
    string Status
    string FPD_Cs
    
    string IMU_Header
    string IMU_GPSWeek
    string IMU_GPSTime
    string GyroX
    string GyroY
    string GyroZ
    string AccX
    string AccY
    string AccZ
    string Tpr
    string IMU_Cs
    float64 x 
    float64 y
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new gps(null);
    if (msg.FPD_Header !== undefined) {
      resolved.FPD_Header = msg.FPD_Header;
    }
    else {
      resolved.FPD_Header = ''
    }

    if (msg.FPD_GPSWeek !== undefined) {
      resolved.FPD_GPSWeek = msg.FPD_GPSWeek;
    }
    else {
      resolved.FPD_GPSWeek = ''
    }

    if (msg.FPD_GPSTime !== undefined) {
      resolved.FPD_GPSTime = msg.FPD_GPSTime;
    }
    else {
      resolved.FPD_GPSTime = ''
    }

    if (msg.Heading !== undefined) {
      resolved.Heading = msg.Heading;
    }
    else {
      resolved.Heading = ''
    }

    if (msg.Pitch !== undefined) {
      resolved.Pitch = msg.Pitch;
    }
    else {
      resolved.Pitch = ''
    }

    if (msg.Roll !== undefined) {
      resolved.Roll = msg.Roll;
    }
    else {
      resolved.Roll = ''
    }

    if (msg.Lattitude !== undefined) {
      resolved.Lattitude = msg.Lattitude;
    }
    else {
      resolved.Lattitude = ''
    }

    if (msg.Longitude !== undefined) {
      resolved.Longitude = msg.Longitude;
    }
    else {
      resolved.Longitude = ''
    }

    if (msg.Altitude !== undefined) {
      resolved.Altitude = msg.Altitude;
    }
    else {
      resolved.Altitude = ''
    }

    if (msg.Ve !== undefined) {
      resolved.Ve = msg.Ve;
    }
    else {
      resolved.Ve = ''
    }

    if (msg.Vn !== undefined) {
      resolved.Vn = msg.Vn;
    }
    else {
      resolved.Vn = ''
    }

    if (msg.Vu !== undefined) {
      resolved.Vu = msg.Vu;
    }
    else {
      resolved.Vu = ''
    }

    if (msg.Baseline !== undefined) {
      resolved.Baseline = msg.Baseline;
    }
    else {
      resolved.Baseline = ''
    }

    if (msg.NSV1 !== undefined) {
      resolved.NSV1 = msg.NSV1;
    }
    else {
      resolved.NSV1 = ''
    }

    if (msg.NSV2 !== undefined) {
      resolved.NSV2 = msg.NSV2;
    }
    else {
      resolved.NSV2 = ''
    }

    if (msg.Status !== undefined) {
      resolved.Status = msg.Status;
    }
    else {
      resolved.Status = ''
    }

    if (msg.FPD_Cs !== undefined) {
      resolved.FPD_Cs = msg.FPD_Cs;
    }
    else {
      resolved.FPD_Cs = ''
    }

    if (msg.IMU_Header !== undefined) {
      resolved.IMU_Header = msg.IMU_Header;
    }
    else {
      resolved.IMU_Header = ''
    }

    if (msg.IMU_GPSWeek !== undefined) {
      resolved.IMU_GPSWeek = msg.IMU_GPSWeek;
    }
    else {
      resolved.IMU_GPSWeek = ''
    }

    if (msg.IMU_GPSTime !== undefined) {
      resolved.IMU_GPSTime = msg.IMU_GPSTime;
    }
    else {
      resolved.IMU_GPSTime = ''
    }

    if (msg.GyroX !== undefined) {
      resolved.GyroX = msg.GyroX;
    }
    else {
      resolved.GyroX = ''
    }

    if (msg.GyroY !== undefined) {
      resolved.GyroY = msg.GyroY;
    }
    else {
      resolved.GyroY = ''
    }

    if (msg.GyroZ !== undefined) {
      resolved.GyroZ = msg.GyroZ;
    }
    else {
      resolved.GyroZ = ''
    }

    if (msg.AccX !== undefined) {
      resolved.AccX = msg.AccX;
    }
    else {
      resolved.AccX = ''
    }

    if (msg.AccY !== undefined) {
      resolved.AccY = msg.AccY;
    }
    else {
      resolved.AccY = ''
    }

    if (msg.AccZ !== undefined) {
      resolved.AccZ = msg.AccZ;
    }
    else {
      resolved.AccZ = ''
    }

    if (msg.Tpr !== undefined) {
      resolved.Tpr = msg.Tpr;
    }
    else {
      resolved.Tpr = ''
    }

    if (msg.IMU_Cs !== undefined) {
      resolved.IMU_Cs = msg.IMU_Cs;
    }
    else {
      resolved.IMU_Cs = ''
    }

    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = 0.0
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = 0.0
    }

    return resolved;
    }
};

module.exports = gps;
