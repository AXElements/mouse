require './lib/mouse/version'

Gem::Specification.new do |s|
  s.name     = 'mouse'
  s.version  = Mouse::VERSION

  s.summary     = 'A library for automating the mouse'
  s.description = <<-EOS
mouse is a rich, high level wrapper around OS X CGEvent APIs that allow
programmatic manipulation of the mouse cursor.

Originally extracted from the AXElements project.
  EOS

  s.authors     = ['Mark Rada']
  s.email       = 'markrada26@gmail.com'
  s.homepage    = 'http://github.com/ferrous26/MRMouse'
  s.licenses    = ['BSD 3-clause']
  s.has_rdoc    = 'yard'

  s.extensions  = ['ext/mouse/extconf.rb']
  s.files       = Dir.glob('lib/**/*.rb') +
                  Dir.glob('ext/**/*.{c,h,rb}')
  s.test_files  = Dir.glob('test/**/test_*.rb') + [ 'test/helper.rb' ]

  s.add_runtime_dependency 'ffi', '~> 1.2.0'

  s.add_development_dependency 'yard', '~> 0.8.3'
  s.add_development_dependency 'kramdown', '~> 0.14.1'
  s.add_development_dependency 'rake-compiler', '~> 0.8.1'
end
