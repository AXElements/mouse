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

static
VALUE
rb_mouse_click_down(VALUE self)
{
  mouse_click_down();
  return CURRENT_POSITION;
}

static
VALUE
rb_mouse_click_up(VALUE self)
{
  mouse_click_up();
  return CURRENT_POSITION;
}

static
VALUE
rb_mouse_click(VALUE self)
{
  mouse_click();
  return CURRENT_POSITION;
}

static
VALUE
rb_mouse_secondary_click(VALUE self)
{
  mouse_secondary_click();
  return CURRENT_POSITION;
}

static
VALUE
rb_mouse_arbitrary_click(VALUE self, VALUE button)
{
  button = rb_funcall(button, sel_to_i, 0);
  mouse_arbitrary_click(NUM2UINT(button));
  return CURRENT_POSITION;
}

static
VALUE
rb_mouse_middle_click(VALUE self)
{
  mouse_middle_click();
  return CURRENT_POSITION;
}

static
VALUE
rb_mouse_multi_click(VALUE self, VALUE num_clicks)
{
  // TODO: there has got to be a more idiomatic way to do this coercion
  num_clicks = rb_funcall(num_clicks, sel_to_i, 0);
  mouse_multi_click(NUM2SIZET(num_clicks));
  return CURRENT_POSITION;
}

static
VALUE
rb_mouse_double_click(VALUE self)
{
  mouse_double_click();
  return CURRENT_POSITION;
}

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
  rb_cCGPoint = rb_const_get(rb_cObject, rb_intern("CGPoint"));
  sel_x = rb_intern("x");
  sel_y = rb_intern("y");
  sel_to_point = rb_intern("to_point");
  sel_to_i     = rb_intern("to_i");
  sel_new = rb_intern("new");

  rb_mMouse = rb_define_module("Mouse");
  rb_funcall(rb_mMouse, rb_intern("extend"), 1, rb_mMouse);

  rb_define_method(rb_mMouse, "current_position", rb_mouse_current_position, 0);
  rb_define_method(rb_mMouse, "move_to",          rb_mouse_move_to,          1);
  rb_define_method(rb_mMouse, "drag_to",          rb_mouse_drag_to,          1);
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
}
