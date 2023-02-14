#pragma once

#include "board.hxx"

#include <ge211.hxx>

#include <iostream>
#include <vector>

//State of the game - Over and Won, Over and Lost, Not over
enum class State
{
    progress,
    won,
    lost,
};


// Represents the state of the 2048 game.
class Model
{
public:

    ///
    using Rectangle = Board::Rectangle;

    /// Model positions will use `int` coordinates, as board positions do.
    using Position = Board::Position;

    /// Model Map will be a map of Positions to Tiles, as in board
    using Map = Board::Map;


    /// Constructs a model with `size` as both its width and height.
    /// Defaults to the classic 4x4 model
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if `size` is less than 2
    ///    or greater than 8.
    explicit Model(int size = 4);


    /// Constructs a model with the given width and height.
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if either dimension is less
    ///    than 2 or greater than 8.
    Model(int width, int height);

    Rectangle board() const;

    Tile get_board_at(Position p) const { return board_.tiles_.at(p); };
    int get_score() {return score_; };

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif


    /// Given a vector of positions, selects one at random
    /// Helper function for generateTile()
    Position randomspot(std::vector<Position> const &v);


    ///Given two adjacent tiles and a successful-move tracker 'sm'
    ///Executes the necessary action (combine, slide, or nothing) on the tiles
    ///SM is incremented whenever a combine or slide happens
    ///Helper function for the 4 move functions
    ///realSM tracks similarly to sm, but is not reset on each iteration over
    /// the column. It is used as a condition to determine whether
    /// generateTile will run
    void playmove(Tile& currtile, Tile& comptile, int& sm, bool& realSM);


    ///Updates the game state based on a set of conditions. Called after
    /// every move.
    void updateGameState();


    ///Each of these is called upon the respective key press. In order:
    /// - Sets all tiles' 'combined' values to false as a baseline
    /// - Runs a for loop that iterates across columns (down, up) or rows
    /// (left,right)
    /// - Runs a while loop on condition that successful moves 'sm' is not 0
    /// (sm is initialized to 1 outside the loop for the sake of the first
    /// iteration)
    /// - In current column/row, iterates from 2nd tile from side facing key
    /// press up to opposite side (E.g. , down_move will start at the 2nd to
    /// bottom row and move upwards. We need only start at the 2nd to last
    /// row since each tile is being compared to the one below it in this case.
    /// - Compares each tile to the one below it, calling playmove to execute
    /// appropriate move
    /// - As long as the previous iteration carried out at least one move,
    /// iterates up the column again. This while-loop structure is necessary
    /// as some more complicated moves (eg a tile moving across two blank
    /// spaces or two tiles moving concurrently) won't be carried out
    /// correctly in only one iteration
    /// - After an iteration in which no slides or combines happen (eg 'sm'
    /// remains at 0, the while loop breaks and we move on to the next column
    /// - After all columns have been appropriately manipulated, the move is
    /// complete and a random empty space generates a tile of value 2 or 4
    /// (That is, if any successful move occurred)

    void down_move();

    void up_move();

    void left_move();

    void right_move();


    /// Places a new tile at a given position

    void placeTile(Position p, Tile t);

    State get_state() { return state_; }

private:

    /// The game score. Every time a tile is combined, the resultant value is
    /// added to this
    int score_ = 0;

    ///The board itself
    Board board_;

    ///The state of the game - won, lost, or in progress
    State state_ = State::progress;


    /// Generates an empty tile map with given dimensions
    Map generatemap(int width, int height);


    /// Checks if there are any empty spaces on the board. If so, adds a tile
    /// one of these spaces at random with value either 2 or 4. If not,
    /// without doing anything
    void generateTile();





    ///View is given access to directly read board data and the score
    friend class View;

};

