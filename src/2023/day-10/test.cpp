#include <gtest/gtest.h>
#include "./Day.cpp"

class TileConnectivityTest : public ::testing::Test {
 protected:
  Map dummyMap;  // Used just for passing a map reference

  TileConnectivityTest() {
    dummyMap.push_back(std::vector<Tile>(1, Tile('.', 0, 0)));  // Single '.' tile map
  }

  void testConnectivityToTop(char currentType, char topType, bool expected) {
    testRelativeConnectivity(currentType, topType, 0, -1, expected, "'" + std::string(1, currentType) + "' should " + (expected ? "" : "not ") + "connect to '" + topType + "' from Top");
  }

  void testConnectivityToRight(char currentType, char rightType, bool expected) {
    testRelativeConnectivity(currentType, rightType, 1, 0, expected, "'" + std::string(1, currentType) + "' should " + (expected ? "" : "not ") + "connect to '" + rightType + "' from Right");
  }

  void testConnectivityToBottom(char currentType, char bottomType, bool expected) {
    testRelativeConnectivity(currentType, bottomType, 0, 1, expected, "'" + std::string(1, currentType) + "' should " + (expected ? "" : "not ") + "connect to '" + bottomType + "' from Bottom");
  }

  void testConnectivityToLeft(char currentType, char leftType, bool expected) {
    testRelativeConnectivity(currentType, leftType, -1, 0, expected, "'" + std::string(1, currentType) + "' should " + (expected ? "" : "not ") + "connect to '" + leftType + "' from Left");
  }

  void testRelativeConnectivity(char primaryType, char secondaryType, int offsetX, int offsetY, bool expected, const std::string& message) {
    Tile primaryTile(primaryType, 1, 1);
    Tile secondaryTile(secondaryType, 1 + offsetY, 1 + offsetX);
    EXPECT_EQ(primaryTile.isConnectedTo(secondaryTile, dummyMap), expected) << message;
  }
};

TEST_F(TileConnectivityTest, TestVerticalPipeWithOtherTiles) {
  // Vertical pipe ('|') should connect to another vertical pipe ('|') from top and bottom
  testConnectivityToTop('|', '|', true);
  testConnectivityToBottom('|', '|', true);

  // Vertical pipe ('|') should connect to 'L' and 'J' from bottom
  testConnectivityToBottom('|', 'L', true);
  testConnectivityToBottom('|', 'J', true);

  // Vertical pipe ('|') should connect to '7' and 'F' from top
  testConnectivityToTop('|', '7', true);
  testConnectivityToTop('|', 'F', true);

  // Vertical pipe ('|') should not connect to horizontal pipe ('-') from any side
  testConnectivityToTop('|', '-', false);
  testConnectivityToBottom('|', '-', false);
  testConnectivityToLeft('|', '-', false);
  testConnectivityToRight('|', '-', false);

  // Vertical pipe ('|') should not connect to any pipe from left or right
  testConnectivityToLeft('|', '|', false);
  testConnectivityToRight('|', '|', false);
  testConnectivityToLeft('|', 'L', false);
  testConnectivityToRight('|', 'L', false);
  testConnectivityToLeft('|', 'J', false);
  testConnectivityToRight('|', 'J', false);
  testConnectivityToLeft('|', '7', false);
  testConnectivityToRight('|', '7', false);
  testConnectivityToLeft('|', 'F', false);
  testConnectivityToRight('|', 'F', false);
}
