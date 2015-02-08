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
  s.homepage    = 'http://github.com/AXElements/mouse'
  s.licenses    = ['BSD 3-clause']
  s.has_rdoc    = 'yard'
  s.platform    = Gem::Platform::RUBY # local

  s.extensions  = ['ext/mouse/extconf.rb']
  s.files       = Dir.glob('lib/**/*.rb') +
                  Dir.glob('ext/**/*.{c,h,rb}') +
                  [
                   'Rakefile',
                   'README.markdown',
                   'History.markdown',
                   '.yardopts'
                  ]
  s.test_files  = Dir.glob('test/**/test_*.rb') + [ 'test/helper.rb' ]

  s.required_ruby_version = '>= 2.0.0'
end
