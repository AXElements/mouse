
#include <ApplicationServices/ApplicationServices.h>
#include <assert.h>
#include "Mouse.h"

static void
run_test(CGPoint point) {
  mouse_move_to(point);
  usleep(10000);
  assert(mouse_current_position().x - point.x < 1);
  assert(mouse_current_position().y - point.y < 1);
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

