#include "interface.hpp"

static void ShowExampleAppDockSpace(bool* p_open);
static void ShowExampleAppMainMenuBar();

UserInterface::UserInterface(MasterRenderer& t_master_renderer , sf::Clock& t_delta_clock)
                            : m_master_renderer(t_master_renderer),m_delta_clock(t_delta_clock){
    m_show_dock = true;
    m_color[0] = 0.0f;
    m_color[1] = 0.0f;
    m_color[2] = 0.0f;
}



void UserInterface::startInterface( ){
    //ImGui::CreateContext();
        ImGui::SFML::Update(*Display::m_window, m_delta_clock.restart() );
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
       // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport /
       // if(show_demo_window)
         //   ImGui::ShowDemoWindow(&show_demo_window);

        ShowExampleAppMainMenuBar();
        if(m_show_dock)
            ShowExampleAppDockSpace(&m_show_dock);

        ImGui::SetNextWindowDockId(1);
        ImGui::SetNextWindowSize(ImVec2(512,512), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Rendering");
        {   
           // std::cout << ImGui::GetWindowDockId() << std::endl;
            ImVec2 pos = ImGui::GetCursorScreenPos();
            auto tex = m_master_renderer.getTextureFBO();

            ImGui::GetWindowDrawList()->AddImage(
                (void*)tex, ImGui::GetCursorScreenPos(),
                ImVec2(ImGui::GetCursorScreenPos().x + 512, 
            ImGui::GetCursorScreenPos().y + 512),ImVec2(0,1), ImVec2(1,0));
        }
        ImGui::End();
        ImGui::SetNextWindowDockId(2);
        ImGui::Begin("Background Color");
        //std::cout << ImGui::GetWindowDockId() << std::endl;
        if (ImGui::ColorEdit3("Background color", m_color)) {
            // this code gets called if color value changes, so
            // the background color is upgraded automatically!
            m_master_renderer.setBackgroundColor( m_color[0], m_color[1], m_color[2] );
        }
        ImGui::End();
        
        ImGui::SFML::Render(*Display::m_window);
}

static void ShowExampleAppDockSpace(bool* p_open)
{
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into.
    // Because 1) it would be confusing to have two docking targets within each others.
    //     and 2) we want our main DockSpace node to always be visible (never hidden within a tab bar): if the DockSpace node disappear its child windows will be orphaned.
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
    flags |= ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", p_open, flags);
    ImGui::PopStyleVar();

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Docking"))
        {
            if (ImGui::MenuItem("Remove DockSpace", NULL, false, p_open != NULL))
                *p_open = false;
            ImGui::EndMenu();
        }
        // Disabling fullscreen would allow the window to be moved to the front of other windows, 
        // which we can't undo at the moment without finer window depth/z control.
        /*if (ImGui::BeginMenu("Options"))
        {
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
            ImGui::EndMenu();
        }*/

        ImGui::EndMenuBar();
    }

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        //ImGui::PushStyleColor(ImGuiCol_DockingBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGui::DockSpace(dockspace_id);
        //ImGui::PopStyleColor();
    }
    else
    {
       // ShowDockingDisabledMessage();
    }

    ImGui::End();
    if (opt_fullscreen)
        ImGui::PopStyleVar();
}

static void ShowExampleAppMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            //ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
