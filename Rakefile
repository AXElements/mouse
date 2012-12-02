task :default => :install

require 'rake/clean'
CLEAN.include '*.plist', '*.gch'

desc 'Run the Clang static analyzer'
task :analyze do
  sh "clang --analyze ext/mouse/mouser.c"
end

desc 'Startup an IRb console with Mouse loaded'
task :console => [:compile] do
  sh 'irb -Ilib -rmouse'
end

desc 'Run tests'
task :test do
  # @todo
  ruby 'test/helper.rb'
end


# Gem stuff

require 'rubygems/package_task'
mouse_spec = Gem::Specification.load('mouse.gemspec')

Gem::PackageTask.new(mouse_spec) { }

desc 'Build and install gem (not including deps)'
task :install => :gem do
  require 'rubygems/installer'
  Gem::Installer.new("pkg/#{ax_elements.file_name}").install
end

require 'rake/extensiontask'
Rake::ExtensionTask.new('mouse', mouse_spec)
