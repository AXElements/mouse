require 'mkmf'

$CFLAGS << ' -std=c99 -Weverything'
$CFLAGS << ' -Wno-disabled-macro-expansion -Wno-gnu -Wno-documentation'

$LIBS   << ' -framework Foundation'
$LIBS   << ' -framework ApplicationServices'
$LIBS   << ' -framework CoreGraphics'

unless RbConfig::CONFIG['CC'].match(/clang/)
  clang = `which clang`.chomp
  fail 'Clang not installed. Cannot build C extension' if clang.empty?
  RbConfig::MAKEFILE_CONFIG['CC']  = clang
  RbConfig::MAKEFILE_CONFIG['CXX'] = clang
end

create_makefile 'mouse/mouse'
