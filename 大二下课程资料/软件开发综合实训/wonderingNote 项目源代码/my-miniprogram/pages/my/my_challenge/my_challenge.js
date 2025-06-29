const { apiDomain } = require("../../../config");
import Toast from '@vant/weapp/toast/toast';

Page({
  data: {
    mainTab: 0, // 0: 参与的挑战, 1: 发起的挑战，2：管理的挑战
    statusBarHeight: 0,
    searchValue: '',
    loading: false,
    joinedChallenges: [],
    createdChallenges: [],
    currentChallenges: [],
    pageSize: 10,
    currentPage: 1,
    hasMore: true,
    lastCursor: "0",
    create_viewed: false
  },

  onLoad() {
    console.log('[DEBUG] 页面初始化开始');
    const systemInfo = wx.getSystemInfoSync()
    this.setData({ 
      statusBarHeight: systemInfo.statusBarHeight 
    })
    console.log('[DEBUG] 系统状态栏高度:', systemInfo.statusBarHeight);

    this.fetchChallenges()

    // 设置主题色
    const savedTheme = wx.getStorageSync('theme') || 0;
    console.log('[DEBUG] 从缓存加载主题:', savedTheme);
    this.setTheme(savedTheme);
  },

  async fetchChallenges() {
    if (this.data.loading) return;
    if (!this.data.hasMore && this.data.currentPage > 1) return;
  
    this.setData({ loading: true });
    const token = wx.getStorageSync('token');
  
    try {
      let url, responseData;
      
      // 如果有搜索关键词，使用搜索接口
      if (this.data.searchValue.trim()) {
        const params = [
          `size=${this.data.pageSize}`,
          `lastCursor=${this.data.lastCursor}`,
          `title=${encodeURIComponent(this.data.searchValue.trim())}`
        ].join('&');
        
        const res = await new Promise((resolve, reject) => {
          wx.request({
            url: `https://${apiDomain}/api/hall/mychallenges/search?${params}`,
            method: 'GET',
            header: { 'Authorization': token },
            success: resolve,
            fail: reject
          });
        });
        
        responseData = res.data.data || {};
        responseData.data = responseData.data || [];
      } 
      // 否则使用原有接口
      else {
        const isJoined = this.data.mainTab === 0;
        const queryParams = [
          `size=${this.data.pageSize}`,
          ...(this.data.lastCursor ? [`lastCursor=${encodeURIComponent(this.data.lastCursor)}`] : [])
        ].join('&');
  
        const res = await new Promise((resolve, reject) => {
          wx.request({
            url: isJoined 
              ? `https://${apiDomain}/api/auth/challenge_info?${queryParams}`
              : `https://${apiDomain}/api/auth/challenge_create?${queryParams}`,
            method: 'GET',
            header: { 'Authorization': token },
            success: resolve,
            fail: reject
          });
        });
        
        responseData = res.data.data || {};
      }
      
      console.log(responseData)
      const challengeList = (responseData.data || []).map(item => this.processChallengeItem(item));
      const targetKey = this.data.mainTab === 0 ? 'joinedChallenges' : 'createdChallenges';
  
      this.setData({
        [targetKey]: this.data.currentPage === 1 ? 
          challengeList : 
          [...this.data[targetKey], ...challengeList],
        currentChallenges: this.data.currentPage === 1 ? 
          challengeList : 
          [...this.data.currentChallenges, ...challengeList],
        lastCursor: responseData.nextCursor || null,
        hasMore: !!responseData.nextCursor,
        currentPage: this.data.currentPage + 1,
        loading: false
      });
  
    } catch (error) {
      wx.showToast({ title: '加载失败', icon: 'none' });
      this.setData({ loading: false });
    }
  },

// 修改后的搜索输入处理
onSearchInput(e) {
  this.setData({ 
    searchValue: e.detail,
    // 清空时自动重置列表
    ...(e.detail.trim() === '' ? {
      currentPage: 1,
      lastCursor: "0",
      hasMore: true,
      currentChallenges: []
    } : {})
  });
  
  // 如果搜索框为空，立即刷新列表
  if (e.detail.trim() === '') {
    this.fetchChallenges();
  }
},
  // 处理单个挑战项数据
  processChallengeItem(item) {
    // 计算剩余天数
    const daysLeft = this.calculateDaysLeft(item.end_time);
    
    // 计算参与人数
    let participantsCount = 0;
    try {
      if (item.participants && typeof item.participants === 'string') {
        // 先尝试直接解析
        try {
          const parsed = JSON.parse(item.participants);
          participantsCount = Array.isArray(parsed) ? parsed.length : 0;
        } catch (e) {
          // 如果直接解析失败，尝试去除外层引号
          const trimmed = item.participants.trim();
          if (trimmed.startsWith('"') && trimmed.endsWith('"')) {
            const unquoted = trimmed.slice(1, -1);
            const parsed = JSON.parse(unquoted);
            participantsCount = Array.isArray(parsed) ? parsed.length : 0;
          } else {
            // 如果还是失败，使用正则表达式匹配
            const idMatches = item.participants.match(/"user_id"/g);
            participantsCount = idMatches ? idMatches.length : 0;
          }
        }
      }
    } catch (e) {
      console.error('解析participants最终失败:', e);
      participantsCount = 0;
    }
  
    // 处理图片URL
    let coverUrl = '';
    try {
      if (item.cover && typeof item.cover === 'string') {
        // 同样处理可能双重引号的情况
        let coverStr = item.cover;
        if (coverStr.startsWith('"') && coverStr.endsWith('"')) {
          coverStr = coverStr.slice(1, -1);
        }
        const coverObj = JSON.parse(coverStr);
        coverUrl = this.processImageUrl(coverObj.url);
      }
    } catch (e) {
      console.error('解析cover失败:', e);
    }
    return {
      ...item,
      daysLeft,  // 添加剩余天数
      participantsCount,  // 添加参与人数
      formattedCover: coverUrl,  // 处理后的封面URL
      formattedEndTime: this.formatTime(item.end_time)  // 格式化结束时间
    };
  },

  // 计算剩余天数
calculateDaysLeft(endTime) {
  if (!endTime) {
    return 0;
  }

  try {
    // 解析为 Date 对象
    const endDate = new Date(endTime);
    const now = new Date();

    // 获取 UTC 00:00 的时间（只保留日期部分）
    const endDateStr = endDate.toISOString().split('T')[0]; // "2025-07-20"
    const nowDateStr = now.toISOString().split('T')[0];     // 当前日期字符串

    const end = new Date(endDateStr + 'T00:00:00.000Z');
    const today = new Date(nowDateStr + 'T00:00:00.000Z');


    // 计算天数差
    const diffMs = end.getTime() - today.getTime();
    const diffDays = Math.floor(diffMs / 86400000); // 1天 = 86400000ms


    return Math.max(0, diffDays); // 不返回负数
  } catch (e) {
    console.error('[ERROR] 天数计算失败', {
      error: e.message,
      stack: e.stack,
      endTime
    });
    return 0;
  }
},

  // 处理图片URL
  processImageUrl(url) {
    let processedUrl = '/static/images/default-challenge-cover.jpg'
    if (url) {
      processedUrl = `https://${apiDomain}${url}`
    }
    return processedUrl
  },

  // 格式化时间
  formatTime(timeString) {
    if (!timeString) return '';
    const date = new Date(timeString);
    return `${date.getFullYear()}-${(date.getMonth()+1).toString().padStart(2, '0')}-${date.getDate().toString().padStart(2, '0')}`;
  },


  switchMainTab(e) {
    const index = parseInt(e.currentTarget.dataset.index)
    console.log('[DEBUG] 切换主标签:', index);
    if (this.data.mainTab === index) {
      console.log('[DEBUG] 标签未变化，跳过');
      return;
    }
    
    this.setData({
      mainTab: index,
      currentPage: 1,
      lastCursor: "0",
      hasMore: true,
      joinedChallenges: index === 0 ? [] : this.data.joinedChallenges,
      createdChallenges: index === 1 ? [] : this.data.createdChallenges,
      currentChallenges: []
    }, () => {
      // 如果是管理的挑战标签，调用fetchChallenges获取更多数据
      if (index === 2) {
        this.fetchManagedChallenges();
      } else {
        this.fetchChallenges();
      }
    });
  },

  onSearchInput(e) {
    const value = e.detail;
    console.log('[DEBUG] 搜索输入:', value);
    this.setData({ searchValue: value })
  },
  // 过滤出有团队ID的挑战（管理的挑战）
  filterManagedChallenges() {
    const managedChallenges = this.data.createdChallenges.filter(item => item.team_id);
    this.setData({
      currentChallenges: managedChallenges,
      loading: false
    });
  },
  // 修改后的搜索方法
  async onSearch() {
    const keyword = this.data.searchValue.trim();
    if (!keyword) {
      wx.showToast({ title: '请输入搜索内容', icon: 'none' });
      return;
    }

    this.setData({
      loading: true,
      currentPage: 1,
      lastCursor: "0",
      currentChallenges: []
    });

    try {
      const token = wx.getStorageSync('token');
      const params = [
        `size=${this.data.pageSize * (this.data.mainTab === 2 ? 10 : 1)}`, // 管理的挑战获取更多数据
        `lastCursor=${this.data.lastCursor}`,
        `title=${encodeURIComponent(keyword)}`
      ].join('&');

      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/hall/mychallenges/search?${params}`,
          method: 'GET',
          header: { 'Authorization': token },
          success: resolve,
          fail: reject
        });
      });
      
      if (res.data.code === '0' || res.data.code === '200') {
        let challengeList = (res.data.data?.data || []).map(item => this.processChallengeItem(item));
        
        // 如果是管理的挑战，筛选有team_id的项
        if (this.data.mainTab === 2) {
          challengeList = challengeList.filter(item => item.team_id);
        }

        this.setData({
          currentChallenges: challengeList,
          lastCursor: res.data.data?.nextCursor || null,
          hasMore: !!res.data.data?.nextCursor,
          loading: false
        });
      } else {
        throw new Error(res.data.msg || '搜索失败');
      }
    } catch (error) {
      wx.showToast({ title: '搜索失败', icon: 'none' });
      this.setData({ loading: false });
    }
  },
  async fetchManagedChallenges() {
    if (this.data.loading) return;
    if (!this.data.hasMore && this.data.currentPage > 1) return;
  
    this.setData({ loading: true });
    const token = wx.getStorageSync('token');
  
    try {
      // 使用发起的挑战接口获取数据
      const queryParams = [
        `size=${this.data.pageSize * 2}`, // 获取更多数据，提高筛选命中率
        ...(this.data.lastCursor ? [`lastCursor=${encodeURIComponent(this.data.lastCursor)}`] : [])
      ].join('&');
  
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/auth/challenge_create?${queryParams}`,
          method: 'GET',
          header: { 'Authorization': token },
          success: resolve,
          fail: reject
        });
      });
      
      const responseData = res.data.data || {};
      const rawChallenges = responseData.data || [];
      
      // 筛选出有team_id的挑战
      const managedChallenges = rawChallenges
        .filter(item => item.team_id)
        .map(item => this.processChallengeItem(item));
      
      // 合并结果
      const allChallenges = [
        ...this.data.currentChallenges,
        ...managedChallenges
      ];
      
      this.setData({
        currentChallenges: allChallenges,
        lastCursor: responseData.nextCursor || null,
        hasMore: !!responseData.nextCursor && allChallenges.length < this.data.pageSize * 3, // 控制加载更多
        currentPage: this.data.currentPage + 1,
        loading: false
      });
      
      // 如果筛选后数量不足，自动加载更多
      if (allChallenges.length < this.data.pageSize && this.data.hasMore) {
        this.fetchManagedChallenges();
      }
      
    } catch (error) {
      wx.showToast({ title: '加载失败', icon: 'none' });
      this.setData({ loading: false });
    }
  },
  enterChallenge(e) {
    const { id, teamid } = e.currentTarget.dataset
    console.log('[选择项的相关信息]', id, teamid)
    const { mainTab } = this.data
    console.log('[DEBUG] 进入挑战详情，ID:', id, '类型:', mainTab === 0 ? '参与' : '发起');
    
    const url = mainTab === 0 
      ? `/pages/interaction/challenge/challenge_submit/challenge_submit?id=${id}`
      : `/pages/my/manage_challenge/manage_challenge?challengeid=${id}&teamid=${teamid}`

    console.log('[DEBUG] 跳转URL:', url);
    wx.navigateTo({ url })
  },

  onPullDownRefresh() {
    console.log('[DEBUG] 下拉刷新触发');
    this.setData({
      currentPage: 1,
      lastCursor: null,
      hasMore: true,
      joinedChallenges: [],
      createdChallenges: [],
      currentChallenges: []
    }, async () => {
      await this.fetchChallenges()
      console.log('[DEBUG] 下拉刷新完成');
      wx.stopPullDownRefresh()
    })
  },

  onReachBottom() {
    console.log('[DEBUG] 滚动到底部');
    if (this.data.hasMore) {
      console.log('[DEBUG] 还有更多数据，开始加载');
      this.fetchChallenges()
    } else {
      console.log('[DEBUG] 已加载全部数据');
    }
  },

  navigateToDetail(e) {
    const challengeId = e.currentTarget.dataset.id;
    console.log('[DEBUG] 跳转到挑战详情，ID:', challengeId);
    
    wx.navigateTo({
      url: `/pages/interaction/challenge/challenge_detail/challenge_detail?id=${challengeId}`
    });
  },

  navigateBack() {
    console.log('[DEBUG] 返回上一页');
    wx.navigateBack()
  },

  setTheme(themeIndex) {
    console.log('[DEBUG] 设置主题:', themeIndex);
    // 主题设置逻辑
  }
})