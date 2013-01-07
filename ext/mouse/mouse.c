#include "mouser.h"
#include "ruby.h"

static VALUE rb_mMouse;
static VALUE rb_cCGPoint;
static ID sel_x;
static ID sel_y;
static ID sel_to_point;
static ID sel_new;

static VALUE sym_pixel;
static VALUE sym_line;
static VALUE sym_up;
static VALUE sym_down;
static VALUE sym_left;
static VALUE sym_right;
static VALUE sym_zoom;
static VALUE sym_expand;
static VALUE sym_contract;

#define CURRENT_POSITION rb_mouse_wrap_point(mouse_current_position())

static
VALUE
rb_mouse_wrap_point(CGPoint point)
{
  // TODO: Data_Wrap_Struct instead
#if NOT_MACRUBY
  return rb_struct_new(rb_cCGPoint, DBL2NUM(point.x), DBL2NUM(point.y));
#else
  return rb_funcall(rb_cCGPoint, sel_new, 2, DBL2NUM(point.x), DBL2NUM(point.y));
#endif
}

static
CGPoint
rb_mouse_unwrap_point(VALUE point)
{
  point = rb_funcall(point, sel_to_point, 0);

#if NOT_MACRUBY
  double x = NUM2DBL(rb_struct_getmember(point, sel_x));
  double y = NUM2DBL(rb_struct_getmember(point, sel_y));
  return CGPointMake(x, y);

#else
  CGPoint* ptr;
  Data_Get_Struct(point, CGPoint, ptr);
  return *ptr;

#endif
}

/*
 * Returns the current co-ordinates of the mouse cursor
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_current_position(VALUE self)
{
  return CURRENT_POSITION;
}

/*
 * Move the mouse cursor to the given co-ordinates
 *
 * @param point [CGPoint,Array(Number,Number),#to_point]
 * @param duration [Number] animation time, in seconds (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_move_to(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      rb_raise(rb_eArgError, "move_to requires at least a one arg");
      break;
    case 1:
      mouse_move_to(rb_mouse_unwrap_point(argv[0]));
      break;
    case 2:
    default:
      mouse_move_to2(rb_mouse_unwrap_point(argv[0]), NUM2DBL(argv[1]));
    }

  return CURRENT_POSITION;
}

/*
 * Drag the mouse cursor to the given co-ordinates
 *
 * @param (see #move_to)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_drag_to(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      rb_raise(rb_eArgError, "drag_to requires at least a one arg");
      break;
    case 1:
      mouse_drag_to(rb_mouse_unwrap_point(argv[0]));
      break;
    case 2:
    default:
      mouse_drag_to2(rb_mouse_unwrap_point(argv[0]), NUM2DBL(argv[1]));
    }

  return CURRENT_POSITION;
}

/*
 * @note Scrolling by `:pixel` may not actually be by real pixels, but instead
 *       correspond to Cocoa co-ords (I don't have a retina display, so I haven't
 *       checked it out yet).
 *
 * Generate `amount` scroll events at the current cursor position
 *
 * Returns number of lines scrolled. A positive `amount` will scroll up
 * and a negative `amount` will scroll down.
 *
 * @param amount [Number]
 * @param units [Symbol] `:pixel` or `:line` (_default_: `:line` ) (__optional__)
 * @return [Number]
 */
static
VALUE
rb_mouse_scroll(int argc, VALUE *argv, VALUE self)
{
  if (argc == 0 || argc > 3)
    rb_raise(rb_eArgError, "scroll requires 1..3 arguments, you gave %d", argc);

  int amt = NUM2INT(argv[0]);

  if (argc == 1) {
    mouse_scroll(amt);
    return argv[0];
  }

  VALUE units = argv[1];

  if (argc == 2) {
    if (units == sym_pixel)
      mouse_scroll2(amt, kCGScrollEventUnitPixel);
    else if (units == sym_line)
      mouse_scroll2(amt, kCGScrollEventUnitLine);
    else
      rb_raise(rb_eArgError, "unknown units `%s'", rb_id2name(units));
  }

  if (argc == 3) {
    double duration = NUM2DBL(argv[2]);

    if (units == sym_pixel)
      mouse_scroll3(amt, kCGScrollEventUnitPixel, duration);
    else if (units == sym_line)
      mouse_scroll3(amt, kCGScrollEventUnitLine, duration);
    else
      rb_raise(rb_eArgError, "unknown units `%s'", rb_id2name(units));
  }

  return argv[0];
}

/*
 * Generate the down click part of a click event
 *
 * This might be useful in concert with {Mouse.click_up} if you want
 * to inject some behaviour between the down and up click events.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_click_down(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_click_down();
      break;
    case 1:
    default:
      mouse_click_down2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate the up click part of a click event
 *
 * This might be useful in concert with {Mouse.click_down} if you want
 * to inject some behaviour between the down and up click events.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_click_up(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_click_up();
      break;
    case 1:
    default:
      mouse_click_up(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate a regular click event (both up and down events)
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_click(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_click();
      break;
    case 1:
    default:
      mouse_click2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate the down click part of a secondary/right click event
 *
 * This might be useful in concert with {Mouse.secondary_click_up} if
 * you want to inject some behaviour between the down and up click
 * events.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_secondary_click_down(int argc, VALUE* argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_secondary_click_down();
      break;
    case 1:
    default:
      mouse_secondary_click_down2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate the up click part of a secondary/right click event
 *
 * This might be useful in concert with {Mouse.secondary_click_down} if
 * you want to inject some behaviour between the down and up click events.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_secondary_click_up(int argc, VALUE* argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_secondary_click_up();
      break;
    case 1:
    default:
      mouse_secondary_click_up2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate a secondary click (both down and up events)
 *
 * Secondary click is often referred to as "right click".
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_secondary_click(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_secondary_click();
      break;
    case 1:
    default:
      mouse_secondary_click2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate the down click part of an arbitrary click event
 *
 * This might be useful in concert with {Mouse.arbitrary_click_up} if
 * you want to inject some behaviour between the down and up click
 * events.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_arbitrary_click_down(int argc, VALUE* argv, VALUE self)
{
  if (argc == 0)
    rb_raise(rb_eArgError, "arbitrary_click_down requires at least one arg");

  uint_t button = NUM2INT(argv[0]);

  switch (argc)
    {
    case 1:
      mouse_arbitrary_click_down(button);
      break;
    case 2:
    default:
      mouse_arbitrary_click_down2(button, rb_mouse_unwrap_point(argv[1]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate the up click part of an arbitrary click event
 *
 * This might be useful in concert with {Mouse.arbitrary_click_down} if
 * you want to inject some behaviour between the down and up click events.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_arbitrary_click_up(int argc, VALUE* argv, VALUE self)
{
  if (argc == 0)
    rb_raise(rb_eArgError, "arbitrary_click_up requires at least one arg");

  uint_t button = NUM2INT(argv[0]);

  switch (argc)
    {
    case 1:
      mouse_arbitrary_click_up(button);
      break;
    case 2:
    default:
      mouse_arbitrary_click_up2(button, rb_mouse_unwrap_point(argv[1]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate a click using an arbitrary mouse button (down and up events)
 *
 * Numbers are used to map the mouse buttons. At the time of writing,
 * the documented values are:
 *
 *  - `kCGMouseButtonLeft   = 0`
 *  - `kCGMouseButtonRight  = 1`
 *  - `kCGMouseButtonCenter = 2`
 *
 * And the rest are not documented! Though they should be easy enough
 * to figure out. See the `CGMouseButton` enum in the reference
 * documentation for the most up to date list.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param button [Number,#to_i]
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_arbitrary_click(int argc, VALUE *argv, VALUE self)
{
  if (argc == 0) {
    rb_raise(rb_eArgError, "arbitrary_click requires at least one arg");
    return Qnil;
  }

  uint_t button = NUM2INT(argv[0]);

  switch (argc)
    {
    case 1:
      mouse_arbitrary_click(button);
      break;
    case 2:
    default:
      mouse_arbitrary_click2(button, rb_mouse_unwrap_point(argv[1]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate a click event for the middle mouse button (down and up events)
 *
 * It doesn't matter if you don't have a middle mouse button.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_middle_click(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_middle_click();
      break;
    case 1:
    default:
      mouse_middle_click(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Generate a multi-click event at the current mouse position
 *
 * Unlike {Mouse.double_click} and {Mouse.triple_click} this will generate
 * a single event with the given number of clicks.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param num_clicks [Number,#to_i]
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_multi_click(int argc, VALUE *argv, VALUE self)
{

  if (argc == 0) {
    rb_raise(rb_eArgError, "multi_click requires at least one arg");
    return Qnil;
  }

  // TODO: there has got to be a more idiomatic way to do this coercion
  size_t num_clicks = NUM2SIZET(argv[0]);

  switch (argc)
    {
    case 1:
      mouse_multi_click(num_clicks);
      break;
    case 2:
    default:
      mouse_multi_click2(num_clicks, rb_mouse_unwrap_point(argv[1]));
    }

  return CURRENT_POSITION;
}

/*
 * Perform a double click at the given mouse position
 *
 * Implemented by first generating a single click, and then a double click.,
 * Apps seem to respond more consistently to this behaviour since that is
 * how a human would have to generate a double click event.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_double_click(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_double_click();
      break;
    case 1:
    default:
      mouse_double_click2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Perform a triple click at the given mouse position
 *
 * Implemented by first generating a single click, then a double click,
 * and finally a triple click. Apps seem to respond more consistently to
 * this behaviour since that is how a human would have to generate a
 * triple click event.
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_triple_click(int argc, VALUE *argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_triple_click();
      break;
    case 1:
    default:
      mouse_triple_click2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Perform a smart magnify (double tap on trackpad)
 *
 * You can optionally specify the point on the screen where to perform
 * the smart magnification.
 *
 * @param point [CGPoint] (_default_: {#current_position}) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_smart_magnify(int argc, VALUE* argv, VALUE self)
{
  switch (argc)
    {
    case 0:
      mouse_smart_magnify();
      break;
    case 1:
    default:
      mouse_smart_magnify2(rb_mouse_unwrap_point(argv[0]));
    }

  return CURRENT_POSITION;
}

/*
 * Perform a pinch gesture in given `direction`
 *
 * You can optionally specify the `magnification` factor and/or
 * `duration` for the pinch event.
 *
 * @param direction [Symbol]
 * @param magnification [Float] (_default_: `2.0`) (__optional__)
 * @param duration [Float] (_default_: `1.0`) (__optional__)
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_pinch(int argc, VALUE* argv, VALUE self)
{
  if (!argc)
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 1+)", argc);

  VALUE             input_direction = argv[0];
  CGGesturePinchDirection direction = kCGDirectionNone;

  if (input_direction == sym_expand)
    direction = kCGDirectionExpand;
  else if (input_direction == sym_contract)
    direction = kCGDirectionContract;
  else
    rb_raise(
	     rb_eArgError,
	     "invalid pinch direction `%s'",
	     rb_id2name(SYM2ID(input_direction))
	     );

  if (argc == 1) {
    mouse_pinch(direction);
    return CURRENT_POSITION;
  }

  double magnification = NUM2DBL(argv[1]);
  if (argc == 2) {
    mouse_pinch2(direction, magnification);
    return CURRENT_POSITION;
  }

  double duration = NUM2DBL(argv[2]);
  mouse_pinch3(direction, magnification, duration);
  return CURRENT_POSITION;
}


void
Init_mouse()
{
  // on either supported Ruby, this should be defined by now
  rb_cCGPoint = rb_const_get(rb_cObject, rb_intern("CGPoint"));

  sel_x        = rb_intern("x");
  sel_y        = rb_intern("y");
  sel_to_point = rb_intern("to_point");
  sel_new      = rb_intern("new");

  sym_pixel    = ID2SYM(rb_intern("pixel"));
  sym_line     = ID2SYM(rb_intern("line"));

  sym_up       = ID2SYM(rb_intern("up"));
  sym_down     = ID2SYM(rb_intern("down"));
  sym_left     = ID2SYM(rb_intern("left"));
  sym_right    = ID2SYM(rb_intern("right"));

  sym_zoom     = ID2SYM(rb_intern("zoom"));
  sym_expand   = ID2SYM(rb_intern("expand"));
  sym_contract = ID2SYM(rb_intern("contract"));

  /*
   * Document-module: Mouse
   *
   * A module with methods that "tap" into the system input methods.
   * This is done by wrapping wrapping around the CoreGraphics event
   * taps API provided by OS X.
   *
   * The module provides a simple Ruby interface to performing mouse
   * interactions such as moving and clicking.
   *
   * This module can be used in a stand alone fashion or you can mix
   * it into another class.
   *
   * [Reference](http://developer.apple.com/library/mac/#documentation/Carbon/Reference/QuartzEventServicesRef/Reference/reference.html)
   */
  rb_mMouse = rb_define_module("Mouse");

  rb_extend_object(rb_mMouse, rb_mMouse);

  rb_define_method(rb_mMouse, "current_position",     rb_mouse_current_position,      0);
  rb_define_method(rb_mMouse, "move_to",              rb_mouse_move_to,              -1);
  rb_define_method(rb_mMouse, "drag_to",              rb_mouse_drag_to,              -1);
  rb_define_method(rb_mMouse, "scroll",               rb_mouse_scroll,               -1);
  rb_define_method(rb_mMouse, "click_down",           rb_mouse_click_down,           -1);
  rb_define_method(rb_mMouse, "click_up",             rb_mouse_click_up,             -1);
  rb_define_method(rb_mMouse, "click",                rb_mouse_click,                -1);
  rb_define_method(rb_mMouse, "secondary_click_down", rb_mouse_secondary_click_down, -1);
  rb_define_method(rb_mMouse, "secondary_click_up",   rb_mouse_secondary_click_up,   -1);
  rb_define_method(rb_mMouse, "secondary_click",      rb_mouse_secondary_click,      -1);
  rb_define_method(rb_mMouse, "middle_click",         rb_mouse_middle_click,         -1);
  rb_define_method(rb_mMouse, "arbitrary_click_down", rb_mouse_arbitrary_click_down, -1);
  rb_define_method(rb_mMouse, "arbitrary_click_up",   rb_mouse_arbitrary_click_up,   -1);
  rb_define_method(rb_mMouse, "arbitrary_click",      rb_mouse_arbitrary_click,      -1);
  rb_define_method(rb_mMouse, "multi_click",          rb_mouse_multi_click,          -1);
  rb_define_method(rb_mMouse, "double_click",         rb_mouse_double_click,         -1);
  rb_define_method(rb_mMouse, "triple_click",         rb_mouse_triple_click,         -1);

  /* @!group Gestures */
  rb_define_method(rb_mMouse, "smart_magnify",        rb_mouse_smart_magnify,        -1);
  rb_define_method(rb_mMouse, "pinch",                rb_mouse_pinch,                -1);
  /* @!endgroup */

  rb_define_alias(rb_mMouse, "right_click_down",      "secondary_click_down");
  rb_define_alias(rb_mMouse, "right_click_up",        "secondary_click_up");
  rb_define_alias(rb_mMouse, "right_click",           "secondary_click");
  rb_define_alias(rb_mMouse, "two_finger_double_tap", "smart_magnify");
}
