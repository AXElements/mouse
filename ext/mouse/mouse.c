#include "mouser.h"
#include "ruby.h"

static VALUE rb_mMouse;
static VALUE rb_cCGPoint;

static
VALUE
rb_mouse_wrap_point(CGPoint point)
{
  return rb_struct_new(rb_cCGPoint, DBL2NUM(point.x), DBL2NUM(point.y));
}

static
VALUE
rb_mouse_current_position(VALUE self)
{
  return rb_mouse_wrap_point(mouse_current_position());
}

void
Init_mouse()
{
  rb_cCGPoint = rb_const_get(rb_cObject, rb_intern("CGPoint"));

  rb_mMouse = rb_define_module("Mouse");
  rb_funcall(rb_mMouse, rb_intern("extend"), 1, rb_mMouse);

  rb_define_method(rb_mMouse, "current_position", rb_mouse_current_position, 0);
}
