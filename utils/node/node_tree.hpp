#pragma once

#include <base/core/type.hpp>
#include "tree_node.hpp"

#define UTILS_NODETREE_MAKE_ERROR(message, self) \
    BASE_MAKE_CLASS_RUNTIME_ERROR(message, "\nself: ", self)

namespace utils
{
    /// @brief 节点树
    class NodeTree : virtual public base::ReferenceObject,
                     public PrintableObject
    {
    public:
        /// @brief 节点树状态
        enum class Status : base::Int32
        {
            /// @brief 尚未初始化
            Uninitialized,
            /// @brief 正在初始化
            Initializing,
            /// @brief 已就绪
            Ready,
        };

        /// @brief 创建一个节点树
        /// @return 节点树引用
        static NodeTreeRef create();

    private:
        /// @brief 根节点
        TreeNodeRef m_root;
        /// @brief 当前状态
        Status m_status = Status::Uninitialized;

    protected:
        NodeTree() = default;

    public:
        ~NodeTree() override = default;

    protected:
        /// @brief 当节点树初始化时
        virtual void _on_initialize();

        /// @brief 当节点树就绪时
        virtual void _on_ready();

        /// @brief 当节点树结束时
        virtual void _on_finalize();

    public:
        const TreeNodeRef &get_root() const;
        Status get_status() const;

    protected:
        /// @brief 强行设为根节点
        /// @param root 待设置根节点
        void _set_root(const TreeNodeRef &root);

        /// @brief 强行移除根节点
        void _remove_root();

        /// @brief 请求进入节点树
        /// @param node 节点对象
        void _request_enter_tree(const TreeNodeRef &node) const;

        /// @brief 请求准备就绪
        /// @param node 节点对象
        void _request_ready(const TreeNodeRef &node) const;

        /// @brief 请求退出节点树
        /// @param node 节点对象
        void _request_exit_tree(const TreeNodeRef &node) const;

    public:
        /// @brief 转换成字符串
        /// @return 转换后的字符串
        std::string to_string() const override;

        /// @brief 请求节点树初始化
        virtual void request_initialize();

        /// @brief 请求节点树结束
        virtual void request_finalize();
    };

    /// @brief 序列化节点树状态枚举
    /// @param os 输出流
    /// @param status 状态枚举
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, NodeTree::Status status);

    /// @brief 序列化节点树
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeTree &node);

    /// @brief 序列化节点树
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeTreeRef &node);

    /// @brief 序列化节点树
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeTreeWeakRef &node);

} // namespace utils
