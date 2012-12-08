require 'test/helper'

class MouseTest < MiniTest::Unit::TestCase

  def test_mouse_current_position
    assert_kind_of CGPoint, Mouse.current_position
  end

end
