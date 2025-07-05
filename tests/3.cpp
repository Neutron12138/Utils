#include <iostream>
#include "../utils/utils.hpp"

class MyTreeNode : public utils::TreeNode
{
public:
    static utils::TreeNodeRef create()
    {
        auto node = std::shared_ptr<MyTreeNode>(new MyTreeNode());
        node->_recursive_set_root(node);
        return node;
    }

public:
    ~MyTreeNode() override = default;

protected:
    void _on_enter_tree(const utils::NodeTreeRef &tree) override
    {
        std::cout << "MyTreeNode@" << this << " enter tree" << std::endl;
    }

    void _on_ready() override
    {
        std::cout << "MyTreeNode@" << this << " ready" << std::endl;
    }

    void _on_exit_tree(const utils::NodeTreeRef &tree) override
    {
        std::cout << "MyTreeNode@" << this << " exit tree" << std::endl;
    }
};

int main()
{
    utils::NodeTreeRef tree = utils::NodeTree::create();
    utils::TreeNodeRef root = tree->get_root();

    utils::TreeNodeRef child1 = MyTreeNode::create();
    utils::TreeNodeRef child1_1 = MyTreeNode::create();

    // 尝试添加空对象
    try
    {
        //root->add_child(utils::TreeNodeRef());
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    // 尝试添加自身
    try
    {
        child1->add_child(child1);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    child1->add_child(child1_1);
    root->add_child(child1);

    // 尝试重复添加
    try
    {
        root->add_child(child1);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }
    try
    {
        root->add_child(child1_1);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    // 尝试添加非TreeNode节点
    utils::NodeRef non_tree_node = utils::Node::create();
    try
    {
        root->add_child(non_tree_node);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    // 尝试删除空对象
    try
    {
        root->remove_child(utils::TreeNodeRef());
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    std::cout << "----------initialize----------" << std::endl;
    tree->request_initialize();
    std::cout << "root: " << root << std::endl
              << "child1: " << child1 << std::endl
              << "child1_1: " << child1_1 << std::endl
              << std::endl;

    std::cout << "----------after initialized----------" << std::endl;
    utils::TreeNodeRef child2 = MyTreeNode::create();
    utils::TreeNodeRef child2_1 = MyTreeNode::create();
    child2->add_child(child2_1);
    root->add_child(child2);
    std::cout << "child2: " << child2 << std::endl
              << "child2_1: " << child2_1 << std::endl
              << std::endl;

    root->remove_child(child1);
    std::cout << "child1: " << child1 << std::endl
              << "child1_1: " << child1_1 << std::endl
              << std::endl;

    // 尝试重复初始化
    try
    {
        tree->request_initialize();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    std::cout << "----------finalize----------" << std::endl;
    tree->request_finalize();
    std::cout << "tree: " << tree << std::endl
              << "root: " << root << std::endl
              << std::endl;

    return 0;
}
