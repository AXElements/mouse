require 'test/helper'

class ArrayTest < MiniTest::Unit::TestCase

  def test_to_point
    x = rand(1_000)
    y = rand(1_000)
    p = [x, y].to_point
    assert_kind_of CGPoint, p
    assert_equal x, p.x
    assert_equal y, p.y
  end

end
