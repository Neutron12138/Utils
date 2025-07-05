#include <iostream>
#include "../utils/utils.hpp"

void print_node_state(const utils::NodeRef &node);
void print_node_state(const utils::TreeNodeRef &node);
void test1();
void test2();

int main()
{
    std::cout << "----------test1----------" << std::endl;
    test1();
    std::cout << "----------test2----------" << std::endl;
    test2();

    return 0;
}

void print_node_state(const utils::NodeRef &node)
{
    std::cout << node.get() << "\tis child: " << node->is_child() << "\tis root:" << node->is_root() << std::endl;
}

void print_node_state(const utils::TreeNodeRef &node)
{
    std::cout << node.get() << "\tis child: " << node->is_child() << "\tis root: " << node->is_root()
              << "\ttree: " << node->get_tree().lock().get() << std::endl;
}

void test1()
{
    utils::NodeRef root = utils::Node::create();
    utils::NodeRef child1 = utils::Node::create();
    utils::NodeRef child2 = utils::Node::create();
    utils::NodeRef child1_1 = utils::Node::create();
    utils::NodeRef child1_2 = utils::Node::create();
    utils::NodeRef child2_1 = utils::Node::create();
    utils::NodeRef child2_2 = utils::Node::create();

    child1->add_child(child1_1);
    child1->add_child(child1_2);
    child2->add_child(child2_1);
    child2->add_child(child2_2);
    root->add_child(child1);
    root->add_child(child2);

    print_node_state(root);
    print_node_state(child1);
    print_node_state(child2);
    print_node_state(child1_1);
    print_node_state(child1_2);
    print_node_state(child2_1);
    print_node_state(child2_2);
}

void test2()
{
    utils::NodeTreeRef tree1 = utils::NodeTree::create();
    utils::NodeTreeRef tree2 = utils::NodeTree::create();

    utils::TreeNodeRef root1 = tree1->get_root();
    utils::TreeNodeRef root2 = tree2->get_root();

    utils::TreeNodeRef child1_1 = utils::TreeNode::create();
    utils::TreeNodeRef child1_2 = utils::TreeNode::create();
    utils::TreeNodeRef child2_1 = utils::TreeNode::create();
    utils::TreeNodeRef child2_2 = utils::TreeNode::create();

    root1->add_child(child1_1);
    root1->add_child(child1_2);
    root2->add_child(child2_1);
    root2->add_child(child2_2);

    print_node_state(root1);
    print_node_state(root2);
    print_node_state(child1_1);
    print_node_state(child1_2);
    print_node_state(child2_1);
    print_node_state(child2_2);
}
