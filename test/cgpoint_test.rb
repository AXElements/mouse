require 'test/helper'

class CGPointTest < MiniTest::Unit::TestCase
  
  def test_attributes
    p = CGPoint.new
    assert_respond_to p, :x
    assert_respond_to p, :y
  end

  def test_to_a
    p = CGPoint.new 1, 2
    assert_equal [1, 2], p.to_a
  end

  def test_to_point
    p = CGPoint.new
    assert_same p, p.to_point
    
    p = CGPoint.new 4, 2
    assert_same p, p.to_point
  end

  def test_initialize
    p = CGPoint.new
    assert_equal 0, p.x
    assert_equal 0, p.y

    x = rand(1_000)
    y = rand(1_000)
    p = CGPoint.new x, y
    assert_equal x, p.x
    assert_equal y, p.y

    x = rand() * 1000.0
    y = rand() * 1000.0
    p = CGPoint.new x, y
    assert_equal x, p.x
    assert_equal y, p.y
  end

  def test_inspect
    assert_equal '#<CGPoint x=1 y=2>', CGPoint.new(1, 2).inspect
    assert_equal '#<CGPoint x=3 y=5>', CGPoint.new(3, 5).inspect
  end

end
