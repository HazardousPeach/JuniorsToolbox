#pragma once

#include <expected>
#include <filesystem>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "clone.hpp"
#include "fsystem.hpp"
#include "objlib/object.hpp"
#include "objlib/template.hpp"
#include "scene/scene.hpp"
#include "serial.hpp"
#include <imgui.h>
#include <imgui_internal.h>

namespace Toolbox::UI {

    class IWindow {
    protected:
        virtual void renderMenuBar()            = 0;
        virtual void renderBody(f32 delta_time) = 0;

    public:
        virtual ~IWindow() = default;

        [[nodiscard]] virtual std::string context() const = 0;
        [[nodiscard]] virtual std::string name() const    = 0;
        [[nodiscard]] virtual bool unsaved() const        = 0;

        // Returns the supported file type, or empty if designed for a folder.
        [[nodiscard]] virtual std::vector<std::string> extensions() const = 0;

        [[nodiscard]] virtual bool loadData(const std::filesystem::path &path) = 0;
        [[nodiscard]] virtual bool saveData(const std::filesystem::path &path) = 0;

        [[nodiscard]] virtual bool update(f32 delta_time) = 0;

        [[nodiscard]] virtual std::string title() const = 0;

        virtual void render(f32 delta_time) = 0;
    };

    class SimpleWindow : public IWindow {
    protected:
        void renderMenuBar() override {}
        void renderBody(f32 delta_time) override {}

    public:
        SimpleWindow() = default;
        ~SimpleWindow() override = default;

        void open() { m_is_open = true; }

        [[nodiscard]] std::string context() const override { return "(OVERRIDE THIS)"; }
        [[nodiscard]] std::string name() const override { return "Base Window"; }
        [[nodiscard]] bool unsaved() const override { return false; }

        // Returns the supported file type, or empty if designed for a folder.
        [[nodiscard]] std::vector<std::string> extensions() const override { return {}; }

        [[nodiscard]] bool loadData(const std::filesystem::path &path) override { return false; }
        [[nodiscard]] bool saveData(const std::filesystem::path &path) override { return false; }

        [[nodiscard]] bool update(f32 delta_time) override { return true; }

        [[nodiscard]] std::string title() const override {
            std::string t = std::format("{} - {}", name(), context());
            if (unsaved())
                t += " (*)";
            return t;
        }

        void render(f32 delta_time) override final {
            const ImGuiViewport *mainViewport = ImGui::GetMainViewport();

            ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_PassthruCentralNode |
                                           ImGuiDockNodeFlags_AutoHideTabBar |
                                           ImGuiDockNodeFlags_NoDockingInCentralNode;

            ImGui::Begin(title().c_str(), &m_is_open, m_flags);
            {
                renderMenuBar();
                renderBody(delta_time);
            }
            ImGui::End();
        }

    private:
        ImGuiID m_window_id;

        bool m_is_open           = false;
        ImGuiWindowFlags m_flags = 0;

        bool m_is_docking_set_up = false;
    };

    class DockWindow : public IWindow {
    protected:
        virtual void buildDockspace(ImGuiID dockspace_id){};

        void renderDockspace();
        void renderMenuBar() override {}
        void renderBody(f32 delta_time) override {}

    public:
        DockWindow()           = default;
        ~DockWindow() override = default;

        void open() { m_is_open = true; }

        [[nodiscard]] std::string context() const override { return "(OVERRIDE THIS)"; }
        [[nodiscard]] std::string name() const override { return "Base Window"; }
        [[nodiscard]] bool unsaved() const override { return false; }

        // Returns the supported file type, or empty if designed for a folder.
        [[nodiscard]] std::vector<std::string> extensions() const override { return {}; }

        [[nodiscard]] bool loadData(const std::filesystem::path &path) override { return false; }
        [[nodiscard]] bool saveData(const std::filesystem::path &path) override { return false; }

        [[nodiscard]] bool update(f32 delta_time) override { return true; }

        [[nodiscard]] std::string title() const override {
            std::string t = std::format("{} - {}", name(), context());
            if (unsaved())
                t += " (*)";
            return t;
        }

        void render(f32 delta_time) override final {
            const ImGuiViewport *mainViewport = ImGui::GetMainViewport();

            ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_PassthruCentralNode |
                                           ImGuiDockNodeFlags_AutoHideTabBar |
                                           ImGuiDockNodeFlags_NoDockingInCentralNode;

            ImGui::Begin(title().c_str(), &m_is_open, m_flags);
            {
                renderDockspace();
                renderMenuBar();
                renderBody(delta_time);
            }
            ImGui::End();
        }

    private:
        ImGuiID m_window_id = {};

        bool m_is_open           = false;
        ImGuiWindowFlags m_flags = 0;

        bool m_is_docking_set_up = false;
    };

    inline std::string getWindowUID(const IWindow &window) {
        return window.title(); }

    inline std::string getWindowChildUID(const IWindow &window, const std::string &child_name) {
        return getWindowUID(window) + "###" + child_name;
    }

}  // namespace Toolbox::UI