#pragma once

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

///Small struct that allows tiles to have a 'combined' value in addition to
/// their integer value, this allows us to prevent double combinations in the
/// same move
struct Tile
{
    int value;
    bool combined;

    explicit Tile(int value, bool combined);
};

const int coordmin = 2;
const int coordmax = 10;


/// Represents the state of the board. Has members 'dims_' (a standard
/// ge211::Dims<int> and 'tiles_' (an unordered map from ge211::Posn<int>'s
/// to Tile structs
class Board
{
public:

    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Board 'Map' will map Board::Positions to Tile structs
    using Map = std::unordered_map<Position, Tile>;

private:

    /// Dimensions is private - it need not be directly manipulated and can
    /// be returned by the below function dimensions() if needed
    Dimensions dims_;

public:

    /// The actual tiles map is made public as it will be accessed and altered
    /// directly by the model
    Map tiles_;

public:

    /// Constructs a board with the given dimensions.
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if either dimension is less
    ///    than 2 or greater than 8.
    explicit Board(Dimensions dims, Map tiles);


    /// Returns the same `Dimensions` value passed to the
    /// constructor.
    Dimensions dimensions() const;


    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;


    ///Builds the 4 necessary directions to be returned by all_directions()
    static std::vector<Board::Dimensions> build_directions();


    /// Returns a reference to a `std::vector` containing all 4 non-diagonal
    /// direction vectors
    static std::vector<Dimensions> const& all_directions();

    Board::Rectangle boardRectangle() const;


private:

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif
};