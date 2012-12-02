#include "mouser.h"
#include "ruby.h"

static VALUE rb_mMouse;
static VALUE rb_cCGPoint;
static ID sel_x;
static ID sel_y;
static ID sel_to_point;
static ID sel_to_i;

#define CURRENT_POSITION rb_mouse_wrap_point(mouse_current_position())

static
VALUE
rb_mouse_wrap_point(CGPoint point)
{
  return rb_struct_new(rb_cCGPoint, DBL2NUM(point.x), DBL2NUM(point.y));
}

static
CGPoint
rb_mouse_unwrap_point(VALUE point)
{
  point = rb_funcall(point, sel_to_point, 0);
  double x = NUM2DBL(rb_struct_getmember(point, sel_x));
  double y = NUM2DBL(rb_struct_getmember(point, sel_y));
  return CGPointMake(x, y);
}

/***
 * Returns the current co-ordinates of the Mouse
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_current_position(VALUE self)
{
  return CURRENT_POSITION;
}

/***
 * Move the cursor to the given co-ordinates
 *
 * @param point [CGPoint,Array(Number,Number),#to_point]
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_move_to(VALUE self, VALUE point)
{
  mouse_move_to(rb_mouse_unwrap_point(point));
  return CURRENT_POSITION;
}

/***
 * Drag the cursor to the given co-ordinates
 *
 * @param point [CGPoint,Array(Number,Number),#to_point]
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_drag_to(VALUE self, VALUE point)
{
  mouse_drag_to(rb_mouse_unwrap_point(point));
  return CURRENT_POSITION;
}

/***
 * Generate `amount` scroll events at the current cursor position
 *
 * @param amount [Number]
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_scroll(VALUE self, VALUE amount)
{
  amount = rb_funcall(amount, sel_to_i, 0);
  mouse_scroll(NUM2SIZET(amount));
  return CURRENT_POSITION;
}

void
Init_mouse()
{
  rb_cCGPoint = rb_const_get(rb_cObject, rb_intern("CGPoint"));
  sel_x = rb_intern("x");
  sel_y = rb_intern("y");
  sel_to_point = rb_intern("to_point");
  sel_to_i     = rb_intern("to_i");

  rb_mMouse = rb_define_module("Mouse");
  rb_funcall(rb_mMouse, rb_intern("extend"), 1, rb_mMouse);

  rb_define_method(rb_mMouse, "current_position", rb_mouse_current_position, 0);
  rb_define_method(rb_mMouse, "move_to",          rb_mouse_move_to,          1);
  rb_define_method(rb_mMouse, "drag_to",          rb_mouse_drag_to,          1);
  rb_define_method(rb_mMouse, "scroll",           rb_mouse_scroll,           1);
}
