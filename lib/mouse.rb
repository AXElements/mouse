require 'mouse/version'

if RUBY_ENGINE == 'macruby'

  framework 'AppKit'

  # A workaround that guarantees that `CGPoint` is defined
  MOUNTAIN_LION_APPKIT_VERSION ||= 1187
  if NSAppKitVersionNumber >= MOUNTAIN_LION_APPKIT_VERSION
    framework '/System/Library/Frameworks/CoreGraphics.framework'
  end

else

  ##
  # A structure that contains a point in a two-dimensional coordinate system
  CGPoint = Struct.new(:x, :y) do

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
      "#<CGPoint x=#{self.x.to_f} y=#{self.y.to_f}>"
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

require 'mouse/mouse'
