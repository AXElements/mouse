#include "mouser.h"
#include "ruby.h"

static VALUE rb_mMouse;
static VALUE rb_cCGPoint;
static ID sel_x;
static ID sel_y;

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
  double x = NUM2DBL(rb_struct_getmember(point, sel_x));
  double y = NUM2DBL(rb_struct_getmember(point, sel_y));
  return CGPointMake(x, y);
}

static
VALUE
rb_mouse_current_position(VALUE self)
{
  return rb_mouse_wrap_point(mouse_current_position());
}

static
VALUE
rb_mouse_move_to(VALUE self, VALUE point)
{
  mouse_move_to(rb_mouse_unwrap_point(point));
  return rb_mouse_wrap_point(mouse_current_position());
}

void
Init_mouse()
{
  rb_cCGPoint = rb_const_get(rb_cObject, rb_intern("CGPoint"));
  sel_x = rb_intern("x");
  sel_y = rb_intern("y");

  rb_mMouse = rb_define_module("Mouse");
  rb_funcall(rb_mMouse, rb_intern("extend"), 1, rb_mMouse);

  rb_define_method(rb_mMouse, "current_position", rb_mouse_current_position, 0);
  rb_define_method(rb_mMouse, "move_to",          rb_mouse_move_to,          1);
}
