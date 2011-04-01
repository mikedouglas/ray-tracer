require 'rake/clean'

CLEAN.include('src/*.o')
CLEAN.include('bin/tests')
CLEAN.include('test.png')

TESTS = FileList['tests/*_test.cc']
SRC = FileList['src/*.cc']
HDRS = FileList['*.h']
T_OBJ = TESTS.ext('o')
OBJ = SRC.ext('o')
LIB = "-L /usr/X11/lib -L vendor -lpng"

rule '.o' => ['.cc'] do |t|
  sh "clang++ -F ./vendor -I /usr/X11/include #{t.source} -I ./src -c -o #{t.name}"
end

file 'tests' => OBJ + T_OBJ do
  sh "clang++ -F ./vendor -framework gtest " + LIB +
    " -o bin/tests " + (OBJ + T_OBJ - ['src/main.o']).join(" ")
end

task :default => OBJ
task :test => 'tests'
