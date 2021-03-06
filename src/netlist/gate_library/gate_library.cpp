#include "netlist/gate_library/gate_library.h"

gate_library::gate_library(const std::string& name) : m_name(name)
{
}

std::string gate_library::get_name() const
{
    return m_name;
}

std::set<std::string>* gate_library::get_gate_types()
{
    return &m_gate_type;
}

std::set<std::string>* gate_library::get_global_vcc_gate_types()
{
    return &m_global_vcc_gate_type;
}

std::set<std::string>* gate_library::get_global_gnd_gate_types()
{
    return &m_global_gnd_gate_type;
}

std::set<std::string>* gate_library::get_input_pin_types()
{
    return &m_input_pin_type;
}

std::set<std::string>* gate_library::get_output_pin_types()
{
    return &m_output_pin_type;
}

std::set<std::string>* gate_library::get_inout_pin_types()
{
    return &m_inout_pin_type;
}

std::map<std::string, std::vector<std::string>>* gate_library::get_gate_type_map_to_input_pin_types()
{
    return &m_gate_type_to_input_pin_types;
}

std::map<std::string, std::vector<std::string>>* gate_library::get_gate_type_map_to_output_pin_types()
{
    return &m_gate_type_to_output_pin_types;
}

std::map<std::string, std::vector<std::string>>* gate_library::get_gate_type_map_to_inout_pin_types()
{
    return &m_gate_type_to_inout_pin_types;
}

std::vector<std::string>* gate_library::get_vhdl_includes()
{
    return &m_vhdl_includes;
}
