require 'rake/clean'
CLEAN.include '*.o', '*.plist', '*.gch'
CLEAN.include 'Mouse'

SRC = FileList['*.c']
OBJ = SRC.ext 'o'

task :default => 'Mouse.o'

rule '.o' => '.c' do |fn|
  sh "clang -c -o #{fn.name} #{fn.source} -Wall -pedantic -fobj-gc -framework ApplicationServices"
end

desc 'Build the mouse tests'
file 'MouseTest' => ['MouseTest.o', 'Mouse.o'] do
  sh 'clang -o MouseTest MouseTest.o Mouse.o'
end

desc 'Run the test for Mouse'
task :test do
  sh './MouseTest'
end
