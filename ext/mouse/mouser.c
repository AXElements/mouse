//
//  Mouser.c
//  MRMouse
//
//  Created by Mark Rada on 12-03-17.
//  Copyright (c) 2012 Mark Rada. All rights reserved.
//

#include "mouser.h"

static const double FPS     = 240;
static const double QUANTUM = 1000000 / 240; // should be FPS, but GCC sucks
static const double DEFAULT_DURATION      = 0.2; // seconds
static const double DEFAULT_MAGNIFICATION = 1.0; // factor

#define NEW_GESTURE(name) CGEventRef name = CGEventCreate(nil);	CHANGE(name, kCGEventGesture);
#define NEW_EVENT(type,point,button) CGEventCreateMouseEvent(nil,type,point,button)
#define POST(event) CGEventPost(kCGHIDEventTap, event)
#define CHANGE(event,type) CGEventSetType(event, type)

#define CLOSE_ENOUGH(a, b) ((fabs(a.x - b.x) < 1.0) && (fabs(a.y - b.y) < 1.0))
#define NOW (CFDateCreate(nil, CFAbsoluteTimeGetCurrent()))

#define POSTRELEASE(x) {                        \
        CGEventRef const _event = x;            \
        POST(_event);				\
        CFRelease(_event);                      \
    }


static
void
mouse_sleep(const uint_t quanta)
{
    usleep(quanta * (uint_t)QUANTUM);
}

CGPoint
mouse_current_position()
{
    CGEventRef const event = CGEventCreate(nil);
    const CGPoint point = CGEventGetLocation(event);
    CFRelease(event);
    return point;
}

// Executes a linear mouse movement animation. It can be a simple cursor
// move or a drag depending on what is passed to `type`.
static
void
mouse_animate(const CGEventType type,
	      const CGMouseButton button,
	      const CGPoint start_point,
	      const CGPoint end_point,
	      const double duration)
{
    CGPoint current_point  = start_point;
    const double     xstep = (end_point.x - start_point.x) / (duration * FPS);
    const double     ystep = (end_point.y - start_point.y) / (duration * FPS);
    CFDateRef  const start = NOW;
    double       remaining = 0.0;
    CFDateRef current_time = NULL;

    while (!CLOSE_ENOUGH(current_point, end_point)) {
        remaining  = end_point.x - current_point.x;
        current_point.x += fabs(xstep) > fabs(remaining) ? remaining : xstep;

        remaining  = end_point.y - current_point.y;
        current_point.y += fabs(ystep) > fabs(remaining) ? remaining : ystep;

        POSTRELEASE(NEW_EVENT(type, current_point, button));

        mouse_sleep(1);
        current_time = NOW;

        // this is a safety
        const double boundary = duration + 1;
        if (CFDateGetTimeIntervalSinceDate(current_time, start) > boundary)
            break;

        CFRelease(current_time);
        current_time = NULL;

        current_point = mouse_current_position();
    }

    CFRelease(start);
    if (current_time)
        CFRelease(current_time);
}


void
mouse_move_to2(const CGPoint point, const double duration)
{
    mouse_animate(kCGEventMouseMoved,
                  kCGMouseButtonLeft,
                  mouse_current_position(),
                  point,
                  duration);
}

void
mouse_move_to(const CGPoint point)
{
    mouse_move_to2(point, DEFAULT_DURATION);
}


void
mouse_drag_to2(const CGPoint point, const double duration)
{
    POSTRELEASE(NEW_EVENT(kCGEventLeftMouseDown,
                          mouse_current_position(),
                          kCGMouseButtonLeft));

    mouse_animate(kCGEventLeftMouseDragged,
                  kCGMouseButtonLeft,
                  mouse_current_position(),
                  point,
                  duration);

    POSTRELEASE(NEW_EVENT(kCGEventLeftMouseUp,
                          mouse_current_position(),
                          kCGMouseButtonLeft));
}

void
mouse_drag_to(const CGPoint point)
{
    mouse_drag_to2(point, DEFAULT_DURATION);
}


#define SCROLL(vval, hval) {                                  \
        const size_t steps = round(FPS * duration);           \
        double current = 0.0;                                 \
                                                              \
        for (size_t step = 0; step < steps; step++) {                  \
            const double   done = (double)(step+1) / (double)steps;    \
            const double scroll = round((done - current) * amount);    \
            POSTRELEASE(CGEventCreateScrollWheelEvent(nil, units, 2, vval, hval)); \
            mouse_sleep(2);                                             \
            current += scroll / (double)amount;                         \
        }                                                              \
    }

void
mouse_scroll3(const int amount,
              const CGScrollEventUnit units,
              const double duration)
{
    SCROLL(scroll, 0);
}

void
mouse_scroll2(const int amount,
              const CGScrollEventUnit units)
{
    mouse_scroll3(amount, units, DEFAULT_DURATION);
}

void
mouse_scroll(const int amount)
{
    mouse_scroll2(amount, kCGScrollEventUnitLine);
}

void
mouse_horizontal_scroll3(const int amount,
                         const CGScrollEventUnit units,
                         const double duration)
{
    SCROLL(0, scroll);
}

void
mouse_horizontal_scroll2(const int amount,
                         const CGScrollEventUnit units)
{
    mouse_horizontal_scroll3(amount, units, DEFAULT_DURATION);
}

void
mouse_horizontal_scroll(const int amount)
{
    mouse_horizontal_scroll2(amount, kCGScrollEventUnitLine);
}

void
mouse_click_down3(const CGPoint point, const uint_t sleep_quanta)
{
    POSTRELEASE(NEW_EVENT(kCGEventLeftMouseDown, point, kCGMouseButtonLeft));
    mouse_sleep(sleep_quanta);
}

void
mouse_click_down2(const CGPoint point)
{
    mouse_click_down3(point, FPS / 10);
}

void
mouse_click_down()
{
    mouse_click_down2(mouse_current_position());
}


void
mouse_click_up2(const CGPoint point)
{
    POSTRELEASE(NEW_EVENT(kCGEventLeftMouseUp, point, kCGMouseButtonLeft));
}

void
mouse_click_up()
{
    mouse_click_up2(mouse_current_position());
}


void
mouse_click2(const CGPoint point)
{
    mouse_click_down2(point);
    mouse_click_up2(point);
}

void
mouse_click()
{
    mouse_click2(mouse_current_position());
}


void
mouse_secondary_click_down3(const CGPoint point, const uint_t sleep_quanta)
{
    CGEventRef const base_event = NEW_EVENT(kCGEventRightMouseDown,
                                            point,
                                            kCGMouseButtonRight);
    POSTRELEASE(base_event);
    mouse_sleep(sleep_quanta);
}

void
mouse_secondary_click_down2(const CGPoint point)
{
    mouse_secondary_click_down3(point, FPS / 10);
}

void
mouse_secondary_click_down()
{
    mouse_secondary_click_down2(mouse_current_position());
}


void
mouse_secondary_click_up2(const CGPoint point)
{
    CGEventRef const base_event = NEW_EVENT(kCGEventRightMouseUp,
                                            point,
                                            kCGMouseButtonRight);
    POSTRELEASE(base_event);
}

void
mouse_secondary_click_up()
{
    mouse_secondary_click_up2(mouse_current_position());
}


void
mouse_secondary_click3(const CGPoint point, const uint_t sleep_quanta)
{
    mouse_secondary_click_down3(point, sleep_quanta);
    mouse_secondary_click_up2(point);
}

void
mouse_secondary_click2(const CGPoint point)
{
    mouse_secondary_click_down2(point);
    mouse_secondary_click_up2(point);
}

void
mouse_secondary_click()
{
    mouse_secondary_click_down();
    mouse_secondary_click_up();
}


void
mouse_arbitrary_click_down3(const CGEventMouseSubtype button,
			    const CGPoint point,
			    const uint_t sleep_quanta)
{
    CGEventRef const base_event = NEW_EVENT(kCGEventOtherMouseDown,
                                            point,
                                            button);
    POSTRELEASE(base_event);
    mouse_sleep(sleep_quanta);
}

void
mouse_arbitrary_click_down2(const CGEventMouseSubtype button,
                            const CGPoint point)
{
    mouse_arbitrary_click_down3(button, point, FPS / 10);
}

void
mouse_arbitrary_click_down(const CGEventMouseSubtype button)
{
    mouse_arbitrary_click_down2(button, mouse_current_position());
}


void mouse_arbitrary_click_up2(const CGEventMouseSubtype button,
                               const CGPoint point)
{
    CGEventRef const base_event = NEW_EVENT(kCGEventOtherMouseUp,
                                            point,
                                            button);
    POSTRELEASE(base_event);
}

void mouse_arbitrary_click_up(const CGEventMouseSubtype button)
{
    mouse_arbitrary_click_up2(button, mouse_current_position());
}


void
mouse_arbitrary_click3(const CGEventMouseSubtype button,
                       const CGPoint point,
                       const uint_t sleep_quanta)
{
    mouse_arbitrary_click_down3(button, point, sleep_quanta);
    mouse_arbitrary_click_up2(button, point);
}

void
mouse_arbitrary_click2(const CGEventMouseSubtype button,
                       const CGPoint point)
{
    mouse_arbitrary_click_down2(button, point);
    mouse_arbitrary_click_up2(button, point);
}

void
mouse_arbitrary_click(const CGEventMouseSubtype button)
{
    mouse_arbitrary_click_down(button);
    mouse_arbitrary_click_up(button);
}


void
mouse_middle_click2(const CGPoint point)
{
    mouse_arbitrary_click2(kCGMouseButtonCenter, point);
}

void
mouse_middle_click()
{
    mouse_middle_click2(mouse_current_position());
}


void
mouse_multi_click2(const size_t num_clicks, const CGPoint point)
{
    CGEventRef const base_event = NEW_EVENT(kCGEventLeftMouseDown,
                                            point,
                                            kCGMouseButtonLeft);
    CGEventSetIntegerValueField(base_event,
                                kCGMouseEventClickState,
                                num_clicks);

    CHANGE(base_event, kCGEventLeftMouseDown);
    POST(base_event);

    CHANGE(base_event, kCGEventLeftMouseUp);
    POSTRELEASE(base_event);
}

void
mouse_multi_click(const size_t num_clicks)
{
    mouse_multi_click2(num_clicks, mouse_current_position());
}


void
mouse_double_click2(const CGPoint point)
{
    // some apps still expect to receive the single click event first
    // and then the double click event
    mouse_multi_click2(1, point);
    mouse_multi_click2(2, point);
}

void
mouse_double_click()
{
    mouse_double_click2(mouse_current_position());
}


void
mouse_triple_click2(const CGPoint point)
{
    // some apps still expect to receive the single click event first
    // and then the double and triple click events
    mouse_double_click2(point);
    mouse_multi_click2(3, point);
}

void
mouse_triple_click()
{
    mouse_triple_click2(mouse_current_position());
}


static
void
mouse_gesture(const CGPoint point,
              const uint_t sleep_quanta,
              void (^ const gesture_block)(void))
{
    POSTRELEASE(NEW_EVENT(kCGEventMouseMoved, point, kCGMouseButtonLeft));

    NEW_GESTURE(gesture);
    CGEventSetIntegerValueField(gesture,
                                kCGEventGestureType,
                                kCGGestureTypeGestureStarted);
    POST(gesture);

    gesture_block();

    CGEventSetIntegerValueField(gesture,
                                kCGEventGestureType,
                                kCGGestureTypeGestureEnded);
    POSTRELEASE(gesture);

    mouse_sleep(sleep_quanta);
}

void
mouse_smart_magnify2(const CGPoint point)
{
    mouse_gesture(point, (FPS / 2), ^(void)
    {
        NEW_GESTURE(event);
        CGEventSetIntegerValueField(event,
                                    kCGEventGestureType,
                                    kCGGestureTypeSmartMagnify);
        POSTRELEASE(event);
    });
}

void
mouse_smart_magnify()
{
    mouse_smart_magnify2(mouse_current_position());
}

void
mouse_swipe2(const CGSwipeDirection direction, const CGPoint point)
{
    uint16_t            axis = 0;
    CGFloat         distance = 1.0;
    CGGestureMotion   motion = kCGGestureMotionNone;

    switch (direction) {
    case kCGSwipeDirectionUp:
        axis     = kCGEventGestureSwipePositionY;
        distance = -(distance);
        motion   = kCGGestureMotionVertical;
        break;
    case kCGSwipeDirectionDown:
        axis     = kCGEventGestureSwipePositionY;
        motion   = kCGGestureMotionVertical;
        break;
    case kCGSwipeDirectionLeft:
        axis     = kCGEventGestureSwipePositionX;
        motion   = kCGGestureMotionHorizontal;
        break;
    case kCGSwipeDirectionRight:
        axis     = kCGEventGestureSwipePositionX;
        distance = -(distance);
        motion   = kCGGestureMotionHorizontal;
        break;
    default:
        return;
    }

    mouse_gesture(point, (FPS / 10), ^(void)
    {
        NEW_GESTURE(swipe);

        CGEventSetIntegerValueField(swipe, kCGEventGestureType,           kCGGestureTypeSwipe);
        CGEventSetIntegerValueField(swipe, kCGEventGestureSwipeMotion,    motion);
        CGEventSetIntegerValueField(swipe, kCGEventGestureSwipeDirection, direction);
        CGEventSetIntegerValueField(swipe, kCGEventGesturePhase,          kCGGesturePhaseBegan);
        CGEventSetDoubleValueField( swipe, kCGEventGestureSwipeProgress,  distance);
        CGEventSetDoubleValueField( swipe, axis,                          distance);

        // TODO: animation steps don't seem to do anything...
        // kCGGesturePhaseChanged
        // kCGGesturePhaseEnded

        POSTRELEASE(swipe);
    });
}

void
mouse_swipe(const CGSwipeDirection direction)
{
    mouse_swipe2(direction, mouse_current_position());
}

void
mouse_pinch4(const CGPinchDirection direction,
	     const double magnification,
 	     const CGPoint point,
	     const double duration)
{
    double _magnification = magnification;

    switch (direction) {
    case kCGPinchExpand:
        break;
    case kCGPinchContract:
        _magnification = -(magnification);
        break;
    default:
        return;
    }

    mouse_gesture(point, FPS / 10, ^(void)
    {
        NEW_GESTURE(pinch);
        CGEventSetIntegerValueField(pinch,
                                    kCGEventGestureType,
                                    kCGGestureTypePinch);

        const size_t steps       = FPS / duration;
        const double step_size   = _magnification / steps;
        const double step_period = (duration / steps) * 1000000;

        CGEventSetDoubleValueField(pinch, kCGEventGesturePinchValue, step_size);

        for (size_t i = 0; i < steps; i++) {
            POST(pinch);
            usleep(step_period);
        }

        CFRelease(pinch);
    });
}

void
mouse_pinch3(const CGPinchDirection direction,
             const double magnification,
             const CGPoint point)
{
    mouse_pinch4(direction, magnification, point, DEFAULT_DURATION);
}

void
mouse_pinch2(const CGPinchDirection direction,
             const double magnification)
{
    mouse_pinch3(direction, magnification, mouse_current_position());
}

void
mouse_pinch(const CGPinchDirection direction)
{
    mouse_pinch2(direction, DEFAULT_MAGNIFICATION);
}

void
mouse_rotate3(const CGRotateDirection direction,
	      const double angle,
	      const CGPoint point,
	      const double duration)
{
    double _angle = angle;

    switch (direction) {
    case kCGRotateClockwise:
        _angle = -(angle);
        break;
    case kCGRotateCounterClockwise:
        break;
    default:
        return;
    }

    mouse_gesture(point, (FPS / 10), ^(void)
    {
        NEW_GESTURE(rotation);
        CGEventSetIntegerValueField(rotation,
                                    kCGEventGestureType,
                                    kCGGestureTypeRotation);

        const size_t steps       = FPS / duration;
        const double step_size   = _angle / steps;
        const double step_period = (duration / steps) * 1000000;

        CGEventSetDoubleValueField(rotation,
                                   kCGEventGestureRotationValue,
                                   step_size);

        for (size_t i = 0; i < steps; i++) {
            POST(rotation);
            usleep(step_period);
        }

        CFRelease(rotation);
    });
}

void
mouse_rotate2(const CGRotateDirection direction,
              const double angle,
              const CGPoint point)
{
    mouse_rotate3(direction, angle, point, DEFAULT_DURATION);
}

void
mouse_rotate(const CGRotateDirection direction, const double angle)
{
    mouse_rotate2(direction, angle, mouse_current_position());
}
