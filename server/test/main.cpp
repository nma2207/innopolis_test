#include <gtest/gtest.h>
#include "numbersprocessor.h"

TEST(ServerTest, NoNumbersTest)
{
  NumbersProcessor processor;

  auto res = processor.process("apples bananas");
  EXPECT_EQ(res.first, "-1");
  EXPECT_EQ(res.second, "-1");

  res = processor.process("");
  EXPECT_EQ(res.first, "-1");
  EXPECT_EQ(res.second, "-1");

  res = processor.process("?.-[]");
  EXPECT_EQ(res.first, "-1");
  EXPECT_EQ(res.second, "-1");
}

TEST(ServerTest, OneNumberTest)
{
  NumbersProcessor processor;

  std::pair<std::string, std::string> res;

  res = processor.process("10");
  EXPECT_EQ(res.first, "10");
  EXPECT_EQ(res.second, "10");

  res = processor.process(" 2 ");
  EXPECT_EQ(res.first, "2");
  EXPECT_EQ(res.second, "2");

  res = processor.process("banana 3");
  EXPECT_EQ(res.first, "3");
  EXPECT_EQ(res.second, "3");

  res = processor.process("bana4na");
  EXPECT_EQ(res.first, "4");
  EXPECT_EQ(res.second, "4");
}

TEST(ServerTest, ManyNumberTest)
{
  NumbersProcessor processor;

  std::pair<std::string, std::string> res;

  res = processor.process("20 apples, 30 bananas, 15 peaches and 1 watermelon");
  EXPECT_EQ(res.first, "1 15 20 30");
  EXPECT_EQ(res.second, "66");

  res = processor.process("1 2");
  EXPECT_EQ(res.first, "1 2");
  EXPECT_EQ(res.second, "3");

  res = processor.process("1 0");
  EXPECT_EQ(res.first, "0 1");
  EXPECT_EQ(res.second, "1");
}
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}