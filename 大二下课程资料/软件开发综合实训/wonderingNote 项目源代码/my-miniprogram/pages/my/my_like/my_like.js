const { apiDomain } = require("../../../config");

// 封装wx.request为Promise
function request(options) {
  return new Promise((resolve, reject) => {
    wx.request({
      ...options,
      success: (res) => {
        if (res.statusCode >= 200 && res.statusCode < 300) {
          resolve(res);
        } else {
          reject(res);
        }
      },
      fail: (err) => {
        reject(err);
      }
    });
  });
}

Page({
  data: {
    searchValue: '',
    likesData: [],
    lastCursor: '0',
    pageSize: 10,
    loading: false,
    hasMore: true
  },

  onLoad() {
    this.fetchLikes();
  },

  async fetchLikes(isRefresh = false) {
    if (this.data.loading || (!this.data.hasMore && !isRefresh)) return;

    this.setData({ loading: true });
    const token = wx.getStorageSync('token');

    try {
      const queryParams = [
        `size=${this.data.pageSize}`,
        ...(this.data.lastCursor && !isRefresh ? [`lastCursor=${this.data.lastCursor}`] : [])
      ].join('&');

      console.log('[DEBUG] 请求参数:', {
        url: `https://${apiDomain}/api/auth/likes_info?${queryParams}&sort=id`,
        method: 'GET',
        size: this.data.pageSize,
        lastCursor: this.data.lastCursor
      });
      console.log(token)

      const res = await request({
        url: `https://${apiDomain}/api/auth/likes_info?${queryParams}&sort=id`,
        method: 'GET',
        header: {
          'Authorization': `Bearer ${token}`
        }
      });

      console.log('[DEBUG] 原始响应数据:', res.data);

      if (res.statusCode === 200 && res.data.code === '0') {
        const responseData = res.data.data;
        console.log('[DEBUG] 接口返回的有效数据:', responseData);

        // 增强数据校验和处理
        const newList = responseData.data
          .filter(item => {
            // 确保item和必要字段存在
            const isValid = item && item.post_id && item.title;
            if (!isValid) {
              console.warn('[WARN] 过滤无效数据项:', item);
            }
            return isValid;
          })
          .map(item => {
            try {
              const formattedItem = {
                id: item.id || 0,
                postId: item.post_id || 0,
                title: item.title || '无标题',
                viewCount: item.view_count || 0,
                likeCount: item.like_count || 0,
                commentCount: item.comment_count || 0,
                createTime: item.create_time || new Date().toISOString(),
                date: this.formatTime(item.create_time),
                weekday: this.getWeekday(item.create_time),
                location: item.location ? this.formatLocation(item.location) : '未知地点',
                cover: (item.cover && item.cover != '{}') ? this.processImageUrl(item.cover) : '/static/images/default-blog-cover.jpg'
              };
              
              // 额外校验关键字段
              if (!formattedItem.postId) {
                console.warn('[WARN] 博文ID缺失:', item);
                formattedItem.postId = 0;
              }
              
              return formattedItem;
            } catch (e) {
              console.error('[ERROR] 格式化数据项出错:', e, '原始数据:', item);
              return null;
            }
          })
          .filter(item => item !== null); // 过滤掉格式化失败的项目

        console.log('[DEBUG] 格式化后的列表数据:', newList);

        this.setData({
          likesData: isRefresh ? newList : [...this.data.likesData, ...newList],
          lastCursor: responseData.nextCursor,
          hasMore: !!responseData.nextCursor && newList.length > 0
        });

        console.log('[DEBUG] 更新后的页面数据状态:', {
          listLength: this.data.likesData.length,
          lastCursor: this.data.lastCursor,
          hasMore: this.data.hasMore
        });

        // 如果没有数据且不是刷新操作，显示提示
        if (newList.length === 0 && !isRefresh) {
          wx.showToast({
            title: '没有更多数据了',
            icon: 'none'
          });
        }
      } else {
        throw new Error(res.data?.msg || '获取点赞列表失败');
      }
    } catch (error) {
      console.error('[ERROR] 获取点赞列表出错:', {
        error: error,
        message: error.message,
        stack: error.stack
      });
      wx.showToast({
        title: error.message || '加载失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  // 处理图片URL
  processImageUrl(url) {
    console.log('[封面原始url]', url)
    return `https://${apiDomain}${JSON.parse(url).url}`
  },

  // 格式化位置信息
  formatLocation(location) {
    if (!location) return '未知地点';
    if (typeof location === 'string') return location;
    if (location.name) return location.name;
    return '坐标位置';
  },

  // 时间格式化方法
  formatTime(dateString) {
    if (!dateString) return '';
    const date = new Date(dateString);
    if (isNaN(date.getTime())) return '';
    
    const now = new Date();
    const diffInSeconds = Math.floor((now - date) / 1000);
    
    if (diffInSeconds < 60) return '刚刚';
    if (diffInSeconds < 3600) return `${Math.floor(diffInSeconds / 60)}分钟前`;
    if (diffInSeconds < 86400) return `${Math.floor(diffInSeconds / 3600)}小时前`;
    if (diffInSeconds < 2592000) return `${Math.floor(diffInSeconds / 86400)}天前`;
    
    const year = date.getFullYear();
    const month = date.getMonth() + 1;
    const day = date.getDate();
    return `${year}-${month < 10 ? '0' + month : month}-${day < 10 ? '0' + day : day}`;
  },

  // 获取星期几
  getWeekday(dateString) {
    if (!dateString) return '';
    const date = new Date(dateString);
    if (isNaN(date.getTime())) return '';
    
    const weekdays = ['周日', '周一', '周二', '周三', '周四', '周五', '周六'];
    return weekdays[date.getDay()];
  },

  // 跳转到详情页
  navigateToDetail(e) {
    const postId = e.currentTarget.dataset.id;
    console.log('跳转到详情页，博文ID:', postId);
    wx.navigateTo({
      url: `/pages/interaction/blog/blog_detail/blog_detail?id=${postId}`
    });
  },

  onSearchInput(e) {
    this.setData({
      searchValue: e.detail
    });
  },

  onSearch() {
    if (!this.data.searchValue.trim()) return;
    this.refreshSearch();
  },

  refreshSearch() {
    this.setData({
      lastCursor: null,
      hasMore: true,
      likesData: []
    }, () => {
      this.fetchLikes(true);
    });
  },

  onPullDownRefresh() {
    this.refreshSearch().then(() => {
      wx.stopPullDownRefresh();
    });
  },

  onReachBottom() {
    if (this.data.hasMore) {
      this.fetchLikes();
    }
  },

  navigateBack() {
    wx.navigateBack();
  }
});