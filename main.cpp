#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

int main() {
    using namespace nana;

    // Define the Nana form
    form fm;

    // Define a label to display the current state of the toggle button
    label label_state(fm);
    label_state.caption("Toggle Button State: OFF");
    label_state.format(true);

    // Define the toggle button
    button toggle_button(fm);
    toggle_button.caption("OFF");
    bool is_toggled = false;

    // Event handler for the toggle button
    toggle_button.events().click([&]() {
        is_toggled = !is_toggled;
        if (is_toggled) {
            toggle_button.caption("ON");
            label_state.caption("Toggle Button State: ON");
            toggle_button.bgcolor(colors::green);
        } else {
            toggle_button.caption("OFF");
            label_state.caption("Toggle Button State: OFF");
            toggle_button.bgcolor(colors::red);
        }
        fm.collocate();
    });

    // Layout the form
    fm.div("vert <><weight=30><><toggle_button><><weight=30><><label_state><>");
    fm["toggle_button"] << toggle_button;
    fm["label_state"] << label_state;
    fm.collocate();

    // Show the form
    fm.show();

    // Start the event loop
    exec();
}