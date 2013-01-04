# 1.1.0 - A bit more granularity

  * Add `Mouse.secondary_click_down` and alias `Mouse.right_click_down`
  * Add `Mouse.secondary_click_up` and alias `Mouse.right_click_up`
  * Add `Mouse.arbitrary_click_down`
  * Add `Mouse.arbitrary_click_up`

# 1.0.6 - Boogs

  * Fix `Mouse.scroll` assuming arguments always included units
  * Fix `Mouse.scroll` assuming amount was always positive (d'oh)

# 1.0.5 - Tweaks for AXElements

  * Coerce `CGPoint.new` arguments using `#to_f`
  * Do not redefine `CGPoint` if it is already defined

# 1.0.4 - Change the homepage

  * Moved github project to be under the AXElements organization

# 1.0.3 - Lion compat

  * Add compatability with OS X 10.7

# 1.0.2 - Re-renam

  * Revert 1.0.1 changes

# 1.0.1 - Rename

  * Rename mouse.bundle to cmouse.bundle to avoid name conflict

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
