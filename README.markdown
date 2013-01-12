# mouse

A port of mouse.rb from [AXElements](http://github.com/Marketcircle/AXElements),
but cleaned up and rewritten in C to be more portable across languages and
runtimes.

By itself, the `mouse` gem is not that useful; but in combination
with a gem for discovering the positions of things (like buttons) on
the screen, this gem is very powerful and can be used for tasks such
as automated functional
testing; this is the purpose of the
[AXElements](http://github.com/Marketcircle/AXElements) project.

[Documentation](http://rdoc.info/gems/mouse/frames)

[![Code Climate](https://codeclimate.com/badge.png)](https://codeclimate.com/github/AXElements/mouse)


## Examples

    require 'mouse'

    Mouse.current_position # => #<CGPoint x=873.2 y=345.0>

    # positions can be given as a an array with two points, or a CGPoint
    Mouse.move_to [10, 10]
    Mouse.move_to CGPoint.new(10, 10)

    # optionally specify how long it should take the mouse to move
    Mouse.move_to [800, 300], 0.2

    Mouse.click
    Mouse.double_click
    Mouse.triple_click

    # secondary_click and right_click are aliases to the same method
    Mouse.secondary_click
    Mouse.right_click

    # positive number scrolls up, negative number scrolls down
    Mouse.scroll 10
    Mouse.scroll -10

    # perform horizontal scrolling as well
    # positive number scrolls left, negative number scrolls right
    Mouse.horizontal_scroll 10
    Mouse.horizontal_scroll -10

    # optionally specify units for scroll amount, :pixel or :line
    Mouse.scroll 10, :pixels
    Mouse.scroll -10, :pixels

    # just like a two finger double tap
    Mouse.smart_magnify
    Mouse.smart_magnify [600, 500]

    # pinch-to-zoom
    Mouse.pinch :zoom
    Mouse.pinch :expand, 2

    # pinch-to-unzoom
    Mouse.pinch :unzoom, 2.0, 5.0
    Mouse.pinch :contract, 1.0

    # even perform rotation gestures!
    Mouse.rotate :clockwise, 90
    Mouse.rotate :counter_clockwise, 180
    Mouse.rotate :cw, 360

    # swipe, swipe, swipe
    Mouse.swipe :up
    Mouse.swipe :down
    Mouse.swipe :left
    Mouse.swipe :right


See the [Mouse Documentation](http://rdoc.info/gems/mouse/Mouse) for
more details.

You may have noticed that when you ask the mouse to move to a specific
location that it may not end up at the exact co-ordinates, but it will
be close (distance of less than 1). This is by design, but that may
change in the future if there are enough complaints.


## TODO

- [ ] More mouse gesture support
- [ ] Make animation duration accurate (current naiveté has a bit of error)
- [ ] Import test app and specialize so we can have better tests


## Copyright

Copyright (c) 2012, Mark Rada
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of Mark Rada nor the names of its
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Mark Rada BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
