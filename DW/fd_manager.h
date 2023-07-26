#pragma once

#include <memory>
#include <vector>
#include "thread.h"
#include "singleton.h"

namespace DW {

    //文件句柄上下文类
    class FdCtx : public std::enable_shared_from_this<FdCtx> {
    public:
        typedef std::shared_ptr<FdCtx> ptr;

        FdCtx(int fd);
        ~FdCtx();

        //是否初始化完成
        bool isInit() const { return m_isInit;}

        //是否socket
        bool isSocket() const { return m_isSocket;}

        //是否已关闭
        bool isClose() const { return m_isClosed;}

        // 设置用户主动设置非阻塞
        void setUserNonblock(bool v) { m_userNonblock = v;}

        //获取是否用户主动设置的非阻塞
        bool getUserNonblock() const { return m_userNonblock;}

        //设置系统非阻塞
        void setSysNonblock(bool v) { m_sysNonblock = v;}

        //获取系统非阻塞
        bool getSysNonblock() const { return m_sysNonblock;}

        //设置超时时间
        void setTimeout(int type, uint64_t v);

        //获取超时时间
        uint64_t getTimeout(int type);
    private:
        //初始化
        bool init();
    private:
        /// 是否初始化
        bool m_isInit: 1;   //设置位域
        /// 是否socket
        bool m_isSocket: 1;
        /// 是否hook非阻塞
        bool m_sysNonblock: 1;
        /// 是否用户主动设置非阻塞
        bool m_userNonblock: 1;
        /// 是否关闭
        bool m_isClosed: 1;
        /// 文件句柄
        int m_fd;
        /// 读超时时间毫秒
        uint64_t m_recvTimeout;
        /// 写超时时间毫秒
        uint64_t m_sendTimeout;
    };

    //文件句柄管理类
    class FdManager {
    public:
        typedef RWMutex RWMutexType;
        FdManager();

        /**
         * @brief 获取/创建文件句柄类FdCtx
         * @param[in] fd 文件句柄
         * @param[in] auto_create 是否自动创建
         * @return 返回对应文件句柄类FdCtx::ptr
         */
        FdCtx::ptr get(int fd, bool auto_create = false);

        /**
         * @brief 删除文件句柄类
         * @param[in] fd 文件句柄
         */
        void del(int fd);
    private:
        /// 读写锁
        RWMutexType m_mutex;
        /// 文件句柄集合
        std::vector<FdCtx::ptr> m_datas;
    };

    /// 文件句柄单例
    using FdMgr = Singleton<FdManager>;

}