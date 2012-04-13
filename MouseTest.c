
#include <ApplicationServices/ApplicationServices.h>
#include <assert.h>
#include "Mouse.h"

static void
run_test(CGPoint point) {
  mouse_move(point);
  usleep(10000);
  assert(mouse_position().x == point.x);
  assert(mouse_position().y == point.y);
}

int
main() {

  run_test(CGPointMake(100, 100));
  run_test(CGPointMake(900, 100));
  run_test(CGPointMake(900, 100));
  run_test(CGPointMake(900, 900));
  run_test(CGPointMake(100, 900));
  run_test(CGPointMake(100, 100));
  run_test(CGPointMake(900, 900));

  return 0;
}

