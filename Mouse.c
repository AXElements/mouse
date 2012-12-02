//
//  Mouse.c
//  MRMouse
//
//  Created by Mark Rada on 12-03-17.
//  Copyright (c) 2012 Mark Rada. All rights reserved.
//

#include <ApplicationServices/ApplicationServices.h>
#include "Mouse.h"

static const double FPS     = 120.0;
static const double QUANTUM = 1 / FPS;
static const double DEFAULT_DURATION = 0.2; // seconds

#define NEW_EVENT(type,point,button) CGEventCreateMouseEvent(nil,type,point,button)
#define POST(event) CGEventPost(kCGHIDEventTap, event)
#define CHANGE(event,type) CGEventSetType(event, type)

#define CLOSE_ENOUGH(a,b) ((pow(a.x-b.x,2)+pow(a.y-b.y,2)) <= 1.0)
#define NOW (CFDateCreate(nil,CFAbsoluteTimeGetCurrent()))

#define RELEASE(x) CFRelease(x)

static
void
mouse_sleep(size_t quanta)
{
  sleep(quanta * QUANTUM);
}

// Executes a linear mouse movement animation. It can be a simple cursor
// move or a drag depending on what is passed to `type`.
static
void

mouse_animate(
	      CGEventType type,
	      CGMouseButton button,
	      CGPoint start_point,
	      CGPoint end_point,
	      double duration
	      )
{
  CFDateRef current_time = NULL;
  CGEventRef event = NULL;
  CGPoint current_point = start_point;
  double     xstep = (end_point.x - start_point.x) / (duration * FPS);
  double     ystep = (end_point.y - start_point.y) / (duration * FPS);
  CFDateRef  start = NOW;

  double remaining = 0.0;

  while (!CLOSE_ENOUGH(current_point, end_point)) {
    remaining  = end_point.x - current_point.x;
    current_point.x += abs(xstep) > abs(remaining) ? remaining : xstep;

    remaining  = end_point.y - current_point.y;
    current_point.y += abs(ystep) > abs(remaining) ? remaining : ystep;

    event = NEW_EVENT(type, current_point, button);
    POST(event);
    RELEASE(event);

    mouse_sleep(1);
    current_time = NOW;
    if (CFDateGetTimeIntervalSinceDate(NOW, start) > 5.0)
      break;
    RELEASE(current_time);
    current_time = NULL;

    current_point = mouse_current_position();
  }

  RELEASE(start);
  if (current_time)
    RELEASE(current_time);
}


CGPoint
mouse_current_position()
{
  CGEventRef event = CGEventCreate(nil);
  CGPoint point = CGEventGetLocation(event);
  RELEASE(event);
  return point;
}

void
mouse_move_to(CGPoint point)
{
  mouse_move_to2(point, DEFAULT_DURATION);
}

void
mouse_move_to2(CGPoint point, double duration)
{
  mouse_animate(
		kCGEventMouseMoved,
		kCGMouseButtonLeft,
		mouse_current_position(),
		point,
		duration
		);
}


void
mouse_drag_to(CGPoint point)
{
  mouse_drag_to2(point, DEFAULT_DURATION);
}

void
mouse_drag_to2(CGPoint point, double duration)
{
  CGEventRef event = NEW_EVENT(
			     kCGEventLeftMouseDown,
			     mouse_current_position(),
			     kCGMouseButtonLeft
			     );
  POST(event);
  RELEASE(event);

  mouse_animate(
		kCGEventLeftMouseDragged,
		kCGMouseButtonLeft,
		mouse_current_position(),
		point,
		duration
		);

  event = NEW_EVENT(
		    kCGEventLeftMouseUp,
		    mouse_current_position(),
		    kCGMouseButtonLeft
		    );
  POST(event);
  RELEASE(event);
}


void
mouse_scroll(size_t amount)
{
  mouse_scroll2(amount, kMouseScrollByLine);
}

void
mouse_scroll2(size_t amount, enum MouseMovementUnit units)
{
  mouse_scroll3(amount, units, DEFAULT_DURATION);
}

void
mouse_scroll3(size_t amount, enum MouseMovementUnit units, double duration)
{
  CGEventRef event = NULL;
  size_t     steps = round(FPS * duration);
  double   current = 0.0;
  double      done = 0;
  size_t    scroll = 0;

  for (size_t step = 0; step < steps; step++) {
    done   = (double)(step+1) / (double)steps;
    scroll = lround((done - current) * amount);
    event  = CGEventCreateScrollWheelEvent(nil, units, 1, scroll);
    POST(event);
    RELEASE(event);
    mouse_sleep(1);
    current += (double)scroll / (double)amount;
  }
}


void
mouse_click_down()
{
  mouse_click_down2(mouse_current_position());
}

void
mouse_click_down2(CGPoint point)
{
  // TODO: replace constant 12 with something more abstract
  mouse_click_down3(point, 12);
}

void
mouse_click_down3(CGPoint point, size_t sleep_quanta)
{
  CGEventRef event = NEW_EVENT(kCGEventLeftMouseDown, point, kCGMouseButtonLeft);
  POST(event);
  RELEASE(event);
  mouse_sleep(sleep_quanta);
}

void
mouse_click_up()
{
  mouse_click_up2(mouse_current_position());
}

void
mouse_click_up2(CGPoint point)
{
  CGEventRef event = NEW_EVENT(kCGEventLeftMouseUp, point, kCGMouseButtonLeft);
  POST(event);
  RELEASE(event);
}

void
mouse_click()
{
  mouse_click2(mouse_current_position());
}

void
mouse_click2(CGPoint point)
{
  mouse_click_down2(point);
  mouse_click_up2(point);
}


void
mouse_secondary_click()
{
  mouse_secondary_click2(mouse_current_position());
}

void
mouse_secondary_click2(CGPoint point)
{
  // TODO: replace constant 12 with something more abstract
  mouse_secondary_click3(point, 12);
}

void
mouse_secondary_click3(CGPoint point, size_t sleep_quanta)
{
  CGEventRef event = NEW_EVENT(
			       kCGEventRightMouseDown,
			       point,
			       kCGMouseButtonRight
			       );
  POST(event);
  mouse_sleep(sleep_quanta);

  CHANGE(event, kCGEventRightMouseUp);
  POST(event);

  RELEASE(event);
}


void
mouse_arbitrary_click(CGEventMouseSubtype button)
{
  mouse_arbitrary_click2(button, mouse_current_position());
}

void
mouse_arbitrary_click2(CGEventMouseSubtype button, CGPoint point)
{
  mouse_arbitrary_click3(button, point, 12);
}

void
mouse_arbitrary_click3(CGEventMouseSubtype button, CGPoint point, size_t sleep_quanta)
{
  CGEventRef event = NEW_EVENT(
			       kCGEventOtherMouseDown,
			       point,
			       button
			       );
  POST(event);
  mouse_sleep(sleep_quanta);
  CHANGE(event, kCGEventOtherMouseUp);
  POST(event);
  RELEASE(event);
}

void
mouse_middle_click()
{
  mouse_middle_click2(mouse_current_position());
}

void
mouse_middle_click2(CGPoint point)
{
  mouse_arbitrary_click2(kCGMouseButtonCenter, point);
}

void
mouse_multi_click(size_t num_clicks)
{
  mouse_multi_click2(num_clicks, mouse_current_position());
}

void
mouse_multi_click2(size_t num_clicks, CGPoint point)
{
  CGEventRef event = NEW_EVENT(
			       kCGEventLeftMouseDown,
			       point,
			       kCGMouseButtonLeft
			       );
  CGEventSetIntegerValueField(event, kCGMouseEventClickState, num_clicks);
  CHANGE(event, kCGEventLeftMouseDown);
  POST(event);
  CHANGE(event, kCGEventLeftMouseUp);
  POST(event);
  RELEASE(event);
}

void
mouse_double_click()
{
  mouse_double_click2(mouse_current_position());
}

void
mouse_double_click2(CGPoint point)
{
  // some apps still expect to receive the single click event first
  // and then the double click event
  mouse_multi_click2(1, point);
  mouse_multi_click2(2, point);
}

void
mouse_triple_click()
{
  mouse_triple_click2(mouse_current_position());
}

void
mouse_triple_click2(CGPoint point)
{
  // some apps still expect to receive the single click event first
  // and then the double and triple click events
  mouse_double_click2(point);
  mouse_multi_click2(3, point);
}
