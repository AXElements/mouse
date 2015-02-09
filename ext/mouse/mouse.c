#include "mouser.h"
#include "ruby.h"

#ifndef UNUSED
#define UNUSED __attribute__ ((unused))
#endif


static VALUE rb_mMouse, rb_cCGPoint;

static ID sel_x, sel_y, sel_to_point, sel_new;

static VALUE sym_pixel, sym_line,
  sym_up, sym_down, sym_left, sym_right,
  sym_zoom, sym_unzoom, sym_expand, sym_contract,
  sym_cw, sym_clockwise, sym_clock_wise,
  sym_ccw, sym_counter_clockwise, sym_counter_clock_wise;

#define CURRENT_POSITION rb_mouse_wrap_point(mouse_current_position())

static
VALUE
rb_mouse_wrap_point(const CGPoint point)
{
    return rb_struct_new(rb_cCGPoint, DBL2NUM(point.x), DBL2NUM(point.y));
}

static
CGPoint
rb_mouse_unwrap_point(const VALUE maybe_point)
{
    const VALUE point = rb_funcall(maybe_point, sel_to_point, 0);
    const double x = NUM2DBL(rb_struct_getmember(point, sel_x));
    const double y = NUM2DBL(rb_struct_getmember(point, sel_y));
    return CGPointMake(x, y);
}

/*
 * Returns the current co-ordinates of the mouse cursor
 *
 * @return [CGPoint]
 */
static
VALUE
rb_mouse_current_position(UNUSED const VALUE self)
{
    return CURRENT_POSITION;
}

/*
 * Move the mouse cursor to the given co-ordinates
 *
 * The default duration is 0.2 seconds.
 *
 * @overload move_to(point)
 *   @param point [CGPoint,Array(Number,Number),#to_point]
 *   @return [CGPoint]
 * @overload move_to(point, duration)
 *   @param point [CGPoint,Array(Number,Number),#to_point]
 *   @param duration [Number] animation time, in seconds
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_move_to(const int argc,
                 VALUE* const argv,
                 UNUSED const VALUE self)
{
    switch (argc) {
    case 0:
        rb_raise(rb_eArgError, "move_to requires at least a one arg");
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
rb_mouse_drag_to(const int argc,
                 VALUE* const argv,
                 UNUSED const VALUE self)
{
    switch (argc) {
    case 0:
        rb_raise(rb_eArgError, "drag_to requires at least a one arg");
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
 *       correspond to Cocoa co-ords (I don't have a retina display, so I
 *       haven't checked it out yet).
 *
 * Generate `amount` scroll events at the current cursor position
 *
 * Returns number of lines/pixels scrolled, default `units` are by `line`.
 * A positive `amount` will scroll up and a negative `amount` will scroll down.
 *
 * An animation duration can also be specified, which defaults to 0.2 seconds.
 *
 * @overload scroll(amount)
 *   @param amount [Number]
 *   @return [Number]
 * @overload scroll(amount, units)
 *   @param amount [Number]
 *   @param units [Symbol] `:pixel` or `:line`
 *   @return [Number]
 * @overload scroll(amount, units, duration)
 *   @param amount [Number]
 *   @param units [Symbol] `:pixel` or `:line`
 *   @param duration [Number] animation time, in seconds
 *   @return [Number]
 */
static
VALUE
rb_mouse_scroll(const int argc, VALUE* const argv, UNUSED const VALUE self)
{
    if (argc == 0 || argc > 3)
        rb_raise(rb_eArgError,
                 "scroll requires 1..3 arguments, you gave %d",
                 argc);

    const int amt = NUM2INT(argv[0]);

    if (argc == 1) {
        mouse_scroll(amt);

    } else {
        const VALUE input_units = argv[1];
        CGScrollEventUnit units;

        if (input_units == sym_pixel)
            units = kCGScrollEventUnitPixel;
        else if (input_units == sym_line)
            units = kCGScrollEventUnitLine;
        else
            rb_raise(rb_eArgError,
                     "unknown units `%s'",
                     rb_id2name(input_units));

        if (argc == 2)
            mouse_scroll2(amt, units);
        else
            mouse_scroll3(amt, units, NUM2DBL(argv[2]));
    }

    return argv[0];
}

/*
 * @note Scrolling by `:pixel` may not actually be by real pixels, but instead
 *       correspond to Cocoa co-ords (I don't have a retina display, so I haven't
 *       checked it out yet).
 *
 * Generate `amount` of horizontal scroll events at the current cursor position
 *
 * Returns number of lines/pixels scrolled, default `units` are by `line`.
 * A positive `amount` will scroll up and a negative `amount` will scroll down.
 *
 * An animation duration can also be specified, which defaults to 0.2 seconds.
 *
 * @overload horizontal_scroll(amount)
 *   @param amount [Number]
 *   @return [Number]
 * @overload horizontal_scroll(amount, units)
 *   @param amount [Number]
 *   @param units [Symbol] `:pixel` or `:line`
 *   @return [Number]
 * @overload horizontal_scroll(amount, units, duration)
 *   @param amount [Number]
 *   @param units [Symbol] `:pixel` or `:line`
 *   @param duration [Number] animation time, in seconds
 *   @return [Number]
 */
static
VALUE
rb_mouse_horizontal_scroll(const int argc,
                           VALUE* const argv,
                           UNUSED const VALUE self)
{
    if (argc == 0 || argc > 3)
        rb_raise(rb_eArgError,
                 "scroll requires 1..3 arguments, you gave %d",
                 argc);

    const int amt = NUM2INT(argv[0]);

    if (argc == 1) {
        mouse_horizontal_scroll(amt);

    } else {
        const VALUE input_units = argv[1];
        CGScrollEventUnit units;

        if (input_units == sym_pixel)
            units = kCGScrollEventUnitPixel;
        else if (input_units == sym_line)
            units = kCGScrollEventUnitLine;
        else
            rb_raise(rb_eArgError,
                     "unknown units `%s'",
                     rb_id2name(input_units));

        if (argc == 2)
            mouse_horizontal_scroll2(amt, units);
        else
            mouse_horizontal_scroll3(amt, units, NUM2DBL(argv[2]));
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload click_down()
 *   @return [CGPoint]
 * @overload click_down(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_click_down(const int argc,
                    VALUE* const argv,
                    UNUSED const VALUE self)
{
    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload click_up()
 *   @return [CGPoint]
 * @overload click_up(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_click_up(const int argc, VALUE* const argv, UNUSED const VALUE self)
{
    switch (argc) {
    case 0:
        mouse_click_up();
        break;
    case 1:
    default:
        mouse_click_up2(rb_mouse_unwrap_point(argv[0]));
    }

    return CURRENT_POSITION;
}

/*
 * Generate a regular click event (both up and down events)
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload click()
 *   @return [CGPoint]
 * @overload click()
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_click(const int argc, VALUE* const argv, UNUSED const VALUE self)
{
    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload secondary_click_down()
 *   @return [CGPoint]
 * @overload secondary_click_down(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_secondary_click_down(const int argc,
                              VALUE* const argv,
                              UNUSED const VALUE self)
{
    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload secondary_click_up()
 *   @return [CGPoint]
 * @overload secondary_click_up(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_secondary_click_up(const int argc,
                            VALUE* const argv,
                            UNUSED const VALUE self)
{
    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload secondary_click()
 *   @return [CGPoint]
 * @overload secondary_click(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_secondary_click(const int argc,
                         VALUE* const argv,
                         UNUSED const VALUE self)
{
    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload arbitrary_click_down()
 *   @return [CGPoint]
 * @overload arbitrary_click_down(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_arbitrary_click_down(const int argc,
                              VALUE* const argv,
                              UNUSED const VALUE self)
{
    if (argc == 0)
        rb_raise(rb_eArgError,
                 "arbitrary_click_down requires at least one arg");

    const uint_t button = NUM2UINT(argv[0]);

    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload arbitrary_click_up()
 *   @return [CGPoint]
 * @overload arbitrary_click_up(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_arbitrary_click_up(const int argc,
                            VALUE* const argv,
                            UNUSED const VALUE self)
{
    if (argc == 0)
        rb_raise(rb_eArgError,
                 "arbitrary_click_up requires at least one arg");

    const uint_t button = NUM2UINT(argv[0]);

    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload arbitrary_click(button)
 *   @param button [Number,#to_i]
 *   @return [CGPoint]
 * @overload arbitrary_click(button, point)
 *   @param button [Number,#to_i]
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_arbitrary_click(const int argc,
                         VALUE* const argv,
                         UNUSED const VALUE self)
{
    if (argc == 0) {
        rb_raise(rb_eArgError, "arbitrary_click requires at least one arg");
        return Qnil;
    }

    const uint_t button = NUM2UINT(argv[0]);

    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload middle_click()
 *   @return [CGPoint]
 * @overload middle_click(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_middle_click(const int argc,
                      VALUE* const argv,
                      UNUSED const VALUE self)
{
    switch (argc) {
    case 0:
        mouse_middle_click();
        break;
    case 1:
    default:
        mouse_middle_click2(rb_mouse_unwrap_point(argv[0]));
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload multi_click(num_clicks)
 *   @param num_clicks [Number,#to_i]
 *   @return [CGPoint]
 * @overload multi_click(num_clicks, point)
 *   @param num_clicks [Number,#to_i]
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_multi_click(const int argc,
                     VALUE* const argv,
                     UNUSED const VALUE self)
{

    if (argc == 0) {
        rb_raise(rb_eArgError, "multi_click requires at least one arg");
        return Qnil;
    }

    // TODO: there has got to be a more idiomatic way to do this coercion
    const size_t num_clicks = NUM2SIZET(argv[0]);

    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload double_click()
 *   @return [CGPoint]
 * @overload double_click(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_double_click(const int argc,
                      VALUE* const argv,
                      UNUSED const VALUE self)
{
    switch (argc) {
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
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload triple_click()
 *   @return [CGPoint]
 * @overload triple_click(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_triple_click(const int argc,
                      VALUE* const argv,
                      UNUSED const VALUE self)
{
    switch (argc) {
    case 0:
        mouse_triple_click();
        break;
    case 1:
    default:
        mouse_triple_click2(rb_mouse_unwrap_point(argv[0]));
    }

    return CURRENT_POSITION;
}


/* @!group Gestures */

/*
 * Perform a smart magnify (double tap on trackpad)
 *
 * You can optionally specify a point to click; the mouse cursor will
 * instantly jump to the given point; otherwise the click event happens
 * at the current cursor position.
 *
 * @overload smart_magnify()
 *   @return [CGPoint]
 * @overload smart_magnify(point)
 *   @param point [CGPoint]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_smart_magnify(const int argc,
                       VALUE* const argv,
                       UNUSED const VALUE self)
{
    switch (argc) {
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
 * Perform a swipe gesture in the given `direction`
 *
 * You can optionally specify a point on screen for the mouse
 * pointer to be moved to before the gesture begins. The movement will
 * be instantaneous; otherwise the click event happens
 * at the current cursor position.
 *
 * You can also optionally specify the duration of the swipe event;
 * the default `duration` is 0.2 seconds.
 *
 * @overload swipe(direction)
 *   @param direction [Symbol]
 *   @return [CGPoint]
 * @overload swipe(direction, point)
 *   @param direction [Symbol]
 *   @param point [CGPoint]
 *   @return [CGPoint]
 * @overload swipe(direction, point, duration)
 *   @param direction [Symbol]
 *   @param point [CGPoint]
 *   @param duration [Float]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_swipe(const int argc, VALUE* const argv, UNUSED const VALUE self)
{
    if (!argc)
        rb_raise(rb_eArgError, "wrong number of arguments (0 for 1+)");

    const VALUE direction_input = argv[0];
    CGSwipeDirection direction;
    if (direction_input == sym_up)
        direction = kCGSwipeDirectionUp;
    else if (direction_input == sym_down)
        direction = kCGSwipeDirectionDown;
    else if (direction_input == sym_left)
        direction = kCGSwipeDirectionLeft;
    else if (direction_input == sym_right)
        direction = kCGSwipeDirectionRight;
    else
        rb_raise(rb_eArgError,
                 "invalid swipe direction `%s'",
                 rb_id2name(SYM2ID(direction_input)));

    if (argc == 1) {
      mouse_swipe(direction);
      return CURRENT_POSITION;
    }

    const CGPoint point = rb_mouse_unwrap_point(argv[1]);
    mouse_swipe2(direction, point);
    return CURRENT_POSITION;
}

/*
 * Perform a pinch gesture in given `direction`
 *
 * You can optionally specify the `magnification` factor and/or
 * `duration` for the pinch event.
 *
 * Available pinch directions are:
 *
 *   - `:zoom` or `:expand`
 *   - `:unzoom` or `:contract`
 *
 * Magnification is a relative magnification setting. A zoom value of
 * `1.0` means `1.0` more than the current zoom level. `2.0` would be
 * `2.0` levels higher than the current zoom. Default is `1.0`.
 *
 * You can also optionally specify a point on screen for the mouse
 * pointer to be moved to before the gesture begins. The movement will
 * be instantaneous. Default `point` is {#current_position}.
 *
 * An animation duration can also be specified. The default is 0.2 seconds.
 *
 * @overload pinch(direction)
 *   @param direction [Symbol]
 *   @return [CGPoint]
 * @overload pinch(direction, magnification)
 *   @param direction [Symbol]
 *   @param magnification [Float]
 *   @return [CGPoint]
 * @overload pinch(direction, magnification, point)
 *   @param direction [Symbol]
 *   @param magnification [Float]
 *   @param point [CGPoint]
 *   @return [CGPoint]
 * @overload pinch(direction, magnification, point, duration)
 *   @param direction [Symbol]
 *   @param magnification [Float]
 *   @param point [CGPoint]
 *   @param duration [Float]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_pinch(const int argc, VALUE* const argv, UNUSED const VALUE self)
{
    if (!argc)
        rb_raise(rb_eArgError, "wrong number of arguments (%d for 1+)", argc);

    const VALUE input_direction = argv[0];
    CGPinchDirection  direction = kCGPinchNone;

    if (input_direction == sym_expand || input_direction == sym_zoom)
        direction = kCGPinchExpand;
    else if (input_direction == sym_contract || input_direction == sym_unzoom)
        direction = kCGPinchContract;
    else
        rb_raise(rb_eArgError,
                 "invalid pinch direction `%s'",
                 rb_id2name(SYM2ID(input_direction)));

    if (argc == 1) {
        mouse_pinch(direction);
        return CURRENT_POSITION;
    }

    const double magnification = NUM2DBL(argv[1]);
    if (argc == 2) {
        mouse_pinch2(direction, magnification);
        return CURRENT_POSITION;
    }

    const CGPoint point = rb_mouse_unwrap_point(argv[2]);
    if (argc == 3) {
        mouse_pinch3(direction, magnification, point);
        return CURRENT_POSITION;
    }

    const double duration = NUM2DBL(argv[3]);
    mouse_pinch4(direction, magnification, point, duration);
    return CURRENT_POSITION;
}

/*
 * Perform a rotation gesture in the given `direction` the given `angle` degrees
 *
 * Possible directions are:
 *
 *   - `:cw`, ':clockwise`, ':clock_wise` to rotate in the clockwise
 *     direction
 *   - `:ccw`, ':counter_clockwise`, `:counter_clock_wise` to rotate in
 *     the the counter clockwise direction
 *
 * The `angle` parameter is a number of degrees to rotate. There are 360
 * degrees in a full rotation, as you would expect in Euclidian geometry.
 *
 * You can also optionally specify a point on screen for the mouse
 * pointer to be moved to before the gesture begins. The movement will
 * be instantaneous. Default `point` is {#current_position}.
 *
 * An animation duration can also be specified. The default is 0.2 seconds.
 *
 * @overload rotate(direction, angle)
 *   @param direction [Symbol]
 *   @param angle [Float]
 *   @return [CGPoint]
 * @overload rotate(direction, angle, point)
 *   @param direction [Symbol]
 *   @param angle [Float]
 *   @param point [CGPoint]
 *   @return [CGPoint]
 * @overload rotate(direction, angle, point, duration)
 *   @param direction [Symbol]
 *   @param angle [Float]
 *   @param point [CGPoint]
 *   @param duration [Float]
 *   @return [CGPoint]
 */
static
VALUE
rb_mouse_rotate(const int argc, VALUE* const argv, UNUSED const VALUE self)
{
    if (argc < 2)
        rb_raise(rb_eArgError, "wrong number of arguments (%d for 2+)", argc);


    const VALUE input_dir = argv[0];
    CGRotateDirection direction = kCGRotateNone;

    if      (input_dir == sym_cw ||
             input_dir == sym_clockwise ||
             input_dir == sym_clock_wise)
        direction = kCGRotateClockwise;

    else if (input_dir == sym_ccw ||
             input_dir == sym_counter_clockwise ||
             input_dir == sym_counter_clock_wise)
        direction = kCGRotateCounterClockwise;
    else
        rb_raise(rb_eArgError,
                 "invalid rotation direction `%s'",
                 rb_id2name(SYM2ID(input_dir)));

    const double angle = NUM2DBL(argv[1]);

    if (argc == 2) {
        mouse_rotate(direction, angle);
        return CURRENT_POSITION;
    }

    const CGPoint point = rb_mouse_unwrap_point(argv[2]);
    if (argc == 3) {
        mouse_rotate2(direction, angle, point);
        return CURRENT_POSITION;
    }

    mouse_rotate3(direction, angle, point, NUM2DBL(argv[3]));
    return CURRENT_POSITION;
}

/* @!endgroup */


void Init_mouse(void);

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
    sym_unzoom   = ID2SYM(rb_intern("unzoom"));
    sym_expand   = ID2SYM(rb_intern("expand"));
    sym_contract = ID2SYM(rb_intern("contract"));

    sym_cw                 = ID2SYM(rb_intern("cw"));
    sym_clockwise          = ID2SYM(rb_intern("clockwise"));
    sym_clock_wise         = ID2SYM(rb_intern("clock_wise"));
    sym_ccw                = ID2SYM(rb_intern("ccw"));
    sym_counter_clockwise  = ID2SYM(rb_intern("counter_clockwise"));
    sym_counter_clock_wise = ID2SYM(rb_intern("counter_clock_wise"));

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
    rb_define_method(rb_mMouse, "horizontal_scroll",    rb_mouse_horizontal_scroll,    -1);
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

    rb_define_method(rb_mMouse, "smart_magnify",        rb_mouse_smart_magnify,        -1);
    rb_define_method(rb_mMouse, "swipe",                rb_mouse_swipe,                -1);
    rb_define_method(rb_mMouse, "pinch",                rb_mouse_pinch,                -1);
    rb_define_method(rb_mMouse, "rotate",               rb_mouse_rotate,               -1);

    rb_define_alias(rb_mMouse, "hscroll",               "horizontal_scroll");
    rb_define_alias(rb_mMouse, "right_click_down",      "secondary_click_down");
    rb_define_alias(rb_mMouse, "right_click_up",        "secondary_click_up");
    rb_define_alias(rb_mMouse, "right_click",           "secondary_click");
    rb_define_alias(rb_mMouse, "two_finger_double_tap", "smart_magnify");
}
