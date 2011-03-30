require 'rake/clean'

CLEAN.include('*.o')
CLEAN.include('tests')

TESTS = FileList['*_test.cc']
SRC = FileList['*.cc'] - TESTS
HDRS = FileList['*.h']
OBJ = SRC.ext('o')
LIB = "-L /usr/X11/lib -L vendor"

rule '.o' => ['.cc'] do |t|
  sh "clang++ -I /usr/X11/include #{t.source} -c -o #{t.name}"
end

file 'tests' => OBJ do
  sh "clang++ -F ./vendor vec3_test.cc -c -o vec3_test.o"
  sh "clang++ -F ./vendor -framework gtest " + LIB +
    " -o tests vec3_test.o " + (OBJ - ['main.o']).join(" ")
end

task :default => OBJ
task :test => 'tests'