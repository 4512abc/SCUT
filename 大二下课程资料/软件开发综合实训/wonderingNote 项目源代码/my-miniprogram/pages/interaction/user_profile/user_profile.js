// pages/user_profile/user_profile.js
const { apiDomain } = require("../../../config");

Page({
  data: {
    userId: '11',
    userInfo: null,
    posts: [],
    challenges: [],
    loading: false,
    postCursor: '0',
    challengeCursor: '0',
    pageSize: 10,
    hasMorePosts: true,
    hasMoreChallenges: true,
    stats: {
      likes: 0,
      comments: 0,
      days: 0
    },
    currentTime: '',
    activeTab: 'posts',
    tabAnimation: null
  },

  onLoad(options) {
    const userId = options?.id;
    console.log('[DEBUG] 加载用户详情页面，用户ID:', userId);
  
    if (!userId) {
      wx.showToast({
        title: '用户ID不存在',
        icon: 'none'
      });
      return;
    }
  
    this.setData({
      userId,
      currentTime: this.getCurrentTime()
    });
  
    this.fetchUserInfo();
  
    // 设置定时器更新时间
    this.setInterval = setInterval(() => {
      this.setData({ currentTime: this.getCurrentTime() });
    }, 60000);
  },
  

  onUnload() {
    clearInterval(this.setInterval);
  },

  getCurrentTime() {
    const now = new Date();
    const hours = now.getHours().toString().padStart(2, '0');
    const minutes = now.getMinutes().toString().padStart(2, '0');
    return `${hours}:${minutes}`;
  },

  async fetchUserInfo() {
    const token = wx.getStorageSync('token');
    this.setData({ loading: true });

    try {
      const res = await this.request({
        url: `https://${apiDomain}/api/users/${this.data.userId}`,
        method: 'GET',
        header: {
          'Authorization': `Bearer ${token}`
        }
      });

      if (res.statusCode === 200 && res.data.code === '0') {
        const userData = res.data.data;
        let avatar = '/static/images/default-challenge-cover.jpg'
        if(userData.avatar && userData.avatar != '{}'){
          avatar = `https://${apiDomain}${JSON.parse(userData.avatar).url}`
        }
        this.setData({
          userInfo: {
            account: userData.account,
            avatar: avatar,
            bio: userData.bio,
            gender: userData.gender,
            location: userData.location,
            status: userData.status,
            createTime: this.formatTime(userData.create_time),
            updateTime: this.formatTime(userData.update_time),
            birthday: this.formatTime(userData.birthday)
          },
          stats: {
            posts: userData.postCount || 0,
            challenges: userData.ChallengeCount || 0,
            comments: userData.CommentCount || 0,
            participants: userData.participantCount || 0,
            days: this.calculateDays(userData.create_time)
          }
        });
        
        this.fetchPosts();
        this.fetchChallenges();
      } else {
        throw new Error(res.data?.msg || '获取用户信息失败');
      }
    } catch (error) {
      console.error('[ERROR] 获取用户信息出错:', {
        error: error,
        message: error.message,
        stack: error.stack
      });
      wx.showToast({
        title: error.message || '获取用户信息失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  async fetchPosts() {
    if (!this.data.hasMorePosts) {
      console.log('[DEBUG] 取消获取博文 - 正在加载或没有更多数据');
      return;
    }

    const token = wx.getStorageSync('token');
    this.setData({ loading: true });

    try {
      const queryParams = [
        `size=${this.data.pageSize}`,
        ...(this.data.postCursor ? [`lastCursor=${this.data.postCursor}`] : [])
      ].join('&');

      console.log('[DEBUG] 请求博文列表，URL:', `https://${apiDomain}/api/users/${this.data.userId}/posts?${queryParams}`);
      
      const res = await this.request({
        url: `https://${apiDomain}/api/users/${this.data.userId}/posts?${queryParams}`,
        method: 'GET',
        header: {
          'Authorization': `Bearer ${token}`
        }
      });

      console.log('[DEBUG] 博文列表响应:', {
        statusCode: res.statusCode,
        data: res.data
      });

      if (res.statusCode === 200 && res.data.code === '0') {
        const postData = res.data.data?.data || [];
        const nextCursor = res.data.data?.nextCursor;

        console.log('[DEBUG] 获取到的博文数据:', {
          count: postData.length,
          nextCursor: nextCursor
        });
        
        
        this.setData({
          posts: [...this.data.posts, ...postData.map(item => {
            let cover = '/static/images/default-blog-cover.jpg'
            if(item.cover && item.cover != '{}'){
              cover = `https://${apiDomain}${JSON.parse(item.cover).url}`
            }
            return {
            id: item.id,
            image: cover,
            title: item.title || '无标题',
            likes: item.like_count || 0,
            time: this.formatTime(item.create_time, true),
            location: item.landmark_name || '未知地点'
            }
          })],
          postCursor: nextCursor,
          hasMorePosts: !!nextCursor && postData.length >= this.data.pageSize
        });
      } else {
        throw new Error(res.data?.msg || '获取博文失败');
      }
    } catch (error) {
      console.error('[ERROR] 获取博文列表出错:', {
        error: error,
        message: error.message,
        stack: error.stack
      });
      wx.showToast({
        title: error.message || '获取博文失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  async fetchChallenges() {
    if (this.data.loading || !this.data.hasMoreChallenges) {
      console.log('[DEBUG] 取消获取挑战 - 正在加载或没有更多数据');
      return;
    }

    const token = wx.getStorageSync('token');
    this.setData({ loading: true });

    try {
      const queryParams = [
        `size=${this.data.pageSize}`,
        ...(this.data.challengeCursor ? [`lastCursor=${this.data.challengeCursor}`] : [])
      ].join('&');

      console.log('[DEBUG] 请求挑战列表，URL:', `https://${apiDomain}/api/users/${this.data.userId}/challenges?${queryParams}`);
      
      const res = await this.request({
        url: `https://${apiDomain}/api/users/${this.data.userId}/challenges?${queryParams}`,
        method: 'GET',
        header: {
          'Authorization': `Bearer ${token}`
        }
      });

      console.log('[DEBUG] 挑战列表响应:', {
        statusCode: res.statusCode,
        data: res.data
      });

      if (res.statusCode === 200 && res.data.code === '0') {
        const challengeData = res.data.data?.data || [];
        const nextCursor = res.data.data?.nextCursor;

        console.log('[DEBUG] 获取到的挑战数据:', {
          count: challengeData.length,
          nextCursor: nextCursor
        });

        this.setData({
          challenges: [...this.data.challenges, ...challengeData.map(item => {
            let image = '/static/images/default-challenge-cover.jpg'
            if(item.cover && item.cover != '{}'){
              image = `https://${apiDomain}${JSON.parse(item.cover).url}`
            }
            return {
            id: item.id,
            image: image,
            title: item.title || '未命名挑战',
            endTime: this.formatTime(item.end_time, true)
            }
          })],
          challengeCursor: nextCursor,
          hasMoreChallenges: !!nextCursor && challengeData.length >= this.data.pageSize
        });
      } else {
        throw new Error(res.data?.msg || '获取挑战失败');
      }
    } catch (error) {
      console.error('[ERROR] 获取挑战列表出错:', {
        error: error,
        message: error.message,
        stack: error.stack
      });
      wx.showToast({
        title: error.message || '获取挑战失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  request(options) {
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
  },

  formatTime(isoString, showTime = false) {
    if (!isoString) return '';
    const date = new Date(isoString);
    if (isNaN(date.getTime())) return '';
    
    const year = date.getFullYear();
    const month = (date.getMonth()+1).toString().padStart(2, '0');
    const day = date.getDate().toString().padStart(2, '0');
    
    if (showTime) {
      const hours = date.getHours().toString().padStart(2, '0');
      const minutes = date.getMinutes().toString().padStart(2, '0');
      return `${month}-${day} ${hours}:${minutes}`;
    }
    return `${year}-${month}-${day}`;
  },

  calculateDays(createTime) {
    if (!createTime) return 0;
    const createDate = new Date(createTime);
    const now = new Date();
    return Math.floor((now - createDate) / (1000 * 60 * 60 * 24));
  },

  // 新增Tab切换方法
  switchTab(e) {
    const tab = e.currentTarget.dataset.tab;
    if (this.data.activeTab === tab) return;
    
    // 创建动画
    const animation = wx.createAnimation({
      duration: 300,
      timingFunction: 'ease'
    });
    
    if (tab === 'challenges') {
      animation.translateX('0%').step();
    } else {
      animation.translateX('0%').step();
    }
    
    this.setData({
      activeTab: tab,
      tabAnimation: animation.export()
    });
    
    // 首次加载数据
    if (tab === 'posts' && this.data.posts.length === 0) {
      this.fetchPosts();
    } else if (tab === 'challenges' && this.data.challenges.length === 0) {
      this.fetchChallenges();
    }
  },

  // 修改onReachBottom方法
  onReachBottom() {
    if (this.data.activeTab === 'posts' && this.data.hasMorePosts) {
      this.fetchPosts();
    } else if (this.data.activeTab === 'challenges' && this.data.hasMoreChallenges) {
      this.fetchChallenges();
    }
  },
  navigateToDetail(e) {
    const postId = e.currentTarget.dataset.id;
    console.log('[DEBUG] 跳转到博文详情，ID:', postId);
    if (!postId) {
      wx.showToast({
        title: '无法查看该内容',
        icon: 'none'
      });
      return;
    }
    wx.navigateTo({
      url: `/pages/interaction/blog/blog_detail/blog_detail?id=${postId}`
    });
  },

  navigateToChallenge(e) {
    const challengeId = e.currentTarget.dataset.id;
    console.log('[DEBUG] 跳转到挑战详情，ID:', challengeId);
    if (!challengeId) {
      wx.showToast({
        title: '无法查看该挑战',
        icon: 'none'
      });
      return;
    }
    wx.navigateTo({
      url: `/pages/interaction/challenge/challenge_detail/challenge_detail?id=${challengeId}`
    });
  },

  navigateBack() {
    wx.navigateBack();
  }
});