##
# A structure that contains a point in a two-dimensional coordinate system
CGPoint = Struct.new(:x, :y) unless defined? CGPoint

##
# Mouse extensions to `CGPoint`
class CGPoint

  # @param x [Number]
  # @param y [Number]
  def initialize x = 0.0, y = 0.0
    super x.to_f, y.to_f
  end

  # @!attribute [rw] x
  #   The `x` co-ordinate of the screen point
  #   @return [Number]

  # @!attribute [rw] y
  #   The `y` co-ordinate of the screen point
  #   @return [Number]

  ##
  # Return a nice string representation of the point
  #
  # Overrides `Object#inspect` to more closely mimic MacRuby `Boxed#inspect`.
  #
  # @return [String]
  def inspect
    "#<CGPoint x=#{self.x.to_f} y=#{self.y.to_f}>"
  end

  ##
  # Returns the receiver, since the receiver is already a {CGPoint}
  #
  # @return [CGPoint]
  def to_point
    self
  end

end

##
# Mouse extensions to `Array`
class Array
  ##
  # Coerce the first two elements of the receiver into a {CGPoint}
  #
  # @return [CGPoint]
  def to_point
    CGPoint.new self[0], self[1]
  end
end

require 'mouse/version'
require 'mouse/mouse'
