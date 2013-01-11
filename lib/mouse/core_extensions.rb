if RUBY_ENGINE == 'macruby'
  require 'mouse/core_extensions/macruby'
else
  require 'mouse/core_extensions/mri'
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
