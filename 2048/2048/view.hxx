#pragma once

#include "model.hxx"

class View
{
public:

    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    Position board_to_screen(Model::Position board_pos) const;

    ///Updates the 'score' Text sprite to match the model score
    void updateScore();

private:

    Model const& model_;


    ///Square sprites for each possible tile value, including empty tiles
    ge211::Rectangle_sprite const square_empty;
    ge211::Rectangle_sprite const square_two;
    ge211::Rectangle_sprite const square_four;
    ge211::Rectangle_sprite const square_eight;
    ge211::Rectangle_sprite const square_sixteen;
    ge211::Rectangle_sprite const square_thirtytwo;
    ge211::Rectangle_sprite const square_sixtyfour;
    ge211::Rectangle_sprite const square_onetwentyeight;
    ge211::Rectangle_sprite const square_twofiftysix;
    ge211::Rectangle_sprite const square_fivetwelve;
    ge211::Rectangle_sprite const square_tentwentyfour;
    ge211::Rectangle_sprite const square_twentyfortyeight;

    ///Basic sans-serif font and size
    ge211::Font gamefont;

    ///Text sprites to be overlaid on the tiles for each corresponding value
    ge211::Text_sprite const twoS;
    ge211::Text_sprite const fourS;
    ge211::Text_sprite const eightS;
    ge211::Text_sprite const sixteenS;
    ge211::Text_sprite const thirtytwoS;
    ge211::Text_sprite const sixtyfourS;
    ge211::Text_sprite const onetwentyeightS;
    ge211::Text_sprite const twofiftysixS;
    ge211::Text_sprite const fivetwelveS;
    ge211::Text_sprite const tentwentyfourS;
    ge211::Text_sprite const twentyfortyeightS;

    ///Messages for score, win condition, and loss condition
    ge211::Text_sprite score;
    ge211::Text_sprite win;
    ge211::Text_sprite loss;

};



