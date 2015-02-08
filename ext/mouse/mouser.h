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

CGPoint mouse_current_position(void);

void mouse_move_to(const CGPoint point);
void mouse_move_to2(const CGPoint point, const double duration);

void mouse_drag_to(const CGPoint point);
void mouse_drag_to2(const CGPoint point, const double duration);

void mouse_scroll(const int amount);
void mouse_scroll2(const int amount, const CGScrollEventUnit units);
void mouse_scroll3(const int amount, const CGScrollEventUnit units, const double duration);

void mouse_horizontal_scroll(const int amount);
void mouse_horizontal_scroll2(const int amount, const CGScrollEventUnit units);
void mouse_horizontal_scroll3(const int amount, const CGScrollEventUnit units, const double duration);

void mouse_click_down(void);
void mouse_click_down2(const CGPoint point);
void mouse_click_down3(const CGPoint point, const uint_t sleep_quanta);

void mouse_click_up(void);
void mouse_click_up2(const CGPoint point);

void mouse_click(void);
void mouse_click2(const CGPoint point);

void mouse_secondary_click_down(void);
void mouse_secondary_click_down2(const CGPoint point);
void mouse_secondary_click_down3(const CGPoint point, const uint_t sleep_quanta);

void mouse_secondary_click_up(void);
void mouse_secondary_click_up2(const CGPoint point);

void mouse_secondary_click(void);
void mouse_secondary_click2(const CGPoint point);
void mouse_secondary_click3(const CGPoint point, const uint_t sleep_quanta);

void mouse_arbitrary_click_down(const CGEventMouseSubtype button);
void mouse_arbitrary_click_down2(const CGEventMouseSubtype button, const CGPoint point);
void mouse_arbitrary_click_down3(const CGEventMouseSubtype button, const CGPoint point, const uint_t sleep_quanta);

void mouse_arbitrary_click_up(const CGEventMouseSubtype button);
void mouse_arbitrary_click_up2(const CGEventMouseSubtype button, const CGPoint point);

void mouse_arbitrary_click(const CGEventMouseSubtype button);
void mouse_arbitrary_click2(const CGEventMouseSubtype button, const CGPoint point);
void mouse_arbitrary_click3(const CGEventMouseSubtype button, const CGPoint point, const uint_t sleep_quanta);

void mouse_middle_click(void);
void mouse_middle_click2(const CGPoint point);

void mouse_multi_click(const size_t num_clicks);
void mouse_multi_click2(const size_t num_clicks, const CGPoint point);

void mouse_double_click(void);
void mouse_double_click2(const CGPoint point);

void mouse_triple_click(void);
void mouse_triple_click2(const CGPoint point);

void mouse_smart_magnify(void);
void mouse_smart_magnify2(const CGPoint point);

void mouse_swipe(const CGSwipeDirection direction);
void mouse_swipe2(const CGSwipeDirection direction, const CGPoint point);

void mouse_pinch(const CGPinchDirection direction);
void mouse_pinch2(const CGPinchDirection direction, const double magnification);
void mouse_pinch3(const CGPinchDirection direction, const double magnification, const CGPoint point);
void mouse_pinch4(const CGPinchDirection direction, const double magnification, const CGPoint point, const double duration);

void mouse_rotate(const CGRotateDirection direction, const double angle);
void mouse_rotate2(const CGRotateDirection direction, const double angle, const CGPoint point);
void mouse_rotate3(const CGRotateDirection direction, const double angle, const CGPoint point, const double duration);
