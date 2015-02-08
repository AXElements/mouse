require 'test/helper'

class MouseTest < MiniTest::Unit::TestCase

  def distance point1, point2
    x = point1.x - point2.x
    y = point1.y - point2.y
    Math.sqrt((x**2) + (y**2))
  end

  def test_mouse_current_position
    assert_kind_of CGPoint, Mouse.current_position
  end

  def test_mouse_move_to
    point = CGPoint.new(100, 100)
    Mouse.move_to point
    assert_in_delta 0, distance(point,Mouse.current_position), 1.0

    point = CGPoint.new(rand(700)+150, rand(500)+100)
    Mouse.move_to point
    assert_in_delta 0, distance(point,Mouse.current_position), 1.0
  end

  def test_mouse_move_to_accepts_duration_argument
    start_time  = Time.now
    start_point = Mouse.current_position

    Mouse.move_to [10, 10], 1
    assert_in_delta 1, (Time.now - start_time), 0.3

    start_time = Time.now
    Mouse.move_to start_point, 0.1
    assert_in_delta 0.1, (Time.now - start_time), 0.05
  end

end
