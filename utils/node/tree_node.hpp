#pragma once

#include "node.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(TreeNode);
    BASE_DECLARE_REF_TYPE(NodeTree);

    /// @brief 树节点类，用于NodeTree，不兼容Node
    class TreeNode : public Node
    {
        friend NodeTree;

    public:
        /// @brief 创建一个节点对象
        /// @return 节点对象引用
        static TreeNodeRef create();

    private:
        /// @brief 该节点所归属的节点树
        NodeTreeWeakRef m_tree;
        /// @brief 该节点是否准备就绪
        bool m_is_ready = false;

    protected:
        inline TreeNode() = default;

    public:
        inline ~TreeNode() override { _reset_tree(); }

    protected:
        /// @brief 当进入节点树时
        /// @param tree 节点树
        virtual void _on_enter_tree(const NodeTreeRef &tree) {}

        /// @brief 当所有子节点ready时
        virtual void _on_ready() {}

        /// @brief 当退出节点树时
        /// @param tree 节点树
        virtual void _on_exit_tree(const NodeTreeRef &tree) {}

    public:
        inline bool is_in_tree() const { return !m_tree.expired(); }
        inline const NodeTreeWeakRef &get_tree() const { return m_tree; }
        inline bool is_ready() const { return m_is_ready; }

    protected:
        /// @brief 递归设置根节点
        /// @param root 根节点
        void _recursive_set_root(const NodeRef &root) override;

        /// @brief 解除与节点树的联系
        void _reset_tree();

        /// @brief 请求进入节点树
        void _request_enter_tree();

        /// @brief 请求准备就绪
        void _request_ready();

        /// @brief 请求退出节点树
        void _request_exit_tree();

    public:
        /// @brief 转换成字符串
        /// @return 转换后的字符串
        std::string to_string() const override;

        /// @brief 与父节点分离，会解除双方的引用
        void detach_from_parent() override;

        /// @brief 添加一个子节点
        /// @param node 待添加节点
        void add_child(const NodeRef &node) override;

        /// @brief 移除一个子节点
        /// @param node 待移除节点
        void remove_child(const NodeRef &node) override;

        /// @brief 清空自身所有子节点
        void clear_children() override;
    };

    /// @brief 序列化节点
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const TreeNode &node);

    /// @brief 序列化节点
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const TreeNodeRef &node);

    /// @brief 序列化节点
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const TreeNodeWeakRef &node);

} // namespace utils
