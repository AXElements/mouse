//
//  Mouser.h
//  MRMouse
//
//  Created by Mark Rada on 12-03-17.
//  Copyright (c) 2012 Mark Rada. All rights reserved.
//

#include <ApplicationServices/ApplicationServices.h>
#include "CGEventAdditions.h"

typedef unsigned int uint_t;

CGPoint mouse_current_position();

void mouse_move_to(CGPoint point);
void mouse_move_to2(CGPoint point, double duration);

void mouse_drag_to(CGPoint point);
void mouse_drag_to2(CGPoint point, double duration);

void mouse_scroll(int amount);
void mouse_scroll2(int amount, CGScrollEventUnit units);
void mouse_scroll3(int amount, CGScrollEventUnit units, double duration);

void mouse_horizontal_scroll(size_t amount);
void mouse_horizontal_scroll2(size_t amount, CGScrollEventUnit units);
void mouse_horizontal_scroll3(size_t amount, CGScrollEventUnit units, double duration);

void mouse_click_down();
void mouse_click_down2(CGPoint point);
void mouse_click_down3(CGPoint point, uint_t sleep_quanta);

void mouse_click_up();
void mouse_click_up2(CGPoint point);

void mouse_click();
void mouse_click2(CGPoint point);

void mouse_secondary_click_down();
void mouse_secondary_click_down2(CGPoint point);
void mouse_secondary_click_down3(CGPoint point, uint_t sleep_quanta);

void mouse_secondary_click_up();
void mouse_secondary_click_up2(CGPoint point);

void mouse_secondary_click();
void mouse_secondary_click2(CGPoint point);
void mouse_secondary_click3(CGPoint point, uint_t sleep_quanta);

void mouse_arbitrary_click_down(CGEventMouseSubtype button);
void mouse_arbitrary_click_down2(CGEventMouseSubtype button, CGPoint point);
void mouse_arbitrary_click_down3(CGEventMouseSubtype button, CGPoint point, uint_t sleep_quanta);

void mouse_arbitrary_click_up(CGEventMouseSubtype button);
void mouse_arbitrary_click_up2(CGEventMouseSubtype button, CGPoint point);

void mouse_arbitrary_click(CGEventMouseSubtype button);
void mouse_arbitrary_click2(CGEventMouseSubtype button, CGPoint point);
void mouse_arbitrary_click3(CGEventMouseSubtype button, CGPoint point, uint_t sleep_quanta);

void mouse_middle_click();
void mouse_middle_click2(CGPoint point);

void mouse_multi_click(size_t num_clicks);
void mouse_multi_click2(size_t num_clicks, CGPoint point);

void mouse_double_click();
void mouse_double_click2(CGPoint point);

void mouse_triple_click();
void mouse_triple_click2(CGPoint point);

void mouse_smart_magnify();
void mouse_smart_magnify2(CGPoint point);
void mouse_smart_magnify3(CGPoint point, uint_t sleep_quanta);

void mouse_swipe(CGSwipeDirection direction);
void mouse_swipe2(CGSwipeDirection direction, CGPoint point);
void mouse_swipe3(CGSwipeDirection direction, CGPoint point, double duration);

void mouse_pinch(CGPinchDirection direction);
void mouse_pinch2(CGPinchDirection direction, double magnification);
void mouse_pinch3(CGPinchDirection direction, double magnification, CGPoint point);
void mouse_pinch4(CGPinchDirection direction, double magnification, CGPoint point, double duration);

void mouse_rotate(CGRotateDirection direction, double angle);
void mouse_rotate2(CGRotateDirection direction, double angle, CGPoint point);
void mouse_rotate3(CGRotateDirection direction, double angle, CGPoint point, double duration);
