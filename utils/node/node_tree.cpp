#include <base/core/exception.hpp>
#include "node_tree.hpp"

namespace utils
{
    NodeTreeRef NodeTree::create()
    {
        NodeTreeRef tree = std::shared_ptr<NodeTree>(new NodeTree());
        TreeNodeRef root = TreeNode::create();
        tree->_set_root(root);
        return tree;
    }

    void NodeTree::_set_root(const TreeNodeRef &root)
    {
        root->m_tree = as<NodeTree>();
        m_root = root;
    }

    void NodeTree::_remove_root()
    {
        m_root->m_tree.reset();
        m_root->_recursive_set_root(m_root);
        m_root.reset();
    }

    void NodeTree::_request_enter_tree(const TreeNodeRef &node) const
    {
        auto self = shared_from_this();

        // 检查对象是否有效
        if (!node)
            throw UTILS_NODE_MAKE_ERROR("Cannot notify an empty node", self, node);
        // 节点必须在节点树中
        if (node->m_tree.expired())
            throw UTILS_NODE_MAKE_ERROR("This node must be in the NodeTree", self, node);
        // 确保节点的节点树是自身
        if (node->m_tree.lock() != self)
            throw UTILS_NODE_MAKE_ERROR("This node is not in the current node tree", self, node);

        node->_request_enter_tree();
    }

    void NodeTree::_request_ready(const TreeNodeRef &node) const
    {
        auto self = shared_from_this();

        // 检查对象是否有效
        if (!node)
            throw UTILS_NODE_MAKE_ERROR("Cannot notify an empty node", self, node);
        // 节点必须在节点树中
        if (node->m_tree.expired())
            throw UTILS_NODE_MAKE_ERROR("This node must be in the NodeTree", self, node);
        // 确保节点的节点树是自身
        if (node->m_tree.lock() != self)
            throw UTILS_NODE_MAKE_ERROR("This node is not in the current node tree", self, node);

        node->_request_enter_tree();
    }

    void NodeTree::_request_exit_tree(const TreeNodeRef &node) const
    {
        auto self = shared_from_this();

        // 检查对象是否有效
        if (!node)
            throw UTILS_NODE_MAKE_ERROR("Cannot notify an empty node", self, node);
        // 节点必须在节点树中
        if (node->m_tree.expired())
            throw UTILS_NODE_MAKE_ERROR("This node must be in the NodeTree", self, node);
        // 确保节点的节点树是自身
        if (node->m_tree.lock() != self)
            throw UTILS_NODE_MAKE_ERROR("This node is not in the current node tree", self, node);

        node->_request_enter_tree();
    }

    std::string NodeTree::to_string() const
    {
        std::stringstream sstr;

        sstr << "NodeTree@" << this << "[";

        if (m_root)
            sstr << "root@" << m_root.get();
        else
            sstr << "root@null";

        sstr << ", status: " << m_status << "]";

        return sstr.str();
    }

    void NodeTree::request_initialize()
    {
        // 只有在未被初始化时才能初始化
        if (m_status != Status::Uninitialized)
            throw BASE_NODETREE_MAKE_ERROR("The NodeTree has been initialized", as<NodeTree>());

        // 初始化
        m_status = Status::Initializing;
        _on_initialize();
        m_root->_request_enter_tree();

        // 准备就绪
        m_root->_request_ready();
        m_status = Status::Ready;
        _on_ready();
    }

    void NodeTree::request_finalize()
    {
        // 只有准备就绪后才能结束
        if (m_status != Status::Ready)
            throw BASE_NODETREE_MAKE_ERROR("The NodeTree has not been initialized yet", as<NodeTree>());

        // 结束
        m_root->_request_exit_tree();
        m_root->clear_children();
        _on_finalize();
        m_status = Status::Uninitialized;
    }

    std::ostream &operator<<(std::ostream &os, NodeTree::Status status)
    {
        switch (status)
        {
        case NodeTree::Status::Uninitialized:
            os << "Uninitialized";
            break;

        case NodeTree::Status::Initializing:
            os << "Initializing";
            break;

        case NodeTree::Status::Ready:
            os << "Ready";
            break;

        default:
            os << "Unknown";
            break;
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const NodeTree &tree)
    {
        os << tree.to_string();
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const NodeTreeRef &tree)
    {
        if (tree)
            os << *tree;
        else
            os << "Node@null";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const NodeTreeWeakRef &tree)
    {
        if (tree.expired())
            os << "Node@null";
        else
            os << *tree.lock();
        return os;
    }

} // namespace utils
