// message_center.js
const { apiDomain } = require('../../../config');

Page({
  data: {
    activeTab: 0,
    loading: false,
    statusBarHeight: 0,
    commentCount: 0,
    announceCount: 0,
    likeCount: 0,
    challengeCount: 0,
    commentList: [],
    announceList: [],
    likeList: [],
    challengeList: [],
    pagination: {
      comment: { hasMore: true, lastCursor: '0' },
      announce: { hasMore: true, lastCursor: '0' },
      like: { hasMore: true, lastCursor: '0' },
      challenge: { hasMore: true, lastCursor: '0' }
    },
    // 新增公告弹窗相关数据
    showAnnounceModal: false,
    currentAnnounce: {
      title: '',
      content: '',
      user_avatar: '',
      user_account: '',
      create_time: ''
    },
    
  },

  onLoad() {
    const systemInfo = wx.getSystemInfoSync();
    this.setData({ statusBarHeight: systemInfo.statusBarHeight });
    this.initData()
  },

  // 初始化数据（合并未读数和消息加载）
  async initData() {
    console.log(this.data.loading)
    try {
      // // 并行获取未读数和评论消息
      await this.fetchMessages()
      await this.fetchMessages()
      // 计算各tab消息总数
      this.calculateTotalCounts();
    } catch (error) {
      console.error('初始化数据失败:', error);
      wx.showToast({ title: '加载失败', icon: 'none' });
    }
  },

  // 计算各tab消息总数
  calculateTotalCounts() {
    this.setData({
      commentTotal: this.data.commentList.length,
      announceTotal: this.data.announceList.length,
      likeTotal: this.data.likeList.length,
      challengeTotal: this.data.challengeList.length
    });
  },


  // 获取消息列表
  async fetchMessages() {
    if (this.data.loading) {
      console.warn('[fetchMessages] 正在加载中，跳过重复请求');
      return;
    }

    console.groupCollapsed(`[fetchMessages] 开始获取消息，当前tab: ${this.data.activeTab}`);
    console.log('[参数检查]', {
      activeTab: this.data.activeTab,
      loading: this.data.loading,
      pagination: this.data.pagination
    });

    const apiMap = {
      0: 'comment_info',
      1: 'announcement_notification',
      2: 'like_notification',
      3: 'notification/challenge_info'
    };
    const currentApi = apiMap[this.data.activeTab];
    const paginationKey = ['comment','announce','like','challenge'][this.data.activeTab];
    const currentPagination = this.data.pagination[paginationKey];

    console.log('[API配置]', {
      currentApi,
      paginationKey,
      currentPagination
    });

    if (!currentPagination.hasMore) {
      console.warn('[分页检查] 没有更多数据，终止请求');
      console.groupEnd();
      return;
    }

    this.setData({ loading: true });
    console.log('[状态更新] 设置loading=true');

    try {
      const params = {
        size: 10,
        lastCursor: currentPagination.lastCursor,
        sort: 'id'
      };

      // 两种请求方式对比调试
      const requestConfig = {
        url: `https://${apiDomain}/api/auth/${currentApi}`,
        method: 'GET',
        // 错误示范：GET请求参数放在data中（但某些服务器可能兼容）
        data: params,
        // 正确做法：应该使用URL参数
        // url: `http://${apiDomain}:8888/api/auth/${currentApi}?${Object.entries(params).map(([k,v])=>`${k}=${encodeURIComponent(v)}`).join('&')}`,
        // method: 'GET'
      };

      console.log('[请求配置]', JSON.parse(JSON.stringify(requestConfig)));

      const startTime = Date.now();
      const res = await this.request(requestConfig);
      const requestDuration = Date.now() - startTime;

      console.log(`[响应结果] 耗时 ${requestDuration}ms`, {
        status: res.statusCode,
        headers: res.header,
        data: res.data
      });
      
      console.log('[接口原始响应]', res)
      if (res.data.code === '0' || res.data.code === '200') {
        console.log('[数据处理] 开始格式化消息列表');
        const rawData = res.data.data.data || res.data.data;
        const newList = this.formatMessageList(rawData, this.data.activeTab);
        const listKey = ['commentList', 'announceList', 'likeList', 'challengeList'][this.data.activeTab];

        console.log('[格式化结果]', {
          rawDataLength: rawData?.length || 0,
          formattedDataSample: newList.slice(0, 1),
          listKey
        });

        this.setData({
          [listKey]: currentPagination.lastCursor !== '0' 
            ? [...this.data[listKey], ...newList] 
            : newList,
          [`pagination.${paginationKey}`]: {
            hasMore: !!res.data.data.nextCursor,
            lastCursor: res.data.data.nextCursor
          }
        }, () => {
          console.log('[状态更新完成]', {
            currentListLength: this.data[listKey].length,
            newPagination: this.data.pagination[paginationKey],
            data: this.data
          });
          
          this.calculateTotalCounts();
        });
      } else {
        console.error('[响应异常] 业务代码错误', {
          code: res.data.code,
          message: res.data.msg
        });
      }
    } catch (error) {
      console.error('[请求失败]', {
        error: error.message,
        stack: error.stack,
        requestError: error.errMsg || error.config
      });
      wx.showToast({ title: '加载失败', icon: 'none' });
    } finally {
      this.setData({ loading: false });
      console.log('[状态更新] 设置loading=false');
      console.groupEnd();
    }
  },

  // 格式化消息数据
  formatMessageList(list, type) {
    const formatters = [
      // 评论
      item => {
        const userId = item.user_id?.toString() || '';
        let avatar = '/static/images/default-avatar.jpg'
        if (item.avatar){
          avatar = `https://${apiDomain}${JSON.parse(item.avatar).url}`
        }
        return {
          id: item.id,
          post_id: item.post_id, // 新增post_id用于跳转
          avatar: avatar,
          username: item.account || '用户' + (userId ? userId.slice(-4) : ''),
          title: item.title || '未知游记',
          content: item.content,
          date: this.formatTime(item.created_time),
          read: item.is_read
        };
      },
      // 公告
      item => ({
        id: item.id,
        title: item.title,
        content: item.content,
        date: this.formatTime(item.update_time || item.created_time),
        read: item.is_read
      }),
      // 点赞
      item => {
        const userId = item.user_id?.toString() || '';
        let avatar = '/static/images/default-avatar.jpg'
        if (item.cover){
          avatar = `https://${apiDomain}${JSON.parse(item.cover).url}`
        }
        console.log('[处理后的头像url]', avatar)
        return {
          id: item.id, // 使用post_id作为跳转参数
          post_id: item.post_id,
          avatar: avatar,
          username: item.account || '用户' + (userId ? userId.slice(-4) : ''),
          title: item.title || '未知内容',
          date: this.formatTime(item.created_time),
          read: item.is_read
        };
      },
      // 挑战
      item => ({
        id: item.id,
        content: item.content,
        date: this.formatTime(item.create_time),
        read: true
      })
    ];

    return (list || []).map(item => {
      try {
        return formatters[type](item);
      } catch (e) {
        console.error('格式化消息失败:', { error: e, rawItem: item });
        return null;
      }
    }).filter(Boolean);
  },

  // 点击评论/点赞项跳转到博客详情
  navigateToBlogDetail(e) {
    console.log('[DEBUG] 点击博客跳转', {
      event: e,
      dataset: e.currentTarget.dataset
    });
    const { postid, type, id, index} = e.currentTarget.dataset;

    // 本地更新已读状态
    const tabMap = {
      0: 'commentList',
      1: 'announceList',
      2: 'likeList',
      3: 'challengeList'
    };
    const listKey = tabMap[this.data.activeTab];
    if (!listKey) return;
    
    let list = this.data[listKey];
    if (!list[index].read) {
      list[index].read = true;
      this.setData({
        [listKey]: list
      });
    }
    if (!postid) {
      console.warn('[WARN] 缺少postid参数', e.currentTarget.dataset);
      return;
    }
    console.log('跳转对应ID', postid)
    console.log('[DEBUG] 准备跳转到博客详情', { postid });
    
    this.markAsRead(type, id);
    wx.navigateTo({
      url: `/pages/interaction/blog/blog_detail/blog_detail?id=${postid}`,
      success: (res) => {
        console.log('[DEBUG] 跳转成功', res);
        this.__isBackFromOtherPage = true; // +++ 标记需要刷新 +++
      },
      fail: (err) => {
        console.error('[ERROR] 跳转失败', err);
        wx.showToast({ title: '跳转失败', icon: 'none' });
      }
    });
  },

  // 点击公告项显示详情弹窗
  async showAnnounceDetail(e) {
    console.log('[DEBUG] 点击公告详情', {
      event: e,
      dataset: e.currentTarget.dataset
    });
    
    const { id, index } = e.currentTarget.dataset;
    if (!id) {
      console.warn('[WARN] 缺少公告id参数', e.currentTarget.dataset);
      return;
    }

    try {
      console.log('[DEBUG] 请求公告详情', { id });
      const res = await this.request({
        url: `https://${apiDomain}/api/auth/announcement_info/${id}`,
        method: 'GET'
      });

      console.log('[DEBUG] 公告详情响应', {
        status: res.statusCode,
        data: res.data
      });

      if (res.data.code === '0' || res.data.code === '200') {
        console.log('[DEBUG] 显示公告弹窗');
        this.setData({
          showAnnounceModal: true,
          currentAnnounce: {
            title: res.data.data.title,
            content: res.data.data.content,
            user_avatar: res.data.data.user_avatar || '/images/default-avatar.jpg',
            user_account: res.data.data.user_account || '系统管理员',
            create_time: this.formatTime(res.data.data.create_time)
          }
        });
        console.log(index)
        this.markAsRead(1, id);
      } else {
        console.warn('[WARN] 公告接口返回异常', res.data);
        wx.showToast({ title: '加载公告详情失败', icon: 'none' });
      }
    } catch (error) {
      console.error('[ERROR] 获取公告详情失败', {
        error: error.errMsg,
        stack: error.stack
      });
      wx.showToast({ title: '加载公告详情失败', icon: 'none' });
    }
  },

  // 关闭公告弹窗
  hideAnnounceModal() {
    this.setData({ showAnnounceModal: false });
  },

  // 标记消息为已读
  async markAsRead(type, messageId) {
    // 1. 先更新本地状态
  const tabNamesE = ['comment', 'announce', 'like', 'challenge'];
  const listKey = `${tabNamesE[type]}List`;
  
  this.setData({
    [listKey]: this.data[listKey].map(item => {
        return { ...item, is_read: true };
    })
  });

  // 2. 调用API（失败时不回滚，保持乐观更新）
    // 确保type是数字类型（处理可能的字符串数字如"0"）
    const typeNum = Number(type);
    const typeNames = ['评论', '公告', '点赞', '挑战'];
    const typeName = typeNames[typeNum] || '未知';
  
    console.groupCollapsed(`[markAsRead] 标记已读 ${typeName}(${typeNum}) id=${messageId}`);
    
    try {
      let apiPath, requestData;
      
      switch(typeNum) {
        case 0: // 评论
          apiPath = `/api/v1/comment/${messageId}`;
          requestData = {}; // 需要空对象
          break;
        case 1: // 公告
          apiPath = `/api/v1/annoucement/${messageId}`;
          requestData = {}; // 需要空对象
          break;
        case 2: // 点赞
          apiPath = `/api/v1/like/${messageId}`;
          requestData = null; // 需要null
          break;
        case 3: // 挑战
          apiPath = '/api/auth/message/mark-read';
          requestData = { type: 'challenge', messageIds: [messageId] };
          break;
        default:
          throw new Error(`不支持的消息类型: ${type} (处理后: ${typeNum})`);
      }
  
      console.log('API请求:', { apiPath, body: requestData });
  
      const res = await this.request({
        url: `https://${apiDomain}${apiPath}`,
        method: 'POST',
        data: requestData
      });
  
      if (res.data.code === '0' || res.data.code === '200') {
        console.log('标记已读成功', res.data);
        
        // 返回跳转ID（如果接口有返回）
        const resultData = {
          postId: res.data.data?.post_id || res.data.data?.postId,
          announceId: res.data.data?.Announcement_id
        };
        
        return resultData.postId || resultData.announceId;
      } else {
         
        throw new Error(res.data.msg || '标记失败'); 
      }
    } catch (error) {
      console.error('标记失败:', error);
      wx.showToast({ title: `操作失败: ${error.message}`, icon: 'none' });
      throw error; // 继续向上抛出错误
    } finally {
      console.groupEnd();
    }
  },



  formatTime(timeString) {
    if (!timeString) return '';
    try {
      const date = new Date(timeString);
      const now = new Date();
      const diff = Math.floor((now - date) / 1000);
      
      if (diff < 60) return '刚刚';
      if (diff < 3600) return `${Math.floor(diff/60)}分钟前`;
      if (diff < 86400) return `${Math.floor(diff/3600)}小时前`;
      
      return `${date.getMonth()+1}月${date.getDate()}日`;
    } catch {
      return '';
    }
  },

  switchTab(e) {
    const index = parseInt(e.currentTarget.dataset.index);
    if (this.data.activeTab === index) return;

    this.setData({ activeTab: index }, () => {
      const currentList = this.data[['commentList','announceList','likeList','challengeList'][index]];
      if (currentList.length === 0) this.fetchMessages();
    });
  },

  loadMore() {
    this.fetchMessages();
  },
  calculateUnreadByLocal() {
    this.setData({
      commentCount: this.data.commentList.filter(item => !item.is_read).length,
      likeCount: this.data.likeList.filter(item => !item.is_read).length,
      // 公告和挑战通常没有read字段
    });
  },
  request(options) {
    const token = wx.getStorageSync('token');
    console.log(token)
    return new Promise((resolve, reject) => {
      wx.request({
        url: options.url,
        method: options.method || 'GET',
        data: options.data,
        header: {
          'Authorization': `Bearer ${token}`,
          'Content-Type': 'application/json'
        },
        success: res => resolve(res),
        fail: err => reject(err)
      });
    });
  },

  navigateBack() {
    wx.navigateBack();
  }
});