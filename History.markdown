# 1.0.0 - Port Completed

  * Added optional `point` argument to all `Mouse` click methods
  * Added duration argument to all `Mouse` methods that are animated
  * Fix differences between MRI CGPoint and MacRuby CGPoint

# 0.1.0 - The basic API

  * Fixed animation timing (sleep(3) type coercion issue)

  * Added `Mouse#click_down`
  * Added `Mouse#click_up`
  * Added `Mouse#click`
  * Added `Mouse#secondary_click`
  * Added `Mouse#arbitrary_click`
  * Added `Mouse#middle_click`
  * Added `Mouse#multi_click`
  * Added `Mouse#double_click`
  * Added `Mouse#triple_click`

# 0.0.1 - Initial Release

  * CRuby and MacRuby compatible

  * Added `Mouse.current_position`
  * Added `Mouse.move_to`
  * Added `Mouse.drag_to`
  * Added `Mouse.scroll`
  * Added `CGPoint` on CRuby to mimic `CGPoint` in MacRuby
  * Added `Array#to_point` to mimic MacRuby allowing Arrays for structs
