#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

// The main game class for 2048
class Controller : public ge211::Abstract_game
{
public:

    // //Constructs a game with 4 as its width and height - default
    // Controller();

    //Constructs a game with size as its width and height
    Controller(int size = 4);

    //Constructs a game with the given dimensions
    Controller(int width, int height);


protected:

    ///Calls the appropriate move function for the arrow keys
    void on_key(ge211::Key key) override;

    // These three delegate to the view
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;


private:
    Model model_;
    View view_;
};
