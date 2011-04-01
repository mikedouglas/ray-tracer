require 'rake/clean'

CLEAN.include('src/*.o')
CLEAN.include('tests/*.o')
CLEAN.include('bin/tests')
CLEAN.include('test.png')

CC = "clang++"
TESTS = FileList['tests/*_test.cc']
SRC = FileList['src/*.cc']
HDRS = FileList['*.h']
T_OBJ = TESTS.ext('o')
OBJ = SRC.ext('o')
LIB = "-L /usr/X11/lib -L vendor -lpng"

rule '.o' => ['.cc'] do |t|
  sh CC + " -F ./vendor -I /usr/X11/include #{t.source} -I ./src -c -o #{t.name}"
end

file 'tests' => OBJ + T_OBJ do
  sh CC + " -F ./vendor -framework gtest " + LIB +
    " -o bin/tests " + (OBJ + T_OBJ - ['src/main.o']).join(" ")
end

file 'example' => OBJ do
  sh CC + " " + LIB + " -o bin/example " + OBJ.join(" ")
end

task :default => OBJ
task :test => 'tests'
