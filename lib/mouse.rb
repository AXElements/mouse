if RUBY_ENGINE == 'macruby'

  # A workaround that guarantees that `CGPoint` is defined
  framework '/System/Library/Frameworks/CoreGraphics.framework'

else

  ##
  # A structure that contains a point in a two-dimensional coordinate system
  class CGPoint < Struct.new(:x, :y)

    # @param x [Number]
    # @param y [Number]
    def initialize x = 0.0, y = 0.0
      super
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
      "#<CGPoint x=#{self.x} y=#{self.y}>"
    end

  end

end

class CGPoint
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

require 'mouse.bundle'
