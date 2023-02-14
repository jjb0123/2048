#include "board.hxx"


using namespace ge211;


Tile::Tile(int value, bool combined)
        : value(value),
          combined(combined)
{ }


Board::Board(Dimensions dims, Map tiles)
        : dims_(dims),
          tiles_(tiles)
{
    if (dims_.width < coordmin || dims_.height < coordmin) {
        throw Client_logic_error("Board::Board: dims too small");
    }

    if (dims_.width > coordmax ||
        dims_.height > coordmax) {
        throw Client_logic_error("Board::Board: dims too large");
    }
}


Board::Dimensions
Board::dimensions() const
{
    return dims_;
}


bool
Board::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}


std::vector<Board::Dimensions>
Board::build_directions()
{
    std::vector<Board::Dimensions> result;

    result.push_back({-1, 0});
    result.push_back({1, 0});
    result.push_back({0, -1});
    result.push_back({0, 1});

    return result;
}


std::vector<Board::Dimensions> const&
Board::all_directions()
{
    static std::vector<Dimensions> result = build_directions();
    return result;
}

Board::Rectangle
Board::boardRectangle() const
{
    return Rectangle::from_top_left(the_origin, dims_);
}

