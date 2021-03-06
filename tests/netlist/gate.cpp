#include "gate_decorator_system/gate_decorator.h"
#include "netlist/gate_library/gate_library_manager.h"
#include "netlist/netlist.h"
#include "netlist/netlist_factory.h"
#include "test_def.h"
#include "gtest/gtest.h"
#include <core/log.h>
#include <iostream>
#include <netlist/gate.h>
#include <netlist/net.h>
/*
 * Child of gate_decorator. Used for testing.
 */
/*
class test_decorator : public gate_decorator
{
public:
    test_decorator(std::shared_ptr<gate> g) : gate_decorator(g)
    {
    }
    gate_decorator_system::decorator_type get_type()
    {
        return "test_decorator";
    }
};
*/
class gate_test : public ::testing::Test
{
protected:
    const std::string g_lib_name = "EXAMPLE_GATE_LIBRARY";

    virtual void SetUp()
    {
        NO_COUT_BLOCK;
        gate_library_manager::load_all();
    }

    virtual void TearDown()
    {
    }

    // Creates an empty netlist with a certain id if passed
    std::shared_ptr<netlist> create_empty_netlist(int id = -1)
    {
        NO_COUT_BLOCK;
        std::shared_ptr<gate_library> gl = gate_library_manager::get_gate_library(g_lib_name);
        std::shared_ptr<netlist> nl      = std::make_shared<netlist>(gl);

        if (id >= 0)
        {
            nl->set_id(id);
        }
        return nl;
    }

    /*
     *      Example netlist circuit diagram (Id in brackets). Used for get fan in and
     *      out nets.
     *
     *
     *      GND (1) =-= INV (3) =--=             ------= INV (4) =
     *                                        AND2 (0) =-
     *      VCC (2) =----------------=             ------=
     *                                                            AND2 (5) =
     *                                                          =
     *
     *     =                       =               =----------=                =
     *       BUF (6)      ... OR2 (7)          ... OR2 (8)
     *     =                       =               =          =                =
     */

    // Creates a simple netlist shown in the diagram above
    std::shared_ptr<netlist> create_example_netlist(int id = -1)
    {
        NO_COUT_BLOCK;
        std::shared_ptr<gate_library> gl = gate_library_manager::get_gate_library(g_lib_name);
        std::shared_ptr<netlist> nl      = std::make_shared<netlist>(gl);
        if (id >= 0)
        {
            nl->set_id(id);
        }

        // Create the gates
        std::shared_ptr<gate> gate_0 = nl->create_gate(1, "AND2", "gate_0");
        std::shared_ptr<gate> gate_1 = nl->create_gate(2, "GND", "gate_1");
        std::shared_ptr<gate> gate_2 = nl->create_gate(3, "VCC", "gate_2");
        std::shared_ptr<gate> gate_3 = nl->create_gate(4, "INV", "gate_3");
        std::shared_ptr<gate> gate_4 = nl->create_gate(5, "INV", "gate_4");
        std::shared_ptr<gate> gate_5 = nl->create_gate(6, "AND2", "gate_5");
        std::shared_ptr<gate> gate_6 = nl->create_gate(7, "BUF", "gate_6");
        std::shared_ptr<gate> gate_7 = nl->create_gate(8, "OR2", "gate_7");
        std::shared_ptr<gate> gate_8 = nl->create_gate(9, "OR2", "gate_8");

        // Add the nets (net_x_y1_y2... := net between the gate with id x and the gates y1,y2,...)
        std::shared_ptr<net> net_1_3 = nl->create_net(13, "net_1_3");
        net_1_3->set_src(gate_1, "O");
        net_1_3->add_dst(gate_3, "I");

        std::shared_ptr<net> net_3_0 = nl->create_net(30, "net_3_0");
        net_3_0->set_src(gate_3, "O");
        net_3_0->add_dst(gate_0, "I0");

        std::shared_ptr<net> net_2_0 = nl->create_net(20, "net_2_0");
        net_2_0->set_src(gate_2, "O");
        net_2_0->add_dst(gate_0, "I1");

        std::shared_ptr<net> net_0_4_5 = nl->create_net(045, "net_0_4_5");
        net_0_4_5->set_src(gate_0, "O");
        net_0_4_5->add_dst(gate_4, "I");
        net_0_4_5->add_dst(gate_5, "I0");

        std::shared_ptr<net> net_7_8 = nl->create_net(78, "net_7_8");
        net_7_8->set_src(gate_7, "O");
        net_7_8->add_dst(gate_8, "I0");

        return nl;
    }

    /*
     *      Example netlist no 2 circuit diagram (Id in brackets). Used for get predecessors
     *      and succesors
     *
     *    =                 =----------=                 =
     *    =                 =----------=                 =
     *    = AND3 (0) =--.    '--= AND3 (1) =
     *   ...               ... |    .--=                ...
     *    =                 =  |    | ...                =
     *                         |    |  =
     *    =                 =--+----'
     *   ...AND3 (2)... |
     *    =                 =  '-------=                 =
     *                                ...AND3 (3)...
     *                                 =                 =
     */

    // Creates a simple netlist shown in the diagram above
    std::shared_ptr<netlist> create_example_netlist_2(int id = -1)
    {
        //NO_COUT_BLOCK;
        std::shared_ptr<gate_library> gl = gate_library_manager::get_gate_library(g_lib_name);
        std::shared_ptr<netlist> nl      = std::make_shared<netlist>(gl);
        if (id >= 0)
        {
            nl->set_id(id);
        }

        // Create the gates
        std::shared_ptr<gate> gate_0 = nl->create_gate(1, "AND4", "gate_0");
        std::shared_ptr<gate> gate_1 = nl->create_gate(2, "AND4", "gate_1");
        std::shared_ptr<gate> gate_2 = nl->create_gate(3, "AND4", "gate_2");
        std::shared_ptr<gate> gate_3 = nl->create_gate(4, "AND4", "gate_3");

        // Add the nets (net_x_y1_y2... := net between the gate with id x and the gates y1,y2,...)

        std::shared_ptr<net> net_0_1_1 = nl->create_net(2, "net_0_1_1");
        net_0_1_1->set_src(gate_0, "O");
        net_0_1_1->add_dst(gate_1, "I0");
        net_0_1_1->add_dst(gate_1, "I1");
        net_0_1_1->add_dst(gate_1, "I2");
        net_0_1_1->add_dst(gate_3, "I0");

        std::shared_ptr<net> net_2_1 = nl->create_net(4, "net_2_1");
        net_2_1->set_src(gate_2, "O");
        net_2_1->add_dst(gate_1, "I3");

        return nl;
    }

    /*
     *      Netlist with one gate and unconnected nets
     *
     *        -----= X_INV (0) =-----
     *
     */

    // Creates a incomplete netlist used for negative tests (see above)
    std::shared_ptr<netlist> create_example_netlist_negative(int id = -1)
    {
        NO_COUT_BLOCK;
        std::shared_ptr<gate_library> gl = gate_library_manager::get_gate_library(g_lib_name);
        std::shared_ptr<netlist> nl(new netlist(gl));
        if (id >= 0)
        {
            nl->set_id(id);
        }

        // Create the gate
        std::shared_ptr<gate> gate_0 = nl->create_gate(1, "INV", "gate_0");

        // net connected to the input pin
        std::shared_ptr<net> net_X_0 = nl->create_net(1, "net_X_0");
        net_X_0->add_dst(gate_0, "I");

        // net connected to the output pin
        std::shared_ptr<net> net_0_X = nl->create_net(2, "net_0_X");
        net_0_X->set_src(gate_0, "O");

        return nl;
    }

    // Creates an endpoint from a gate and a pin_type
    endpoint get_endpoint(std::shared_ptr<gate> g, std::string pin_type)
    {
        endpoint ep;
        ep.gate     = g;
        ep.pin_type = pin_type;
        return ep;
    }

    // Creates an endpoint by passing the gate-id of a netlist nl and a pin type
    endpoint get_endpoint(std::shared_ptr<netlist> nl, int gate_id, std::string pin_type)
    {
        std::shared_ptr<gate> g = nl->get_gate_by_id(gate_id);
        return get_endpoint(g, pin_type);
    }

    // Checks if two endpoint vectors have the same content regardless of their order
    bool vectors_have_same_content(std::vector<endpoint> vec_1, std::vector<endpoint> vec_2)
    {
        if (vec_1.size() != vec_2.size())
            return false;

        // Each element of vec_1 must be found in vec_2
        while (vec_1.size() > 0)
        {
            auto it_1       = vec_1.begin();
            bool found_elem = false;
            for (auto it_2 = vec_2.begin(); it_2 != vec_2.end(); it_2++)
            {
                if (*it_1 == *it_2)
                {
                    found_elem = true;
                    vec_2.erase(it_2);
                    break;
                }
            }
            if (!found_elem)
            {
                return false;
            }
            vec_1.erase(it_1);
        }

        return true;
    }

    /*
     * Returns if a string contains a certain substring
     */
    bool string_contains_substring(std::string str, std::string sub_str)
    {
        return (str.find(sub_str) != std::string::npos);
    }

    /*
     * Functions passed to the register_decorator map to access the test decorator

    static std::shared_ptr<gate_decorator> get_test_decorator(std::shared_ptr<gate> g)
    {
        return std::shared_ptr<gate_decorator>(new test_decorator(g));
    }*/

    //    /*
    //     * Register the test decorator in a netlist nl for a gate with type gate_type
    //     */
    //    bool register_test_decorator(std::shared_ptr<netlist> nl, std::string gate_type = "INV")
    //    {
    //        std::function<std::shared_ptr<gate_decorator>(std::shared_ptr<gate>)> constructor = get_test_decorator;
    //        std::map<std::string, std::function<std::shared_ptr<gate_decorator>(std::shared_ptr<gate>)>> g_type_to_constructor;
    //        g_type_to_constructor[gate_type] = constructor;
    //        return nl->register_gate_decorator_type("test_decorator", g_type_to_constructor);
    //    }
};

/**
 * Testing the constructor as well as the copy constructor of the gate
 *
 * Functions: constructor, copy constructor, get_id, get_name, get_type
 */
TEST_F(gate_test, check_constructor)
{
    TEST_START
    // Create a gate (id = 100) and append it to its netlist
    std::shared_ptr<netlist> nl     = create_empty_netlist(0);
    std::shared_ptr<gate> test_gate = nl->create_gate(100, "AND2", "gate_name");

    EXPECT_EQ(test_gate->get_id(), (u32)100);
    EXPECT_EQ(test_gate->get_type(), "AND2");
    EXPECT_EQ(test_gate->get_name(), "gate_name");
    EXPECT_EQ(test_gate->get_netlist()->get_id(), (u32)0);

    TEST_END
}

/**
 * Testing the output operator<< by testing, if the output stream contains certain
 * information, like id, name ...
 *
 * Functions: operator<<
 */
/*
TEST_F(gate_test, check_out_operator) {
    TEST_START
        std::shared_ptr<netlist> nl = create_example_netlist(0);

        {
            std::stringstream ss;
            ss << *(nl->get_gate_by_id(0));

        }


    TEST_END
}*/

/**
 * Testing the function set_name and get_name
 *
 * Functions: get_name, set_name
 */
TEST_F(gate_test, check_set_and_get_name)
{
    TEST_START
    // Create a gate and append it to its netlist
    std::shared_ptr<netlist> nl     = create_empty_netlist(0);
    std::shared_ptr<gate> test_gate = nl->create_gate(1, "AND2", "gate_name");

    EXPECT_EQ(test_gate->get_name(), "gate_name");

    // Set a new name
    NO_COUT(test_gate->set_name("new_name"));
    EXPECT_EQ(test_gate->get_name(), "new_name");

    // Set the name to the same new name again
    NO_COUT(test_gate->set_name("new_name"));
    EXPECT_EQ(test_gate->get_name(), "new_name");

    TEST_END
}

///**
// * Testing the access on decorators by query the test decorator and verify success by
// * call get_decorator_types and query_decorator
// *
// * Functions: query_decorator, has_decorator_type, get_decorator_types
// */
//TEST_F(gate_test, check_decorator_types)
//{
//    TEST_START
//    {
//            // Query the test decorator
//            std::shared_ptr<netlist> nl = create_empty_netlist(0);
//            register_test_decorator(nl, "INV"); // Register decorator for X_INV
//            std::shared_ptr<gate> test_gate(new gate(nl, 0, "INV", "gate_name"));
//            nl -> add_gate(test_gate);
//            std::shared_ptr<gate_decorator> dec = test_gate->query_decorator("test_decorator");
//            EXPECT_EQ(dec->get_type(), "test_decorator");
//            EXPECT_TRUE(test_gate->has_decorator_type("test_decorator"));
//            EXPECT_EQ(test_gate->get_decorator_types(), std::set<std::string>({"test_decorator"}));
//
//        }
//        {
//            // The decorator isn't queried
//            std::shared_ptr<netlist> nl = create_empty_netlist(0);
//            std::shared_ptr<gate> test_gate= nl->create_gate(1, "INV", "gate_name");
//            EXPECT_FALSE(test_gate->has_decorator_type("test_decorator"));
//            EXPECT_EQ(test_gate->get_decorator_types(), std::set<std::string>({}));
//        }
//
//
//
//    TEST_END
//}

/**
 * Testing functions which returns the pin types. Further test for different gate types
 * are for in the tests for netlist (get_input_pin_types, ... )
 *
 * Functions: get_input_pin_types, get_output_pin_types, get_inout_pin_types
 */
TEST_F(gate_test, check_pin_types)
{
    TEST_START
    // Create a gate and append it to its netlist
    std::shared_ptr<netlist> nl     = create_empty_netlist(0);
    std::shared_ptr<gate> test_gate = nl->create_gate(1, "AND2", "gate_name");

    EXPECT_EQ(test_gate->get_input_pin_types(), std::vector<std::string>({"I0", "I1"}));
    EXPECT_EQ(test_gate->get_output_pin_types(), std::vector<std::string>({"O"}));
    EXPECT_EQ(test_gate->get_inout_pin_types(), std::vector<std::string>({}));

    TEST_END
}

/**
 * Testing functions which returns the fan-in nets nets by using the
 * example netlist (see above)
 *
 * Functions: get_fan_in_nets
 */
TEST_F(gate_test, check_get_fan_in_nets)
{
    TEST_START

    // Create the example
    std::shared_ptr<netlist> nl = create_example_netlist(0);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // All input pins are occupied
        std::shared_ptr<gate> gate_0                 = nl->get_gate_by_id(1);
        std::set<std::shared_ptr<net>> fan_in_nets_0 = {nl->get_net_by_id(30), nl->get_net_by_id(20)};
        EXPECT_EQ(gate_0->get_fan_in_nets(), fan_in_nets_0);
    }
    {
        // Not all input pins are occupied
        std::shared_ptr<gate> gate_5                 = nl->get_gate_by_id(6);
        std::set<std::shared_ptr<net>> fan_in_nets_5 = {nl->get_net_by_id(045)};
        EXPECT_EQ(gate_5->get_fan_in_nets(), fan_in_nets_5);
    }
    {
        // No input pins are occupied
        std::shared_ptr<gate> gate_6                 = nl->get_gate_by_id(7);
        std::set<std::shared_ptr<net>> fan_in_nets_6 = {};
        EXPECT_EQ(gate_6->get_fan_in_nets(), fan_in_nets_6);
    }
    {
        // No input-pin exist
        std::shared_ptr<gate> gate_1                 = nl->get_gate_by_id(2);
        std::set<std::shared_ptr<net>> fan_in_nets_1 = {};
        EXPECT_EQ(gate_1->get_fan_in_nets(), fan_in_nets_1);
    }
    TEST_END
}

/**
 * Testing functions which returns the fan-out nets nets by using the
 * example netlist (see above)
 *
 * Functions: get_fan_out_nets
 */
TEST_F(gate_test, check_get_fan_out_nets)
{
    TEST_START

    // Create the example
    std::shared_ptr<netlist> nl = create_example_netlist(0);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // All output pins are occupied
        std::shared_ptr<gate> gate_0                  = nl->get_gate_by_id(1);
        std::set<std::shared_ptr<net>> fan_out_nets_0 = {nl->get_net_by_id(045)};
        EXPECT_EQ(gate_0->get_fan_out_nets(), fan_out_nets_0);
    }
    {
        // Not all output pins are occupied
        std::shared_ptr<gate> gate_7                  = nl->get_gate_by_id(8);
        std::set<std::shared_ptr<net>> fan_out_nets_7 = {nl->get_net_by_id(78)};
        EXPECT_EQ(gate_7->get_fan_out_nets(), fan_out_nets_7);
    }
    {
        // No output pins are occupied
        std::shared_ptr<gate> gate_8                  = nl->get_gate_by_id(9);
        std::set<std::shared_ptr<net>> fan_out_nets_8 = {};
        EXPECT_EQ(gate_8->get_fan_out_nets(), fan_out_nets_8);
    }
    {
        // No output pin exist
        std::shared_ptr<gate> gate_6                  = nl->get_gate_by_id(7);
        std::set<std::shared_ptr<net>> fan_out_nets_6 = {};
        EXPECT_EQ(gate_6->get_fan_out_nets(), fan_out_nets_6);
    }
    TEST_END
}

/**
 * Testing functions which returns the fan-in net, connected to a specific pin-type,
 * by using the example netlist (see above)
 *
 * Functions: get_fan_in_net
 */
TEST_F(gate_test, check_get_fan_in_net)
{
    TEST_START

    // Create the example
    std::shared_ptr<netlist> nl = create_example_netlist(0);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // Get an existing net at an existing pin-type
        std::shared_ptr<gate> gate_0 = nl->get_gate_by_id(1);
        EXPECT_EQ(gate_0->get_fan_in_net("I0"), nl->get_net_by_id(30));
        EXPECT_EQ(gate_0->get_fan_in_net("I1"), nl->get_net_by_id(20));
    }
    {
        // Get the net of a pin where no net is connected
        std::shared_ptr<gate> gate_5 = nl->get_gate_by_id(6);
        EXPECT_EQ(gate_5->get_fan_in_net("I1"), nullptr);
    }
    {
        // Get the net of a non existing pin
        std::shared_ptr<gate> gate_0 = nl->get_gate_by_id(1);
        EXPECT_EQ(gate_0->get_fan_in_net("NEx_PIN"), nullptr);
    }
    {
        // Get the net of a non existing pin-type of a gate where no input pin exist
        std::shared_ptr<gate> gate_1 = nl->get_gate_by_id(2);
        EXPECT_EQ(gate_1->get_fan_in_net("NEx_PIN"), nullptr);
    }
    {
        // Pass an empty string
        std::shared_ptr<gate> gate_0 = nl->get_gate_by_id(1);
        EXPECT_EQ(gate_0->get_fan_in_net(""), nullptr);
    }
    TEST_END
}

/**
 * Testing functions which returns the fan-out net, connected to a specific pin-type,
 * by using the example netlist (see above)
 *
 * Functions: get_fan_out_net
 */
TEST_F(gate_test, check_get_fan_out_net)
{
    TEST_START

    // Create the example
    std::shared_ptr<netlist> nl = create_example_netlist(0);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // Get an existing net at an existing pin-type
        std::shared_ptr<gate> gate_0 = nl->get_gate_by_id(1);
        EXPECT_EQ(gate_0->get_fan_out_net("O"), nl->get_net_by_id(045));
    }
    {
        // Get the net of a pin where no net is connected
        std::shared_ptr<gate> gate_4 = nl->get_gate_by_id(5);
        EXPECT_EQ(gate_4->get_fan_out_net("O"), nullptr);
    }
    {
        // Get the net of a non existing pin
        std::shared_ptr<gate> gate_0 = nl->get_gate_by_id(1);
        EXPECT_EQ(gate_0->get_fan_out_net("NEx_PIN"), nullptr);
    }
    {
        // Get the net of a non existing pin-type of a gate where no output pin exist
        std::shared_ptr<gate> gate_6 = nl->get_gate_by_id(7);
        EXPECT_EQ(gate_6->get_fan_out_net("NEx_PIN"), nullptr);
    }
    {
        // Pass an empty string
        std::shared_ptr<gate> gate_0 = nl->get_gate_by_id(1);
        EXPECT_EQ(gate_0->get_fan_out_net(""), nullptr);
    }
    TEST_END
}

/**
 * Testing the get_predecessors function by using the exmaple netlists (see above)
 *
 * Functions: get_predecessors
 */
TEST_F(gate_test, check_get_predecessors)
{
    TEST_START
    // Create the examples
    std::shared_ptr<netlist> nl_1 = create_example_netlist(1);
    std::shared_ptr<netlist> nl_2 = create_example_netlist_2(2);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // Get predecessors for a gate with multiple predecessors (some of them are the same gate)
        std::shared_ptr<gate> gate_1 = nl_2->get_gate_by_id(2);
        std::vector<endpoint> pred   = {get_endpoint(nl_2, 1, "O"), get_endpoint(nl_2, 1, "O"), get_endpoint(nl_2, 1, "O"), get_endpoint(nl_2, 3, "O")};
        EXPECT_TRUE(vectors_have_same_content(gate_1->get_predecessors(), pred));
        EXPECT_EQ(gate_1->get_predecessors().size(), (size_t)4);
    }
    {
        // Get predecessors for a gate no predecessors
        std::shared_ptr<gate> gate_0 = nl_2->get_gate_by_id(1);
        EXPECT_TRUE(gate_0->get_predecessors().empty());
    }
    {
        // Get predecessors for a given (existing) pin type
        std::shared_ptr<gate> gate_3 = nl_2->get_gate_by_id(4);
        std::vector<endpoint> pred   = {get_endpoint(nl_2, 1, "O")};
        EXPECT_TRUE(vectors_have_same_content(gate_3->get_predecessors(DONT_CARE, "O"), pred));
    }
    {
        // Get predecessors for a given (non-existing) pin type
        std::shared_ptr<gate> gate_1 = nl_2->get_gate_by_id(2);
        EXPECT_TRUE(gate_1->get_predecessors("NEx_PIN").empty());
        EXPECT_EQ(gate_1->get_predecessors("NEx_PIN").size(), (size_t)0);
    }
    {
        // Get predecessors for a given (existing) gate type
        std::shared_ptr<gate> gate_0 = nl_1->get_gate_by_id(1);
        std::vector<endpoint> pred   = {get_endpoint(nl_1, 4, "O")};
        EXPECT_TRUE(vectors_have_same_content(gate_0->get_predecessors(DONT_CARE, DONT_CARE, "INV"), pred));
        EXPECT_EQ(gate_0->get_predecessors(DONT_CARE, DONT_CARE, "INV").size(), (size_t)1);
    }
    {
        // Get predecessors for a given (non-existing) gate type
        std::shared_ptr<gate> gate_1 = nl_2->get_gate_by_id(2);
        EXPECT_TRUE(gate_1->get_predecessors(DONT_CARE, DONT_CARE, "NEx_GATE").empty());
        EXPECT_EQ(gate_1->get_predecessors(DONT_CARE, DONT_CARE, "NEx_GATE").size(), (size_t)0);
    }
    //        {
    //            // Get predecessors for a given decorator type
    //            std::shared_ptr<netlist> dec_nl = create_example_netlist(3);
    //            register_test_decorator(dec_nl, "INV"); // Register a decorator for X_INV
    //            std::vector<endpoint> pred = {
    //                    get_endpoint(dec_nl,3,"O")
    //            };
    //            std::shared_ptr<gate> gate_0 = dec_nl->get_gate_by_id(0);
    //            EXPECT_EQ(gate_0->get_predecessors(DONT_CARE, DONT_CARE, "test_decorator"), pred);
    //        }

    // ########################
    // NEGATIVE TESTS
    // ########################
    std::shared_ptr<netlist> nl_neg = create_example_netlist_negative(2);

    {
        // Get predecessors for a gate with unconnected nets
        std::shared_ptr<gate> gate_0 = nl_neg->get_gate_by_id(1);
        EXPECT_TRUE(gate_0->get_predecessors().empty());
        EXPECT_EQ(gate_0->get_predecessors().size(), (size_t)0);
    }
    TEST_END
}

/**
 * Testing the get_successors function by using the exmaple netlists (see above).
 *
 * Functions: get_successors
 */
TEST_F(gate_test, check_get_successors)
{
    TEST_START
    // Create the examples
    std::shared_ptr<netlist> nl_1 = create_example_netlist(1);
    std::shared_ptr<netlist> nl_2 = create_example_netlist_2(2);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // Get successors for a gate with multiple successors (some of them are the same gate)
        std::shared_ptr<gate> gate_0 = nl_2->get_gate_by_id(1);
        std::vector<endpoint> succ   = {get_endpoint(nl_2, 2, "I0"), get_endpoint(nl_2, 2, "I1"), get_endpoint(nl_2, 2, "I2"), get_endpoint(nl_2, 4, "I0")};
        EXPECT_TRUE(vectors_have_same_content(gate_0->get_successors(), succ));
        EXPECT_EQ(gate_0->get_successors().size(), (size_t)4);
    }
    {
        // Get successors for a gate no successors
        std::shared_ptr<gate> gate_1 = nl_2->get_gate_by_id(2);
        EXPECT_TRUE(gate_1->get_successors().empty());
    }
    {
        // Get successors for a given (existing) pin type
        std::shared_ptr<gate> gate_0 = nl_2->get_gate_by_id(1);
        std::vector<endpoint> succ   = {get_endpoint(nl_2, 2, "I0"), get_endpoint(nl_2, 4, "I0")};
        EXPECT_TRUE(vectors_have_same_content(gate_0->get_successors(DONT_CARE, "I0"), succ));
        EXPECT_EQ(gate_0->get_successors(DONT_CARE, "I0").size(), (size_t)2);
    }
    {
        // Get successors for a given (non-existing) pin type
        std::shared_ptr<gate> gate_0 = nl_2->get_gate_by_id(1);
        EXPECT_TRUE(gate_0->get_successors(DONT_CARE, "NEx_PIN").empty());
        EXPECT_EQ(gate_0->get_successors(DONT_CARE, "NEx_PIN").size(), (size_t)0);
    }
    {
        // Get successors for a given (existing) gate type
        std::shared_ptr<gate> gate_0 = nl_1->get_gate_by_id(1);
        std::vector<endpoint> succ   = {get_endpoint(nl_1, 5, "I")};
        EXPECT_TRUE(vectors_have_same_content(gate_0->get_successors(DONT_CARE, DONT_CARE, "INV"), succ));
        EXPECT_EQ(gate_0->get_successors(DONT_CARE, DONT_CARE, "INV").size(), (size_t)1);
    }
    {
        // Get successors for a given (non-existing) gate type
        std::shared_ptr<gate> gate_0 = nl_1->get_gate_by_id(1);
        EXPECT_TRUE(gate_0->get_successors(DONT_CARE, DONT_CARE, "NEx_GATE").empty());
        EXPECT_EQ(gate_0->get_successors(DONT_CARE, DONT_CARE, "NEx_GATE").size(), (size_t)0);
    }
    //        {
    //            // Get successors for a given decorator type
    //            std::shared_ptr<netlist> dec_nl = create_example_netlist(3);
    //            register_test_decorator(dec_nl, "INV"); // Register a decorator for X_INV
    //            std::vector<endpoint> succ = {
    //                    get_endpoint(dec_nl,4,"I")
    //            };
    //            std::shared_ptr<gate> gate_0 = dec_nl->get_gate_by_id(0);
    //            EXPECT_EQ(gate_0->get_successors(DONT_CARE, DONT_CARE, "test_decorator"), succ);
    //            EXPECT_EQ(gate_0->get_num_of_successors(DONT_CARE, DONT_CARE, "test_decorator"), 1);
    //        }

    // ########################
    // NEGATIVE TESTS
    // ########################
    std::shared_ptr<netlist> nl_neg = create_example_netlist_negative(2);
    {
        // Get successors for a gate with unconnected nets
        std::shared_ptr<gate> gate_0 = nl_neg->get_gate_by_id(1);
        EXPECT_TRUE(gate_0->get_successors().empty());
    }
    TEST_END
}

/**
 * Testing the get_unique_predecessors and get_unique_successors function
 *
 * Functions: get_unique_predecessors, get_unique_successors
 */
TEST_F(gate_test, check_get_unique_predecessors_and_successors)
{
    TEST_START
    // Create the examples
    std::shared_ptr<netlist> nl_2 = create_example_netlist_2(2);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // Get the unique predecessors
        std::shared_ptr<gate> gate_1 = nl_2->get_gate_by_id(2);
        std::set<endpoint> pred      = {get_endpoint(nl_2, 1, "O"), get_endpoint(nl_2, 1, "O"), get_endpoint(nl_2, 3, "O")};
        EXPECT_TRUE((gate_1->get_unique_predecessors() == pred));
    }
    {
        // Get the unique successors
        std::shared_ptr<gate> gate_0 = nl_2->get_gate_by_id(1);
        std::set<endpoint> succ      = {get_endpoint(nl_2, 2, "I0"), get_endpoint(nl_2, 2, "I1"), get_endpoint(nl_2, 2, "I2"), get_endpoint(nl_2, 4, "I0")};
        EXPECT_TRUE((gate_0->get_unique_successors() == succ));
    }
    TEST_END
}

/**
 * Testing the get_predecessor function (TODO: wrong documentation/function ?)
 *
 * Functions: get_predecessor
 */
TEST_F(gate_test, check_get_predecessor)
{
    TEST_START
    // Create the examples
    std::shared_ptr<netlist> nl_2 = create_example_netlist_2(2);

    // ########################
    // POSITIVE TESTS
    // ########################
    {
        // This way the function shouldn't work...
        std::shared_ptr<gate> gate_1 = nl_2->get_gate_by_id(2);
        //auto pred = gate_1->get_predecessor("O");
        //EXPECT_EQ(1,2);
    }

    // TODO: True tests if requirements are clear
    TEST_END
}

// TODO: Tests with decorator type
