/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2020 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_RADIO_BUTTON_HPP
#define TGUI_RADIO_BUTTON_HPP


#include <TGUI/Renderers/RadioButtonRenderer.hpp>
#include <TGUI/Widgets/ClickableWidget.hpp>
#include <TGUI/Text.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Radio button widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API RadioButton : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<RadioButton> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const RadioButton> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new radio button widget
        ///
        /// @return The new radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static RadioButton::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another radio button
        ///
        /// @param radioButton  The other radio button
        ///
        /// @return The new radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static RadioButton::Ptr copy(RadioButton::ConstPtr radioButton);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButtonRenderer* getSharedRenderer();
        const RadioButtonRenderer* getSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButtonRenderer* getRenderer();
        const RadioButtonRenderer* getRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the radio button
        ///
        /// @param size  The new size of the radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the full size of the radio button
        ///
        /// @return Full size of the radio button
        ///
        /// The returned size includes the text next to the radio button.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the position where the widget is drawn and where the widget is placed
        ///
        /// This function returns (0,0) is the height of the text next to the radio button is less than the radio button height.
        /// Otherwise (0, -offset) will be returned where the offset is the distance between the top of the text and the top
        /// of the radio button.
        ///
        /// @return Offset of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getWidgetOffset() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks or unchecks the radio button
        /// @param checked  Should the radio button be checked?
        ///
        /// If the radio button is checked, it will tell its parent to uncheck all the other radio buttons.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setChecked(bool checked);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the radio button is checked or not
        /// @return Is the radio button checked?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isChecked() const
        {
            return m_checked;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the radio button
        ///
        /// @param text  The new text to draw next to the radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text of the radio button
        ///
        /// @return The text that is drawn next to the radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::String& getText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text
        ///
        /// @param size  The new text size.
        ///              When the size is set to 0 then the text is auto-sized
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text
        ///
        /// @return Character size of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Allows (or disallows) the radio button to be checked by clicking on the text next to it
        ///
        /// @param acceptTextClick  Will clicking on the text trigger a checked event?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextClickable(bool acceptTextClick);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the radio button can be checked by clicking on the text next to it
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isTextClickable() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keyPressed(const sf::Event::KeyEvent& event) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Signal& getSignal(std::string signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the mouse enters the widget. If requested, a callback will be send.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseEnteredWidget() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the mouse leaves the widget. If requested, a callback will be send.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseLeftWidget() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the check color that is being used in the current state
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const Color& getCurrentCheckColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the background color that is being used in the current state
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const Color& getCurrentBackgroundColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the border color that is being used in the current state
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const Color& getCurrentBorderColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Resets the sizes of the textures if they are used
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void updateTextureSizes();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the text color of the label depending on the current state
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTextColor();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<RadioButton>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalBool onCheck   = {"Checked"};   ///< Radio button was checked. Optional parameter: bool which is always true
        SignalBool onUncheck = {"Unchecked"}; ///< Radio button was unchecked. Optional parameter: bool which is always false
        SignalBool onChange  = {"Changed"};   ///< Radio button was checked or unchecked. Optional parameter: bool indicating whether it is checked


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // This is the checked flag. When the radio button is checked then this variable will be true.
        bool m_checked = false;

        // When this boolean is true (default) then the radio button will also be checked by clicking on the text.
        bool m_allowTextClick = true;

        // This will contain the text that is written next to radio button.
        Text m_text;

        Sprite m_spriteUnchecked;
        Sprite m_spriteChecked;
        Sprite m_spriteUncheckedHover;
        Sprite m_spriteCheckedHover;
        Sprite m_spriteUncheckedDisabled;
        Sprite m_spriteCheckedDisabled;
        Sprite m_spriteUncheckedFocused;
        Sprite m_spriteCheckedFocused;

        // Cached renderer properties
        Borders   m_bordersCached;
        TextStyle m_textStyleCached;
        TextStyle m_textStyleCheckedCached;
        Color     m_checkColorCached;
        Color     m_checkColorHoverCached;
        Color     m_checkColorDisabledCached;
        Color     m_borderColorCached;
        Color     m_borderColorHoverCached;
        Color     m_borderColorDisabledCached;
        Color     m_borderColorFocusedCached;
        Color     m_borderColorCheckedCached;
        Color     m_borderColorCheckedHoverCached;
        Color     m_borderColorCheckedDisabledCached;
        Color     m_borderColorCheckedFocusedCached;
        Color     m_backgroundColorCached;
        Color     m_backgroundColorHoverCached;
        Color     m_backgroundColorDisabledCached;
        Color     m_backgroundColorCheckedCached;
        Color     m_backgroundColorCheckedHoverCached;
        Color     m_backgroundColorCheckedDisabledCached;
        float     m_textDistanceRatioCached = 0.2f;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_RADIO_BUTTON_HPP
