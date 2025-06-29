const { apiDomain } = require("../../../config");

// pages/my/my_blog/my_blog.js
Page({
  data: {
    searchValue: '',
    active: 0,
    pageSize: 10,
    lastCursor: '0',
    blogs: [],
    loading: false,
    hasMore: true,
    rawBlogs: [] // 保存原始数据用于排序
  },

  onLoad() {
    console.log('[DEBUG] 页面初始化，开始加载博文数据');
    this.loadBlogs();
  },

  goBack() {
    console.log('[DEBUG] 点击返回按钮');
    wx.navigateBack({
      delta: 1,
      fail: (err) => {
        console.warn('[DEBUG] 返回失败，将跳转到首页', err);
        wx.switchTab({
          url: '/pages/index/index'
        })
      }
    })
  },

  async loadBlogs() {
    if (!this.data.hasMore || this.data.loading) return;

    this.setData({ loading: true });
    const token = wx.getStorageSync('token');

    try {
      const params = {
        size: this.data.pageSize,
        lastCursor: this.data.lastCursor
      };

      if (this.data.searchValue.trim()) {
        params.title = this.data.searchValue.trim();
      }

      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/hall/myposts/search`,
          method: 'GET',
          header: { 'Authorization': token },
          data: params,
          success: (res) => {
            if (res.statusCode === 200) {
              resolve(res.data);
            } else {
              reject(new Error(res.data.msg || '请求失败'));
            }
          },
          fail: reject
        });
      });

      if (res.code === '0' || res.code === '200') {
        console.log('[原始响应数据]', res.data)
        const newBlogs = (res.data?.data || []).map(item => { 
          let cover = '/static/images/default-blog-cover.jpg'
          if(item.cover && item.cover != '{}'){
            cover = `https://${apiDomain}${JSON.parse(item.cover).url}`  
          }
          return {
          id: item.id,
          title: item.title,
          content: item.published_account,
          likeCount: item.like_count,
          commentCount: item.comment_count,
          createTime: item.created_time,
          coverUrl: cover,
          isPublic: true,
          canDelete: false
        }});

        this.setData({
          rawBlogs: [...this.data.rawBlogs, ...newBlogs],
          lastCursor: res.data?.nextCursor || null,
          hasMore: !!res.data?.nextCursor
        }, () => this.sortBlogs());
        console.log('[加载后的数据]', this.data.rawBlogs)
      } else {
        throw new Error(res.msg || '加载失败');
      }
    } catch (error) {
      wx.showToast({ title: error.message, icon: 'none' });
    } finally {
      this.setData({ loading: false });
    }
  },
  // 新增：格式化搜索接口返回的数据
formatSearchResultItem(item) {
  return {
    id: item.post_id,
    coverUrl: '/images/default-cover.jpg', // 搜索接口可能不返回封面，使用默认
    title: item.title || '无标题',
    content: item.published_account || '未知作者',
    viewCount: 0, // 搜索接口不返回浏览数
    likeCount: item.like_count || 0,
    commentCount: item.comment_count || 0,
    createTime: item.created_time,
    isPublic: true, // 假设搜索到的都是公开的
    canDelete: false // 搜索到的博文不可删除
  };
},

  // 修改排序方法，将viewCount改为likeCount
  sortBlogs() {
    const { active, rawBlogs } = this.data;
    let sortedBlogs = [...rawBlogs];
    
    if (active === 0) {
      // 按创建时间降序
      sortedBlogs.sort((a, b) => new Date(b.createTime) - new Date(a.createTime));
    } else {
      // 按点赞数降序
      console.log('按照点赞数排序前', sortedBlogs)
      sortedBlogs.sort((a, b) => b.likeCount - a.likeCount);
      console.log('按照点赞数排序后', sortedBlogs)
    }

    this.setData({
      blogs: sortedBlogs
    });
    
    console.log('[DEBUG] 排序完成，当前排序方式:', active === 0 ? '按时间排序' : '按点赞数排序');
  },

   // 新增：跳转到博文详情
   navigateToBlogDetail(e) {
    const postId = e.currentTarget.dataset.id;
    if (!postId) {
      console.error('缺少博文ID参数', e);
      wx.showToast({ title: '数据错误', icon: 'none' });
      return;
    }

    wx.navigateTo({
      url: `/pages/interaction/blog/blog_detail/blog_detail?id=${postId}`,
      fail: (err) => {
        console.error('跳转失败:', err);
        wx.showToast({ title: '跳转失败', icon: 'none' });
      }
    });
  },

  // 新增：删除博文
  deleteBlog(e) {
    const postId = e.currentTarget.dataset.id;
    if (!postId) {
      console.error('缺少博文ID参数', e);
      wx.showToast({ title: '数据错误', icon: 'none' });
      return;
    }

    wx.showModal({
      title: '确认删除',
      content: '确定要删除这篇博文吗？',
      success: async (res) => {
        if (res.confirm) {
          try {
            wx.showLoading({ title: '删除中...', mask: true });
            const token = wx.getStorageSync('token');
            
            const result = await new Promise((resolve, reject) => {
              wx.request({
                url: `https://${apiDomain}/api/posts/${postId}/delete`,
                method: 'DELETE',
                header: {
                  'Authorization': token,
                  'content-type': 'application/json'
                },
                success: (res) => {
                  if (res.statusCode === 200) {
                    resolve(res.data);
                  } else {
                    reject(new Error(res.data.msg || '删除失败'));
                  }
                },
                fail: (err) => {
                  reject(new Error('网络错误，请稍后重试'));
                }
              });
            });

            if (result.data && result.data.success) {
              wx.showToast({ title: '删除成功', icon: 'success' });
              // 从列表中移除已删除的博文
              this.setData({
                blogs: this.data.blogs.filter(blog => blog.id !== postId),
                rawBlogs: this.data.rawBlogs.filter(blog => blog.id !== postId)
              });
            } else {
              throw new Error(result.msg || '删除失败');
            }
          } catch (error) {
            console.error('删除博文失败:', error);
            wx.showToast({ title: error.message || '删除失败', icon: 'none' });
          } finally {
            wx.hideLoading();
          }
        }
      }
    });
  },

  // 修改formatBlogItem方法，添加删除按钮所需数据
  formatBlogItem(item) {
    console.log(item)
    return {
      id: item.id,
      coverUrl: item.cover || '/images/default-cover.jpg',
      title: item.title || '无标题',
      content: item.landmark_name || '未知地点',
      viewCount: item.view_count || 0,
      likeCount: item.like_count || 0,
      createTime: item.create_time,
      isPublic: item.is_public,
      canDelete: true // 标记可删除
    };
  },
  onSearchInput(event) {
    // 修复2：兼容不同事件结构
    const value = typeof event.detail === 'string' 
      ? event.detail 
      : (event.detail.value || '');
  
    this.setData({ 
      searchValue: value,
      ...(value === '' ? {
        blogs: [],
        rawBlogs: [],
        lastCursor: '0',
        hasMore: true
      } : {})
    });
    
    if (value === '') {
      this.loadBlogs();
    }
  },
  onSearch(event) {
    // 修复1：安全获取搜索值
    const keyword = typeof event.detail === 'string' 
      ? event.detail.trim() 
      : (event.detail.value || '').trim();
  
    console.log('[DEBUG] 搜索事件触发，关键词:', keyword);
    
    this.setData({
      searchValue: keyword,
      blogs: [],
      rawBlogs: [],
      lastCursor: '0',
      hasMore: true
    }, () => {
      this.loadBlogs();
    });
  },

  onChange(event) {
    const newActive = event.detail.index;
    console.log('[DEBUG] 标签切换，当前选中:', newActive === 0 ? '最新发布' : '最多点赞');
    this.setData({
      active: newActive
    }, () => {
      this.sortBlogs();
    });
  },

  onPullDownRefresh() {
    console.log('[DEBUG] 下拉刷新触发');
    this.setData({
      blogs: [],
      rawBlogs: [],
      lastCursor: '0',
      hasMore: true
    }, async () => {
      console.log('[DEBUG] 数据重置完成，开始刷新数据');
      await this.loadBlogs();
      wx.stopPullDownRefresh();
      console.log('[DEBUG] 下拉刷新完成');
    });
  },

  onReachBottom() {
    console.log('[DEBUG] 滚动到底部，hasMore:', this.data.hasMore);
    if (this.data.hasMore) {
      this.loadBlogs();
    }
  },

  formatDate(dateString) {
    try {
      const date = new Date(dateString);
      const result = `${date.getFullYear()}-${(date.getMonth() + 1).toString().padStart(2, '0')}-${date.getDate().toString().padStart(2, '0')}`;
      console.log('[DEBUG] 格式化日期:', dateString, '->', result);
      return result;
    } catch (e) {
      console.error('[DEBUG] 日期格式化出错:', e);
      return dateString;
    }
  },

  getWeekday(dateString) {
    try {
      const weekdays = ['周日', '周一', '周二', '周三', '周四', '周五', '周六'];
      const date = new Date(dateString);
      const result = weekdays[date.getDay()];
      console.log('[DEBUG] 获取星期:', dateString, '->', result);
      return result;
    } catch (e) {
      console.error('[DEBUG] 获取星期出错:', e);
      return '';
    }
  }
});