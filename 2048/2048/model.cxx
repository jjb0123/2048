#include "model.hxx"


using namespace ge211;


Model::Model(int size)
        : Model(size, size)
{}


Model::Model(int width, int height)
        : board_({width, height},
                 generatemap(width, height))
{generateTile();}


Model::Rectangle
Model::board() const
{
    return board_.boardRectangle();
}


Model::Map
Model::generatemap(int width, int height)
{
    Board::Map tilesmap;

    int i,j;
    for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
        {
            Board::Position posn = {i,j};
            tilesmap.insert({posn,Tile(0,true)});
        }
    }

    return tilesmap;
}


void
Model::generateTile()
{
    std::vector<Position> emptytiles;

    for(auto tile : board_.tiles_)
    {
        if(tile.second.value == 0)
        {
            emptytiles.push_back(tile.first);
        }
    }

    if (emptytiles.empty())
    {
        return;
    }
    else {
        Position randomPos = randomspot(emptytiles);
        Tile& newTile = board_.tiles_.at(randomPos);
        ge211::Random_source<int> ntv(1, 2);
        int newVal = ntv.next();
        newTile.value = (2 * newVal);
    }
}

void Model::placeTile(ge211::Posn<int> p, Tile t)
{
    board_.tiles_.at(p) = t;

}
///Code for selecting a random element of a map sourced from
/// https://www.techiedelight.com/get-random-value-stl-containers-cpp/
Model::Position
Model::randomspot(std::vector<Board::Position> const &v)
{
    auto it = v.cbegin();
    int random = rand() % v.size();
    std::advance(it,random);

    return *it;
}


void
Model::playmove(Tile& currtile, Tile& comptile, int& sm, bool& realSM)
{
    if (currtile.value != 0 && comptile.value == 0)
    {
        comptile.value = currtile.value;
        currtile.value = 0;
        sm = 1;
        realSM = true;
    }

    if (currtile.value != 0 &&
        comptile.value != 0 &&
        currtile.value == comptile.value &&
        !currtile.combined && !comptile.combined)
    {
        comptile.value *= 2;
        comptile.combined = true;
        currtile.value = 0;
        sm = 1;
        realSM=true;
        score_ += comptile.value;
    }
}


void
Model::updateGameState()
{
    /// Note: the three separate for loops here look somewhat messy, but this
    /// structure eliminates some edge case bugs in the logic as opposed to a
    /// larger encompassing for loop


    //First checks if any 2048-valued tile is present on the board. If so,
    // the game is won regardless of other conditions
    for(auto wintile : board_.tiles_) {

        if (wintile.second.value == 2048)

        {
            state_ = State::won;
            return;
        }

    //Provided no 2048 tile was found, checks if any empty spaces (aka
    // 0-valued tiles) are present. If so, there is an available move there
    // and the game is in progress still
    for(auto tile : board_.tiles_)
    {
        if (tile.second.value == 0)
        {
            state_ = State::progress;

            return;
        }
    }


    // Provided neither of the above conditions is met, we will iterate
    // over every tile on the board and check the 4 tiles bordering it
    // (out of bounds positions for edge tiles are ignored)
    // if we find anywhere that two bordering tiles share the same value,
    // a combine-move is possible and the game is not over
    for(auto tile : board_.tiles_)
    {
        for (auto dir: board_.all_directions()) {
            Position comp {(tile.first.x + dir.width),
                           (tile.first.y + dir.height)};

            if (!board_.good_position(comp)) {
                continue;
            }

            if (tile.second.value == board_.tiles_.at(comp).value) {
                state_ = State::progress;
                return;
            }

        }
    }

    //If no above conditions have been met (all spaces are filled, no
    // 2048 tile is present, and no combines are possible), the game is lost
    state_ = State::lost;
    return;

    }
}
/// Function to Alter the Board


/// The move functions here appear rather bulky haven been each written
/// individually, but due to the fact that the directions are rather deeply
/// integrated into the for-loop structures, further abstraction into helpers
/// would have been difficult
void
Model::down_move()
{
    for(auto& tile : board_.tiles_)
    {
        tile.second.combined = false;
    }

    int i;
    bool realSM = false;
    for(i=0;i<board_.dimensions().width;i++)
    {
        int sm = 1;
        while(sm != 0)
        {
            sm = 0;
            int k;
            for (k = (board_.dimensions().height - 2); k>=0; k--)
            {
                Tile& currtile = board_.tiles_.at({i,k});
                Tile& comptile = board_.tiles_.at({i,k+1});

                playmove(currtile,comptile,sm, realSM);
            }
        }
    }
    if(realSM)
    {
        generateTile();
    }
    updateGameState();
}


void
Model::up_move()
{
    for(auto& tile : board_.tiles_)
    {
        tile.second.combined = false;
    }

    int i;
    bool realSM = false;
    for(i=0;i<board_.dimensions().width;i++)
    {
        int sm = 1;
        while(sm != 0)
        {
            sm = 0;
            int k;
            for (k = 1; k<board_.dimensions().height; k++)
            {
                Tile& currtile = board_.tiles_.at({i,k});
                Tile& comptile = board_.tiles_.at({i,k-1});

                playmove(currtile,comptile,sm,realSM);
            }
        }
    }
    if(realSM)
    {
        generateTile();
    }
    updateGameState();
}


void
Model::left_move()
{
    for(auto& tile : board_.tiles_)
    {
        tile.second.combined = false;
    }

    int i;
    bool realSM = false;
    for(i=0;i<board_.dimensions().height;i++)
    {
        int sm = 1;
        while(sm != 0)
        {
            sm = 0;
            int k;
            for (k = 1; k<board_.dimensions().height; k++)
            {
                Tile& currtile = board_.tiles_.at({k,i});
                Tile& comptile = board_.tiles_.at({k-1,i});

                playmove(currtile,comptile,sm,realSM);
            }
        }
    }
    if(realSM)
    {
        generateTile();
    }
    updateGameState();
}


void
Model::right_move()
{
    for(auto& tile : board_.tiles_)
    {
        tile.second.combined = false;
    }

    int i;
    bool realSM = false;
    for(i=0;i<board_.dimensions().height;i++)
    {
        int sm = 1;
        while(sm != 0)
        {
            sm = 0;
            int k;
            for (k = (board_.dimensions().width - 2); k>=0; k--)
            {
                Tile& currtile = board_.tiles_.at({k,i});
                Tile& comptile = board_.tiles_.at({k+1,i});

                playmove(currtile,comptile,sm,realSM);
            }
        }
    }
    if(realSM)
    {
        generateTile();
    }
    updateGameState();
}

