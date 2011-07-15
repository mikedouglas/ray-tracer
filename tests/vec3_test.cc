#include "scene.h"
#include "constants.h"
#include "vec3.h"
#include "shape.h"
#include "sphere.h"
#include "image.h"
#include <gtest/gtest.h>

TEST(vec3, equality) {
    ASSERT_TRUE(Vec3(1, 2, 3) == Vec3(1, 2, 3));
    ASSERT_TRUE(Vec3(1, 2, 3) != Vec3(2, 3, 4));
}

TEST(vec3, add) {
    Vec3 a(1, 2, 3);
    ASSERT_EQ(Vec3(2, 4, 6), a+a);
}

TEST(vec3, mult) {
    Vec3 a(1, 2, 3);
    ASSERT_EQ(Vec3(2, 4, 6), 2*a);
}

TEST(vec3, divide) {
    Vec3 a(2, 4, 6);
    ASSERT_EQ(Vec3(1, 2, 3), a/2);
}

TEST(vec3, dot) {
    Vec3 a(2, 4, 6);
    Vec3 b(3, 5, 7);
    ASSERT_EQ(2*3+4*5+6*7, dot(a,b));
}

TEST(vec3, cross) {
    Vec3 a(2, 4, 6);
    Vec3 b(3, 5, 7);
    ASSERT_EQ(Vec3(-2, 4, -2), cross(a,b));
}

TEST(sphere, normal) {
    Sphere a(NULL, 1, 0, 0, 0);
    ASSERT_EQ(Vec3(0, 1, 0), a.normal(Vec3(0, 1, 0)));
    Sphere b(NULL, 1, 1, 0, 0);
    ASSERT_EQ(Vec3(-1, 0, 0), b.normal(Vec3(0, 0, 0)));
}

TEST(sphere, intersect) {
  Ray straight_at(Point(0, 0, 0), Vector(1, 0, 0));
  Ray away_from(Point(0, 0, 0), Vector(-1, 0, 0));
  Sphere a(NULL, 1, 3, 0, 0);
  ASSERT_EQ(a.intersect(straight_at), 2);
  ASSERT_EQ(a.intersect(away_from), 0);
}

TEST(scene, intersect) {
  Ray towards(Point(0, 0, -1), Vector(0, 0, 1));
  Scene scene(Vector(0, 0, -1));
  Surface sur(Color(255,0,0), 0, 0, 0);
  Sphere a(&sur, 1, 0, 0, 1);
  ASSERT_EQ(scene.trace(towards), Color(0, 0, 0));
  scene.addShape(&a);
  ASSERT_EQ(scene.trace(towards), Color(255,0,0));
  Ray away(Point(0, 0, -1), Vector(0, 0, -1));
  ASSERT_EQ(scene.trace(away), Color(50, 50, 50));
}

TEST(image, empty_write) {
  Scene scene(Point(200, 200, 1000));
  Surface surr(Color(150,0,0), 8, 0.1, 0);
  Surface surb(Color(0, 0, 200), 5, 0.2, 0);
  Surface surb2(Color(0, 0, 200), 5, 0, 0.3);
  Surface surg(Color(0,200,0), 8, 0, 0);
  scene.addShape(new Sphere(&surr, 70, 90, 320, 100));
  scene.addShape(new Sphere(&surb2, 40, 320, 85, 85));
  scene.addShape(new Sphere(&surr, 80, 440, 120, 0));
  scene.addShape(new Sphere(&surg, 60, 360, 400, 50));
  Light l(Point(200,200,200), Color(255,219,88), 0.5);
  scene.addLight(&l);
  Image *img = scene.render();
  img->write_png("test.png");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
