#include "mouser.h"
#include "ruby.h"

static VALUE rb_mMouse;
static VALUE rb_cCGPoint;
static ID sel_x;
static ID sel_y;
static ID sel_to_point;
static ID sel_to_i;
static ID sel_new;

#define CURRENT_POSITION rb_mouse_wrap_point(mouse_current_position())

static
VALUE
rb_mouse_wrap_point(CGPoint point)
{
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
 * Generate `amount` scroll events at the current cursor position
 *
 * Returns number of lines scrolled.
 *
 * @param amount [Number]
 * @return [Number]
 */
static
VALUE
rb_mouse_scroll(VALUE self, VALUE amount)
{
  amount = rb_funcall(amount, sel_to_i, 0);
  mouse_scroll(NUM2SIZET(amount));
  return amount;
}

/*
 * Generate the down click part of a click event at the current position
 *
 * This might be useful in concert with {Mouse.click_up} if you want
 * to inject some behaviour between the down and up click events.
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_click_down(VALUE self)
{
  mouse_click_down();
  return CURRENT_POSITION;
}

/*
 * Generate the up click part of a click event at the current position
 *
 * This might be useful in concert with {Mouse.click_down} if you want
 * to inject some behaviour between the down and up click events.
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_click_up(VALUE self)
{
  mouse_click_up();
  return CURRENT_POSITION;
}

/*
 * Generate a regular click event at the current mouse position
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_click(VALUE self)
{
  mouse_click();
  return CURRENT_POSITION;
}

/*
 * Generate a secondary click at the current mouse position
 *
 * Secondary click is often referred to as "right click".
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_secondary_click(VALUE self)
{
  mouse_secondary_click();
  return CURRENT_POSITION;
}

/*
 * Generate a click using an arbitrary mouse button at the current position
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
 * @param button [Number,#to_i]
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_arbitrary_click(VALUE self, VALUE button)
{
  button = rb_funcall(button, sel_to_i, 0);
  mouse_arbitrary_click(NUM2UINT(button));
  return CURRENT_POSITION;
}

/*
 * Generate a click event for the middle mouse button at the current position
 *
 * It doesn't matter if you don't have a middle mouse button.
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_middle_click(VALUE self)
{
  mouse_middle_click();
  return CURRENT_POSITION;
}

/*
 * Generate a multi-click event at the current mouse position
 *
 * Unlike {Mouse.double_click} and {Mouse.triple_click} this will generate
 * a single event with the given number of clicks.
 *
 * @param num_clicks [Number,#to_i]
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_multi_click(VALUE self, VALUE num_clicks)
{
  // TODO: there has got to be a more idiomatic way to do this coercion
  num_clicks = rb_funcall(num_clicks, sel_to_i, 0);
  mouse_multi_click(NUM2SIZET(num_clicks));
  return CURRENT_POSITION;
}

/*
 * Perform a double click at the given mouse position
 *
 * Implemented by first generating a single click, and then a double click.,
 * Apps seem to respond more consistently to this behaviour since that is
 * how a human would have to generate a double click event.
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_double_click(VALUE self)
{
  mouse_double_click();
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
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_triple_click(VALUE self)
{
  mouse_triple_click();
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
  sel_to_i     = rb_intern("to_i");
  sel_new      = rb_intern("new");

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
   * [Reference](http://developer.apple.com/library/mac/#documentation/Carbon/Reference/QuartzEventServicesRef/Reference/reference.html)
   */
  rb_mMouse = rb_define_module("Mouse");

  rb_funcall(rb_mMouse, rb_intern("extend"), 1, rb_mMouse);

  rb_define_method(rb_mMouse, "scroll",           rb_mouse_scroll,           1);
  rb_define_method(rb_mMouse, "click_down",       rb_mouse_click_down,       0);
  rb_define_method(rb_mMouse, "click_up",         rb_mouse_click_up,         0);
  rb_define_method(rb_mMouse, "click",            rb_mouse_click,            0);
  rb_define_method(rb_mMouse, "secondary_click",  rb_mouse_secondary_click,  0);
  rb_define_method(rb_mMouse, "arbitrary_click",  rb_mouse_arbitrary_click,  1);
  rb_define_method(rb_mMouse, "middle_click",     rb_mouse_middle_click,     0);
  rb_define_method(rb_mMouse, "multi_click",      rb_mouse_multi_click,      1);
  rb_define_method(rb_mMouse, "double_click",     rb_mouse_double_click,     0);
  rb_define_method(rb_mMouse, "triple_click",     rb_mouse_triple_click,     0);
  rb_define_method(rb_mMouse, "current_position", rb_mouse_current_position,  0);
  rb_define_method(rb_mMouse, "move_to",          rb_mouse_move_to,          -1);
  rb_define_method(rb_mMouse, "drag_to",          rb_mouse_drag_to,          -1);
}
