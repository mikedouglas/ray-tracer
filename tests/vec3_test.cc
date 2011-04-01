#include "constants.h"
#include "vec3.h"
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

TEST(image, empty_write) {
  Image img(250, 250);
  img.write_png("test.png");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
