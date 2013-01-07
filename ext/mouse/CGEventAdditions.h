/* @!group Additional CGEvent Definitions */

// This group of enumerations and typedefs were more or less copied from
// the AutomationKit framework that was once available from Panic Inc.
// on GitHub. It was made available under the same terms as the mouse
// gem with Panic Inc. substituted in place of Mark Rada.

#include "IOHIDEventTypes.h"


/* !!!
 * Additions to the CGEvent API.
 *
 * Reverse engineered by listening to all events from CoreGraphics.
 * Gesture types correlate to those defined in IOKit's IOHIDEvent.h (public open source).
 *
 * This API should be public, but Apple apparently doesn't want anyone else listening to
 * and generating touch events. That's not going to stop us, though. :)
 *
 * These should never change, as it would break binary compatibility with existing system apps.
 */


/*!
 * @enum CGEventType additions
 * @abstract Additional CGEvent types
 *
 * @constant kCGEventGesture                Gesture event
 */
enum {
  kCGEventGesture = 29,
};


/*!
 * @enum CGEventField additions
 * @abstract Additional CGEvent fields
 *
 * @constant kCGEventGestureType            Gesture type
 *
 * @constant kCGEventGestureRotationValue   Rotation value
 * @constant kCGEventGesturePinchValue      Pinch value
 *
 * @constant kCGEventGestureScrollValueX    Scroll x delta
 * @constant kCGEventGestureScrollValueX    Scroll y delta
 *
 * @constant kCGEventGestureSwipeMotion     Swipe motion
 * @constant kCGEventGestureSwipeProgress   Swipe progress
 * @constant kCGEventGestureSwipePositionX  Swipe x position
 * @constant kCGEventGestureSwipePositionY  Swipe y position
 */
enum {
  kCGEventGestureType           = 110,

  kCGEventGestureRotationValue  = 113,
  kCGEventGesturePinchValue     = 113,

  kCGEventGestureScrollValueX   = 113,
  kCGEventGestureScrollValueY   = 119,

  kCGEventGestureSwipeDirection = 117,
  kCGEventGestureSwipeMotion    = 123,
  kCGEventGestureSwipeProgress  = 124,
  kCGEventGestureSwipePositionX = 125,
  kCGEventGestureSwipePositionY = 126,

  kCGEventGesturePhase          = 132,
};


/*!
 * @enum CGGestureType
 * @abstract Gesture types
 *
 * @constant kCGGestureTypeNone              None (used for resting touches)
 *
 * @constant kCGGestureTypeRotation          Rotation
 * @constant kCGGestureTypeScroll            Scroll (two-fingers)
 * @constant kCGGestureTypeSwipe             Swipe (three-fingers)
 * @constant kCGGestureTypePinch             Pinch
 * @constant kCGGestureTypeSmartMagnify      Smart magnify
 *
 * @constant kCGGestureTypeDockSwipe         Swipes consumed by Dock (Mission Control)
 *
 * @constant kCGGestureTypeGestureStarted    Gesture started
 * @constant kCGGestureTypeGestureEnded      Gesture ended
 */
typedef uint16_t CGGestureType;
enum {
  // Null type is used for resting touches
  kCGGestureTypeNone           = kIOHIDEventTypeNULL,

  // Application-consumable gestures
  kCGGestureTypeRotation       = kIOHIDEventTypeRotation,
  kCGGestureTypeScroll         = kIOHIDEventTypeScroll,
  kCGGestureTypeSwipe          = kIOHIDEventTypeSwipe,
  kCGGestureTypePinch          = kIOHIDEventTypeZoom,
  kCGGestureTypeSmartMagnify   = kIOHIDEventTypeZoomToggle,

  // Consumed by Dock (Mission Control gestures).
  // These never make it to an app's event loop.
  // As such, these events aren't recordable.
  kCGGestureTypeDockSwipe      = kIOHIDEventTypeDockSwipe,

  // Gesture start/end types
  // IOHIDEvent strangely has no reference to these.
  kCGGestureTypeGestureStarted = 61,
  kCGGestureTypeGestureEnded   = 62,
};


/*!
 * @enum CGGesturePhase
 * @abstract Gesture phases
 *
 * @constant kCGGesturePhaseUndefined        Undefined
 * @constant kCGGesturePhaseBegan            Gesture began
 * @constant kCGGesturePhaseChanged          Gesture changed
 * @constant kCGGesturePhaseEnded            Gesture ended
 * @constant kCGGesturePhaseCancelled        Gesture cancelled
 */
typedef uint16_t CGGesturePhase;
enum {
  kCGGesturePhaseUndefined = kIOHIDEventPhaseUndefined,
  kCGGesturePhaseBegan     = kIOHIDEventPhaseBegan,
  kCGGesturePhaseChanged   = kIOHIDEventPhaseChanged,
  kCGGesturePhaseEnded     = kIOHIDEventPhaseEnded,
  kCGGesturePhaseCancelled = kIOHIDEventPhaseCancelled,
};


/*!
 * @enum CGGestureMotion
 * @abstract Gesture motions
 *
 * @constant kCGGestureMotionNone            None
 *
 * @constant kCGGestureMotionHorizontalX     Horizontal
 * @constant kCGGestureMotionVerticalY       Vertical
 *
 * @constant kCGGestureMotionPinch           Pinch
 * @constant kCGGestureMotionRotate          Rotation
 *
 * @constant kCGGestureMotionTap             Tap
 * @constant kCGGestureMotionDoubleTap       Double tap
 *
 * @constant kCGGestureMotionFromLeftEdge    From the left edge
 * @constant kCGGestureMotionOffLeftEdge     Off the left edge
 * @constant kCGGestureMotionFromRightEdge   From the right edge
 * @constant kCGGestureMotionOffRightEdge    Off the right edge
 * @constant kCGGestureMotionFromTopEdge     From the top edge
 * @constant kCGGestureMotionOffTopEdge      Off the top edge
 * @constant kCGGestureMotionFromBottomEdge  From the bottom edge
 * @constant kCGGestureMotionOffBottomEdge   Off the bottom edge
 */
typedef uint16_t CGGestureMotion;
enum {
  kCGGestureMotionNone           = kIOHIDGestureMotionNone,

  kCGGestureMotionHorizontalX    = kIOHIDGestureMotionHorizontalX,
  kCGGestureMotionVerticalY      = kIOHIDGestureMotionVerticalY,

  kCGGestureMotionPinch          = kIOHIDGestureMotionScale,
  kCGGestureMotionRotate         = kIOHIDGestureMotionRotate,

  kCGGestureMotionTap            = kIOHIDGestureMotionTap,
  kCGGestureMotionDoubleTap      = kIOHIDGestureMotionDoubleTap,

  kCGGestureMotionFromLeftEdge   = kIOHIDGestureMotionFromLeftEdge,
  kCGGestureMotionOffLeftEdge    = kIOHIDGestureMotionOffLeftEdge,
  kCGGestureMotionFromRightEdge  = kIOHIDGestureMotionFromRightEdge,
  kCGGestureMotionOffRightEdge   = kIOHIDGestureMotionOffRightEdge,
  kCGGestureMotionFromTopEdge    = kIOHIDGestureMotionFromTopEdge,
  kCGGestureMotionOffTopEdge     = kIOHIDGestureMotionOffTopEdge,
  kCGGestureMotionFromBottomEdge = kIOHIDGestureMotionFromBottomEdge,
  kCGGestureMotionOffBottomEdge  = kIOHIDGestureMotionOffBottomEdge,
};


/*!
 * @enum CGGestureSwipeDirection
 * @abstract Swipe directions
 *
 * @constant kCGGestureSwipeDirectionNone    None
 * @constant kCGGestureSwipeDirectionUp      Up
 * @constant kCGGestureSwipeDirectionDown    Down
 * @constant kCGGestureSwipeDirectionLeft    Left
 * @constant kCGGestureSwipeDirectionRight   Right
 */
typedef uint16_t CGGestureSwipeDirection;
enum {
  kCGGestureSwipeDirectionNone  = kIOHIDSwipeNone,
  kCGGestureSwipeDirectionUp    = kIOHIDSwipeUp,
  kCGGestureSwipeDirectionDown  = kIOHIDSwipeDown,
  kCGGestureSwipeDirectionLeft  = kIOHIDSwipeLeft,
  kCGGestureSwipeDirectionRight = kIOHIDSwipeRight,
};
