require 'mouse.bundle'
require 'ffi'

unless RUBY_ENGINE == 'macruby'

  class CGPoint < FFI::Struct
    layout :x, :double,
           :y, :double

    def to_point
      self
    end

    def x; self[:x] end
    def x= new_x; self[:x] = new_x end

    def y; self[:y] end
    def y= new_y; self[:y] = new_y end

    def inspect
      "#<CGPoint x=#{self[:x]} y=#{self[:y]}>"
    end
  end

  class Array
    def to_point
      point = CGPoint.new
      point[:x] = self[0]
      point[:y] = self[1]
      point
    end
  end

end
