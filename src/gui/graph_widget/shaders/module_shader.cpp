#include "gui/graph_widget/shaders/module_shader.h"

#include "gui/gui_globals.h"
#include "gui/graph_widget/graph_context.h"
#include "gui/module_model/module_item.h"

module_shader::module_shader(const graph_context* const context) : graph_shader(context)
{

}

void module_shader::added(const QSet<u32> gates, const QSet<u32> nets)
{
    Q_UNUSED(gates)
    Q_UNUSED(nets)
}

void module_shader::removed(const QSet<u32> gates, const QSet<u32> nets)
{
    Q_UNUSED(gates)
    Q_UNUSED(nets)
}

void module_shader::update()
{
    m_shading.module_visuals.clear();
    m_shading.gate_visuals.clear();
    m_shading.net_visuals.clear();

    // IDS TECHNICALLY DONT NEED TO BE CHECKED BECAUSE THE CONTEXT ENSURES VALIDITY
    // OPTIMIZE OUT ???

    for (u32 id : m_context->modules())
    {
        module_item* item = g_netlist_relay.get_module_item(id);

        if (!item)
            continue;

        graphics_node::visuals v;
        v.main_color = item->color();
        m_shading.module_visuals.insert(id, v);
    }
}