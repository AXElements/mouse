require 'rake/clean'
CLEAN.include '*.o', '*.plist', '*.gch'
CLEAN.include 'Mouse'

SRC = FileList['*.c']
OBJ = SRC.ext 'o'

task :default => 'Mouse.o'

rule '.o' => '.c' do |fn|
  sh "clang -o #{fn.name} -c #{fn.source} -Wall -Werror -pedantic"
end

desc 'Build the mouse tests'
file 'MouseTest' => ['MouseTest.o', 'Mouse.o'] do
  sh 'clang -o MouseTest MouseTest.o Mouse.o -framework ApplicationServices'
end

desc 'Run the test for Mouse'
task :test do
  sh './MouseTest'
end
