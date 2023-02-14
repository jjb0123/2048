#include "view.hxx"

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;
using Dimensions = ge211::Dims<int>;

// Color constants
const int grid_size = 200;
const int margin = 10;
const Dimensions squaredims = {grid_size-margin,grid_size-margin};

static Color const twosquarecolor{224, 224, 224};
static Color const foursquarecolor{255, 204, 204};
static Color const eightsquarecolor{255, 102, 102};
static Color const sixteensquarecolor{255, 51, 51};
static Color const thirtytwosquarecolor{253,153,51};
static Color const sixtyfoursquarecolor{255,128,0};
static Color const onetwentyeightsquarecolor{255,255,102};
static Color const twofiftysixsquarecolor{255,255,0};
static Color const fivetwelvesquarecolor{204, 255, 153};
static Color const tentwentyfoursquarecolor{178, 255, 102};
static Color const twentyfortyeightsquarecolor{128,255,0};

static Color const gridsquarecolor{100,100,100};

View::View(Model const& model)
        : model_(model),
          square_empty(squaredims, gridsquarecolor),
          square_two(squaredims, twosquarecolor),
          square_four(squaredims, foursquarecolor),
          square_eight(squaredims,eightsquarecolor),
          square_sixteen(squaredims, sixteensquarecolor),
          square_thirtytwo(squaredims, thirtytwosquarecolor),
          square_sixtyfour(squaredims,sixtyfoursquarecolor),
          square_onetwentyeight(squaredims, onetwentyeightsquarecolor),
          square_twofiftysix(squaredims, twofiftysixsquarecolor),
          square_fivetwelve(squaredims, fivetwelvesquarecolor),
          square_tentwentyfour(squaredims, tentwentyfoursquarecolor),
          square_twentyfortyeight(squaredims, twentyfortyeightsquarecolor),

          gamefont("sans.ttf", (grid_size / 4)),

          twoS("2", gamefont),
          fourS("4", gamefont),
          eightS("8", gamefont),
          sixteenS("16", gamefont),
          thirtytwoS("32", gamefont),
          sixtyfourS("64", gamefont),
          onetwentyeightS("128", gamefont),
          twofiftysixS("256", gamefont),
          fivetwelveS("512", gamefont),
          tentwentyfourS("1024", gamefont),
          twentyfortyeightS("2048", gamefont),

          score("0", gamefont),
          win("You Win!", gamefont),
          loss("Game Over", gamefont)

          {}


// Dimensions will be of type int
using Dimensions = ge211::Dims<int>;
// Position will be of type int
using Position = ge211::Posn<int>;
// A square will be initialised, with size of type int
using Rectangle = ge211::Rect<int>;

void
View::draw(ge211::Sprite_set& set)
{

    int hpos;
    int vpos;

    for(hpos = 0; hpos < model_.board().width; hpos++)
    {
        for(vpos = 0; vpos < model_.board().width;vpos++)
        {
            ///The switch block draws the appropriate square and text in
            /// every board position each frame
            switch (model_.board_.tiles_.at({hpos,vpos}).value)
            {
            case 0:
                set.add_sprite(square_empty,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                break;
            case 2:
                set.add_sprite(square_two,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(twoS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 4:
                set.add_sprite(square_four,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(fourS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 8:
                set.add_sprite(square_eight,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(eightS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 16:
                set.add_sprite(square_sixteen,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(sixteenS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 32:
                set.add_sprite(square_thirtytwo,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(thirtytwoS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 64:
                set.add_sprite(square_sixtyfour,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(sixtyfourS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 128:
                set.add_sprite(square_onetwentyeight,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(onetwentyeightS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 256:
                set.add_sprite(square_twofiftysix,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(twofiftysixS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 512:
                set.add_sprite(square_fivetwelve,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(fivetwelveS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 1024:
                set.add_sprite(square_tentwentyfour,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(tentwentyfourS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;
            case 2048:
                set.add_sprite(square_twentyfortyeight,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 1);
                set.add_sprite(twentyfortyeightS,
                               {board_to_screen({hpos,vpos, }).x + 5,
                                board_to_screen({hpos,vpos}).y + 5}, 2);
                break;

            }
        }
    }

    updateScore();
    set.add_sprite(score,
                   {grid_size * model_.board().dimensions().width * 4/3,
                    grid_size * model_.board().dimensions().height / 4},
                   1);

    if(model_.state_ == State::won)
    {
        set.add_sprite(win,
                       {grid_size * model_.board().dimensions().width * 4/3,
                        (grid_size * model_.board().dimensions().height / 4)
                        + 100},
                       1);
    }
    if(model_.state_ == State::lost)
    {
        set.add_sprite(loss,
                       {grid_size * model_.board().dimensions().width * 4/3,
                        (grid_size * model_.board().dimensions().height / 4)
                        + 100},
                       1);
    }
}


View::Dimensions
View::initial_window_dimensions() const
{
    return {grid_size * model_.board().dimensions().width * 2,
    grid_size * model_.board().dimensions().height};
}


std::string
View::initial_window_title() const
{
    return "2048!";
}


View::Position
View::board_to_screen(Model::Position board_pos) const
{
    return {grid_size * board_pos.x, grid_size * board_pos.y};
}

void
View::updateScore()
{
    std::string s = "Score: " + (std::to_string(model_.score_));
    score = ge211::Text_sprite(s,gamefont);
}