// Auto-generated. Do not edit!

// (in-package canbus.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class frame {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.VI_GearInfo = null;
      this.VI_BrakeInfo = null;
      this.VI_Button1 = null;
      this.VI_Button2 = null;
      this.VI_HandBrakeSt = null;
      this.VI_JerkSt = null;
      this.VI_AccelPedalPosition = null;
      this.VI_FrontSteeringAngle = null;
      this.VI_RemainingTimes = null;
      this.VI_VehicleSpeed = null;
      this.SI2_LongitudinalAccel = null;
      this.SI2_LateralAccel = null;
      this.SI2_YawRate = null;
      this.SR_CurrentSteeringAngle = null;
      this.SR_CurrentSteeringSpeed = null;
      this.SR_HandTorque = null;
      this.SR_HandTorqueSign = null;
      this.SR_WorkMode = null;
      this.SR_HandTorqueLimit = null;
      this.SR_Error = null;
      this.SR_Warning = null;
      this.SR_LiveCounter = null;
    }
    else {
      if (initObj.hasOwnProperty('VI_GearInfo')) {
        this.VI_GearInfo = initObj.VI_GearInfo
      }
      else {
        this.VI_GearInfo = 0;
      }
      if (initObj.hasOwnProperty('VI_BrakeInfo')) {
        this.VI_BrakeInfo = initObj.VI_BrakeInfo
      }
      else {
        this.VI_BrakeInfo = 0;
      }
      if (initObj.hasOwnProperty('VI_Button1')) {
        this.VI_Button1 = initObj.VI_Button1
      }
      else {
        this.VI_Button1 = 0;
      }
      if (initObj.hasOwnProperty('VI_Button2')) {
        this.VI_Button2 = initObj.VI_Button2
      }
      else {
        this.VI_Button2 = 0;
      }
      if (initObj.hasOwnProperty('VI_HandBrakeSt')) {
        this.VI_HandBrakeSt = initObj.VI_HandBrakeSt
      }
      else {
        this.VI_HandBrakeSt = 0;
      }
      if (initObj.hasOwnProperty('VI_JerkSt')) {
        this.VI_JerkSt = initObj.VI_JerkSt
      }
      else {
        this.VI_JerkSt = 0;
      }
      if (initObj.hasOwnProperty('VI_AccelPedalPosition')) {
        this.VI_AccelPedalPosition = initObj.VI_AccelPedalPosition
      }
      else {
        this.VI_AccelPedalPosition = 0.0;
      }
      if (initObj.hasOwnProperty('VI_FrontSteeringAngle')) {
        this.VI_FrontSteeringAngle = initObj.VI_FrontSteeringAngle
      }
      else {
        this.VI_FrontSteeringAngle = 0.0;
      }
      if (initObj.hasOwnProperty('VI_RemainingTimes')) {
        this.VI_RemainingTimes = initObj.VI_RemainingTimes
      }
      else {
        this.VI_RemainingTimes = 0.0;
      }
      if (initObj.hasOwnProperty('VI_VehicleSpeed')) {
        this.VI_VehicleSpeed = initObj.VI_VehicleSpeed
      }
      else {
        this.VI_VehicleSpeed = 0.0;
      }
      if (initObj.hasOwnProperty('SI2_LongitudinalAccel')) {
        this.SI2_LongitudinalAccel = initObj.SI2_LongitudinalAccel
      }
      else {
        this.SI2_LongitudinalAccel = 0.0;
      }
      if (initObj.hasOwnProperty('SI2_LateralAccel')) {
        this.SI2_LateralAccel = initObj.SI2_LateralAccel
      }
      else {
        this.SI2_LateralAccel = 0.0;
      }
      if (initObj.hasOwnProperty('SI2_YawRate')) {
        this.SI2_YawRate = initObj.SI2_YawRate
      }
      else {
        this.SI2_YawRate = 0.0;
      }
      if (initObj.hasOwnProperty('SR_CurrentSteeringAngle')) {
        this.SR_CurrentSteeringAngle = initObj.SR_CurrentSteeringAngle
      }
      else {
        this.SR_CurrentSteeringAngle = 0.0;
      }
      if (initObj.hasOwnProperty('SR_CurrentSteeringSpeed')) {
        this.SR_CurrentSteeringSpeed = initObj.SR_CurrentSteeringSpeed
      }
      else {
        this.SR_CurrentSteeringSpeed = 0.0;
      }
      if (initObj.hasOwnProperty('SR_HandTorque')) {
        this.SR_HandTorque = initObj.SR_HandTorque
      }
      else {
        this.SR_HandTorque = 0.0;
      }
      if (initObj.hasOwnProperty('SR_HandTorqueSign')) {
        this.SR_HandTorqueSign = initObj.SR_HandTorqueSign
      }
      else {
        this.SR_HandTorqueSign = 0.0;
      }
      if (initObj.hasOwnProperty('SR_WorkMode')) {
        this.SR_WorkMode = initObj.SR_WorkMode
      }
      else {
        this.SR_WorkMode = 0;
      }
      if (initObj.hasOwnProperty('SR_HandTorqueLimit')) {
        this.SR_HandTorqueLimit = initObj.SR_HandTorqueLimit
      }
      else {
        this.SR_HandTorqueLimit = 0.0;
      }
      if (initObj.hasOwnProperty('SR_Error')) {
        this.SR_Error = initObj.SR_Error
      }
      else {
        this.SR_Error = 0;
      }
      if (initObj.hasOwnProperty('SR_Warning')) {
        this.SR_Warning = initObj.SR_Warning
      }
      else {
        this.SR_Warning = 0;
      }
      if (initObj.hasOwnProperty('SR_LiveCounter')) {
        this.SR_LiveCounter = initObj.SR_LiveCounter
      }
      else {
        this.SR_LiveCounter = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type frame
    // Serialize message field [VI_GearInfo]
    bufferOffset = _serializer.int32(obj.VI_GearInfo, buffer, bufferOffset);
    // Serialize message field [VI_BrakeInfo]
    bufferOffset = _serializer.int32(obj.VI_BrakeInfo, buffer, bufferOffset);
    // Serialize message field [VI_Button1]
    bufferOffset = _serializer.int32(obj.VI_Button1, buffer, bufferOffset);
    // Serialize message field [VI_Button2]
    bufferOffset = _serializer.int32(obj.VI_Button2, buffer, bufferOffset);
    // Serialize message field [VI_HandBrakeSt]
    bufferOffset = _serializer.int32(obj.VI_HandBrakeSt, buffer, bufferOffset);
    // Serialize message field [VI_JerkSt]
    bufferOffset = _serializer.int32(obj.VI_JerkSt, buffer, bufferOffset);
    // Serialize message field [VI_AccelPedalPosition]
    bufferOffset = _serializer.float64(obj.VI_AccelPedalPosition, buffer, bufferOffset);
    // Serialize message field [VI_FrontSteeringAngle]
    bufferOffset = _serializer.float64(obj.VI_FrontSteeringAngle, buffer, bufferOffset);
    // Serialize message field [VI_RemainingTimes]
    bufferOffset = _serializer.float64(obj.VI_RemainingTimes, buffer, bufferOffset);
    // Serialize message field [VI_VehicleSpeed]
    bufferOffset = _serializer.float64(obj.VI_VehicleSpeed, buffer, bufferOffset);
    // Serialize message field [SI2_LongitudinalAccel]
    bufferOffset = _serializer.float64(obj.SI2_LongitudinalAccel, buffer, bufferOffset);
    // Serialize message field [SI2_LateralAccel]
    bufferOffset = _serializer.float64(obj.SI2_LateralAccel, buffer, bufferOffset);
    // Serialize message field [SI2_YawRate]
    bufferOffset = _serializer.float64(obj.SI2_YawRate, buffer, bufferOffset);
    // Serialize message field [SR_CurrentSteeringAngle]
    bufferOffset = _serializer.float64(obj.SR_CurrentSteeringAngle, buffer, bufferOffset);
    // Serialize message field [SR_CurrentSteeringSpeed]
    bufferOffset = _serializer.float64(obj.SR_CurrentSteeringSpeed, buffer, bufferOffset);
    // Serialize message field [SR_HandTorque]
    bufferOffset = _serializer.float64(obj.SR_HandTorque, buffer, bufferOffset);
    // Serialize message field [SR_HandTorqueSign]
    bufferOffset = _serializer.float64(obj.SR_HandTorqueSign, buffer, bufferOffset);
    // Serialize message field [SR_WorkMode]
    bufferOffset = _serializer.int32(obj.SR_WorkMode, buffer, bufferOffset);
    // Serialize message field [SR_HandTorqueLimit]
    bufferOffset = _serializer.float64(obj.SR_HandTorqueLimit, buffer, bufferOffset);
    // Serialize message field [SR_Error]
    bufferOffset = _serializer.int32(obj.SR_Error, buffer, bufferOffset);
    // Serialize message field [SR_Warning]
    bufferOffset = _serializer.int32(obj.SR_Warning, buffer, bufferOffset);
    // Serialize message field [SR_LiveCounter]
    bufferOffset = _serializer.float64(obj.SR_LiveCounter, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type frame
    let len;
    let data = new frame(null);
    // Deserialize message field [VI_GearInfo]
    data.VI_GearInfo = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [VI_BrakeInfo]
    data.VI_BrakeInfo = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [VI_Button1]
    data.VI_Button1 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [VI_Button2]
    data.VI_Button2 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [VI_HandBrakeSt]
    data.VI_HandBrakeSt = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [VI_JerkSt]
    data.VI_JerkSt = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [VI_AccelPedalPosition]
    data.VI_AccelPedalPosition = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [VI_FrontSteeringAngle]
    data.VI_FrontSteeringAngle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [VI_RemainingTimes]
    data.VI_RemainingTimes = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [VI_VehicleSpeed]
    data.VI_VehicleSpeed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SI2_LongitudinalAccel]
    data.SI2_LongitudinalAccel = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SI2_LateralAccel]
    data.SI2_LateralAccel = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SI2_YawRate]
    data.SI2_YawRate = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SR_CurrentSteeringAngle]
    data.SR_CurrentSteeringAngle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SR_CurrentSteeringSpeed]
    data.SR_CurrentSteeringSpeed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SR_HandTorque]
    data.SR_HandTorque = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SR_HandTorqueSign]
    data.SR_HandTorqueSign = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SR_WorkMode]
    data.SR_WorkMode = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [SR_HandTorqueLimit]
    data.SR_HandTorqueLimit = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [SR_Error]
    data.SR_Error = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [SR_Warning]
    data.SR_Warning = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [SR_LiveCounter]
    data.SR_LiveCounter = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 140;
  }

  static datatype() {
    // Returns string type for a message object
    return 'canbus/frame';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9aaf52d1c4f27f1011105abbe0b2efe7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 VI_GearInfo  
    int32 VI_BrakeInfo  
    int32 VI_Button1  
    int32 VI_Button2  
    int32 VI_HandBrakeSt  
    int32 VI_JerkSt  
    float64 VI_AccelPedalPosition  
    float64 VI_FrontSteeringAngle  
    float64 VI_RemainingTimes  
    float64 VI_VehicleSpeed  
    float64 SI2_LongitudinalAccel  
    float64 SI2_LateralAccel  
    float64 SI2_YawRate  
    
    float64 SR_CurrentSteeringAngle 
    float64 SR_CurrentSteeringSpeed 
    float64 SR_HandTorque
    float64 SR_HandTorqueSign
    int32 SR_WorkMode 
    float64 SR_HandTorqueLimit 
    int32 SR_Error
    int32 SR_Warning 
    float64 SR_LiveCounter 
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new frame(null);
    if (msg.VI_GearInfo !== undefined) {
      resolved.VI_GearInfo = msg.VI_GearInfo;
    }
    else {
      resolved.VI_GearInfo = 0
    }

    if (msg.VI_BrakeInfo !== undefined) {
      resolved.VI_BrakeInfo = msg.VI_BrakeInfo;
    }
    else {
      resolved.VI_BrakeInfo = 0
    }

    if (msg.VI_Button1 !== undefined) {
      resolved.VI_Button1 = msg.VI_Button1;
    }
    else {
      resolved.VI_Button1 = 0
    }

    if (msg.VI_Button2 !== undefined) {
      resolved.VI_Button2 = msg.VI_Button2;
    }
    else {
      resolved.VI_Button2 = 0
    }

    if (msg.VI_HandBrakeSt !== undefined) {
      resolved.VI_HandBrakeSt = msg.VI_HandBrakeSt;
    }
    else {
      resolved.VI_HandBrakeSt = 0
    }

    if (msg.VI_JerkSt !== undefined) {
      resolved.VI_JerkSt = msg.VI_JerkSt;
    }
    else {
      resolved.VI_JerkSt = 0
    }

    if (msg.VI_AccelPedalPosition !== undefined) {
      resolved.VI_AccelPedalPosition = msg.VI_AccelPedalPosition;
    }
    else {
      resolved.VI_AccelPedalPosition = 0.0
    }

    if (msg.VI_FrontSteeringAngle !== undefined) {
      resolved.VI_FrontSteeringAngle = msg.VI_FrontSteeringAngle;
    }
    else {
      resolved.VI_FrontSteeringAngle = 0.0
    }

    if (msg.VI_RemainingTimes !== undefined) {
      resolved.VI_RemainingTimes = msg.VI_RemainingTimes;
    }
    else {
      resolved.VI_RemainingTimes = 0.0
    }

    if (msg.VI_VehicleSpeed !== undefined) {
      resolved.VI_VehicleSpeed = msg.VI_VehicleSpeed;
    }
    else {
      resolved.VI_VehicleSpeed = 0.0
    }

    if (msg.SI2_LongitudinalAccel !== undefined) {
      resolved.SI2_LongitudinalAccel = msg.SI2_LongitudinalAccel;
    }
    else {
      resolved.SI2_LongitudinalAccel = 0.0
    }

    if (msg.SI2_LateralAccel !== undefined) {
      resolved.SI2_LateralAccel = msg.SI2_LateralAccel;
    }
    else {
      resolved.SI2_LateralAccel = 0.0
    }

    if (msg.SI2_YawRate !== undefined) {
      resolved.SI2_YawRate = msg.SI2_YawRate;
    }
    else {
      resolved.SI2_YawRate = 0.0
    }

    if (msg.SR_CurrentSteeringAngle !== undefined) {
      resolved.SR_CurrentSteeringAngle = msg.SR_CurrentSteeringAngle;
    }
    else {
      resolved.SR_CurrentSteeringAngle = 0.0
    }

    if (msg.SR_CurrentSteeringSpeed !== undefined) {
      resolved.SR_CurrentSteeringSpeed = msg.SR_CurrentSteeringSpeed;
    }
    else {
      resolved.SR_CurrentSteeringSpeed = 0.0
    }

    if (msg.SR_HandTorque !== undefined) {
      resolved.SR_HandTorque = msg.SR_HandTorque;
    }
    else {
      resolved.SR_HandTorque = 0.0
    }

    if (msg.SR_HandTorqueSign !== undefined) {
      resolved.SR_HandTorqueSign = msg.SR_HandTorqueSign;
    }
    else {
      resolved.SR_HandTorqueSign = 0.0
    }

    if (msg.SR_WorkMode !== undefined) {
      resolved.SR_WorkMode = msg.SR_WorkMode;
    }
    else {
      resolved.SR_WorkMode = 0
    }

    if (msg.SR_HandTorqueLimit !== undefined) {
      resolved.SR_HandTorqueLimit = msg.SR_HandTorqueLimit;
    }
    else {
      resolved.SR_HandTorqueLimit = 0.0
    }

    if (msg.SR_Error !== undefined) {
      resolved.SR_Error = msg.SR_Error;
    }
    else {
      resolved.SR_Error = 0
    }

    if (msg.SR_Warning !== undefined) {
      resolved.SR_Warning = msg.SR_Warning;
    }
    else {
      resolved.SR_Warning = 0
    }

    if (msg.SR_LiveCounter !== undefined) {
      resolved.SR_LiveCounter = msg.SR_LiveCounter;
    }
    else {
      resolved.SR_LiveCounter = 0.0
    }

    return resolved;
    }
};

module.exports = frame;
