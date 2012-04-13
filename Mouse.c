//
//  Mouse.c
//  MRMouse
//
//  Created by Mark Rada on 12-03-17.
//  Copyright (c) 2012 Mark Rada. All rights reserved.
//

#import <ApplicationServices/ApplicationServices.h>
#import "Mouse.h"

static const double FPS     = 120.0;
static const double QUANTUM = 1 / FPS;

#define EVENT(type,point,button) CGEventCreateMouseEvent(nil, type, point, button)
#define POST(event) CGEventPost(kCGHIDEventTap, event)
#define CHANGE(event,type) CGEventSetType(event, type)
#define CLOSE_ENOUGH(a,b) (sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)) <= 1.0)
#define NOW() (CFDateCreate(nil,CFAbsoluteTimeGetCurrent()))

/* static void */
/* mouse_animate(CGPoint end_point, double duration, int button, int type) { */
/*   CGPoint current_point = mouse_position(); */
/*   double xstep          = (end_point.x - current_point.x) / (FPS * duration); */
/*   double ystep          = (end_point.y - current_point.y) / (FPS * duration); */
/*   CFDateRef start       = NOW(); */

/*   double remaining; */
/*   while (!CLOSE_ENOUGH(current_point, end_point)) { */
/*     remaining  = end_point.x - current_point.x; */
/*     current_point.x += abs(xstep) > abs(remaining) ? remaining : xstep; */

/*     remaining  = end_point.y - current_point.y; */
/*     current_point.y += abs(ystep) > abs(remaining) ? remaining : ystep; */

/*     POST(EVENT(type, current_point, button)); */

/*     usleep(QUANTUM); */
/*     if (CFDateGetTimeIntervalSinceDate(start, NOW()) > 5.0) */
/*       break; */

/*     current_point = mouse_position(); */
/*   } */
/* } */

CGPoint
mouse_position() {
  return CGEventGetLocation(CGEventCreate(nil));
}

bool
mouse_move(CGPoint point) {
  return mouse_move2(point, 0.2);
}

bool
mouse_move2(CGPoint point, double timeout) {
  CGEventRef event = EVENT(kCGEventMouseMoved, point, kCGMouseButtonLeft);
  POST(event);
  return true;
}
