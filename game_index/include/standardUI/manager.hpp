#pragma once
#include "button.hpp"
#include "ui_helpers.hpp"
#include <vector>
#include <utility>
#include <functional>
#include <type_traits>
namespace ui{

class Manager{
    public:
    // Sometimes, a long descriptive name is better than a short unclear name
    using ButtonDisplayDependency = Button::DisplayDependency;
    using ButtonState = Button::State;

        template<typename... Args>
        // Rectangle, idle tex, hover tex, pressed tex, onClick lambda.
        Button& emplaceButton(Args&&... args){
            return buttons.emplace_back(std::forward<Args>(args)...);
        }
        // This is to have text in buttons without making any "function not found" type
        // of errors from the other places that create the button WITHOUT text
        Button& placeButton(std::string text, Vector2 pos, Texture2D tex, std::function<void()> onClick = nullptr){
            Button button (pos, tex, onClick);
            button.label = text;
            return buttons.emplace_back(button);
        }

        // Lets you create and initialize your button first and then emplace it
        // via this function
        Button& addButton(const Button button) {
            return buttons.emplace_back(button);
        }

        void updateAll(Vector2 mouse){
            for(auto& b : buttons){
                b.applyAlignment();

                switch(b.DependencyType){
                    case ButtonDisplayDependency::OnHover:
                        for(const auto& p : buttons){
                            if(b.targetName == p.name && p.state == ButtonState::Hover || p.state == ButtonState::Pressed){
                                b.update(mouse);
                            }
                        }
                        break;

                    case ButtonDisplayDependency::OnClick:
                        for(const auto& p : buttons){
                            if(b.targetName == p.name && p.toggled){
                                b.update(mouse);
                            }
                        }
                        break;

                    default:
                        b.update(mouse);
                        break;
                }
            }
        }

        void drawAll() const{
            for(auto& b : buttons){
                switch(b.DependencyType){
                    case ButtonDisplayDependency::OnHover:
                        for(const auto& p : buttons){
                            if(b.targetName == p.name && p.state == ButtonState::Hover || p.state == ButtonState::Pressed){
                                b.draw();
                            }
                        }
                        break;
                    case ButtonDisplayDependency::OnClick:
                        for(const auto& p : buttons){
                            if(b.targetName == p.name && p.toggled){
                                b.draw();
                            }
                        }
                        break;
                    default: b.draw(); break;
                }
            }
        }

        // For more easily seing borders, great for debugging.
        void highlightOutlines() const{
            for(const auto& b : buttons) b.drawOutline();
        }

        void clearAll(){
            buttons.clear();
        }

        // Texture2D and func vector.
        UI_Helper& setupHelper(Texture2D background, std::function<void()> action = nullptr){
            Helper = UI_Helper{background, std::move(action)}; return Helper;
        }

        UI_Helper Helper;

    private:
        std::vector<Button> buttons;
};
} //Namespace ends here
