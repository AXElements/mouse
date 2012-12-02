if RUBY_ENGINE == 'macruby'

  framework '/System/Library/Frameworks/CoreGraphics.framework'

else

  ##
  #
  class CGPoint < Struct.new(:x, :y)
    ##
    # Return a nice string representation of the point
    #
    # Overrides `Object#inspect` to more closely mimic MacRuby `Boxed#inspect`.
    #
    # @return [String]
    def inspect
      "#<CGPoint x=#{self[:x]} y=#{self[:y]}>"
    end
  end

end


##
# Mouse extensions to `CGPoint`
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
