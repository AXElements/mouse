##
# A structure that contains a point in a two-dimensional coordinate system
CGPoint = Struct.new(:x, :y) unless defined? CGPoint

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

end
