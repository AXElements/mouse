task default: :test

require 'rake/clean'
CLOBBER.include '*.plist', '*.gch'

desc 'Run the Clang static analyzer'
task :analyze do
  sh 'clang --analyze ext/mouse/mouser.c'
end

desc 'Startup an IRb console with Mouse loaded'
task console: :compile do
  sh 'irb -Ilib -rmouse'
end

require 'rake/testtask'
Rake::TestTask.new do |t|
  t.libs << '.'
  t.pattern = 'test/*_test.rb'
end
task test: :compile

# Gem stuff

require 'rubygems/package_task'
mouse_spec = Gem::Specification.load('mouse.gemspec')

Gem::PackageTask.new(mouse_spec) {}

require 'rake/extensiontask'
Rake::ExtensionTask.new('mouse', mouse_spec) do |t|
  t.lib_dir = 'lib/mouse'
  t.ext_dir = 'ext/mouse'
end

desc 'Build and install gem (not including deps)'
task install: :gem do
  require 'rubygems/installer'
  Gem::Installer.new("pkg/#{mouse_spec.file_name}").install
end
