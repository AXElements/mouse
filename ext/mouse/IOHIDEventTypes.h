/*
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_HID_IOHIDEVENTTYPES_H
#define _IOKIT_HID_IOHIDEVENTTYPES_H /* { */

#include <IOKit/IOTypes.h>

#define IOHIDEventTypeMask(type) (1<<type)
#define IOHIDEventFieldBase(type) (type << 16)
/*!
    @typedef IOHIDEventType
    @abstract The type of event represented by an IOHIDEventRef.
    @discussion It is possible that a single IOHIDEventRef can conform to
    multiple event types through the use of sub events.  For futher information
    as to how to determinte the type of event please reference IOHIDEventGetType
    and IOHIDEventConformsTo.
    @constant kIOHIDEventTypeNULL
    @constant kIOHIDEventTypeVendorDefined
    @constant kIOHIDEventTypeButton
    @constant kIOHIDEventTypeTranslation
    @constant kIOHIDEventTypeRotation
    @constant kIOHIDEventTypeScroll
    @constant kIOHIDEventTypeScale
    @constant kIOHIDEventTypeVelocity
    @constant kIOHIDEventTypeOrientation
    @constant kIOHIDEventTypeKeyboard
    @constant kIOHIDEventTypeDigitizer
    @constant kIOHIDEventTypeAmbientLightSensor
    @constant kIOHIDEventTypeAccelerometer
    @constant kIOHIDEventTypeProximity
    @constant kIOHIDEventTypeTemperature
    @constant kIOHIDEventTypeMouse
    @constant kIOHIDEventTypeProgress
    @constant kIOHIDEventTypeNavigationSwipe
    @constant kIOHIDEventTypeGyro
    @constant kIOHIDEventTypeCompass
    @constant kIOHIDEventTypeZoomToggle
    @constant kIOHIDEventTypeDockSwipe
    @constant kIOHIDEventTypePower
    @constant kIOHIDEventTypeBrightness
    @constant kIOHIDEventTypeFluidTouchGesture
    @constant kIOHIDEventTypeBoundaryScroll
    @constant kIOHIDEventTypeReset

*/
enum {
    kIOHIDEventTypeNULL,                    // 0
    kIOHIDEventTypeVendorDefined,
    kIOHIDEventTypeButton,
    kIOHIDEventTypeKeyboard,
    kIOHIDEventTypeTranslation,
    kIOHIDEventTypeRotation,                // 5
    kIOHIDEventTypeScroll,
    kIOHIDEventTypeScale,
    kIOHIDEventTypeZoom,
    kIOHIDEventTypeVelocity,
    kIOHIDEventTypeOrientation,             // 10
    kIOHIDEventTypeDigitizer,
    kIOHIDEventTypeAmbientLightSensor,
    kIOHIDEventTypeAccelerometer,
    kIOHIDEventTypeProximity,
    kIOHIDEventTypeTemperature,             // 15
    kIOHIDEventTypeNavigationSwipe,
    kIOHIDEventTypeSwipe = kIOHIDEventTypeNavigationSwipe,
    kIOHIDEventTypeMouse,
    kIOHIDEventTypeProgress,
    kIOHIDEventTypeCount,
    kIOHIDEventTypeGyro,                    // 20
    kIOHIDEventTypeCompass,
    kIOHIDEventTypeZoomToggle,
    kIOHIDEventTypeDockSwipe, // just like kIOHIDEventTypeNavigationSwipe, but intended for consumption by Dock
    kIOHIDEventTypeSymbolicHotKey,
    kIOHIDEventTypePower,                   // 25
    kIOHIDEventTypeBrightness,
    kIOHIDEventTypeFluidTouchGesture, // This will eventually superseed Navagation and Dock swipes
    kIOHIDEventTypeBoundaryScroll,
    kIOHIDEventTypeReset,
};
typedef uint32_t IOHIDEventType;

/*
    @typedef IOHIDEventField
    @abstract Keys used to set and get individual event fields.
*/
enum {
    kIOHIDEventFieldIsRelative = IOHIDEventFieldBase(kIOHIDEventTypeNULL),
    kIOHIDEventFieldIsCollection
};

enum {
    kIOHIDEventFieldVendorDefinedUsagePage = IOHIDEventFieldBase(kIOHIDEventTypeVendorDefined),
    kIOHIDEventFieldVendorDefinedUsage,
    kIOHIDEventFieldVendorDefinedVersion,
    kIOHIDEventFieldVendorDefinedDataLength,
    kIOHIDEventFieldVendorDefinedData
};

enum  {
    kIOHIDEventFieldButtonMask = IOHIDEventFieldBase(kIOHIDEventTypeButton),
    kIOHIDEventFieldButtonNumber,
    kIOHIDEventFieldButtonClickCount,
    kIOHIDEventFieldButtonPressure
};

enum {
    kIOHIDEventFieldTranslationX = IOHIDEventFieldBase(kIOHIDEventTypeTranslation),
    kIOHIDEventFieldTranslationY,
    kIOHIDEventFieldTranslationZ
};

enum {
    kIOHIDEventFieldRotationX = IOHIDEventFieldBase(kIOHIDEventTypeRotation),
    kIOHIDEventFieldRotationY,
    kIOHIDEventFieldRotationZ
};

enum {
    kIOHIDEventFieldScrollX = IOHIDEventFieldBase(kIOHIDEventTypeScroll),
    kIOHIDEventFieldScrollY,
    kIOHIDEventFieldScrollZ,
    kIOHIDEventFieldScrollIsPixels
};

enum {
    kIOHIDEventFieldScaleX = IOHIDEventFieldBase(kIOHIDEventTypeScale),
    kIOHIDEventFieldScaleY,
    kIOHIDEventFieldScaleZ
};

enum {
    kIOHIDEventFieldVelocityX = IOHIDEventFieldBase(kIOHIDEventTypeVelocity),
    kIOHIDEventFieldVelocityY,
    kIOHIDEventFieldVelocityZ
};

/*!
 @typedef IOHIDMotionType
 @abstract Type of Motion event triggered.
 @discussion
 @constant kIOHIDMotionStart
 @constant kIOHIDMotionEnd
 */
enum {
    kIOHIDMotionStart   = 0,
    kIOHIDMotionEnd     = 1,
};
typedef uint32_t IOHIDMotionType;


/*!
	@typedef IOHIDAccelerometerType
	@abstract Type of accelerometer event triggered.
    @discussion
	@constant kIOHIDAccelerometerTypeNormal
	@constant kIOHIDAccelerometerTypeShake
*/
enum {
    kIOHIDAccelerometerTypeNormal   = 0,
    kIOHIDAccelerometerTypeShake    = 1
};
typedef uint32_t IOHIDAccelerometerType;
typedef IOHIDMotionType IOHIDAccelerometerSubType;

enum {
    kIOHIDEventFieldAccelerometerX = IOHIDEventFieldBase(kIOHIDEventTypeAccelerometer),
    kIOHIDEventFieldAccelerometerY,
    kIOHIDEventFieldAccelerometerZ,
    kIOHIDEventFieldAccelerometerType,
	kIOHIDEventFieldAccelerometerSubType
};

enum {
    kIOHIDEventFieldMouseX = IOHIDEventFieldBase(kIOHIDEventTypeMouse),
    kIOHIDEventFieldMouseY,
    kIOHIDEventFieldMouseZ,
    kIOHIDEventFieldMouseButtonMask,
    kIOHIDEventFieldMouseNumber,
    kIOHIDEventFieldMouseClickCount,
    kIOHIDEventFieldMousePressure
};

/*!
 @typedef IOHIDGyroType
 @abstract Type of Gyro event triggered.
 @discussion
 @constant kIOHIDGyroTypeNormal
 @constant kIOHIDGyroTypeShake
 */
enum {
    kIOHIDGyroTypeNormal   = 0,
    kIOHIDGyroTypeShake    = 1,
	kIOHIDGyroTypeMotion   = 2
};
typedef uint32_t IOHIDGyroType;
typedef IOHIDMotionType IOHIDGyroSubType ;

enum {
    kIOHIDEventFieldGyroX = IOHIDEventFieldBase(kIOHIDEventTypeGyro),
    kIOHIDEventFieldGyroY,
    kIOHIDEventFieldGyroZ,
    kIOHIDEventFieldGyroType,
    kIOHIDEventFieldGyroSubType,
};

typedef IOHIDMotionType IOHIDCompassType ;

enum {
    kIOHIDEventFieldCompassX = IOHIDEventFieldBase(kIOHIDEventTypeCompass),
    kIOHIDEventFieldCompassY,
    kIOHIDEventFieldCompassZ,
	kIOHIDEventFieldCompassType
};

enum {
    kIOHIDEventFieldAmbientLightSensorLevel = IOHIDEventFieldBase(kIOHIDEventTypeAmbientLightSensor),
    kIOHIDEventFieldAmbientLightSensorRawChannel0,
    kIOHIDEventFieldAmbientLightSensorRawChannel1,
    kIOHIDEventFieldAmbientLightSensorRawChannel2,
    kIOHIDEventFieldAmbientLightSensorRawChannel3,
    kIOHIDEventFieldAmbientLightDisplayBrightnessChanged
};

enum {
    kIOHIDEventFieldTemperatureLevel = IOHIDEventFieldBase(kIOHIDEventTypeTemperature)
};

enum {
    kIOHIDEventFieldProximityDetectionMask = IOHIDEventFieldBase(kIOHIDEventTypeProximity),
	kIOHIDEventFieldProximityLevel
};


enum {
    kIOHIDEventFieldOrientationRadius   = IOHIDEventFieldBase(kIOHIDEventTypeOrientation),
    kIOHIDEventFieldOrientationAzimuth,
    kIOHIDEventFieldOrientationAltitude
};

enum {
    kIOHIDEventFieldKeyboardUsagePage = IOHIDEventFieldBase(kIOHIDEventTypeKeyboard),
    kIOHIDEventFieldKeyboardUsage,
    kIOHIDEventFieldKeyboardDown,
    kIOHIDEventFieldKeyboardRepeat
};

enum {
    kIOHIDEventFieldDigitizerX = IOHIDEventFieldBase(kIOHIDEventTypeDigitizer),
    kIOHIDEventFieldDigitizerY,
    kIOHIDEventFieldDigitizerZ,
    kIOHIDEventFieldDigitizerButtonMask,
    kIOHIDEventFieldDigitizerType,
    kIOHIDEventFieldDigitizerIndex,
    kIOHIDEventFieldDigitizerIdentity,
    kIOHIDEventFieldDigitizerEventMask,
    kIOHIDEventFieldDigitizerRange,
    kIOHIDEventFieldDigitizerTouch,
    kIOHIDEventFieldDigitizerPressure,
    kIOHIDEventFieldDigitizerBarrelPressure,
    kIOHIDEventFieldDigitizerTwist,
    kIOHIDEventFieldDigitizerTiltX,
    kIOHIDEventFieldDigitizerTiltY,
    kIOHIDEventFieldDigitizerAltitude,
    kIOHIDEventFieldDigitizerAzimuth,
    kIOHIDEventFieldDigitizerQuality,
    kIOHIDEventFieldDigitizerDensity,
    kIOHIDEventFieldDigitizerIrregularity,
    kIOHIDEventFieldDigitizerMajorRadius,
    kIOHIDEventFieldDigitizerMinorRadius,
    kIOHIDEventFieldDigitizerCollection,
    kIOHIDEventFieldDigitizerCollectionChord,
    kIOHIDEventFieldDigitizerChildEventMask
};

enum {
    kIOHIDEventFieldSwipeMask = IOHIDEventFieldBase(kIOHIDEventTypeSwipe),
    kIOHIDEventFieldSwipeMotion,
    kIOHIDEventFieldSwipeProgress,
    kIOHIDEventFieldSwipePositionX,
    kIOHIDEventFieldSwipePositionY,
    kIOHIDEventFieldSwipeFlavor,
};

enum {
    kIOHIDEventFieldNavigationSwipeMask = IOHIDEventFieldBase(kIOHIDEventTypeNavigationSwipe),
    kIOHIDEventFieldNavigationSwipeMotion,
    kIOHIDEventFieldNavigationSwipeProgress,
    kIOHIDEventFieldNavigationSwipePositionX,
    kIOHIDEventFieldNavigationSwipePositionY,
    kIOHIDEventFieldNavagationSwipeFlavor,
};

enum {
    kIOHIDEventFieldDockSwipeMask = IOHIDEventFieldBase(kIOHIDEventTypeDockSwipe),
    kIOHIDEventFieldDockSwipeMotion,
    kIOHIDEventFieldDockSwipeProgress,
    kIOHIDEventFieldDockSwipePositionX,
    kIOHIDEventFieldDockSwipePositionY,
    kIOHIDEventFieldDockSwipeFlavor,
};

enum {
    kIOHIDEventFieldFluidTouchGestureMask = IOHIDEventFieldBase(kIOHIDEventTypeFluidTouchGesture),
    kIOHIDEventFieldFluidTouchGestureMotion,
    kIOHIDEventFieldFluidTouchGestureProgress,
    kIOHIDEventFieldFluidTouchGesturePositionX,
    kIOHIDEventFieldFluidTouchGesturePositionY,
    kIOHIDEventFieldFluidTouchGestureFlavor,
};

enum {
    kIOHIDEventFieldBoundaryScrollMask = IOHIDEventFieldBase(kIOHIDEventTypeBoundaryScroll),
    kIOHIDEventFieldBoundaryScrollMotion,
    kIOHIDEventFieldBoundaryScrollProgress,
    kIOHIDEventFieldBoundaryScrollPositionX,
    kIOHIDEventFieldBoundaryScrollPositionY,
    kIOHIDEventFieldBoundaryScrollFlavor,
};

enum {
    kIOHIDEventFieldProgressEventType = IOHIDEventFieldBase(kIOHIDEventTypeProgress),
    kIOHIDEventFieldProgressLevel,
};

enum {
    kIOHIDEventFieldSymbolicHotKeyValue = IOHIDEventFieldBase(kIOHIDEventTypeSymbolicHotKey),
    kIOHIDEventFieldSymbolicHotKeyIsCGSEvent,
};

/*!
 @typedef IOHIDPowerType
 @abstract Type of Power event triggered.
 @discussion
 @constant kIOHIDPowerTypePower
 @constant kIOHIDPowerTypeCurrent
 @constant kIOHIDPowerTypeVoltage
 */
enum {
    kIOHIDPowerTypePower    = 0,
    kIOHIDPowerTypeCurrent  = 1,
	kIOHIDPowerTypeVoltage  = 2
};
typedef uint32_t IOHIDPowerType;

/*!
 @typedef IOHIDPowerSubType
 @abstract Reserved
 @discussion
 @constant kIOHIDPowerSubTypeNormal
 */
enum {
    kIOHIDPowerSubTypeNormal = 0
};
typedef uint32_t IOHIDPowerSubType;

enum {
    kIOHIDEventFieldPowerMeasurement = IOHIDEventFieldBase(kIOHIDEventTypePower),
    kIOHIDEventFieldPowerType,
    kIOHIDEventFieldPowerSubType,
};

enum {
    kIOHIDEventFieldBrightnessLevel = IOHIDEventFieldBase(kIOHIDEventTypeBrightness),
};

typedef uint32_t IOHIDEventField;

/*!
    @typedef IOHIDSwipeMask
    @abstract Mask detailing the type of swipe detected.
    @discussion
    @constant kIOHIDSwipeUp
    @constant kIOHIDSwipeDown
    @constant kIOHIDSwipeLeft
    @constant kIOHIDSwipeRight
*/
enum {
    kIOHIDSwipeNone             = 0x00000000,
    kIOHIDSwipeUp               = 0x00000001,
    kIOHIDSwipeDown             = 0x00000002,
    kIOHIDSwipeLeft             = 0x00000004,
    kIOHIDSwipeRight            = 0x00000008,
    kIOHIDScaleExpand           = 0x00000010,
    kIOHIDScaleContract         = 0x00000020,
    kIOHIDRotateCW              = 0x00000040,
    kIOHIDRotateCCW             = 0x00000080,
};
typedef uint32_t IOHIDSwipeMask;

/*!
    @typedef IOHIDGestureMotion
    @abstract
    @constant kIOHIDGestureMotionNone
    @constant kIOHIDGestureMotionHorizontalX
    @constant kIOHIDGestureMotionVerticalY
    @constant kIOHIDGestureMotionScale
    @constant kIOHIDGestureMotionRotate
    @constant kIOHIDGestureMotionTap
    @constant kIOHIDGestureMotionDoubleTap
    @constant kIOHIDGestureMotionFromLeftEdge
    @constant kIOHIDGestureMotionOffLeftEdge
    @constant kIOHIDGestureMotionFromRightEdge
    @constant kIOHIDGestureMotionOffRightEdge
    @constant kIOHIDGestureMotionFromTopEdge
    @constant kIOHIDGestureMotionOffTopEdge
    @constant kIOHIDGestureMotionFromBottomEdge
    @constant kIOHIDGestureMotionOffBottomEdge
*/
enum {
    kIOHIDGestureMotionNone,
    kIOHIDGestureMotionHorizontalX,
    kIOHIDGestureMotionVerticalY,
    kIOHIDGestureMotionScale,
    kIOHIDGestureMotionRotate,
    kIOHIDGestureMotionTap,
    kIOHIDGestureMotionDoubleTap,
    kIOHIDGestureMotionFromLeftEdge,
    kIOHIDGestureMotionOffLeftEdge,
    kIOHIDGestureMotionFromRightEdge,
    kIOHIDGestureMotionOffRightEdge,
    kIOHIDGestureMotionFromTopEdge,
    kIOHIDGestureMotionOffTopEdge,
    kIOHIDGestureMotionFromBottomEdge,
    kIOHIDGestureMotionOffBottomEdge,
};
typedef uint16_t IOHIDGestureMotion;

/*!
    @typedef IOHIDGestureFlavor
    @abstract
    @constant kIOHIDGestureFlavorNone
    @constant kIOHIDGestureFlavorNotificationCenterPrimary
    @constant kIOHIDGestureFlavorNotificationCenterSecondary
    @constant kIOHIDGestureFlavorDockPrimary
    @constant kIOHIDGestureFlavorDockSecondary
    @constant kIOHIDGestureFlavorNavagationPrimary
    @constant kIOHIDGestureFlavorNavagationSecondary
*/
enum {
    kIOHIDGestureFlavorNone,
    kIOHIDGestureFlavorNotificationCenterPrimary,
    kIOHIDGestureFlavorNotificationCenterSecondary,
    kIOHIDGestureFlavorDockPrimary,
    kIOHIDGestureFlavorDockSecondary,
    kIOHIDGestureFlavorNavagationPrimary,
    kIOHIDGestureFlavorNavagationSecondary,
};
typedef uint16_t IOHIDGestureFlavor;

/*!
    @typedef IOHIDProximityDetectionMask
    @abstract Proximity mask detailing the inputs that were detected.
    @discussion
    @constant kIOHIDProximityDetectionLargeBodyContact
    @constant kIOHIDProximityDetectionLargeBodyFarField
    @constant kIOHIDProximityDetectionIrregularObjects
    @constant kIOHIDProximityDetectionEdgeStraddling
    @constant kIOHIDProximityDetectionFlatFingerClasp
    @constant kIOHIDProximityDetectionFingerTouch
    @constant kIOHIDProximityDetectionReceiver
    @constant kIOHIDProximityDetectionSmallObjectsHovering
    @constant kIOHIDProximityDetectionReceiverCrude
    @constant kIOHIDProximityDetectionReceiverMonitoring
*/
enum {
    kIOHIDProximityDetectionLargeBodyContact                = 0x0001,
    kIOHIDProximityDetectionLargeBodyFarField               = 0x0002,
    kIOHIDProximityDetectionIrregularObjects                = 0x0004,
    kIOHIDProximityDetectionEdgeStraddling                  = 0x0008,
    kIOHIDProximityDetectionFlatFingerClasp                 = 0x0010,
    kIOHIDProximityDetectionFingerTouch                     = 0x0020,
    kIOHIDProximityDetectionReceiver                        = 0x0040,
    kIOHIDProximityDetectionSmallObjectsHovering            = 0x0080,
    kIOHIDProximityDetectionReceiverCrude                   = 0x0100,
    kIOHIDProximityDetectionReceiverMonitoring              = 0x0200
};
typedef uint32_t IOHIDProximityDetectionMask;

/*!
	@typedef IOHIDDigitizerType
	@abstract The type of digitizer path initiating an event.
    @discussion The IOHIDDigitizerType usually corresponds to the Logical Collection usage defined in Digitizer Usage Page (0x0d) of the USB HID Usage Tables.
	@constant kIOHIDDigitizerTypeStylus
    @constant kIOHIDDigitizerTypePuck
    @constant kIOHIDDigitizerTypeFinger
*/
enum {
    kIOHIDDigitizerTransducerTypeStylus  = 0x20,
    kIOHIDDigitizerTransducerTypePuck,
    kIOHIDDigitizerTransducerTypeFinger,
    kIOHIDDigitizerTransducerTypeHand
};
typedef uint32_t IOHIDDigitizerTransducerType;

/*!
	@typedef IOHIDDigitizerEventMask
	@abstract Event mask detailing the events being dispatched by a digitizer.
    @discussion It is possible for digitizer events to contain child digitizer events, effectively, behaving as collections.
    In the collection case, the child event mask field referrence by kIOHIDEventFieldDigitizerChildEventMask will detail the
    cumulative event state of the child digitizer events.
    <br>
    <b>Please Note:</b>
    If you append a child digitizer event to a parent digitizer event, appropriate state will be transfered on to the parent.
    @constant kIOHIDDigitizerEventRange Issued when the range state has changed.
    @constant kIOHIDDigitizerEventTouch Issued when the touch state has changed.
    @constant kIOHIDDigitizerEventPosition Issued when the position has changed.
    @constant kIOHIDDigitizerEventStop Issued when motion has achieved a state of calculated non-movement.
    @constant kIOHIDDigitizerEventPeak Issues when new maximum values have been detected.
    @constant kIOHIDDigitizerEventIdentity Issued when the identity has changed.
    @constant kIOHIDDigitizerEventAttribute Issued when an attribute has changed.
    @constant kIOHIDDigitizerEventUpSwipe Issued when an up swipe has been detected.
    @constant kIOHIDDigitizerEventDownSwipe Issued when an down swipe has been detected.
    @constant kIOHIDDigitizerEventLeftSwipe Issued when an left swipe has been detected.
    @constant kIOHIDDigitizerEventRightSwipe Issued when an right swipe has been detected.
    @constant kIOHIDDigitizerEventSwipeMask Mask used to gather swipe events.
*/
// NOTE: commented out because of compiler warning, not used right now so we'll skip it
/* enum { */
/*     kIOHIDDigitizerEventRange                               = 0x00000001, */
/*     kIOHIDDigitizerEventTouch                               = 0x00000002, */
/*     kIOHIDDigitizerEventPosition                            = 0x00000004, */
/*     kIOHIDDigitizerEventStop                                = 0x00000008, */
/*     kIOHIDDigitizerEventPeak                                = 0x00000010, */
/*     kIOHIDDigitizerEventIdentity                            = 0x00000020, */
/*     kIOHIDDigitizerEventAttribute                           = 0x00000040, */
/*     kIOHIDDigitizerEventCancel                              = 0x00000080, */
/*     kIOHIDDigitizerEventStart                               = 0x00000100, */
/*     kIOHIDDigitizerEventResting                             = 0x00000200, */
/*     kIOHIDDigitizerEventSwipeUp                             = 0x01000000, */
/*     kIOHIDDigitizerEventSwipeDown                           = 0x02000000, */
/*     kIOHIDDigitizerEventSwipeLeft                           = 0x04000000, */
/*     kIOHIDDigitizerEventSwipeRight                          = 0x08000000, */
/*     kIOHIDDigitizerEventSwipeMask                           = 0xFF000000, */
/* }; */
/* typedef uint32_t IOHIDDigitizerEventMask; */

enum {
    kIOHIDEventOptionNone                                   = 0x00000000,
    kIOHIDEventOptionIsAbsolute                             = 0x00000001,
    kIOHIDEventOptionIsCollection                           = 0x00000002,
    kIOHIDEventOptionPixelUnits                             = 0x00000004
};
typedef uint32_t IOHIDEventOptionBits;

enum {
    kIOHIDEventPhaseUndefined                               = 0x00,
    kIOHIDEventPhaseBegan                                   = 0x01,
    kIOHIDEventPhaseChanged                                 = 0x02,
    kIOHIDEventPhaseEnded                                   = 0x04,
    kIOHIDEventPhaseCancelled                               = 0x08,
    kIOHIDEventPhaseMayBegin                                = 0x80,
    kIOHIDEventEventPhaseMask                               = 0xFF,
    kIOHIDEventEventOptionPhaseShift                        = 24,
};
typedef uint16_t IOHIDEventPhaseBits;

/*!
 @typedef IOHIDSymbolicHotKey
 @abstract Enumerted values for sending symbolic hot key events.
 @constant kIOHIDSymbolicHotKeyDictionaryApp    This will get translated into a kCGSDictionaryAppHotKey by CG.
 @constant kIOHIDSymbolicHotKeyOptionIsCGSHotKey
                                                This is an option flag to denote that the SymbolicHotKey value is
                                                actually from the enumeration in CGSHotKeys.h.
 */
enum {
    kIOHIDSymbolicHotKeyUndefined,
    kIOHIDSymbolicHotKeyDictionaryApp,
};
typedef uint32_t IOHIDSymbolicHotKeyValue;


enum {
    kIOHIDEventSenderIDUndefined                            = 0x0000000000000000LL,
};
typedef uint64_t IOHIDEventSenderID; // must be the same size as that returned from IORegistryEntry::getRegistryEntryID

#ifndef KERNEL
/*!
	@typedef IOHIDFloat
*/
#ifdef __LP64__
typedef double IOHIDFloat;
#else
typedef float IOHIDFloat;
#endif
/*!
	@typedef IOHID3DPoint
*/
typedef struct _IOHID3DPoint {
    IOHIDFloat  x;
    IOHIDFloat  y;
    IOHIDFloat  z;
} IOHID3DPoint;
#endif

#endif /* _IOKIT_HID_IOHIDEVENTTYPES_H } */
