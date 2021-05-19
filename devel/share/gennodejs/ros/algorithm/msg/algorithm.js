// Auto-generated. Do not edit!

// (in-package algorithm.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class algorithm {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.CurrentSteeringAngle = null;
      this.LongitudinalAccel = null;
    }
    else {
      if (initObj.hasOwnProperty('CurrentSteeringAngle')) {
        this.CurrentSteeringAngle = initObj.CurrentSteeringAngle
      }
      else {
        this.CurrentSteeringAngle = 0.0;
      }
      if (initObj.hasOwnProperty('LongitudinalAccel')) {
        this.LongitudinalAccel = initObj.LongitudinalAccel
      }
      else {
        this.LongitudinalAccel = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type algorithm
    // Serialize message field [CurrentSteeringAngle]
    bufferOffset = _serializer.float64(obj.CurrentSteeringAngle, buffer, bufferOffset);
    // Serialize message field [LongitudinalAccel]
    bufferOffset = _serializer.float64(obj.LongitudinalAccel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type algorithm
    let len;
    let data = new algorithm(null);
    // Deserialize message field [CurrentSteeringAngle]
    data.CurrentSteeringAngle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [LongitudinalAccel]
    data.LongitudinalAccel = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'algorithm/algorithm';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9844dd521b673e544e6966cec9aa7917';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 CurrentSteeringAngle
    float64 LongitudinalAccel
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new algorithm(null);
    if (msg.CurrentSteeringAngle !== undefined) {
      resolved.CurrentSteeringAngle = msg.CurrentSteeringAngle;
    }
    else {
      resolved.CurrentSteeringAngle = 0.0
    }

    if (msg.LongitudinalAccel !== undefined) {
      resolved.LongitudinalAccel = msg.LongitudinalAccel;
    }
    else {
      resolved.LongitudinalAccel = 0.0
    }

    return resolved;
    }
};

module.exports = algorithm;
