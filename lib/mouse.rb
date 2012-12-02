if RUBY_ENGINE == 'macruby'

  framework '/System/Library/Frameworks/CoreGraphics.framework'

else

  class CGPoint < Struct.new(:x, :y)

    def to_point
      self
    end

    def inspect
      "#<CGPoint x=#{self[:x]} y=#{self[:y]}>"
    end

  end

end

class Array
  def to_point
    CGPoint.new self[0], self[1]
  end
end

require 'mouse.bundle'
