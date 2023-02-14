#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{}

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_)
{}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key)
{
    if(key == ge211::Key::down())
    {
        model_.down_move();
        return;
    }
    if(key == ge211::Key::up())
    {
        model_.up_move();
        return;
    }
    if(key == ge211::Key::left())
    {
        model_.left_move();
        return;
    }
    if(key == ge211::Key::right())
    {
        model_.right_move();
        return;
    }
    else
    {
        return;
    }

}


View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}




