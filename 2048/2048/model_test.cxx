#include "model.hxx"
#include <catch.hxx>

TEST_CASE("Win the Game")
{

    /// Checks if game is won when 2048 tile appears
    Model m(4);

    Tile t(2048, false);
    m.placeTile({0, 0}, t);
    m.updateGameState();

    CHECK(m.get_state() == State::won);
}

TEST_CASE("Tiles Do not merge")
{

    /// Checks if tiles with different values do not merge
    Model m(4);

    m.placeTile({0,0}, Tile(2, false));
    m.placeTile({0,1}, Tile(4, false));

    m.up_move();
    CHECK(m.get_board_at({0,0}).value == 2);
    CHECK(m.get_board_at({0,1}).value == 4);

}


TEST_CASE("Game Over")
{
    /// Checks if game ends with a full grid with no moves to be made
    Model m(4);

    m.placeTile({0, 0}, Tile(2, false));
    m.placeTile({0,1}, Tile(8, false));
    m.placeTile({0, 2}, Tile(16, false));
    m.placeTile({0, 3}, Tile(32,false));
    m.placeTile({1, 0}, Tile(4,false));
    m.placeTile({2, 0}, Tile(8, false));
    m.placeTile({3, 0}, Tile(16, false));
    m.placeTile({1, 1}, Tile(128, false));
    m.placeTile({1, 2}, Tile(256, false));
    m.placeTile({1, 3}, Tile(512, false));
    m.placeTile({2, 1}, Tile(1024, false));
    m.placeTile({2, 2}, Tile(2, false));
    m.placeTile({2, 3}, Tile(64, false));
    m.placeTile({3, 1}, Tile(128, false));
    m.placeTile({3, 2}, Tile(4, false));
    m.placeTile({3, 3}, Tile(1024, false));

    m.updateGameState();
    CHECK(m.get_state() == State::lost);
}


TEST_CASE("Combine Tiles")
{
    /// Checks if tiles are successfully merged
    Model m(4);

    m.placeTile({0,0}, Tile(2, false));
    m.placeTile({1,0}, Tile(2, false));

    m.left_move();
    CHECK(m.get_board_at({0, 0}).value == 4);
}

TEST_CASE("Is score count accurate?")
{

    /// Evaluates if score count is accurate on screen
    Model m(4);
    CHECK(m.get_score() == 0);

    m.placeTile({0,0}, Tile(16, false));
    m.placeTile({0,1}, Tile(16, false));

    CHECK(m.get_score() == 0);

    m.up_move();

    CHECK(m.get_score() == 32);

    m.placeTile({2,2}, Tile(32, false));
    m.placeTile({2,3}, Tile(32, false));

    CHECK(m.get_score() == 32);

    m.down_move();
    CHECK(m.get_score() == 96);

}