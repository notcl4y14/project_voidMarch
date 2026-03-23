#pragma once
#include <raylib.h>
#include <functional>
#include <cstdint>
namespace ui{

class Button{
    public:
        using Action = std::function<void()>;
        enum class DisplayDependency : std::uint8_t { None, OnHover, OnClick };
        enum class AlignmentX : std::uint8_t { None, Left, Right, Center };
        enum class AlignmentY : std::uint8_t { None, Top, Bottom, Center };

        // You know, some functions just don't need to be initializers for ALL properties
        // just do the external stuff after creating it :sob:
        Button(Vector2 pos, Texture2D tex, Action onClick = nullptr, std::string name = {}, ui::Button::DisplayDependency dependency = ui::Button::DisplayDependency::None, std::string targetName = {})
            : tex(tex)
            , onClick(std::move(onClick))
            , name(name)
            , DependencyType(dependency)
            , targetName(targetName)
        {
            bounds = Rectangle {
                pos.x,
                pos.y,
                (float) tex.width/3,
                (float) tex.height
            };
        }

        // You can either call it each tick or only when
        // the window resizes
        void applyAlignment() {
            int windowWidth = GetScreenWidth();
            int windowHeight = GetScreenHeight();

            // Alignment at X-axis
            switch (alignmentX) {
                case AlignmentX::None:
                // Comment the next `case AlignmentX::Left` and enable this one
                // to see a cool effect lmao
                // case AlignmentX::Left:
                    break;

                case AlignmentX::Left:
                    bounds.x = 0;
                    break;

                case AlignmentX::Right:
                    // Places it at the right side of the window...
                    // ...The right side of its rectangle at least,
                    // because the X, Y position is at the top-left corner
                    // of its rectangle, and putting that instead would make the
                    // rest offscreen.
                    bounds.x = windowWidth - bounds.width;
                    break;

                case AlignmentX::Center:
                    bounds.x = ((float) windowWidth / 2) - (bounds.width / 2);
                    break;
            }

            // Alignment at Y-axis
            switch (alignmentY) {
                case AlignmentY::None:
                // Comment the next `case AlignmentX::Top` and enable this one
                // to see a cool effect lmao
                // case AlignmentY::Top:
                    break;

                case AlignmentY::Top:
                    bounds.y = 0;
                    break;

                case AlignmentY::Bottom:
                    // Same stuff but for Y-axis
                    bounds.y = windowHeight - bounds.height;
                    break;

                case AlignmentY::Center:
                    bounds.y = ((float) windowHeight / 2) - (bounds.height / 2);
                    break;
            }

            // Applying offset alignment, unless set to None
            if (alignmentX != AlignmentX::None) {
                bounds.x += alignmentOffsetX;
            }

            if (alignmentY != AlignmentY::None) {
                bounds.y += alignmentOffsetY;
            }
        }

        void update(Vector2 mouse){
            bool inside = CheckCollisionPointRec(mouse, bounds);

            if(!inside) state = State::Idle;
            else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) state = State::Pressed;
            else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && state == State::Pressed){
                state = State::Clicked;
                if(toggled) toggled = false;
                else toggled = true;
                if(onClick) onClick();
            }
            else state = State::Hover;
        }

        void draw() const{
            float frameW = bounds.width;
            float srcX = 0.0f;
            switch(state){
                case State::Idle:    srcX = 0.0f;           break;
                case State::Hover:   srcX = frameW;         break;
                case State::Pressed:
                case State::Clicked: srcX = frameW * 2.0f;  break;
            }

            // Draw the texture instead, which, for some reason,
            // presents a rectangular button with a fixed size that
            // does not match the actual bounds of the button used with it.
            // --
            // Rectangle src { srcX, 0.0f, frameW, bounds.height };
            // Vector2   dst { bounds.x, bounds.y };
            // DrawTextureRec(tex, src, dst, WHITE);

            // Draw the rectangular area with bounds' size.
            // --
            DrawRectangleRec(bounds, BLUE);

            // Draw text. Oh really?
            // --
            DrawText(label.c_str(), bounds.x, bounds.y, 16, WHITE);
        }

        void drawOutline() const{
            DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, RED);
        }

        DisplayDependency DependencyType = DisplayDependency::None;
        std::string name;
        std::string targetName; // Used for checking when to update when set to custom dependency.
        std::string label; // Used for label, text on button
        enum class State : std::uint8_t {Idle, Hover, Pressed, Clicked};
        State state = State::Idle;
        bool toggled = false;

        // Alignment for both axes
        AlignmentX alignmentX = AlignmentX::None;
        AlignmentY alignmentY = AlignmentY::None;
        // Offset applied to the finalized aligned positions,
        // won't work if the alignment for the axis is None.
        float alignmentOffsetX = 0.0f;
        float alignmentOffsetY = 0.0f;

    private:
        Rectangle bounds;
        Texture2D tex;
        Action onClick;
};


} // Namespace ends here
