#include "interface.hpp"

static void ShowExampleAppDockSpace(bool* p_open);
static void ShowExampleAppMainMenuBar();
static void ShowExampleAppPropertyEditor(bool *p_open);

UserInterface::UserInterface(MasterRenderer& t_master_renderer )
                            : m_master_renderer(t_master_renderer){
    m_show_dock = true;
    m_show_demo_window = true;
    m_color[0] = 0.0f;
    m_color[1] = 0.0f;
    m_color[2] = 0.0f;
    m_light_color[0] = 1.0f;
    m_light_color[1] = 1.0f;
    m_light_color[2] = 1.0f;
}



void UserInterface::startInterface( std::vector<Entity*>& t_entities ){

     ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    //ImGui::CreateContext();
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
                ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), 
            ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight() - 30),ImVec2(0,1), ImVec2(1,0));
        }
	//std::cout << ImGui::GetWindowWidth() << " "<< ImGui::GetWindowHeight() << std::endl; 
	m_master_renderer.setDisplayHeight( ImGui::GetWindowHeight());
	m_master_renderer.setDisplayWidth( ImGui::GetWindowWidth());
        ImGui::End();
        ImGui::SetNextWindowDockId(2);
        ImGui::Begin("Objects");
        ImGui::SetNextWindowSize(ImVec2(430,450), ImGuiCond_FirstUseEver);
        //ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");
        if (ImGui::Button("Add Object"))
                ImGui::OpenPopup("Add Object");
            if (ImGui::BeginPopupModal("Add Object", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Selected an object to be loaded:");
                ImGui::Separator();
                const char* items[] = {"Entity"};
                static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
                if (ImGui::BeginCombo("Type", item_current)) // The second parameter is the label previewed before opening the combo.
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (item_current == items[n]);
                        if (ImGui::Selectable(items[n], is_selected))
                            item_current = items[n];
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                    }
                    ImGui::EndCombo();
                }
                ImGui::Text("Model:");
                static char buf1[64] = ""; ImGui::InputText("", buf1, 64);
                ImGui::SameLine();
                if (ImGui::Button("Select##Model"))
                    ImGui::OpenPopup("Select Model");

                std::string path = "./source/res/models";
                std::vector <std::string> files_model;
                static int selected_obj = -1;
                for (auto & p : fs::directory_iterator(path)){
                        files_model.push_back(p.path().string());
                }

                if (ImGui::BeginPopupModal("Select Model"))
                {
                    ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Select the model:");
                    for(int i = 0;i < files_model.size(); i++){
                        char buf[32];
                        sprintf(buf, "%s", files_model[i]);
                        if (ImGui::Selectable(files_model[i].c_str(), selected_obj == i))
                            selected_obj = i;
                    }
                    ImGui::EndPopup();
                }
                if(selected_obj != -1){
                    files_model[selected_obj].erase(0, 2);
                    strcpy(buf1,files_model[selected_obj].c_str());
                }
                ImGui::Text("Texture:");
                static char buf2[64] = ""; ImGui::InputText("", buf2, 64);
                ImGui::SameLine();
                if (ImGui::Button("Select##Texture"))
                    ImGui::OpenPopup("Select Texture");
                std::string path_texture = "./source/res/img";
                std::vector <std::string> files_texture;
                static int selected_texture = -1;
                for (auto & p : fs::directory_iterator(path_texture)){
                        files_texture.push_back(p.path().string());
                }

                if (ImGui::BeginPopupModal("Select Texture"))
                {
                    ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Select the texture:");
                    for(int i = 0;i < files_texture.size(); i++){
                        char buf[32];
                        sprintf(buf, "%s", files_texture[i]);
                        if (ImGui::Selectable(files_texture[i].c_str(), selected_texture == i))
                            selected_texture = i;
                    }
                    ImGui::EndPopup();
                }
                if(selected_texture != -1){
                    files_texture[selected_texture].erase(0, 2);
                    strcpy(buf2,files_texture[selected_texture].c_str());
                }
                    

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
                ImGui::PopStyleVar();

                if (ImGui::Button("OK", ImVec2(120,0))) { 
                    if( (buf1 != NULL) && (buf2 != NULL)){
                        Loader loader = Loader();
                        RawModel model_raw = loader.loadObj(buf1);
                        ModelTexture model_texture = ModelTexture( loader.loadTexture( buf2),10.0f,1.0f );
                        TexturedModel model = TexturedModel (model_raw, model_texture);
                        Entity *entity = new Entity( model, glm::vec3(0.0f,0.0f,-2.0f), glm::vec3(0.0f,0.0f,0.0f), 1.0f );
                        t_entities.push_back(entity);
                    }
                    
                    ImGui::CloseCurrentPopup(); 
                }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120,0))) { ImGui::CloseCurrentPopup(); }
                ImGui::EndPopup();
            }
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
        //ImGui::Columns(2);
        ImGui::Separator();

        struct funcs
        {
            static void ShowDummyObject(const char* prefix, Entity* entity)
            {
                ImGui::PushID((uintptr_t)entity); // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
                ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
                bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, (uintptr_t)entity);
                ImGui::NextColumn();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("my sailor is rich");
                ImGui::NextColumn();
                if (node_open)
                {
                    static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
                     static int selected = -1;
                   /* for (int n = 0; n < 5; n++)
                    {
                        char buf[32];
                        sprintf(buf, "Object %d", n);
                        if (ImGui::Selectable(buf, selected == n))
                            selected = n;
                    }*/
                    for (int i = 0; i < 8; i++)
                    {
                        //ImGui::PushID(i); // Use field index as identifier.
                       // if (i < 2)
                        {
                           // ShowDummyObject("Child", 424242);
                        }
                        //else
                        {
                            // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
                            //ImGui::AlignTextToFramePadding();
                            //ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Field_%d", i);
                           // ImGui::NextColumn();
                           // ImGui::PushItemWidth(-1);
                            //if (i >= 5)
                              //  ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
                          //  else
                               // ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
                          // ImGui::PopItemWidth();
                           // ImGui::NextColumn();
                        }
                        //ImGui::PopID();
                    }
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
        };

        // Iterate dummy objects with dummy members (all the same data)
        static int selected = -1;
        for(int i = 0; i < t_entities.size(); i++){
            char buf[32];
            sprintf(buf, "Entity %d", i);
            if (ImGui::Selectable(buf, selected == i))
                selected = i;
        }
        /*for (Entity* entity : t_entities){
            char buf[32];
            sprintf(buf, "Entity %d", (uintptr_t) entity);
            if (ImGui::Selectable(buf, selected == 1))
                selected = 1;
            //funcs::ShowDummyObject("Entity", entity);
        }*/
            
        //for (int obj_i = 0; obj_i < 3; obj_i++)
            //funcs::ShowDummyObject("Object", obj_i);

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::End();
        ImGui::Begin("Scene Properties");
            ImGui::PushItemWidth(300);
            ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Background:");
            ImGui::Spacing();
            ImGui::Text("Background Color");
            ImGui::SameLine(150);
            if (ImGui::ColorEdit3("##backgroundcolor", m_color)) {
                m_master_renderer.setBackgroundColor( m_color[0], m_color[1], m_color[2] );
            }
            ImGui::Separator();

            ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Directional Light:");
            ImGui::Spacing();
            static float f1 = 0.5f;
            static float vec3f_light_position[3] = {1.0f,1.0f,1.0f};

            vec3f_light_position[0] = m_master_renderer.getLightPosition().x;
            vec3f_light_position[1] = m_master_renderer.getLightPosition().y;
            vec3f_light_position[2] = m_master_renderer.getLightPosition().z;
	    //f1 = m_master_renderer.getLightIntensity();

            ImGui::Text("Intensity");
            ImGui::SameLine(150); ImGui::DragFloat("##lightintensity", &f1, 0.005f,0.0f,1.0f);
            m_master_renderer.setLightIntensity(f1);
            ImGui::Text("Light color");
            ImGui::SameLine(150);
            if (ImGui::ColorEdit3("##lightcolor",m_light_color)) {
                m_master_renderer.setLightColor(glm::vec3(m_light_color[0],m_light_color[1],m_light_color[2]));
            }
            ImGui::Text("Position");
            ImGui::SameLine(150);
            ImGui::DragFloat3("##LightPosition", vec3f_light_position,0.01f);
            m_master_renderer.setLightPosition(glm::vec3(vec3f_light_position[0],vec3f_light_position[1],vec3f_light_position[2]));


            ImGui::Separator();
            static float vec3f_camera_position[3] = { 1.0f, 1.0f, 1.0f};
            static float vec2f_camera_rotation[2] = { 1.0f, 1.0f};

            vec3f_camera_position[0] = m_master_renderer.getCameraPosition().x;
            vec3f_camera_position[1] = m_master_renderer.getCameraPosition().y;
            vec3f_camera_position[2] = m_master_renderer.getCameraPosition().z;
            vec2f_camera_rotation[0] = m_master_renderer.getCameraPitch();
            vec2f_camera_rotation[1] = m_master_renderer.getCameraYaw();

            ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), "Camera:");
            ImGui::Spacing();
            ImGui::Text("Position");
            ImGui::SameLine(150);
            ImGui::DragFloat3("##Position", vec3f_camera_position,0.01f);
            m_master_renderer.setCameraPosition(glm::vec3(vec3f_camera_position[0],vec3f_camera_position[1],vec3f_camera_position[2]));

            ImGui::Text("Pitch");
            ImGui::SameLine(150);
            ImGui::DragFloat("##Pitch", &vec2f_camera_rotation[0],0.01f);
            m_master_renderer.setCameraPitch(vec2f_camera_rotation[0]);

            ImGui::Text("Yaw");
            ImGui::SameLine(150);
            ImGui::DragFloat("##Yaw", &vec2f_camera_rotation[1],0.01f);
            m_master_renderer.setCameraYaw(vec2f_camera_rotation[1]);

        ImGui::End();
         {
            static float f = 0.0f;
            static int counter = 0;
            static float vec3f_entity_position[3] = { 0.0f, -1.0f, -1.0f};
            static float vec3f_entity_rotation[3] = { 0.0f, 0.0f, 0.0f};
            static float vec3f_entity_scale[3] = { 1.0f, 1.0f, 1.0f};
            static std::vector <std::array<float,3>> vec3f_entitites_position;
            static std::vector <std::array<float,3>> vec3f_entitites_rotation;
            static std::vector  <std::array<float,3>> vec3f_entitites_scale;

            vec3f_entitites_scale.resize(t_entities.size());
            vec3f_entitites_position.resize(t_entities.size());
            vec3f_entitites_rotation.resize(t_entities.size());
            static float f_scale=1.00f;
            static bool checkRotationLoop = false;
            static glm::vec3 entity_position;
            for(int i = 0;i < vec3f_entitites_position.size();i++){
                if(selected != -1 && selected == i){
                    vec3f_entitites_position[i][0] = t_entities[i]->getPosition().x;
                    vec3f_entitites_position[i][1] = t_entities[i]->getPosition().y;
                    vec3f_entitites_position[i][2] = t_entities[i]->getPosition().z;
                    vec3f_entitites_rotation[i][0] = t_entities[i]->getRotation().x;
                    vec3f_entitites_rotation[i][1] = t_entities[i]->getRotation().y;
                    vec3f_entitites_rotation[i][2] = t_entities[i]->getRotation().z;
                    vec3f_entitites_scale[i][0]    = t_entities[i]->getScale().x;
                    vec3f_entitites_scale[i][1]    = t_entities[i]->getScale().y;
                    vec3f_entitites_scale[i][2]    = t_entities[i]->getScale().z;
                }
            }
            
            ImGui::Begin("Inspector");                          // Create a window called "Hello, world!" and append into it.
            if(selected != -1){

                ImGui::Text("Entity %d",selected );               // Display some text (you can use a format strings too)
                vec3f_entity_position[0] = vec3f_entitites_position[selected][0];
                vec3f_entity_position[1] = vec3f_entitites_position[selected][1];
                vec3f_entity_position[2] = vec3f_entitites_position[selected][2];

                ImGui::DragFloat3("Position", vec3f_entity_position,0.01f);
                t_entities[selected]->setPosition(glm::vec3( vec3f_entity_position[0], vec3f_entity_position[1], vec3f_entity_position[2]));

                vec3f_entity_rotation[0] = vec3f_entitites_rotation[selected][0];
                vec3f_entity_rotation[1] = vec3f_entitites_rotation[selected][1];
                vec3f_entity_rotation[2] =vec3f_entitites_rotation[selected][2];

                ImGui::DragFloat3("Rotation", vec3f_entity_rotation,0.01f);
                if(!checkRotationLoop){
                    t_entities[selected]->setRotation(glm::vec3(vec3f_entity_rotation[0],vec3f_entity_rotation[1],vec3f_entity_rotation[2]));
                }

                vec3f_entity_scale[0] = vec3f_entitites_scale[selected][0];
                vec3f_entity_scale[1] = vec3f_entitites_scale[selected][1];
                vec3f_entity_scale[2] = vec3f_entitites_scale[selected][2];

                ImGui::DragFloat3("Scale", vec3f_entity_scale,0.01f);
                t_entities[selected]->setScale(glm::vec3( vec3f_entity_scale[0], vec3f_entity_scale[1], vec3f_entity_scale[2]));

                ImGui::Checkbox("Rotation Loop", &checkRotationLoop);
                if(checkRotationLoop){

                    t_entities[selected]->increaseRotation(0,0.01f,0);
                }
            }
           
            ImGui::End();
        }
       //if (m_show_demo_window)
            //ImGui::ShowDemoWindow(&m_show_demo_window);  
        ImGui::Render(); 
}



void UserInterface::loadStyle(){
    
    auto *style = &ImGui::GetStyle();
    style->WindowRounding = 5.3f;
    style->GrabRounding = style->FrameRounding = 2.3f;
    style->ScrollbarRounding = 5.0f;
    style->FrameBorderSize = 1.0f;
    style->ItemSpacing.y = 6.5f;

    style->Colors[ImGuiCol_Text]                  = {0.73333335f, 0.73333335f, 0.73333335f, 1.00f};
    style->Colors[ImGuiCol_TextDisabled]          = {0.34509805f, 0.34509805f, 0.34509805f, 1.00f};
    style->Colors[ImGuiCol_WindowBg]              = {0.23529413f, 0.24705884f, 0.25490198f, 0.94f};
    style->Colors[ImGuiCol_ChildBg]               = {0.23529413f, 0.24705884f, 0.25490198f, 0.00f};
    style->Colors[ImGuiCol_PopupBg]               = {0.23529413f, 0.24705884f, 0.25490198f, 0.94f};
    style->Colors[ImGuiCol_Border]                = {0.33333334f, 0.33333334f, 0.33333334f, 0.50f};
    style->Colors[ImGuiCol_BorderShadow]          = {0.15686275f, 0.15686275f, 0.15686275f, 0.00f};
    style->Colors[ImGuiCol_FrameBg]               = {0.16862746f, 0.16862746f, 0.16862746f, 0.54f};
    style->Colors[ImGuiCol_FrameBgHovered]        = {0.453125f, 0.67578125f, 0.99609375f, 0.67f};
    style->Colors[ImGuiCol_FrameBgActive]         = {0.47058827f, 0.47058827f, 0.47058827f, 0.67f};
    //style->Colors[ImGuiCol_TitleBg]               = {0.04f, 0.04f, 0.04f, 1.00f};
    style->Colors[ImGuiCol_TitleBg]               = {0.47f, 0.47f, 0.47f, 1.00f};
    //style->Colors[ImGuiCol_TitleBgCollapsed]      = {0.16f, 0.29f, 0.48f, 1.00f};
    //style->Colors[ImGuiCol_TitleBgActive]         = {0.00f, 0.00f, 0.00f, 0.51f};
    style->Colors[ImGuiCol_MenuBarBg]             = {0.27058825f, 0.28627452f, 0.2901961f, 0.80f};
    style->Colors[ImGuiCol_ScrollbarBg]           = {0.27058825f, 0.28627452f, 0.2901961f, 0.60f};
    style->Colors[ImGuiCol_ScrollbarGrab]         = {0.21960786f, 0.30980393f, 0.41960788f, 0.51f};
    style->Colors[ImGuiCol_ScrollbarGrabHovered]  = {0.21960786f, 0.30980393f, 0.41960788f, 1.00f};
    style->Colors[ImGuiCol_ScrollbarGrabActive]   = {0.13725491f, 0.19215688f, 0.2627451f, 0.91f};
    // style->Colors[ImGuiCol_ComboBg]               = {0.1f, 0.1f, 0.1f, 0.99f};
    style->Colors[ImGuiCol_CheckMark]             = {0.90f, 0.90f, 0.90f, 0.83f};
    style->Colors[ImGuiCol_SliderGrab]            = {0.70f, 0.70f, 0.70f, 0.62f};
    style->Colors[ImGuiCol_SliderGrabActive]      = {0.30f, 0.30f, 0.30f, 0.84f};
    style->Colors[ImGuiCol_Button]                = {0.33333334f, 0.3529412f, 0.36078432f, 0.49f};
    style->Colors[ImGuiCol_ButtonHovered]         = {0.21960786f, 0.30980393f, 0.41960788f, 1.00f};
    style->Colors[ImGuiCol_ButtonActive]          = {0.13725491f, 0.19215688f, 0.2627451f, 1.00f};
    style->Colors[ImGuiCol_Header]                = {0.33333334f, 0.3529412f, 0.36078432f, 0.53f};
    style->Colors[ImGuiCol_HeaderHovered]         = {0.453125f, 0.67578125f, 0.99609375f, 0.67f};
    style->Colors[ImGuiCol_HeaderActive]          = {0.47058827f, 0.47058827f, 0.47058827f, 0.67f};
    style->Colors[ImGuiCol_Separator]             = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
    style->Colors[ImGuiCol_SeparatorHovered]      = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
    style->Colors[ImGuiCol_SeparatorActive]       = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
    style->Colors[ImGuiCol_ResizeGrip]            = {1.00f, 1.00f, 1.00f, 0.85f};
    style->Colors[ImGuiCol_ResizeGripHovered]     = {1.00f, 1.00f, 1.00f, 0.60f};
    style->Colors[ImGuiCol_ResizeGripActive]      = {1.00f, 1.00f, 1.00f, 0.90f};
    style->Colors[ImGuiCol_PlotLines]             = {0.61f, 0.61f, 0.61f, 1.00f};
    style->Colors[ImGuiCol_PlotLinesHovered]      = {1.00f, 0.43f, 0.35f, 1.00f};
    style->Colors[ImGuiCol_PlotHistogram]         = {0.90f, 0.70f, 0.00f, 1.00f};
    style->Colors[ImGuiCol_PlotHistogramHovered]  = {1.00f, 0.60f, 0.00f, 1.00f};
    style->Colors[ImGuiCol_TextSelectedBg]        = {0.18431373f, 0.39607847f, 0.79215693f, 0.90f};
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

static void ShowExampleAppPropertyEditor(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(430,450), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Example: Property editor", p_open))
    {
        ImGui::End();
        return;
    }

    //ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
    ImGui::Columns(2);
    ImGui::Separator();

    struct funcs
    {
        static void ShowDummyObject(const char* prefix, int uid)
        {
            ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
            ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
            bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
            ImGui::NextColumn();
            ImGui::AlignTextToFramePadding();
            ImGui::Text("my sailor is rich");
            ImGui::NextColumn();
            if (node_open)
            {
                static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
                for (int i = 0; i < 8; i++)
                {
                    ImGui::PushID(i); // Use field index as identifier.
                    if (i < 2)
                    {
                        ShowDummyObject("Child", 424242);
                    }
                    else
                    {
                        // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Field_%d", i);
                        ImGui::NextColumn();
                        ImGui::PushItemWidth(-1);
                        if (i >= 5)
                            ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
                        else
                            ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
                        ImGui::PopItemWidth();
                        ImGui::NextColumn();
                    }
                    ImGui::PopID();
                }
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
    };

    // Iterate dummy objects with dummy members (all the same data)
    for (int obj_i = 0; obj_i < 3; obj_i++)
        funcs::ShowDummyObject("Object", obj_i);

    ImGui::Columns(1);
    ImGui::Separator();
    ImGui::PopStyleVar();
    ImGui::End();
}
