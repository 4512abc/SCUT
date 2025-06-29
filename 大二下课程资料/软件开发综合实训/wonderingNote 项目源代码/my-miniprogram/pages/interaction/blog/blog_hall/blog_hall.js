const { apiDomain } = require("../../../../config");

Page({
  data: {
    blogs: [],
    activeTagFilter: "",
    searchValue: "",
    pageSize: 12,
    hasMore: true,
    loading: false,
    lastCursor: "0",
    sort: 'id',
    searchKeyword: "",
    isSearching: false,
    // 时间搜索相关
    showTimePicker: false,
    startTime: "",
    endTime: "",
    minDate: new Date(2020, 0, 1).getTime(),
    maxDate: new Date().getTime(),
    currentDate: new Date().getTime(),
    formatter: (type, value) => {
      if (type === 'year') return `${value}年`;
      if (type === 'month') return `${value}月`;
      if (type === 'day') return `${value}日`;
      return value;
    },
    selectingStartTime: true,
  },

  onLoad() {
    this.loadBlogs();
  },

  onShow(){
    this.loadBlogs(true);
  },

  onHide(){
    this.setData({
      searchKeyword : '',
      searchValue: ''
    })
  },
  // 获取普通博文列表
  async loadNormalBlogs(refresh = false) {
    if (this.data.loading || (!refresh && !this.data.hasMore)) return;
    
    console.log('[loadNormalBlogs] 开始加载，refresh:', refresh);
    this.setData({ loading: true });

    try {
      const token = wx.getStorageSync('token');
      const params = {
        size: this.data.pageSize,
        sort: this.data.sort,
        lastCursor: refresh ? "0" : this.data.lastCursor
      };

      console.log('[loadNormalBlogs] 请求参数:', params);
      
      const result = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/hall/posts`,
          method: 'GET',
          header: { 
            'Authorization': token,
            'Content-Type': 'application/json'
          },
          data: params,
          success: (res) => {
            console.log('[loadNormalBlogs] 请求成功，响应数据:', res.data);
            if (res.data.code === '200' || res.data.code === '0') {
              const blogData = this.processBlogData(res.data.data.data || []);
              resolve({
                blogData,
                nextCursor: res.data.data.nextCursor || null
              });
            } else {
              console.error('[loadNormalBlogs] 接口返回错误:', res.data.msg);
              reject(new Error(res.data.msg || '请求失败'));
            }
          },
          fail: (err) => {
            console.error('[loadNormalBlogs] 请求失败:', err);
            reject(err);
          }
        });
      });

      this.setData({
        blogs: refresh ? result.blogData : [...this.data.blogs, ...result.blogData],
        lastCursor: result.nextCursor,
        hasMore: result.nextCursor !== null && result.nextCursor !== "0",
        loading: false
      });

    } catch (error) {
      console.error('[loadNormalBlogs] 加载失败:', error);
      wx.showToast({ title: '加载失败', icon: 'none' });
      this.setData({ loading: false });
    }
  },

// 搜索博文
async searchBlogs(refresh = false) {
  if (this.data.loading || (!refresh && !this.data.hasMore)) return;
  
  console.log('[searchBlogs] 开始搜索，refresh:', refresh);
  this.setData({ loading: true });

  try {
    const token = wx.getStorageSync('token');
    const params = {
      size: this.data.pageSize,
      sort: this.data.sort,
      lastCursor: refresh ? "0" : this.data.lastCursor
    };

    // 添加搜索参数
    if (this.data.searchKeyword) params.title = this.data.searchKeyword;
    params.startTime = this.data.startTime? this.data.startTime + " 00:00:00" : null;
    params.endTime = this.data.endTime? this.data.endTime + " 00:00:00": null

    console.log('[searchBlogs] 搜索参数:', params);
    
    const result = await new Promise((resolve, reject) => {
      wx.request({
        url: this.buildUrlWithParams(`https://${apiDomain}/api/hall/posts/search`, params),
        method: 'GET',
        header: { 'Authorization': token },
        success: (res) => {
          console.log('[searchBlogs] 搜索成功，响应数据:', res.data);
          if (res.data.code === '200' || res.data.code === '0') {
            const blogData = this.processBlogData(res.data.data.data || []);
            resolve({
              blogData,
              nextCursor: res.data.data.nextCursor || null
            });
          } else {
            console.error('[searchBlogs] 接口返回错误:', res.data.msg);
            reject(new Error(res.data.msg || '搜索失败'));
          }
        },
        fail: (err) => {
          console.error('[searchBlogs] 请求失败:', err);
          reject(err);
        }
      });
    });

    this.setData({
      blogs: refresh ? result.blogData : [...this.data.blogs, ...result.blogData],
      lastCursor: result.nextCursor,
      hasMore: result.nextCursor !== null && result.nextCursor !== "0",
      loading: false
    });

  } catch (error) {
    console.error('[searchBlogs] 搜索失败:', error);
    wx.showToast({ title: '搜索失败', icon: 'none' });
    this.setData({ loading: false });
  }
},

// 统一的加载方法
async loadBlogs(refresh = false) {
  if (this.data.isSearching) {
    await this.searchBlogs(refresh);
  } else {
    await this.loadNormalBlogs(refresh);
  }
},
// 构建带查询参数的URL
buildUrlWithParams(baseUrl, params) {
  const queryString = Object.keys(params)
    .filter(key => params[key] !== undefined && params[key] !== null && params[key] !== '')
    .map(key => `${encodeURIComponent(key)}=${encodeURIComponent(params[key])}`)
    .join('&');
  
  const fullUrl = queryString ? `${baseUrl}?${queryString}` : baseUrl;
  console.log('[buildUrlWithParams] 构建的URL:', fullUrl);
  return fullUrl;
},

// 处理博文数据
processBlogData(data) {
  console.log('[processBlogData] 原始数据:', data);

  
  const result = data.map(item => {
    // 处理 cover 字段
    let imageUrl = '/static/images/default-blog-cover.jpg'; // 默认图片
    try {
      if (item.content && item.content !== '{}') {
        
        const coverData = JSON.parse(item.content);
        console.log(coverData)
        if (coverData.url) {
          imageUrl = `https://${apiDomain}${coverData.url}`;
        }
        console.log('[封面数据字段]', coverData)
      }else if (item.cover && item.cover !== '{}') {
        
        const coverData = JSON.parse(item.cover);
        console.log(coverData)
        if (coverData.url) {
          imageUrl = `https://${apiDomain}${coverData.url}`;
        }
        console.log('[封面数据字段]', coverData)
      }
    } catch (e) {
      console.error('解析 cover 失败:', item.cover);
    }
    let avatar = "/static/images/default-avatar.jpg"
    if(item.user_avater){
      avatar = `https://${apiDomain}${JSON.parse(item.user_avater).url}`
    }
    return {
      id: item.id,
      cover: imageUrl,  // 使用处理后的图片URL
      title: item.title,
      description: item.landmark_name || '暂无描述',
      view_count: item.view_count || 0,
      likes: item.like_count || 0,
      comments: item.comment_count || 0,
      create_time: item.create_time,
      user: item.user_account || '匿名用户',
      avatar: avatar,
      tags: item.tags || [],
      user_id: item.user_id
    };
  });
  
  console.log('[processBlogData] 处理后的数据:', result);
  return result;
},

  // 标题搜索
  onSearch(e) {
    const keyword = e.detail.trim();
    console.log('搜索关键词:', keyword);
    
    this.setData({ 
      searchKeyword: keyword,
      isSearching: keyword !== "" || this.data.startTime !== "" || this.data.endTime !== "",
      lastCursor: "0",
      hasMore: true,
      blogs: []
    });
    
    // 防抖处理
    if (this.searchTimer) clearTimeout(this.searchTimer);
    this.searchTimer = setTimeout(() => {
      this.loadBlogs(true);
    }, 500);
  },

  // 时间搜索相关方法
  showTimePicker(e) {
    const type = e.currentTarget.dataset.type; // 'start' 或 'end'
    this.setData({
      showTimePicker: true,
      selectingStartTime: type === 'start',
      currentDate: type === 'start' ? 
        (this.data.startTime ? new Date(this.data.startTime).getTime() : this.data.currentDate) :
        (this.data.endTime ? new Date(this.data.endTime).getTime() : this.data.currentDate)
    });
  },

  onTimeConfirm(e) {
    const date = new Date(e.detail);
    const formattedDate = `${date.getFullYear()}-${(date.getMonth()+1).toString().padStart(2,'0')}-${date.getDate().toString().padStart(2,'0')}`;
    
    if (this.data.selectingStartTime) {
      // 选择开始时间后，自动设置结束时间为当前日期
      const now = new Date();
      const endDate = `${now.getFullYear()}-${(now.getMonth()+1).toString().padStart(2,'0')}-${now.getDate().toString().padStart(2,'0')}`;
      
      this.setData({ 
        startTime: formattedDate,
        endTime: endDate, // 自动设置为当前日期
        showTimePicker: false,
        isSearching: true,
        lastCursor: "0",
        hasMore: true,
        blogs: []
      });
      
      // 立即触发搜索
      this.loadBlogs(true);
    } else {
      // 保留原有的结束时间选择逻辑
      if (this.data.startTime && new Date(formattedDate) < new Date(this.data.startTime)) {
        wx.showToast({
          title: '结束时间不能早于开始时间',
          icon: 'none'
        });
        return;
      }
      this.setData({ 
        endTime: formattedDate,
        showTimePicker: false,
        isSearching: true,
        lastCursor: "0",
        hasMore: true,
        blogs: []
      });
      this.loadBlogs(true);
    }
  },

  onTimeCancel() {
    this.setData({ showTimePicker: false });
  },

  clearTimeSearch() {
    this.setData({
      startTime: "",
      endTime: "",
      isSearching: this.data.searchKeyword !== "",
      lastCursor: "0",
      hasMore: true,
      blogs: []
    });
    if (this.data.searchKeyword) {
      this.loadBlogs(true);
    }
  },

  // 清除所有搜索条件
  clearSearch() {
    this.setData({ 
      searchValue: "",
      searchKeyword: "",
      startTime: "",
      endTime: "",
      isSearching: false,
      lastCursor: "0",
      hasMore: true,
      blogs: []
    });
    this.loadBlogs(true);
  },

  // 其他原有方法保持不变...
  

  onTagTap(e) {
    const tag = e.currentTarget.dataset.tag;
    this.setData({ 
      activeTagFilter: this.data.activeTagFilter === tag ? "" : tag,
      lastCursor: "0",
      hasMore: true
    });
    this.loadBlogs(true);
  },

  onReachBottom() {
    this.loadBlogs();
  },

  onPullDownRefresh() {
    console.log('[onPullDownRefresh] 触发下拉刷新');
    
    // 显示导航栏加载动画
    wx.showNavigationBarLoading();
    
    // 重置分页参数
    this.setData({
      lastCursor: "0",
      hasMore: true,
      blogs: []  // 清空当前数据
    });
    
    // 调用原有loadBlogs方法（不修改其内部逻辑）
    this.loadBlogs(true).finally(() => {
      // 无论成功失败都停止动画
      wx.stopPullDownRefresh();
      wx.hideNavigationBarLoading();
      console.log('[onPullDownRefresh] 刷新完成');
    });
  },

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

  navigateToWrite() {
    wx.navigateTo({
      url: '/pages/interaction/blog/blog_create/blog_create'
    });
  },
  navigateToUserDetail(e){
    const userId = e.currentTarget.dataset.userid;
    console.log('[DEBUG] 点击了头像，用户ID:', userId);

    // 示例：跳转用户详情页
    wx.navigateTo({
      url: `/pages/interaction/user_profile/user_profile?id=${userId}`
    });
  }
});